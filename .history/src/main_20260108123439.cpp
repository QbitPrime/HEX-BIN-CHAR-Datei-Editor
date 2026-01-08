// src/main.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>
#include <cstddef>

#include "FileManager.h"
#include "Converter.h"

// Ausgabe einer Zeile im "Hex-Editor"-Stil
static void printByteLine(std::size_t index, std::uint8_t value) {
    std::cout << std::setw(4) << index << "  "
              << "0x" << std::setw(6) << std::setfill('0') << std::hex << index
              << std::dec << std::setfill(' ') << "  "
              << Converter::toHex(value) << "   "
              << Converter::toBinary(value) << "   "
              << Converter::toAscii(value) << "\n";
}

// Wandelt einen String in ein Byte um, je nach Eingabeform
static bool parseByteValue(const std::string& mode,
                           const std::string& valueStr,
                           std::uint8_t& outValue) {
    if (mode == "hex") {
        // z.B. "58" oder "0x58"
        unsigned int v = 0;
        try {
            v = static_cast<unsigned int>(std::stoul(valueStr, nullptr, 16));
        } catch (...) {
            return false;
        }
        if (v > 255) return false;
        outValue = static_cast<std::uint8_t>(v);
        return true;
    }

    if (mode == "bin") {
        // erwartet genau 8 Zeichen '0'/'1'
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
        // ein einzelnes Zeichen
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

    // Wenn nur input angegeben ist: nur anzeigen
    if (argc == 2) {
        const auto& data = fm.getData();
        std::cout << "Datei geladen. Anzahl Bytes: " << data.size() << "\n\n";
        std::cout << "Idx   Addr      Hex  Binary      ASCII\n";
        std::cout << "-------------------------------------------\n";
        for (std::size_t i = 0; i < data.size(); ++i) {
            printByteLine(i, data[i]);
        }
        return 0;
    }

    // Bearbeiten + speichern
    const std::string outputPath = argv[2];
    std::size_t index = 0;
    try {
        index = static_cast<std::size_t>(std::stoul(argv[3], nullptr, 10));
    } catch (...) {
        std::cout << "Fehler: Index ist keine Zahl.\n";
        return 1;
    }

    const std::string mode = argv[4];
    const std::string valueStr = argv[5];

    std::uint8_t newValue = 0;
    if (!parseByteValue(mode, valueStr, newValue)) {
        std::cout << "Fehler: Wert konnte nicht geparst werden.\n";
        return 1;
    }

    if (!fm.setByte(index, newValue)) {
        std::cout << "Fehler: Index außerhalb des Bereichs.\n";
        return 1;
    }

    if (!fm.saveFile(outputPath)) {
        std::cout << "Fehler: Datei konnte nicht gespeichert werden.\n";
        return 1;
    }

    std::cout << "Gespeichert als: " << outputPath << "\n";
    return 0;
}
