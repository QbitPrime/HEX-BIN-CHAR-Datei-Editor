# HEX / BIN / ASCII DATEI-EDITOR – PHASE 2
=======================================

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

HexEditor/
|
|-- src/
|   |-- main.cpp
|   |-- FileManager.cpp
|   |-- Converter.cpp
|
|-- include/
|   |-- FileManager.h
|   |-- Converter.h
|
|-- README.txt
|-- .gitignore
|-- test.bin   (Beispieldatei für Tests)


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

hexeditor test.bin

Die Datei wird vollständig geladen und byteweise in
Hex-, Binär- und ASCII-Darstellung ausgegeben.

Hinweis:
Die Datei „test.bin“ dient als Beispieldatei.
Es können auch beliebige andere Dateien als Eingabe übergeben werden.


2) Byte bearbeiten und speichern

hexeditor <input> <output> <index> <hex|bin|ascii> <value>

Beispiele:

hexeditor test.bin test_modified.bin 0 hex 58
hexeditor test.bin test_modified.bin 1 bin 01100001
hexeditor test.bin test_modified.bin 2 ascii Z

Nach der Bearbeitung wird das geänderte Byte vor und nach
der Änderung angezeigt. Anschließend wird die modifizierte
Datei gespeichert.


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

Zur Unterstützung bei der sprachlichen Strukturierung der
Dokumentation wurden KI-basierte Werkzeuge eingesetzt.
Die Implementierung und Tests der Software erfolgten eigenständig.
