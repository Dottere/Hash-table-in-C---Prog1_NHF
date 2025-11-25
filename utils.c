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
        printf("Már történt beolvasás \"%s\" fájlból. Szeretnéd felülírni?\n[i] - igen\n[n] - nem\nVálasz: ", path);
        if (!fgets(choice, sizeof(choice), stdin)) return false;

        if (choice[0] == 'n' || choice[0] == 'N') return false;
        if (choice[0] == 'i' || choice[0] == 'I') return true;

        wprintf(L"Érvénytelen választás.\n");
    }
}

void howToModify(HashTable *ht, char const *path) {
    char choice[16];
    while (true) {
        wprintf(L"#Módosítás#\n");
        wprintf(L"1. Hozzáadás\n2.Törlés\n3.Mégsem\nVálasztás:");
        if (!fgets(choice, sizeof(choice), stdin)) return;

        if (choice[0] == '1') {
            wprintf(L"Hány elemet szeretnél hozzáadni?\n1.Egyet manuálisan\n2.Többet fájlból\n3.Mégsem\nVálasztás: ");
            if (!fgets(choice, sizeof(choice), stdin)) return;

            if (choice[0] == '1') {
                Alkalmazott *ujEmber = readFromInput();

                if (ujEmber) {
                    ujEmber->kov = NULL;

                    int const res = htinsert(ht, &ujEmber);

                    if (res == 0) wprintf(L"✓ Sikeresen hozzáadva!\n");
                    else wprintf(L"✗ Hiba a beszúrásnál! Hibakód: %d\n", res);

                    freeNode(ujEmber);
                }
            }
            else if (choice[0] == '2') {
                wprintf(L"Az új fájl elérési útja: ");
                char *newPath = readPath();

                while (!pathExists(newPath)){
                    printf("Nem létező fájl:\"%s\"\nÚjra: ", newPath);
                    free(newPath);
                    newPath = readPath();
                }

                if (path && strcmp(path, newPath) == 0) {
                    wprintf(L"Nem szúrhatod be ugyanazt a listát kétszer!");
                    free(newPath);
                    continue;
                }

                Alkalmazott *ujLista = readFromCSV(newPath);
                free(newPath);

                if (ujLista) {
                    int const result = htinsert(ht, &ujLista);
                    if (result == 0) wprintf(L"Elem sikeresen beszúrva!");
                    else wprintf(L"✗ Beszúrás az új listába sikertelen! Hibakód: %d\n", result);
                    linkedListFree(&ujLista);
                } else {
                    wprintf(L"Hiba, nem sikerült beolvasni a fájlt!");
                }
            }
        }
        else if (choice[0] == '2') {
            Alkalmazott *dummy = (Alkalmazott*) calloc(1, sizeof(Alkalmazott));
            dummy->szemelyes_adatok = (SzemelyesAdat*) calloc(1, sizeof(SzemelyesAdat));

            char inputBuff[256];

            wprintf(L"Ahhoz, hogy törölj a táblából szükségünk van három dologra:\n");

            wprintf(L"Név: ");
            if (fgets(inputBuff, sizeof(inputBuff), stdin) != NULL) {
                inputBuff[strcspn(inputBuff, "\n")] = '\0';

                mbstowcs(dummy->szemelyes_adatok->nev, inputBuff, 63);
            }

            wprintf(L"E-mail cím: ");
            if (fgets(inputBuff, sizeof(inputBuff), stdin) != NULL) {
                inputBuff[strcspn(inputBuff, "\n")] = '\0';

                mbstowcs(dummy->szemelyes_adatok->email, inputBuff, 63);
            }


            wprintf(L"Születési dátum: ");
            if (fgets(inputBuff, sizeof(inputBuff), stdin) != NULL) {
                inputBuff[strcspn(inputBuff, "\n")] = '\0';

                mbstowcs(dummy->szemelyes_adatok->szul_datum, inputBuff, 23);
            }

            if (htdelete(ht, dummy)==0) {
                wprintf(L"Sikeres törlés!");
            }
            else {
                wprintf(L"Nem található a listában a megadott elem!");
            }

            free(dummy->szemelyes_adatok);
            free(dummy);

        } else if (choice[0] == '3')
            return;
    }
}