#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#include <wchar.h>
#include <locale.h>

#define FNV_OFFSET 2166136261u
#define FNV_PRIME 16777619u

uint32_t FNV1a(const wchar_t *);

int main(void) {
    setlocale(LC_ALL, "en_US.UTF-8");

    wchar_t test[99];
    wscanf(L"%ls", test);

    wprintf(L"The FNV1a hash of %ls is: %" PRIu32 "\n", test, FNV1a(test));


    return 0;
}

uint32_t FNV1a(const wchar_t *str) {
    const size_t size = wcstombs(NULL, str, 0);
    if (size == (size_t)-1){
        return 1;
    }

    char *utf8 = malloc(size+1);
    if (!utf8) return 1;

    wcstombs(utf8, str, size + 1);

    uint32_t hash = FNV_OFFSET;

    for (size_t i = 0; i < size; i++) {
        hash ^= (uint8_t)utf8[i];
        hash *= FNV_PRIME;
    }
    free(utf8);
    return hash;
}


