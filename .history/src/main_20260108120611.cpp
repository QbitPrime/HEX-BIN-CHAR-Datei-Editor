// src/main.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>

#include "FileManager.h"
#include "Converter.h"

static void printByteLine(std::size_t index, std::uint8_t value) {
    std::cout << std::setw(4) << index << "  "
              << "0x" << std::setw(6) << std::setfill('0') << std::hex << index
              << std::dec << std::setfill(' ') << "  "
              << Converter::toHex(value) << "   "
              << Converter::toBinary(value) << "   "
              << Converter::toAscii(value) << "\n";
}

int main() {
    FileManager fm;
    const std::string inputPath = "test.bin";

    if (!fm.loadFile(inputPath)) {
        std::cout << "Fehler: Datei konnte nicht geladen werden.\n";
        return 1;
    }

    const auto& data = fm.getData();
    std::cout << "Datei geladen. Anzahl Bytes: " << data.size() << "\n\n";

    std::cout << "Idx   Addr      Hex  Binary      ASCII\n";
    std::cout << "-------------------------------------------\n";

    // Alle Bytes der Datei anzeigen
    for (std::size_t i = 0; i < data.size(); ++i) {
        printByteLine(i, data[i]);
    }

    return 0;
}
