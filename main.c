#include <stdio.h>
#include <inttypes.h>

#include <locale.h>
#include <wchar.h>

#include "headers/debugmalloc.h"
//#include "headers/ht.h"
#include "headers/fnv1a.h"
// #include "headers/datastructs.h"
#include "headers/ht.h"
#include "headers/io.h"
#include "headers/linkedlist.h"

int main(void) {
    setlocale(LC_ALL, "");

    //wchar_t test[100];
    //wscanf(L"%99ls", test);

    //wprintf(L"The FNV1a hash of %ls is: %" PRIu32 "\n", test, FNV1a(test));
    //wprintf(L"The FNV1a hash of %ls is: 0x%08X\n", (const unsigned short *)test, FNV1a(test));

    //printFromCSV("../employees.csv");
    Alkalmazott *linkedList = readFromCSV("../employees.csv");
    linkedListPrint(&linkedList);
    return 0;
}

