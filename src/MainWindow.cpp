#include "MainWindow.h"

// Qt Widgets für GUI Elemente
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QMenuBar>
#include <QStatusBar>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

// Standardbibliothek für Formatierung der Hex-Anzeige
#include <sstream>
#include <iomanip>

#include "converter.h"

/*
------------------------------------------------------------
Hilfsfunktion: formatiert eine Speicheradresse als Hexwert
Beispiel: 00000010
Diese Funktion wird beim Aufbau der Hex-Editor Ansicht benutzt.
------------------------------------------------------------
*/
static std::string hexAddr(std::size_t v, int width = 8) {
    std::ostringstream oss;
    oss << std::uppercase << std::hex
        << std::setw(width) << std::setfill('0') << v;
    return oss.str();
}

/*
------------------------------------------------------------
Konstruktor des Hauptfensters

Hier wird die komplette grafische Oberfläche aufgebaut:
- Hex Anzeige
- Eingabefelder
- Menü
- Layout
------------------------------------------------------------
*/
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {

    // Textfeld für die Hex-Editor Anzeige
    view_ = new QPlainTextEdit(this);
    view_->setReadOnly(true); // Anzeige soll nicht direkt editierbar sein
    view_->setLineWrapMode(QPlainTextEdit::NoWrap);

    // Eingabe für den Byte Index
    indexEdit_ = new QLineEdit(this);
    indexEdit_->setPlaceholderText("Index (dezimal)");

    // Auswahl des Eingabemodus (hex/bin/ascii)
    modeBox_ = new QComboBox(this);
    modeBox_->addItems({"hex", "bin", "ascii"});

    // Eingabefeld für neuen Wert
    valueEdit_ = new QLineEdit(this);
    valueEdit_->setPlaceholderText("Wert (FF / 01100001 / Z)");

    // Button zum Anwenden der Änderung
    applyBtn_ = new QPushButton("Ändern", this);

    // Anzeige der Details eines Bytes
    detailsLabel_ = new QLabel("Details: -", this);

    // Zentrales Widget + Layouts
    auto* central = new QWidget(this);
    auto* vbox = new QVBoxLayout(central);

    // Hex-Anzeige
    vbox->addWidget(view_);

    // Eingabezeile
    auto* hbox = new QHBoxLayout();
    hbox->addWidget(new QLabel("Index:", this));
    hbox->addWidget(indexEdit_);
    hbox->addWidget(new QLabel("Modus:", this));
    hbox->addWidget(modeBox_);
    hbox->addWidget(new QLabel("Wert:", this));
    hbox->addWidget(valueEdit_);
    hbox->addWidget(applyBtn_);

    vbox->addLayout(hbox);
    vbox->addWidget(detailsLabel_);

    setCentralWidget(central);

    /*
    Menüstruktur der Anwendung
    Datei → Öffnen / Speichern / Speichern unter
    */
    auto* fileMenu = menuBar()->addMenu("&Datei");

    fileMenu->addAction("&Öffnen...", this, &MainWindow::openFile);
    fileMenu->addAction("&Speichern", this, &MainWindow::saveFile);
    fileMenu->addAction("Speichern &unter...", this, &MainWindow::saveFileAs);
    
    /*
    Hilfe Menü mit kurzer Anleitung zur Benutzung der Anwendung
    */
    auto* helpMenu = menuBar()->addMenu("&Hilfe");
    helpMenu->addAction("&Benutzung", this, &MainWindow::showHelp);

    // Verbindung des Buttons mit der Änderungsfunktion
    connect(applyBtn_, &QPushButton::clicked,
            this, &MainWindow::applyChange);

    statusBar()->showMessage("Bereit");

    setWindowTitle("Hex Editor");
    resize(1050, 650);
}

/*
------------------------------------------------------------
Datei öffnen

- Öffnet einen Dateidialog
- lädt die Datei über FileManager
- baut anschließend die Hex-Ansicht neu auf
------------------------------------------------------------
*/
void MainWindow::openFile() {

    const QString path = QFileDialog::getOpenFileName(this, "Datei öffnen");

    if (path.isEmpty())
        return;

    if (!fm_.loadFile(path.toStdString())) {
        statusBar()->showMessage("Konnte Datei nicht laden.");
        return;
    }

    currentPath_ = path;

    rebuildView();

    statusBar()->showMessage(
        QString("Geladen: %1 (%2 Bytes)")
        .arg(currentPath_)
        .arg(static_cast<qulonglong>(fm_.getData().size()))
    );
}

