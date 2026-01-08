#include "FileManager.h"
#include <fstream>

bool FileManager::loadFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        return false;
    }

    data_.assign(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );

    return true;
}

bool FileManager::saveFile(const std::string& path) const {
    std::ofstream file(path, std::ios::binary | std::ios::trunc);
    if (!file) {
        return false;
    }

    file.write(reinterpret_cast<const char*>(data_.data()),
               static_cast<std::streamsize>(data_.size()));
    return static_cast<bool>(file);
}

const std::vector<std::uint8_t>& FileManager::getData() const {
    return data_;
}

bool FileManager::setByte(std::size_t index, std::uint8_t value) {
    if (index >= data_.size()) {
        return false;
    }
    data_[index] = value;
    return true;
}
