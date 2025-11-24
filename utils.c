//
// Created by lin on 11/24/25.
//

#include "headers/utils.h"

void printHelp(void) {
    wprintf(L"A program mely funkcionalitását szeretnéd használni?\n");
    wprintf(L"0. Kiírja újra ezt a segítséget.\n");
    wprintf(L"1. Beolvasás CSV fájlból.\n");
    wprintf(L"2. Hash-Tábla kilistázása.\n");
    wprintf(L"3. Ütközések tesztelése.\n");
    wprintf(L"4. Hash-Tábla módosítása.\n");
    wprintf(L"5. Kiírás CSV fájlba.\n");
    wprintf(L"6. Kilép.\n");
}

void statistics(HashTable *ht) {
    wprintf(L"\nÜtközés statisztika:\n");
    sleep(1);
    int emptyBuckets = 0;
    int collisions = 0;
    for (size_t j = 0; j < ht->size; j++) {
        if (ht->buckets[j] == NULL) {
            emptyBuckets++;
        } else {
            int chainLen = 0;
            Alkalmazott const *iter2 = ht->buckets[j];
            while (iter2) {
                chainLen++;
                iter2 = iter2->kov;
            }
            if (chainLen > 1) {
                collisions++;
                wprintf(L"  Bucket[%zu]: %d elem (ütközés)\n", j, chainLen);
            }
        }
    }
    wprintf(L"Üres vödrök: %d/%zu\n", emptyBuckets, ht->size);
    wprintf(L"Ütközéses vödrök: %d (%.2lf%%)\n", collisions, ((double)collisions/(double)ht->size)*100);
    wprintf(L"\nTeszt befejezve!\n");
}

bool confirmOverwrite(const char *path) {
    char choice[16];
    while (true) {
        wprintf(L"Már történt beolvasás \"%hs\" fájlból. Szeretnéd felülírni?\n[i] - igen\n[n] - nem\nVálasz: ", path);
        if (!fgets(choice, sizeof(choice), stdin)) return false;

        if (choice[0] == 'n' || choice[0] == 'N') return false;
        if (choice[0] == 'i' || choice[0] == 'I') return true;

        wprintf(L"Érvénytelen választás.\n");
    }
}

void howToModify(HashTable *ht, char const *path) {
    char choice1[16];
    while (true) {
        wprintf(L"Hogyan szeretnéd módosítani a Hash-Táblát?\n1. Hozzáadni\n2. Törölni");
        if (!fgets(choice1, sizeof(choice1), stdin)) return;

        if (choice1[0] == '1') {
            char choice2[16];
            wprintf(L"Hány elemet szeretnél hozzáadni?\n1. Egyet manuálisan\n2. Többet fájlból");
            if (!fgets(choice2, sizeof(choice2), stdin)) return;

            if (choice2[0] == '1') {
                Alkalmazott *ujEmber = readFromInput();

                if (ujEmber) {
                    int const res = htinsert(ht, &ujEmber);

                    if (res == 0) {
                        wprintf(L"✓ Sikeresen hozzáadva!\n");
                    } else {
                        wprintf(L"✗ Hiba a beszúrásnál! Hibakód: %d\n", res);
                        freeNode(ujEmber);
                        return;
                    }

                    freeNode(ujEmber);
                } else {
                    wprintf(L"Hiba az adatok felvéleténél (Memória)\n");
                }
            } else if (choice2[0] == '2') {
                wprintf(L"Mely fájlból szeretnél újonnan beszúrni?");
                wprintf(L"Elérési út: ");
                char *newPath = readPath();
                while (!pathExists(path)){
                    wprintf(L"Ilyen elérési út nem létezik:\"%hs\"\n", newPath);
                    wprintf(L"Elérési út: ");
                    free(newPath);
                    path = readPath();
                }

                if (strcmp(path, newPath) == 0) {
                    wprintf(L"Nem szúrhatod be ugyanazt a listát kétszer!");
                    break;
                }

                Alkalmazott *ujLista = readFromCSV(newPath);
                if (!ujLista) {
                    wprintf(L"Hiba történt az új lista beolvasásakor!");
                    return;
                }
                free(newPath);

                int const result = htinsert(ht, &ujLista);

                if (result != 0) {
                    wprintf(L"✗ Beszúrás az új listába sikertelen! Hibakód: %d\n", result);
                    linkedListFree(&ujLista);
                    return;
                }
                linkedListFree(&ujLista);
                return;
            }
        } else if (choice1[0] == '2') {
            wchar_t name[64];
            wchar_t email[64];
            wchar_t szul[24];

            char inputBuff[256];

            wprintf(L"Ahhoz, hogy törölj a táblából szükségünk van három dologra:\n");

            wprintf(L"Név: ");
            if (fgets(inputBuff, sizeof(inputBuff), stdin) != NULL) {
                inputBuff[strcspn(inputBuff, "\n")] = '\0';

                mbstowcs(name, inputBuff, sizeof(name) / sizeof(wchar_t) - 1);
            }

            wprintf(L"E-mail cím: ");
            if (fgets(inputBuff, sizeof(inputBuff), stdin) != NULL) {
                inputBuff[strcspn(inputBuff, "\n")] = '\0';

                mbstowcs(email, inputBuff, sizeof(email) / sizeof(wchar_t) - 1);
            }


            wprintf(L"Születési dátum: ");
            if (fgets(inputBuff, sizeof(inputBuff), stdin) != NULL) {
                inputBuff[strcspn(inputBuff, "\n")] = '\0';

                mbstowcs(szul, inputBuff, sizeof(szul) / sizeof(wchar_t) - 1);
            }

            wchar_t *catStr = (wchar_t*) calloc(wcslen(name) + wcslen(email) + wcslen(szul) + 1, sizeof(wchar_t));
            if (!catStr) return;

            wcscpy(catStr, name); wcscat(catStr, email); wcscat(catStr, szul);
            uint32_t const hash = FNV1a(catStr);
            uint32_t const index = hash % ht->size;

            free(catStr);

            Alkalmazott *current = ht->buckets[index];
            Alkalmazott *prev = NULL;
            bool found = false;

            while (current != NULL) {
                if (wcscmp(current->szemelyes_adatok->nev, name) == 0 &&
                    wcscmp(current->szemelyes_adatok->email, email) == 0 &&
                    wcscmp(current->szemelyes_adatok->szul_datum, szul) == 0) {
                    if (prev == NULL) {
                        ht->buckets[index] = current->kov;
                    } else {
                        prev->kov = current->kov;
                    }

                    freeNode(current);
                    found = true;
                    wprintf(L"✓ Sikeres törlés!\n");
                    break;
                }
                prev = current;
                current = current->kov;
            }
            if (!found) {
                wprintf(L"⚠ Nem található ilyen elem a táblában.\n");
            }

        }
    }
}