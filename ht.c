//
// Created by lin on 11/7/25.
//

#include "headers/ht.h"

/**
 * @brief Létrehoz egy Hash-Táblát amellyel képes a htinsert() függvény dolgozni
 *
 * Ez a program csak fix méretű Hash-Táblákkal tud dolgozni, ezért szükséges egy kezdeti méret
 * megadása amely változatlan marad a futam végéig.
 *
 * @param initSize A Hash-Tábla mérete.
 * @return Egy pointert ad vissza a létrehozott Hash-Táblához.
 * @note Kapcsolódó függvények: htinsert(), htfree()
 */
HashTable *htcreate(int initSize) {
    HashTable *ht = (HashTable*) malloc(sizeof(HashTable));

    if (!ht) {
        perror("Couldn't allocate memory for hash table");
        return NULL;
    }

    ht->buckets = (Alkalmazott**) calloc(initSize, sizeof(Alkalmazott*));

    if (!ht->buckets) {
        perror("Couldn't allocate memory for this many buckets in hash table.");
        return NULL;
    }

    ht->size = initSize;

    return ht;
}

/**
 * @brief Beszúrja egy láncolt lista elemeit a bekért Hash-Táblába
 *
 * Végigmegy a láncolt lista elemein egyesével, mindegyikből csinál egy hasht a név, e-mail cím, és születési dátum
 * felhasználásával, majd veszi a beadott Hash-Tábla méretét és azzal maradékosan leosztva a Hash-t megkapja, hogy melyik
 * indexre kell beszúrni a kért elemet. Abban az esetben, ha ütközés történik, akkor a vödrökön belül láncolja az elemeket.
 *
 * @param ht Egy pointer a Hash-Táblára amelybe beszúrni kívánunk.
 * @param linkedListHead Egy pointer egy láncolt lista első pointerjére, amelynek az elemeit beszúrni kívánjuk.
 * @return 0 Minden rendben.
 * @return -1 Láncolt lista mérete nagyobb mint a Hash-Tábla mérete.
 * @return -2 Nem sikerült a kulcsot felépíteni a név, e-mail cím és születési dátum kombinációjából.
 * @return -3 Nem sikerült egy új Alkalmazott elemet foglalni, amely szükséges a Hash-Táblába való beszúráshoz.
 * @return -4 Nem sikerült az új Alkalmazott struktúra összes elemének memóriát foglalni.
 * @return -5 Valamely a két paraméter közül NULL.
 *
 * @note Az eredeti láncolt lista érintetlen marad.
 * @note Kapcsolódó függvények: htcreate(), htfree()
 *
 */
int htinsert(HashTable const *ht, Alkalmazott **linkedListHead) {
    if (!ht || !linkedListHead || !*linkedListHead) return -5;
    if (linkedListLen(linkedListHead)>ht->size) return -1;

    Alkalmazott const *iter = *linkedListHead;
    while (iter) {
        wchar_t const *nev = iter->szemelyes_adatok->nev;
        ulong const nevLen = wcslen(nev);

        wchar_t const *email = iter->szemelyes_adatok->email;
        ulong const emailLen = wcslen(email);

        wchar_t const *szul = iter->szemelyes_adatok->szul_datum;
        ulong const szulLen = wcslen(szul);

        wchar_t *catStr = (wchar_t*) calloc((nevLen+emailLen+szulLen+1), sizeof(wchar_t));
        if (!catStr) return -2;

        wcscpy(catStr, nev);
        wcscat(catStr, email);
        wcscat(catStr, szul);

        uint32_t const hash = FNV1a(catStr);
        uint32_t const index = hash % ht->size;

        Alkalmazott *newNode = (Alkalmazott*) malloc(sizeof(Alkalmazott));
        if (!newNode) {
            free(catStr);
            return -3;
        }

        newNode->szemelyes_adatok = (SzemelyesAdat*) malloc(sizeof(SzemelyesAdat));
        newNode->munka_adatok = (MunkaAdat*) malloc(sizeof(MunkaAdat));
        newNode->penzugyi_adatok = (PenzugyiAdat*) malloc(sizeof(PenzugyiAdat));

        if (!newNode->szemelyes_adatok || !newNode->munka_adatok || !newNode->penzugyi_adatok) {
            free(catStr);
            free(newNode->szemelyes_adatok);
            free(newNode->munka_adatok);
            free(newNode->penzugyi_adatok);
            free(newNode);
            return -4;
        }

        memcpy(newNode->szemelyes_adatok, iter->szemelyes_adatok, sizeof(SzemelyesAdat));
        memcpy(newNode->munka_adatok, iter->munka_adatok, sizeof(MunkaAdat));
        memcpy(newNode->penzugyi_adatok, iter->penzugyi_adatok, sizeof(PenzugyiAdat));

        newNode->kov = ht->buckets[index];
        ht->buckets[index] = newNode;

        free(catStr);
        iter = iter->kov;
    }

    return 0;
}

/**
 * @brief Kiíratja a hash tábla összes elemét
 *
 * Végigmegy a hash tábla összes vödrén és kiírja az ott tárolt
 * alkalmazottakat. Ütközés esetén a láncolt lista elemeit '->' jellel
 * elválasztva jeleníti meg.
 *
 * @param ht Pointer a kiíratni kívánt HashTable struktúrára
 * @return Nincs visszatérési érték
 *
 * @note A kimenet a standard kimenetre (stdout) kerül
 * @warning Ha ht NULL akkor nem csinál semmit.
 *
 * Példa kimenet:
 * @code
 * Bucket[0]: elem1 -> elem2
 * Bucket[2]: elem3
 * @endcode
 */
void printHashTable(HashTable const *ht) {
    if (!ht) return;
    wprintf(L"\n=== Hash-Tábla tartalma ===\n");
    for (size_t i = 0; i < ht->size; i++) {
        if (ht->buckets[i] != NULL) {
            wprintf(L"Bucket[%zu]: ", i);
            Alkalmazott *iter = ht->buckets[i];
            int count = 0;
            while (iter) {
                if (count > 0) wprintf(L" -> ");
                wprintf(L"%ls", iter->szemelyes_adatok->nev);
                iter = iter->kov;
                count++;
            }
            wprintf(L" (összesen: %d elem)\n", count);
        }
    }
    wprintf(L"========================\n\n");
}

/**
 * @brief Felszabadítja a Hash Tábla által foglalt memóriát.
 *
 * Végigmegy az összes vödrön és felszabadítja először a bennük tárolt adatokat, magukat a vödröket, és végül a Hash-Táblát
 *
 * @param ht Pointer a felszabadítani kívánt ht struktúrára
 * @return Nincs visszatérési érték
 * @warning Ha ht NULL akkor nem csinál semmit, hibakódot sem jelez.
 * @note Kapcsolódó függvények: htcreate), htinsert()
 */
void htfree(HashTable *ht) {
    if (!ht) return;

    // Minden bucket bejárása
    for (size_t i = 0; i < ht->size; i++) {
        Alkalmazott *current = ht->buckets[i];

        // Láncolt lista felszabadítása a bucket-ben
        while (current) {
            Alkalmazott *next = current->kov;

            // Belső struktúrák felszabadítása
            free(current->szemelyes_adatok);
            free(current->munka_adatok);
            free(current->penzugyi_adatok);
            free(current);

            current = next;
        }
    }

    // Buckets tömb felszabadítása
    free(ht->buckets);

    // HashTable felszabadítása
    free(ht);
}