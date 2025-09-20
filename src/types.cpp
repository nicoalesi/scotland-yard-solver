#include "types.h"

uint8_t to_uint8(int32_t n) {
    if (n < 0 || UINT8_MAX < n) {
        throw std::invalid_argument("Value out of range.");
    }

    return static_cast<uint8_t>(n);
}

uint8_t to_uint8(size_t n) {
    if (UINT8_MAX < n) {
        throw std::invalid_argument("Value out of range.");
    }

    return static_cast<uint8_t>(n);
}

uint16_t to_uint16(int32_t n) {
    if (n < 0 || UINT16_MAX < n) {
        throw std::invalid_argument("Value out of range.");
    }

    return static_cast<uint16_t>(n);
}

uint32_t to_uint32(int32_t n) {
    if (n < 0) {
        throw std::invalid_argument("Value out of range.");
    }

    return static_cast<uint32_t>(n);
}
