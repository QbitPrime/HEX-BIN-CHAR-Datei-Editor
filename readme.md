# Hex/Bin/ASCII Datei-Editor 

Dieses Projekt ist im Rahmen des Kurses **„Programmierung mit C/C++“** entstanden.
In Phase 2 wird eine erste lauffähige Version eines einfachen Datei-Editors umgesetzt.

Die Anwendung ermöglicht es, den Inhalt einer Binärdatei byteweise darzustellen und
einzelne Bytes gezielt zu verändern.


## Funktionsumfang (Phase 2)

- Laden einer Datei im Binärmodus
- Tabellarische Anzeige des Datei-Inhalts:
  - Index / Adresse
  - Hexadezimaldarstellung
  - Binärdarstellung
  - ASCII-Zeichen (falls darstellbar)
- Bearbeiten einzelner Bytes über die Kommandozeile
- Eingabe neuer Werte in:
  - Hexadezimalform
  - Binärform
  - ASCII-Form
- Speichern der Änderungen in einer neuen Datei

Die grafische Benutzeroberfläche wird in Phase 3 umgesetzt.

---

## Projektstruktur

HexEditor/
│
├── src/
│ ├── main.cpp
│ ├── FileManager.cpp
│ └── Converter.cpp
│
├── include/
│ ├── FileManager.h
│ └── Converter.h
│
├── README.md
└── test.bin

## Kompilierung

Voraussetzungen:
- C++-Compiler (z. B. g++ / MinGW unter Windows)
- Kompilierung im Projektordner

```powershell
g++ -Iinclude src/main.cpp src/FileManager.cpp src/Converter.cpp -o hexeditor

## Ausführung
 
Datei Anzeigen:
```powershell
.\hexeditor test.bin

Byte bearbeiten und speichern:
```powershell
.\hexeditor <input> <output> <index> <hex|bin|ascii> <value>

Beispiele:
```powershell
.\hexeditor test.bin test_modified.bin 0 hex 58
.\hexeditor test.bin test_modified.bin 1 bin 01100001
.\hexeditor test.bin test_modified.bin 2 ascii Z