/*
------------------------------------------------------------
Hilfsfunktion für Speichern

Falls noch kein Dateipfad existiert,
wird automatisch ein "Speichern unter" Dialog geöffnet.
------------------------------------------------------------
*/
bool MainWindow::ensurePathForSave() {

    if (!currentPath_.isEmpty())
        return true;

    const QString path =
        QFileDialog::getSaveFileName(this, "Speichern unter...");

    if (path.isEmpty())
        return false;

    currentPath_ = path;
    return true;
}

/*
------------------------------------------------------------
Datei speichern (aktuellen Pfad verwenden)
------------------------------------------------------------
*/
void MainWindow::saveFile() {

    if (fm_.getData().empty()) {
        statusBar()->showMessage("Keine Datei geladen.");
        return;
    }

    if (!ensurePathForSave()) {
        statusBar()->showMessage("Speichern abgebrochen.");
        return;
    }

    if (!fm_.saveFile(currentPath_.toStdString())) {
        statusBar()->showMessage("Speichern fehlgeschlagen.");
        return;
    }

    statusBar()->showMessage("Gespeichert.");
}

/*
------------------------------------------------------------
Speichern unter

Der Benutzer kann einen neuen Dateinamen wählen.
------------------------------------------------------------
*/
void MainWindow::saveFileAs() {

    if (fm_.getData().empty()) {
        statusBar()->showMessage("Keine Datei geladen.");
        return;
    }

    const QString path =
        QFileDialog::getSaveFileName(this, "Speichern unter...");

    if (path.isEmpty()) {
        statusBar()->showMessage("Speichern abgebrochen.");
        return;
    }

    currentPath_ = path;

    if (!fm_.saveFile(currentPath_.toStdString())) {
        statusBar()->showMessage("Speichern fehlgeschlagen.");
        return;
    }

    statusBar()->showMessage(
        QString("Gespeichert als: %1").arg(currentPath_)
    );

    rebuildView();
}

/*
------------------------------------------------------------
Zeigt eine kurze Hilfe zur Benutzung des Programms an.

Die Hilfe erklärt dem Benutzer die grundlegenden Schritte:
Datei öffnen, Index eingeben, Modus wählen, Wert ändern
und Datei speichern.
------------------------------------------------------------
*/
void MainWindow::showHelp() {

    QMessageBox::information(
        this,
        "Benutzung",
        "Benutzung des Hex Editors:\n\n"

        "1. Öffnen Sie eine Binärdatei über Datei -> Öffnen.\n"
        "2. Der Inhalt der Datei wird im Editor angezeigt.\n\n"

        "INDEX:\n"
        "Der Index gibt die Position eines Bytes in der Datei an.\n"
        "Das erste Byte hat den Index 0.\n"
        "Das zweite Byte hat den Index 1 usw.\n"
        "Der Index wird unten links im Eingabefeld eingegeben.\n\n"

        "Beispiel:\n"
        "Index 0  -> erstes Byte der Datei\n"
        "Index 10 -> elftes Byte der Datei\n\n"

        "BYTE ÄNDERN:\n"
        "3. Geben Sie den gewünschten Index ein.\n"
        "4. Wählen Sie den Modus: hex, bin oder ascii.\n"
        "5. Geben Sie einen neuen Wert ein.\n"
        "6. Klicken Sie auf 'Ändern', um das Byte zu bearbeiten.\n\n"

        "SPEICHERN:\n"
        "7. Speichern Sie die Datei über Datei -> Speichern\n"
        "   oder Datei -> Speichern unter.\n\n"

        "Beispiele für Werte:\n"
        "hex   : FF\n"
        "bin   : 01000001\n"
        "ascii : Z"
    );
}

