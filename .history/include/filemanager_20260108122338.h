#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <cstdint>
#include <cstddef> // für std::size_t

class FileManager {
public:
    // Lädt eine Binärdatei und speichert die Bytes im internen Puffer.
    bool loadFile(const std::string& path);

    // Speichert den internen Puffer als Binärdatei.
    bool saveFile(const std::string& path) const;

    // Gibt Zugriff auf die geladenen Daten (nur lesend).
    const std::vector<std::uint8_t>& getData() const;

    // Ändert ein Byte an einer bestimmten Position.
    bool setByte(std::size_t index, std::uint8_t value);

private:
    // Interner Byte-Puffer (Inhalt der geladenen Datei).
    std::vector<std::uint8_t> data_;
};

#endif
