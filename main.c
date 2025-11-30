#include "headers/debugmalloc.h"
#include "headers/utils.h"

#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(void) {
    setlocale(LC_ALL, "");

    bool run = true;

    HashTable *ht = NULL;
    char *path = NULL;

    printHelp();

    while (run) {

        int const choice = readMenuChoice();

        switch (choice){
            case 0:
                printHelp();
                break;

            case 1:
                handleLoadOption(&ht, &path);
                break;
            case 2:
                if (ensureTableExists(ht)) searchInHashTable(&ht);
                break;
            case 3:
                if (ensureTableExists(ht)) printHashTable(ht);
                break;
            case 4:
                if (ensureTableExists(ht)) statistics(ht);
                break;
            case 5:
                if (ensureTableExists(ht)) howToModify(ht, path);
                break;
            case 6:
                if (ensureTableExists(ht)) writeToFile(&ht);
                break;
            case 7:
                if (confirmExit()) run = false;
                break;
            default:
                wprintf(L"Helytelen opció!\n");
                break;
        }
    }
    free(path);
    if (ht) htfree(ht);
    return 0;
}