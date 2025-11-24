//
// Created by lin on 11/7/25.
//

#include "headers/fnv1a.h"

/*
Expects a stream of bytes that gets hashed into a single 32-bit integer
 */
uint32_t FNV1a(const wchar_t *str) {
    if (!str) return 0;

    // Get required size for UTF-8 conversion
    size_t const size = wcstombs(NULL, str, 0);
    if (size == (size_t)-1) {
        return 0;  // Conversion error
    }

    // Allocate buffer for UTF-8 string
    char *utf8_str = (char *)malloc(size + 1);
    if (!utf8_str) {
        return 0;  // Allocation failed
    }

    // Convert to UTF-8
    wcstombs(utf8_str, str, size + 1);

    // Calculate FNV-1a hash
    uint32_t hash = FNV_OFFSET;
    for (size_t i = 0; i < size; i++) {
        hash ^= (uint8_t)utf8_str[i];
        hash *= FNV_PRIME;
    }

    free(utf8_str);
    return hash;
}