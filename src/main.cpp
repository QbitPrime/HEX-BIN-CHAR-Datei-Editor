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
    /*
    QApplication ist das zentrale Objekt jeder Qt GUI Anwendung.

    Es verwaltet:
    - das Event-System
    - Fenster
    - Benutzerinteraktionen (Maus, Tastatur)
    */
    QApplication app(argc, argv);

    /*
    Erzeugt das Hauptfenster der Anwendung.

    Die Klasse MainWindow baut dabei die komplette GUI auf
    und stellt alle Funktionen des Hex-Editors bereit.
    */
    MainWindow window;

    /*
    Zeigt das Hauptfenster auf dem Bildschirm an.
    */
    window.show();

    /*
    Startet die Qt Event-Schleife.

    Diese Schleife verarbeitet:
    - Benutzerinteraktionen
    - GUI Updates
    - Events der Anwendung

    Die Funktion blockiert, bis das Fenster geschlossen wird.
    */
    return app.exec();
}