#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <cstdint>

class Converter {
public:
    static std::string toHex(std::uint8_t byte);
    static std::string toBinary(std::uint8_t byte);
    static char toAscii(std::uint8_t byte);
};

#endif
