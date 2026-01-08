#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

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

int main(int argc, char* argv[])
    FileManager fm;
    const std::string inputPath  = "test.bin";
    const std::string outputPath = "test_modified.bin";

    if (!fm.loadFile(inputPath)) {
        std::cout << "Datei konnte nicht geladen werden: " << inputPath << "\n";
        return 1;
    }

    auto data = fm.getData(); // Kopie nur für Anzeigezwecke
    std::cout << "Datei geladen. Anzahl Bytes: " << data.size() << "\n\n";

    std::cout << "Idx  Addr      Hex  Binary      ASCII\n";
    std::cout << "-----------------------------------------\n";

    const std::size_t count = (data.size() < 16) ? data.size() : 16;
    for (std::size_t i = 0; i < count; ++i) {
        printByteLine(i, data[i]);
    }

    // --- Bearbeitung: Byte an Position 0 auf 'X' (0x58) setzen ---
    // Standardwerte (falls keine Parameter übergeben werden)
    std::size_t editIndex = 0;
    std::uint8_t newValue = static_cast<std::uint8_t>('X'); // 0x58

    // Optional: Parameter verarbeiten
    // args: input output index valueHex
    if (argc >= 5) {
    inputPath  = argv[1];
    outputPath = argv[2];
    editIndex  = static_cast<std::size_t>(std::stoul(argv[3], nullptr, 10));
    unsigned int v = static_cast<unsigned int>(std::stoul(argv[4], nullptr, 16));
    newValue = static_cast<std::uint8_t>(v & 0xFF);
}

    std::cout << "Neu: ";
    printByteLine(editIndex, fm.getData()[editIndex]);

    // --- Speichern in neue Datei ---
    if (!fm.saveFile(outputPath)) {
        std::cout << "Fehler beim Speichern: " << outputPath << "\n";
        return 1;
    }

    std::cout << "\nGespeichert als: " << outputPath << "\n";
    return 0;
}
