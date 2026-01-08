#include "Converter.h"
#include <bitset>
#include <sstream>
#include <iomanip>

std::string Converter::toHex(std::uint8_t byte) {
    std::ostringstream oss;
    oss << std::uppercase
        << std::hex
        << std::setw(2)
        << std::setfill('0')
        << static_cast<int>(byte);
    return oss.str();
}

std::string Converter::toBinary(std::uint8_t byte) {
    return std::bitset<8>(byte).to_string();
}

char Converter::toAscii(std::uint8_t byte) {
    // Druckbare ASCII-Zeichen typischerweise 32..126
    if (byte >= 32 && byte <= 126) {
        return static_cast<char>(byte);
    }
    return '.';
}
