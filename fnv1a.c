//
// Created by lin on 11/7/25.
//

#include "headers/fnv1a.h"
#include "headers/debugmalloc.h"

uint32_t FNV1a(const wchar_t *str) {
    if (!str) return 0;

    size_t const size = wcstombs(NULL, str, 0);
    if (size == (size_t)-1) {
        return 0;
    }

    char *utf8_str = (char *)malloc(size + 1);
    if (!utf8_str) {
        return 0;
    }

    wcstombs(utf8_str, str, size + 1);

    uint32_t hash = FNV_OFFSET;
    for (size_t i = 0; i < size; i++) {
        hash ^= (uint8_t)utf8_str[i];
        hash *= FNV_PRIME;
    }

    free(utf8_str);
    return hash;
}