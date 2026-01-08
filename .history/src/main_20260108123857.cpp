// src/main.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>
#include <cstddef>

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

// Wandelt einen Eingabewert (hex/bin/ascii) in ein Byte um
static bool parseByteValue(const std::string& mode,
                           const std::string& valueStr,
                           std::uint8_t& outValue) {
    if (mode == "hex") {
        try {
            unsigned int v = static_cast<unsigned int>(
                std::stoul(valueStr, nullptr, 16));
            if (v > 255) return false;
            outValue = static_cast<std::uint8_t>(v);
            return true;
        } catch (...) {
            return false;
        }
    }

    if (mode == "bin") {
        if (valueStr.size() != 8) return false;
        std::uint8_t v = 0;
        for (char c : valueStr) {
            if (c != '0' && c != '1') return false;
            v = static_cast<std::uint8_t>((v << 1) | (c - '0'));
        }
        outValue = v;
        return true;
    }

    if (mode == "ascii") {
        if (valueStr.size() != 1) return false;
        outValue = static_cast<std::uint8_t>(valueStr[0]);
        return true;
    }

    return false;
}

static void printUsage() {
    std::cout
        << "Usage:\n"
        << "  hexeditor <input>\n"
        << "  hexeditor <input> <output> <index> <hex|bin|ascii> <value>\n\n"
        << "Examples:\n"
        << "  hexeditor test.bin\n"
        << "  hexeditor test.bin test_modified.bin 0 hex 58\n"
        << "  hexeditor test.bin test_modified.bin 1 bin 01100001\n"
        << "  hexeditor test.bin test_modified.bin 2 ascii Z\n";
}

int main(int argc, char* argv[]) {
    // Erlaubte Aufrufvarianten prüfen
    if (argc != 2 && argc != 6) {
        printUsage();
        return 1;
    }

    const std::string inputPath = argv[1];

    FileManager fm;
    if (!fm.loadFile(inputPath)) {
        std::cout << "Fehler: Datei konnte nicht geladen werden.\n";
        return 1;
    }

    // Fall 1: Nur anzeigen
    if (argc == 2) {
        const auto& data = fm.getData();

        std::cout << "Datei geladen. Anzahl Bytes: "
                  << data.size() << "\n\n";

        std::cout << "Idx   Addr      Hex  Binary      ASCII\n";
        std::cout << "-------------------------------------------\n";

        for (std::size_t i = 0; i < data.size(); ++i) {
            printByteLine(i, data[i]);
        }
        return 0;
    }

    // Fall 2: Bearbeiten und speichern
    const std::string outputPath = argv[2];

    std::size_t index = 0;
    try {
        index = static_cast<std::size_t>(
            std::stoul(argv[3], nullptr, 10));
    } catch (...) {
        std::cout << "Fehler: Index ist keine Zahl.\n";
        return 1;
    }

    const std::string mode = argv[4];
    const std::string valueStr = argv[5];

    std::uint8_t newValue = 0;
    if (!parseByteValue(mode, valueStr, newValue)) {
        std::cout << "Fehler: Wert konnte nicht interpretiert werden.\n";
        return 1;
    }

    const auto& data = fm.getData();
    if (index >= data.size()) {
        std::cout << "Fehler: Index außerhalb des Bereichs.\n";
        return 1;
    }

    // Alten Wert merken und anzeigen
    std::uint8_t oldValue = data[index];

    std::cout << "Bearbeitung:\n";
    std::cout << "Index: " << index << "\n";
    std::cout << "Alt:  "
              << "Hex=" << Converter::toHex(oldValue) << "  "
              << "Bin=" << Converter::toBinary(oldValue) << "  "
              << "ASCII=" << Converter::toAscii(oldValue) << "\n";

    // Byte setzen
    fm.setByte(index, newValue);

    std::cout << "Neu:  "
              << "Hex=" << Converter::toHex(newValue) << "  "
              << "Bin=" << Converter::toBinary(newValue) << "  "
              << "ASCII=" << Converter::toAscii(newValue) << "\n";

    // Datei speichern
    if (!fm.saveFile(outputPath)) {
        std::cout << "Fehler: Datei konnte nicht gespeichert werden.\n";
        return 1;
    }

    std::cout << "Gespeichert als: " << outputPath << "\n";
    return 0;
}
