#include <iostream>
#include <iomanip>
#include "FileManager.h"
#include "Converter.h"

int main() {
    FileManager fm;
    const std::string path = "test.bin";

    if (!fm.loadFile(path)) {
        std::cout << "Datei konnte nicht geladen werden: " << path << "\n";
        return 1;
    }

    const auto& data = fm.getData();
    std::cout << "Datei geladen. Anzahl Bytes: " << data.size() << "\n\n";

    // Kopfzeile
    std::cout << "Idx  Addr      Hex  Binary      ASCII\n";
    std::cout << "-----------------------------------------\n";

    // Nur die ersten 16 Bytes anzeigen (Phase 2: überschaubar)
    const std::size_t count = (data.size() < 16) ? data.size() : 16;

    for (std::size_t i = 0; i < count; ++i) {
        std::cout << std::setw(3) << i << "  "
                  << "0x" << std::setw(6) << std::setfill('0') << std::hex << i
                  << std::dec << std::setfill(' ') << "  "
                  << Converter::toHex(data[i]) << "   "
                  << Converter::toBinary(data[i]) << "   "
                  << Converter::toAscii(data[i]) << "\n";
    }

    return 0;
}
