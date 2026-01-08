#include "Converter.h"
#include <string>

//Wandelt ein Byte in eine zweistellige Hexadezimaldarstellung um
std::string Converter::toHex(std::uint8_t byte) {
    // Tabelle mit Hex-Zeichen
    const char hexDigits[] = "0123456789ABCDEF";

    std::string result;
    result += hexDigits[(byte >> 4) & 0x0F]; // oberes Halb-Byte
    result += hexDigits[byte & 0x0F];        // unteres Halb-Byte

    return result;
}

// Wandelt ein Byte in eine Binärdarstellung um.

std::string Converter::toBinary(std::uint8_t byte) {
    std::string result;

    // Jedes Bit einzeln prüfen (von links nach rechts)
    for (int i = 7; i >= 0; --i) {
        if (byte & (1 << i)) {
            result += '1';
        } else {
            result += '0';
        }
    }

    return result;
}

// Wandelt ein Byte in ein darstellbares ASCII-Zeichen um. Nicht darstellbare Zeichen werden als '.' ausgegeben
char Converter::toAscii(std::uint8_t byte) {
    // Bereich der druckbaren ASCII-Zeichen
    if (byte >= 32 && byte <= 126) {
        return static_cast<char>(byte);
    }

    return '.';
}
