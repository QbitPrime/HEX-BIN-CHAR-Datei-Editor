#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <cstdint>

class Converter {
public:
    // Byte -> zweistellige Hex-Darstellung 
    static std::string toHex(std::uint8_t byte);

    // Byte -> Binärdarstellung mit 8 Bit 
    static std::string toBinary(std::uint8_t byte);

    // Byte -> ASCII-Zeichen; falls nicht druckbar, wird '.' zurückgegeben
    static char toAscii(std::uint8_t byte);
};

#endif
