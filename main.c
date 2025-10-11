#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include <wchar.h>
#include <locale.h>

#define FNV_OFFSET 0x811C9DC5
#define FNV_PRIME 0x01000193

typedef struct {
    const unsigned char *data;
    size_t len;
}hashInput;

// Fowler-Noll-Vo-1a hash function
uint32_t FNV1a(hashInput);
hashInput get_bytes(const char *);

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");

    wchar_t test[99];

    while (wscanf(L"%ls", test) != EOF) {
        wprintf(L"%ls FNV1a hash-je: %" PRIu32 "\n", test, FNV1a(get_bytes(test)));

    }

    return 0;
}

uint32_t FNV1a(const hashInput input) {
    uint32_t hash = FNV_OFFSET;
    for (size_t i = 0; i < input.len; i++) {
        hash ^= input.data[i];
        hash *= FNV_PRIME;
    }
    return hash;
}

hashInput get_bytes(const char *str) {
    const hashInput output = {.data = (const unsigned char*)str, .len = strlen(str)};
    return output;
}