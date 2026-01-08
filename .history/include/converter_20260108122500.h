#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <cstdint>

class Converter {
public:
    // Byte -> zweistellige Hex-Darstellung (z. B. 65 -> "41")
    static std::string toHex(std::uint8_t byte);

    // Byte -> Binärdarstellung mit 8 Bit (z. B. 5 -> "00000101")
    static std::string toBinary(std::uint8_t byte);

    // Byte -> ASCII-Zeichen; falls nicht druckbar, wird '.' zurückgegeben
    static char toAscii(std::uint8_t byte);
};

#endif
