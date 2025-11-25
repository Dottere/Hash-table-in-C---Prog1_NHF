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
    Alkalmazott *linkedList = NULL;
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

                wprintf(L"A beolvasást választottad! Kérlek add meg a beolvasandó fájl elérési útvonalát: ");
                    path = readPath();
                while (!pathExists(path)){
                        printf("Ilyen elérési út nem létezik:\"%s\"\n", path);
                        wprintf(L"Elérési út: ");
                        free(path);
                        path = readPath();
                }

                wprintf(L"Beolvasás CSV-ből láncolt listába...\n");
                linkedList = readFromCSV(path);

                if (!linkedList) {
                    wprintf(L"Hiba történt az adatok beolvasásakor, a láncolt lista nem jött létre. A program kilép");
                    break;
                }

                wprintf(L"Hash-Tábla létrehozása %d elemszámmal...\n", linkedListLen(&linkedList));
                ht = htcreate(linkedListLen(&linkedList));
                if (!ht) {
                    wprintf(L"Nem sikerült a Hash-Táblának memóriát foglalni. A program kilép.");
                    free(path);
                    return -1;
                }

                wprintf(L"Beszúrás a Hash-Táblába...\n");
                int const result = htinsert(ht, &linkedList);

                if (result != 0) {
                    wprintf(L"✗ Beszúrás sikertelen! Hibakód: %d\n", result);
                    free(path);
                    path = NULL;
                    htfree(ht);
                    linkedListFree(&linkedList);
                    ht = NULL;
                    linkedList = NULL;
                    return -1;
                }
                linkedListFree(&linkedList);

                wprintf(L"✓ Beszúrás sikeres!\n");
                break;

            case 2:
                if (ht)
                    printHashTable(ht);
                else {
                    wprintf(L"Hash-Tábla nem létezik, először olvass be egyet fájlból! (1)");
                }
                break;
            case 3:
                if (ht)
                    statistics(ht);
                else {
                    wprintf(L"Hash-Tábla nem létezik, először olvass be egyet fájlból! (1)");
                }
                break;
            case 4:
                if (ht)
                    howToModify(ht, path);
                else {
                    wprintf(L"Hash-Tábla nem létezik, először olvass be egyet fájlból! (1)");
                }
                break;
            case 5:
                if (!ht) {
                    wprintf(L"Nincs beolvasva HashTábla, nem lehet adatot kiírni!");
                    break;
                }

                wprintf(L"Add meg a célfájl elérési útját! (pl export.csv): ");
                char *outPath = readPath();

                if (pathExists(outPath)) {
                    if (!confirmOverwrite(outPath)) {
                        free(outPath);
                        wprintf(L"A kiírás megszakítva!\n");
                        break;
                    }
                }

                wprintf(L"Fájl írása: %s ...\n", outPath);

                int const writeRes = writeToCSV(ht, outPath);

                if (writeRes == 0) {
                    wprintf(L"Sikeres kiírás!\n");
                } else {
                    wprintf(L"Hiba történt a fájl írásakor! Hibakód: %d\n", writeRes);
                }
                free(outPath);
                break;

            case 6:
                wprintf(L"A program kilép.\n");
                htfree(ht);
                linkedListFree(&linkedList);
                run = false;
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

