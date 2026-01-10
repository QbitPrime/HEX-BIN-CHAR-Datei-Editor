# HEX / BIN / ASCII DATEI-EDITOR – PHASE 2
---------------

Dieses Projekt ist im Rahmen des Kurses
„Programmierung mit C/C++“ entstanden.

In Phase 2 wird eine erste lauffähige Version eines einfachen
Datei-Editors umgesetzt.


## FUNKTIONALITÄT (PHASE 2)
-----------------------

- Laden einer Datei im Binärmodus
- Tabellarische Anzeige des Datei-Inhalts:
  * Index / Adresse
  * Hexadezimaldarstellung
  * Binärdarstellung
  * ASCII-Zeichen (falls darstellbar)
- Bearbeiten einzelner Bytes über die Kommandozeile
- Eingabe neuer Werte in:
  * Hexadezimalform
  * Binärform
  * ASCII-Form
- Anzeige des alten und neuen Wertes nach einer Bearbeitung
- Speichern der Änderungen in einer neuen Datei

Die grafische Benutzeroberfläche wird in Phase 3 umgesetzt.


## PROJEKTSTRUKTUR
---------------

src/
  - main.cpp
  - FileManager.cpp
  - Converter.cpp

include/
  - FileManager.h
  - Converter.h

Weitere Dateien:
  - README.txt
  - .gitignore
  - test.bin (Beispieldatei)


## KOMPILIERUNG
------------

Voraussetzungen:
- C++-Compiler (z. B. g++ / MinGW unter Windows)
- Kompilierung im Projektordner

Kompilierbefehl:

g++ -Iinclude src/main.cpp src/FileManager.cpp src/Converter.cpp -o hexeditor


## AUSFÜHRUNG
----------

1) Datei anzeigen

Befehl:
  hexeditor test.bin

Beschreibung:
  Die Datei wird vollständig geladen und byteweise in
  Hex-, Binär- und ASCII-Darstellung ausgegeben.

Hinweis:
  Die Datei „test.bin“ dient als Beispieldatei.
  Es können auch beliebige andere Dateien als Eingabe
  übergeben werden.


2) Byte bearbeiten und speichern

Befehl:
  hexeditor <input> <output> <index> <hex|bin|ascii> <value>

Beispiele:
  hexeditor test.bin test_modified.bin 0 hex 58
  hexeditor test.bin test_modified.bin 1 bin 01100001
  hexeditor test.bin test_modified.bin 2 ascii Z

Ergebnis:
  Nach der Bearbeitung wird das geänderte Byte vor und
  nach der Änderung angezeigt. Anschließend wird die
  modifizierte Datei gespeichert.


ENTWICKLUNGSSTAND
-----------------

Diese Version entspricht Phase 2 (Beginning).

Der Fokus liegt auf der Kernlogik:
- Dateiverwaltung
- Umrechnungslogik
- Benutzerinteraktion über die Kommandozeile

Eine grafische Benutzeroberfläche sowie erweiterte
Bearbeitungsfunktionen folgen in Phase 3.


HINWEIS ZUR NUTZUNG VON KI-WERKZEUGEN
------------------------------------

KI-basierte Werkzeuge wurden unterstützend bei der
sprachlichen Strukturierung der Dokumentation sowie
bei der Fehlersuche und Analyse von Compiler- und
Laufzeitfehlern eingesetzt.

Die Konzeption der Softwarearchitektur, die Implementierung
des Codes sowie die Tests der Anwendung erfolgten
eigenständig.
