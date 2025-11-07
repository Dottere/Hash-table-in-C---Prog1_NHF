#include <stdio.h>
#include <inttypes.h>

#include <locale.h>
#include <wchar.h>

//#include "headers/debugmalloc.h"
//#include "headers/ht.h"
#include "headers/fnv1a.h"
#include "headers/datastructs.h"

#define FNV_OFFSET 2166136261u
#define FNV_PRIME 16777619u

int htinsert(const wchar_t*, uint32_t *);

int main(void) {
    setlocale(LC_ALL, "en_US.UTF-8");

    wchar_t test[100];
    wscanf(L"%99ls", test);

    //wprintf(L"The FNV1a hash of %ls is: %" PRIu32 "\n", test, FNV1a(test));
    wprintf(L"The FNV1a hash of %ls is: 0x%08X\n", (const unsigned short *)test, FNV1a(test));

    return 0;
}

