#include <iostream>
#include "FileManager.h"

int main() {
    FileManager fm;

    const std::string path = "test.bin";

    if (!fm.loadFile(path)) {
        std::cout << "Datei konnte nicht geladen werden: " << path << "\n";
        return 1;
    }

    const auto& data = fm.getData();
    std::cout << "Datei geladen. Anzahl Bytes: " << data.size() << "\n";

    return 0;
}
