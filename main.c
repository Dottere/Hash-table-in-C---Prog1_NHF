#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

#include <locale.h>
#include <wchar.h>

#include "headers/debugmalloc.h"
//#include "headers/ht.h"
#include "headers/fnv1a.h"
// #include "headers/datastructs.h"
#include "headers/ht.h"
#include "headers/io.h"
#include "headers/linkedlist.h"
#include "headers/utils.h"

int main(void) {
    setlocale(LC_ALL, "");

    bool run = true;

    HashTable *ht = NULL;
    char *path = NULL;

    printHelp();

    while (run) {

        char choice[16];
        wprintf(L"\nVálasztás: ");
        if (!fgets(choice, sizeof(choice), stdin)) {
            wprintf(L"Hiba történt a beolvasáskor!\n");
            continue;
        }

        size_t const len = strlen(choice);
        if (len > 0 && choice[len-1] == '\n')
            choice[len-1] = '\0';

        long const choiceNum = strtol(choice, NULL, 10);

        switch (choiceNum){
            case 0:
                printHelp();
                break;

            case 1:
                if (ht) {
                    if (!confirmOverwrite(path))
                        break;

                    htfree(ht);
                    ht = NULL;
                }

                if (path) {
                    free(path);
                    path = NULL;
                }

                int const res = readingFromFile(&ht, &path);
                if (res != 0) {
                    return -1;
                }

                wprintf(L"✓ Beszúrás sikeres!\n");
                break;
            case 2:
                if (!ht) {
                    wprintf(L"Nincs beolvasva HashTábla, nem lehet adatot kiírni!");
                    break;
                }
                searchInHashTable(&ht);
                break;
            case 3:
                if (ht)
                    printHashTable(ht);
                else {
                    wprintf(L"Hash-Tábla nem létezik, először olvass be egyet fájlból! (1)");
                }
                break;
            case 4:
                if (ht)
                    statistics(ht);
                else {
                    wprintf(L"Hash-Tábla nem létezik, először olvass be egyet fájlból! (1)");
                }
                break;
            case 5:
                if (ht)
                    howToModify(ht, path);
                else {
                    wprintf(L"Hash-Tábla nem létezik, először olvass be egyet fájlból! (1)");
                }
                break;
            case 6:
                if (!ht) {
                    wprintf(L"Nincs beolvasva HashTábla, nem lehet adatot kiírni!");
                    break;
                }

                writeToFile(&ht);
                break;

            case 7:
                wprintf(L"\nBiztosan ki akarsz lépni?\n1. Igen\n2.Nem\nVálasztás: ");
                if (!fgets(choice, 16, stdin)) break;
                if (choice[0] == '1') {
                    wprintf(L"A program kilép.\n");
                    htfree(ht);
                    run = false;
                    break;
                }
                if (choice[0] == '2') {
                    break;
                }
                wprintf(L"Helytelen opció!\n");
                break;

            default:
                wprintf(L"Helytelen opció!\n");
                break;
        }
    }

    if (path) {
        free(path);
    }
    return 0;
}


