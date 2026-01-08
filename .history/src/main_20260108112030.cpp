#include <iostream>
#include <iomanip>
#include <string>

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
    const std::size_t editIndex = 0;
    const std::uint8_t newValue = static_cast<std::uint8_t>('X'); // 0x58

    std::cout << "\nBearbeitung:\n";
    std::cout << "Alt: ";
    printByteLine(editIndex, fm.getData()[editIndex]);

    if (!fm.setByte(editIndex, newValue)) {
        std::cout << "Fehler: Index außerhalb des Bereichs.\n";
        return 1;
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