/*
------------------------------------------------------------
Interpretation der Eingabe des Benutzers

Der Wert kann eingegeben werden als:
- hex
- bin
- ascii

Die Funktion wandelt den Wert in ein Byte um.
------------------------------------------------------------
*/
bool MainWindow::parseByteValueQt(
        const QString& mode,
        const QString& valueStr,
        std::uint8_t& outValue) const {

    const QString m = mode.trimmed().toLower();
    const QString v = valueStr.trimmed();

    if (m == "hex") {

        QString t = v;

        if (t.startsWith("0x", Qt::CaseInsensitive))
            t = t.mid(2);

        bool ok = false;
        int val = t.toInt(&ok, 16);

        if (!ok || val < 0 || val > 255)
            return false;

        outValue = static_cast<std::uint8_t>(val);
        return true;
    }

    if (m == "bin") {

        if (v.size() != 8)
            return false;

        std::uint8_t val = 0;

        for (QChar c : v) {

            if (c != '0' && c != '1')
                return false;

            val = static_cast<std::uint8_t>(
                (val << 1) | (c.unicode() - '0')
            );
        }

        outValue = val;
        return true;
    }

    if (m == "ascii") {

        if (v.size() != 1)
            return false;

        outValue = static_cast<std::uint8_t>(
            v[0].toLatin1()
        );

        return true;
    }

    return false;
}

/*
------------------------------------------------------------
Ändert ein Byte an der angegebenen Position

1. Index prüfen
2. Eingabewert interpretieren
3. Byte im FileManager ändern
4. Anzeige aktualisieren
------------------------------------------------------------
*/
void MainWindow::applyChange() {

    const auto& data = fm_.getData();

    if (data.empty()) {
        statusBar()->showMessage("Keine Datei geladen.");
        return;
    }

    bool ok = false;

    std::size_t idx =
        indexEdit_->text().trimmed().toULongLong(&ok, 10);

    if (!ok || idx >= data.size()) {
        statusBar()->showMessage("Ungültiger Index.");
        return;
    }

    std::uint8_t newVal = 0;

    if (!parseByteValueQt(
            modeBox_->currentText(),
            valueEdit_->text(),
            newVal)) {

        statusBar()->showMessage(
            "Ungültiger Wert für Modus."
        );
        return;
    }

    fm_.setByte(idx, newVal);

    rebuildView();
    updateDetails(idx);

    statusBar()->showMessage("Byte geändert.");
}

/*
------------------------------------------------------------
Zeigt zusätzliche Informationen über ein Byte an
(Hex, Binär und ASCII Darstellung)
------------------------------------------------------------
*/
void MainWindow::updateDetails(std::size_t index) {

    const auto& data = fm_.getData();

    if (index >= data.size()) {
        detailsLabel_->setText("Details: -");
        return;
    }

    const std::uint8_t b = data[index];

    detailsLabel_->setText(
        QString("Details @%1 | Hex=%2 | Bin=%3 | ASCII=%4")
        .arg(static_cast<qulonglong>(index))
        .arg(QString::fromStdString(Converter::toHex(b)))
        .arg(QString::fromStdString(Converter::toBinary(b)))
        .arg(QChar::fromLatin1(Converter::toAscii(b)))
    );
}

/*
------------------------------------------------------------
Baut die komplette Hex-Editor Anzeige neu auf

Darstellung pro Zeile:
Adresse | 16 Hex Werte | ASCII Darstellung
------------------------------------------------------------
*/
void MainWindow::rebuildView() {

    const auto& data = fm_.getData();

    std::ostringstream oss;

    oss << "File: "
        << (currentPath_.isEmpty()
            ? "<kein pfad>"
            : currentPath_.toStdString())
        << " | Size: "
        << data.size()
        << " Bytes\n\n";

    for (std::size_t base = 0;
         base < data.size();
         base += 16) {

        oss << hexAddr(base) << "  ";

        for (int i = 0; i < 16; ++i) {

            std::size_t off =
                base + static_cast<std::size_t>(i);

            if (off < data.size())
                oss << Converter::toHex(data[off]) << " ";
            else
                oss << "   ";
        }

        oss << " ";

        for (int i = 0; i < 16; ++i) {

            std::size_t off =
                base + static_cast<std::size_t>(i);

            if (off < data.size())
                oss << Converter::toAscii(data[off]);
            else
                oss << " ";
        }

        oss << "\n";
    }

    view_->setPlainText(
        QString::fromStdString(oss.str())
    );
}