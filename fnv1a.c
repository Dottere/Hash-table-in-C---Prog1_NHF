//
// Created by lin on 11/7/25.
//

#include "headers/fnv1a.h"

typedef struct {
    size_t size;
    char *str;
} utf8_size_and_str;

utf8_size_and_str *utf8_conv(const wchar_t *);

extern uint32_t FNV1a(const wchar_t *str) {

    utf8_size_and_str *utf8 = utf8_conv(str);
    const size_t size = utf8->size;
    const char *utf8_str = utf8->str;

    if (size == (size_t)-1) {
        free((size_t *)utf8->size);
        free(utf8->str);
        free(utf8);
        return 1;
    }

    wcstombs((char *)utf8_str, str, size + 1);

    uint32_t hash = FNV_OFFSET;

    for (size_t i = 0; i < size; i++) {
        hash ^= (uint8_t)utf8_str[i];
        hash *= FNV_PRIME;
    }

    free(utf8->str);
    free(utf8);

    return hash;
}

utf8_size_and_str *utf8_conv(const wchar_t *str) {
    const size_t size = wcstombs(NULL, str, 0);
    if (size == (size_t)-1) {
        return NULL;
    }

    // ReSharper disable once CppRedundantCastExpression
    char *utf8_str = (char *)malloc(sizeof(char) * size+1);
    if (!utf8_str) return NULL;

    utf8_size_and_str *utf8 = malloc(sizeof(utf8_size_and_str));

    utf8->size = size;
    utf8->str = utf8_str;

    return utf8;
}
