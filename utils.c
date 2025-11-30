//
// Created by lin on 11/24/25.
//

#include "headers/utils.h"
#include "headers/datastructs.h"
#include "headers/linkedlist.h"
#include "headers/io.h"
#include "headers/debugmalloc.h"

#include <wchar.h>
#include <stdbool.h>

void printHelp(void) {
    wprintf(L"A program mely funkcionalitását szeretnéd használni?\n");
    wprintf(L"0. Kiírja újra ezt a segítséget.\n");
    wprintf(L"1. Beolvasás CSV fájlból.\n");
    wprintf(L"2. Keresés a Hash-Táblában\n");
    wprintf(L"3. Hash-Tábla kilistázása.\n");
    wprintf(L"4. Ütközések tesztelése.\n");
    wprintf(L"5. Hash-Tábla módosítása.\n");
    wprintf(L"6. Kiírás CSV fájlba.\n");
    wprintf(L"7. Kilép.\n");
}


int readingFromFile(HashTable **ht, char **path) {
    wprintf(L"A beolvasást választottad! Kérlek add meg a beolvasandó fájl elérési útvonalát: ");
    *path = readPath();
    if (!pathExists(*path)){
        wprintf(L"Ilyen elérési út nem létezik:\"%s\"\n", *path);
        free(*path);
        return -1;
    }

    wprintf(L"Beolvasás CSV-ből láncolt listába...\n");
    Alkalmazott *linkedList = readFromCSV(*path);

    if (!linkedList) {
        wprintf(L"Hiba történt az adatok beolvasásakor, a láncolt lista nem jött létre. A program kilép");
        free(*path);
        *path=NULL;
        return -1;
    }

    wprintf(L"Hash-Tábla létrehozása %d elemszámmal...\n", linkedListLen(&linkedList));
    *ht = htcreate(linkedListLen(&linkedList));
    if (!*ht) {
        wprintf(L"Nem sikerült a Hash-Táblának memóriát foglalni. A program kilép.");
        free(*path);
        return -1;
    }

    wprintf(L"Beszúrás a Hash-Táblába...\n");
    int const result = htinsert(*ht, &linkedList);

    if (result != 0) {
        wprintf(L"✗ Beszúrás sikertelen! Hibakód: %d\n", result);
        free(*path);
        *path = NULL;
        htfree(*ht);
        linkedListFree(&linkedList);
        *ht = NULL;
        linkedList = NULL;
        return -1;
    }

    linkedListFree(&linkedList);
    return 0;
}


void searchInHashTable(HashTable **ht) {
    Alkalmazott *target = (Alkalmazott*) calloc(1, sizeof(Alkalmazott));
    target->szemelyes_adatok = (SzemelyesAdat*) calloc(1, sizeof(SzemelyesAdat));
    target->munka_adatok = NULL;
    target->penzugyi_adatok = NULL;
    target->kov = NULL;
    target->storedHash = 0;

    wprintf(L"Ahhoz, hogy egy specifikus személyt megtalálj szükséged van három dologra:\n");

    readFromInputHelper(L"ID:", target->szemelyes_adatok->id, 16);
    readFromInputHelper(L"E-Mail:", target->szemelyes_adatok->email, 64);
    readFromInputHelper(L"Születési dátum:", target->szemelyes_adatok->szul_datum, 24);

    htfind(*ht, target);


    free(target->szemelyes_adatok);
    free(target);
}


void statistics(HashTable const *ht) {
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
        wprintf(L"A fájl (\"%hs\") már létezik...\n Szeretnéd felülírni?\n1. Igen\n2. Nem\nVálasz: ", path);
        if (!fgets(choice, sizeof(choice), stdin)) return false;

        if (choice[0] == '1') return true;
        if (choice[0] == '2') return false;

        wprintf(L"Érvénytelen választás.\n");
    }
}


void howToModify(HashTable *ht, char const *path) {
    char choice[16];
    while (true) {
        wprintf(L"\n--- Módosítás Menü ---\n");
        wprintf(L"1. Hozzáadás\n2. Törlés\n3. Módosítás\n4. Vissza\nVálasztás: ");
        if (!fgets(choice, sizeof(choice), stdin)) return;

        // Hozzáadás
        if (choice[0] == '1') {
            addLogic(ht, path, choice);
        }
        // Törlés
        else if (choice[0] == '2') {
            delLogic(ht);
        }
        // Módosítás
        else if (choice[0] == '3') {
            updateLogic(ht, choice);
        }
        // Mégse
        else if (choice[0] == '4') {
            return;
        }
    }
}


void addLogic(HashTable *ht, char const *path, char *choice) {
    wprintf(L"Hány elemet szeretnél hozzáadni?\n1.Egyet manuálisan\n2.Többet fájlból\n3.Mégsem\nVálasztás: ");

    if (!fgets(choice, 16, stdin)) return;
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

        if (!pathExists(newPath)){
            wprintf(L"Nem létező fájl:\"%hs\"\nÚjra: ", newPath);
            free(newPath);
            return;
        }

        if (path && strcmp(path, newPath) == 0) {
            wprintf(L"Nem szúrhatod be ugyanazt a listát kétszer!");
            free(newPath);
            return;
        }

        Alkalmazott *ujLista = readFromCSV(newPath);

        free(newPath);

        if (ujLista) {
            int const result = htinsert(ht, &ujLista);

            if (result == 0) wprintf(L"Elem sikeresen beszúrva!");
            else wprintf(L"✗ Beszúrás az új listába sikertelen! Hibakód: %d\n", result);

            linkedListFree(&ujLista);
        }
        else
            wprintf(L"Hiba, nem sikerült beolvasni a fájlt!");
    }
}


