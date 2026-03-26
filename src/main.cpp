/*
------------------------------------------------------------
Haupteinstiegspunkt der Anwendung.

Diese Datei startet die Qt Anwendung und erzeugt
das Hauptfenster des Hex-Editors.
------------------------------------------------------------
*/

#include <QApplication>
#include "MainWindow.h"

/*
------------------------------------------------------------
main()

Parameter:
argc / argv enthalten mögliche Startparameter der Anwendung.

Ablauf:
1. Qt-Anwendung initialisieren
2. Hauptfenster erzeugen
3. Fenster anzeigen
4. Event-Loop starten
------------------------------------------------------------
*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}