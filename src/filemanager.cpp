#include "FileManager.h"
#include <fstream>

// Lädt eine Binärdatei vollständig in den internen Datenpuffer
bool FileManager::loadFile(const std::string& path) {
    // Datei im Binärmodus öffnen weil somit keine Umwandlungen stattfinden
    std::ifstream file(path, std::ios::binary);

    // Prüfen, ob die Datei erfolgreich geöffnet wurde
    if (!file) {
        return false;
    }

    // Bestehende Daten ggf. löschen
    data_.clear();

    //Datei byteweise einlesen
    char byte;
    while (file.read(&byte, 1)) {
        data_.push_back(static_cast<std::uint8_t>(byte));
    }

    return true;
}

//Speichert den aktuellen Datenpuffer als Binärdatei. Vorhandene Datei wird überschrieben.
bool FileManager::saveFile(const std::string& path) const {
    // Datei im Binärmodus zum Schreiben öffnen
    std::ofstream file(path, std::ios::binary | std::ios::trunc);

    // Prüfen, ob die Datei geöffnet werden konnte
    if (!file) {
        return false;
    }

    //Schreiben aller Bytes aus dem internen Puffer in die Datei. Die Daten werden unverändert gespeichert.
    for (std::uint8_t byte : data_) {
        file.write(reinterpret_cast<const char*>(&byte), 1);
    }

    return true;
}

//Gibt einen konstanten Zugriff auf die geladenen Binärdaten zurück. Die Daten können gelesen, aber nicht direkt verändert werden.
const std::vector<std::uint8_t>& FileManager::getData() const {
    return data_;
}

//Setzt ein einzelnes Byte an der angegebenen Position. Vor dem Schreiben wird geprüft, ob der Index gültig ist.
bool FileManager::setByte(std::size_t index, std::uint8_t value) {
    if (index >= data_.size()) {
        return false;
    }

    data_[index] = value;
    return true;
}