void delLogic(HashTable *ht) {
    Alkalmazott *temp = (Alkalmazott*) calloc(1, sizeof(Alkalmazott));
    temp->szemelyes_adatok = (SzemelyesAdat*) calloc(1, sizeof(SzemelyesAdat));

    wprintf(L"Ahhoz, hogy törölj a táblából szükségünk van három dologra:\n");

    readFromInputHelper(L"ID: ", temp->szemelyes_adatok->id, 16);
    readFromInputHelper(L"E-Mail: ", temp->szemelyes_adatok->email, 64);
    readFromInputHelper(L"Születési dátum: ", temp->szemelyes_adatok->szul_datum, 24);

    if (htdelete(ht, temp)==0)
        wprintf(L"Sikeres törlés!");
    else
        wprintf(L"Nem található a listában a megadott elem!");


    free(temp->szemelyes_adatok);
    free(temp);
}


void updateLogic(HashTable *ht, char *choice) {
    Alkalmazott *temp = (Alkalmazott*) calloc(1, sizeof(Alkalmazott));
    temp->szemelyes_adatok = (SzemelyesAdat*) calloc(1, sizeof(SzemelyesAdat));

    wprintf(L"\n--- Módosítás ---\nKinek az adatait szeretnéd módosítani? (Azonosítók)\n");

    readFromInputHelper(L"ID: ", temp->szemelyes_adatok->id, 16);
    readFromInputHelper(L"E-Mail: ", temp->szemelyes_adatok->email, 64);
    readFromInputHelper(L"Születési dátum: ", temp->szemelyes_adatok->szul_datum, 24);

    if (!htfind(ht, temp)) {
        freeNode(temp);
        return;
    }

    wprintf(L"\nMit szeretnél módosítani?\n");
    wprintf(L"1. Név\n2. Születési dátum [KULCS]\n3. ID [KULCS]\n4. Nem\n");
    wprintf(L"5. Lakhely\n6. E-mail [KULCS]\n7. Telefon\n8. Személyi szám\n");
    wprintf(L"9. Beosztás\n10. Részleg\n11. Felettes\n12. Munkakezdet\n");
    wprintf(L"13. Munkavége\n14. Munkarend\n15. Bankszámlaszám\n16. Fizetés\n");
    wprintf(L"Választás (szám): ");
    if (!fgets(choice, 16, stdin)) { freeNode(temp); return; }

    int const fieldType = (int) strtol(choice, NULL, 10);
    if (fieldType < 1 || fieldType > 16) {
        wprintf(L"Érvénytelen mező!\n");
        freeNode(temp);
        return;
    }

    wchar_t newValue[128];
    readFromInputHelper(L"Új érték: ", newValue, 128);

    if (htupdate(ht, temp, fieldType, newValue)) {
        wprintf(L"✓ Sikeres módosítás!\n");
    } else {
        wprintf(L"✗ Hiba! Sikertelen módosítás.\n");
    }

    freeNode(temp);
}


void writeToFile(HashTable **ht) {
    wprintf(L"Add meg a célfájl elérési útját! (pl export.csv): ");
    char *outPath = readPath();

    if (pathExists(outPath)) {
        if (!confirmOverwrite(outPath)) {
            free(outPath);
            wprintf(L"A kiírás megszakítva!\n");
            return;
        }
    }

    wprintf(L"Fájl írása: %s ...\n", outPath);

    int const writeRes = writeToCSV(*ht, outPath);

    if (writeRes == 0) {
        wprintf(L"Sikeres kiírás!\n");
    } else {
        wprintf(L"Hiba történt a fájl írásakor! Hibakód: %d\n", writeRes);
    }
    free(outPath);
}

int readMenuChoice(void) {
    char choice[16];
    wprintf(L"\nVálasztás: ");
    if (!fgets(choice, sizeof(choice), stdin)) {
        return -1;
    }

    choice[strcspn(choice, "\n")] = '\0';

    if (strlen(choice) == 0) return -1;

    char *endptr;
    long const val = strtol(choice, &endptr, 10);

    if (choice == endptr) return -1;

    return (int)val;
}

void handleLoadOption(HashTable **ht, char **path) {
    if (*ht) {
        if (!confirmOverwrite(*path)) return;
        free(*path);
        *path = NULL;
        htfree(*ht);
        *ht = NULL;
    }

    int const res = readingFromFile(ht, path);
    if (res == 0)
        wprintf(L"✓ Beszúrás sikeres!\n");
}

bool ensureTableExists(HashTable *ht) {
    if (!ht) {
        wprintf(L"Nincs beolvasva HashTábla, nem lehet adatot kiírni/módosítani! (Használd az 1-es gombot)\n");
        return false;
    }
    return true;
}

bool confirmExit(void) {
    wprintf(L"\nBiztosan ki akarsz lépni?\n1. Igen\n2. Nem\nVálasztás: ");

    char choice[16];
    if (!fgets(choice, sizeof(choice), stdin)) return false;

    if (choice[0] == '1') {
        wprintf(L"A program kilép.\n");
        return true;
    }

    return false;
}