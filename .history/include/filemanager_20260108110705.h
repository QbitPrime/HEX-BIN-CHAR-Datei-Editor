#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <cstdint>

class FileManager {
public:
    // Lädt eine Datei vollständig in den Speicher.
    bool loadFile(const std::string& path);

    // Speichert den aktuellen Puffer wieder in die Datei.
    bool saveFile(const std::string& path) const;

    // Zugriff auf die geladenen Daten (read-only).
    const std::vector<std::uint8_t>& getData() const;

    // Erlaubt später das Bearbeiten einzelner Bytes.
    bool setByte(std::size_t index, std::uint8_t value);

private:
    std::vector<std::uint8_t> data_;
};

#endif
