// src/main.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>

#include "FileManager.h"
#include "Converter.h"

// Ausgabe einer Tabellenzeile für ein Byte
static void printByteLine(std::size_t index, std::uint8_t value) {
    std::cout << std::setw(3) << index << "  "
              << "0x" << std::setw(6) << std::setfill('0') << std::hex << index
              << std::dec << std::setfill(' ') << "  "
              << Converter::toHex(value) << "   "
              << Converter::toBinary(value) << "   "
              << Converter::toAscii(value) << "\n";
}

static void printUsage() {
    std::cout
        << "Usage:\n"
        << "  hexeditor <input> <output> <index> <valueHex>\n"
        << "Example:\n"
        << "  hexeditor test.bin test_modified.bin 0 58\n\n"
        << "Notes:\n"
        << "  <index>     = Byte-Index (decimal)\n"
        << "  <valueHex>  = new byte value in hex (00..FF)\n\n"
        << "If no arguments are provided, defaults are used.\n";
}

int main(int argc, char* argv[]) {
    // Defaults (Phase 2: simple + deterministic)
    std::string inputPath  = "test.bin";
    std::string outputPath = "test_modified.bin";
    std::size_t editIndex  = 0;
    std::uint8_t newValue  = static_cast<std::uint8_t>('X'); // 0x58

    // Optional CLI arguments: input output index valueHex
    if (argc == 5) {
        try {
            inputPath  = argv[1];
            outputPath = argv[2];

            editIndex = static_cast<std::size_t>(std::stoull(argv[3], nullptr, 10));

            // valueHex: parse as hex (base 16). Accepts e.g. "58" or "0x58".
            unsigned long v = std::stoul(argv[4], nullptr, 16);
            if (v > 0xFFUL) {
                std::cout << "Error: valueHex must be in range 00..FF\n";
                printUsage();
                return 1;
            }
            newValue = static_cast<std::uint8_t>(v);
        } catch (const std::exception& e) {
            std::cout << "Error parsing arguments: " << e.what() << "\n";
            printUsage();
            return 1;
        }
    } else if (argc != 1) {
        // Any other arg count is considered invalid
        printUsage();
        return 1;
    }

    FileManager fm;

    if (!fm.loadFile(inputPath)) {
        std::cout << "Datei konnte nicht geladen werden: " << inputPath << "\n";
        return 1;
    }

    const auto& data = fm.getData();
    std::cout << "Datei geladen. Anzahl Bytes: " << data.size() << "\n\n";

    // Tabelle (nur erste 16 Bytes anzeigen)
    std::cout << "Idx  Addr      Hex  Binary      ASCII\n";
    std::cout << "-----------------------------------------\n";

    const std::size_t count = (data.size() < 16) ? data.size() : 16;
    for (std::size_t i = 0; i < count; ++i) {
        printByteLine(i, data[i]);
    }

    // Bearbeitung demonstrieren
    std::cout << "\nBearbeitung:\n";
    if (editIndex >= data.size()) {
        std::cout << "Fehler: Index außerhalb des Bereichs. Index=" << editIndex
                  << ", Bytes=" << data.size() << "\n";
        return 1;
    }

    std::cout << "Alt: ";
    printByteLine(editIndex, fm.getData()[editIndex]);

    if (!fm.setByte(editIndex, newValue)) {
        std::cout << "Fehler: setByte fehlgeschlagen.\n";
        return 1;
    }

    std::cout << "Neu: ";
    printByteLine(editIndex, fm.getData()[editIndex]);

    // Speichern (in neue Datei)
    if (!fm.saveFile(outputPath)) {
        std::cout << "Fehler beim Speichern: " << outputPath << "\n";
        return 1;
    }

    std::cout << "\nGespeichert als: " << outputPath << "\n";
    return 0;
}
