// src/main.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>
#include <cstddef> // für std::size_t

// Eigene Module aus dem Projekt
#include "FileManager.h"
#include "Converter.h"

// Gibt eine formatierte Zeile für ein einzelnes Byte aus.
// Darstellung wie in einem einfachen Hex-Editor:
// - Index / Adresse
// - Hexadezimalwert
// - Binärdarstellung
// - ASCII-Zeichen
static void printByteLine(std::size_t index, std::uint8_t value) {
    std::cout << std::setw(4) << index << "  "
              << "0x" << std::setw(6) << std::setfill('0')
              << std::hex << index
              << std::dec << std::setfill(' ') << "  "
              << Converter::toHex(value) << "   "
              << Converter::toBinary(value) << "   "
              << Converter::toAscii(value) << "\n";
}

int main() {
    // Instanz der Dateiverwaltung erzeugen
    FileManager fm;

    // Pfad zur zu ladenden Datei
    const std::string inputPath = "test.bin";

    // Versuch, die Datei zu laden
    if (!fm.loadFile(inputPath)) {
        std::cout << "Fehler: Datei konnte nicht geladen werden.\n";
        return 1;
    }

    // Zugriff auf die geladenen Binärdaten
    const auto& data = fm.getData();

    std::cout << "Datei geladen. Anzahl Bytes: " << data.size() << "\n\n";

    // Tabellenkopf für die Ausgabe
    std::cout << "Idx   Addr      Hex  Binary      ASCII\n";
    std::cout << "-------------------------------------------\n";

    // Ausgabe aller Bytes der Datei
    for (std::size_t i = 0; i < data.size(); ++i) {
        printByteLine(i, data[i]);
    }

    return 0;
}
