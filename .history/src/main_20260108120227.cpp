// src/main.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>

#include "FileManager.h"
#include "Converter.h"

static void printByteLine(std::size_t index, std::uint8_t value) {
    std::cout << std::setw(3) << index << "  "
              << "0x" << std::setw(6) << std::setfill('0') << std::hex << index
              << std::dec << std::setfill(' ') << "  "
              << Converter::toHex(value) << "   "
              << Converter::toBinary(value) << "   "
              << Converter::toAscii(value) << "\n";
}

int main() {
    FileManager fm;

    const std::string inputPath  = "test.bin";
    const std::string outputPath = "test_modified.bin";

    if (!fm.loadFile(inputPath)) {
        std::cout << "Fehler: Datei konnte nicht geladen werden.\n";
        return 1;
    }

    const auto& data = fm.getData();
    std::cout << "Datei geladen. Anzahl Bytes: " << data.size() << "\n\n";

    std::cout << "Idx  Addr      Hex  Binary      ASCII\n";
    std::cout << "-----------------------------------------\n";

    const std::size_t count = (data.size() < 16) ? data.size() : 16;
    for (std::size_t i = 0; i < count; ++i) {
        printByteLine(i, data[i]);
    }

    // Einfacher Demo-Edit: erstes Byte auf 'X' setzen
    std::size_t editIndex = 0;
    std::uint8_t newValue = static_cast<std::uint8_t>('X');

    if (editIndex < data.size()) {
        std::cout << "\nBearbeitung:\n";
        std::cout << "Alt: ";
        printByteLine(editIndex, fm.getData()[editIndex]);

        fm.setByte(editIndex, newValue);

        std::cout << "Neu: ";
        printByteLine(editIndex, fm.getData()[editIndex]);
    }

    if (!fm.saveFile(outputPath)) {
        std::cout << "Fehler: Datei konnte nicht gespeichert werden.\n";
        return 1;
    }

    std::cout << "\nGespeichert als: " << outputPath << "\n";
    return 0;
}
