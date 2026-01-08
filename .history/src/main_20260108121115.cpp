// src/main.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>

// Eigene Module aus dem Projekt
#include "FileManager.h"
#include "Converter.h"

//Gibt eine formatierte Zeile für ein einzelnes Byte aus. Die Darstellung orientiert sich an einem klassischen Hex-Editor:
// Index / Adresse
// Hexadezimalwert
// Binärdarstellung
// ASCII-Zeichen 
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
    // (für Phase 2 fest im Code definiert)
    const std::string inputPath = "test.bin";

    // Versuch, die Datei zu laden
    if (!fm.loadFile(inputPath)) {
        std::cout << "Fehler: Datei konnte nicht geladen werden.\n";
        return 1;
    }

    // Zugriff auf die geladenen Binärdaten
    const auto& data = fm.getData();

    std::cout << "Datei geladen. Anzahl Bytes: "
              << data.size() << "\n\n";

    // Tabellenkopf für die Ausgabe
    std::cout << "Idx   Addr      Hex  Binary      ASCII\n";
    std::cout << "-------------------------------------------\n";

    /*
     * Ausgabe aller Bytes der Datei.
     * Für Phase 2 erfolgt die Darstellung vollständig in der Konsole,
     * um die Umrechnungslogik zu testen.
     * Eine grafische Darstellung folgt erst in Phase 3.
     */
    for (std::size_t i = 0; i < data.size(); ++i) {
        printByteLine(i, data[i]);
    }

    return 0;
}
