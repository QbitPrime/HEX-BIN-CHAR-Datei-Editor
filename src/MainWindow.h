#pragma once

/*
------------------------------------------------------------
Header-Datei für das Hauptfenster des Hex-Editors.

Die Klasse MainWindow stellt die grafische Benutzeroberfläche
der Anwendung bereit und verbindet die GUI mit der
Programmlogik (FileManager + Converter).
------------------------------------------------------------
*/

#include <QMainWindow>
#include <QString>
#include <cstdint>

#include "filemanager.h"

/*
Forward Declarations der Qt Widgets.
Die tatsächlichen Includes erfolgen in der .cpp Datei.
*/
class QPlainTextEdit;
class QLineEdit;
class QLabel;
class QComboBox;
class QPushButton;

/*
------------------------------------------------------------
Klasse MainWindow

Verantwortlichkeiten:
- Aufbau der grafischen Benutzeroberfläche
- Öffnen und Speichern von Dateien
- Bearbeiten einzelner Bytes
- Darstellung der Hex / Bin / ASCII Werte
------------------------------------------------------------
*/
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:


    // Öffnet eine Datei über einen Dateidialog und lädt sie mit Hilfe des FileManager.
    void openFile();

    //Speichert die aktuell geladene Datei.
    void saveFile();

    //Speichert die Datei unter einem neuen Namen.
    void saveFileAs();
   
    // Wendet eine Byte-Änderung an.
    void applyChange();
    
    //Zeigt eine kurze Hilfe zur Benutzung der Anwendung an.
    void showHelp();

private:

    /*
    Baut die komplette Hex-Editor Ansicht neu auf.
    Dabei wird die Datei zeilenweise dargestellt:
    Adresse | Hex Werte | ASCII Darstellung
    */
    void rebuildView();

    /*
    Wandelt eine Benutzereingabe in ein Byte um.
    Unterstützte Eingabeformate:
    - hex
    - bin
    - ascii
    */
    bool parseByteValueQt(
        const QString& mode,
        const QString& valueStr,
        std::uint8_t& outValue
    ) const;

    /*
    Aktualisiert die Detailanzeige eines Bytes
    (Hex, Binär, ASCII).
    */
    void updateDetails(std::size_t index);

    /*
    Hilfsfunktion für Speichern.
    Wenn noch kein Dateipfad existiert,
    wird ein "Speichern unter" Dialog geöffnet.
    */
    bool ensurePathForSave();


    /*
    ------------------------------------------------------------
    Daten der Anwendung
    ------------------------------------------------------------
    */

    // Aktueller Dateipfad
    QString currentPath_;

    // FileManager übernimmt Laden/Speichern der Binärdaten
    FileManager fm_;


    /*
    ------------------------------------------------------------
    GUI Elemente
    ------------------------------------------------------------
    */

    // Hauptanzeige des Hex Editors
    QPlainTextEdit* view_ = nullptr;

    // Eingabefeld für den Byte Index
    QLineEdit* indexEdit_ = nullptr;

    // Auswahl des Eingabemodus (hex / bin / ascii)
    QComboBox* modeBox_ = nullptr;

    // Eingabefeld für neuen Wert
    QLineEdit* valueEdit_ = nullptr;

    // Button zum Anwenden der Änderung
    QPushButton* applyBtn_ = nullptr;

    // Anzeige der Detailinformationen eines Bytes
    QLabel* detailsLabel_ = nullptr;
};