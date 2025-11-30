//
// Created by lin on 11/7/25.
//

#include "headers/ht.h"

#include <threads.h>


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


int htinsert(HashTable *ht, Alkalmazott **linkedListHead) {
    if (!ht || !linkedListHead || !*linkedListHead) return -5;
    while (linkedListLen(linkedListHead)>ht->size) {
        int const res = htresize(ht);
        if (res != 0) {
            return -1;
        }
    }

    Alkalmazott *iter = *linkedListHead;
    while (iter) {
        uint32_t const hash = calculateHash(iter);
        if (hash == 0) return -2;
        uint32_t const index = hash % ht->size;


        iter->storedHash = hash;

        Alkalmazott *newNode = (Alkalmazott*) malloc(sizeof(Alkalmazott));
        if (!newNode) {
            return -3;
        }

        newNode->storedHash = hash;
        newNode->szemelyes_adatok = (SzemelyesAdat*) malloc(sizeof(SzemelyesAdat));
        newNode->munka_adatok = (MunkaAdat*) malloc(sizeof(MunkaAdat));
        newNode->penzugyi_adatok = (PenzugyiAdat*) malloc(sizeof(PenzugyiAdat));

        if (!newNode->szemelyes_adatok || !newNode->munka_adatok || !newNode->penzugyi_adatok) {
            free(newNode->szemelyes_adatok);
            free(newNode->munka_adatok);
            free(newNode->penzugyi_adatok);
            free(newNode);
            return -4;
        }

        memcpy(newNode->szemelyes_adatok, iter->szemelyes_adatok, sizeof(SzemelyesAdat));
        memcpy(newNode->munka_adatok, iter->munka_adatok, sizeof(MunkaAdat));
        memcpy(newNode->penzugyi_adatok, iter->penzugyi_adatok, sizeof(PenzugyiAdat));

        newNode->kov = NULL;

        if (ht->buckets[index] == NULL) {

            ht->buckets[index] = newNode;
        } else {

            Alkalmazott *current = ht->buckets[index];
            while (current->kov != NULL) {
                current = current->kov;
            }

            current->kov = newNode;
        }

        iter = iter->kov;
    }

    return 0;
}


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


void htfree(HashTable *ht) {
    if (!ht) return;

    // Minden bucket bejárása
    for (size_t i = 0; i < ht->size; i++) {
        Alkalmazott *current = ht->buckets[i];

        // Láncolt lista felszabadítása a bucket-ben
        while (current) {
            Alkalmazott *next = current->kov;

            // Belső struktúrák felszabadítása
            freeNode(current);

            current = next;
        }
    }

    // Buckets tömb felszabadítása
    free(ht->buckets);

    // HashTable felszabadítása
    free(ht);
}


int htresize(HashTable *ht) {
    size_t const oldSize = ht->size;
    size_t const newSize = oldSize * 2;

    Alkalmazott **new_buckets = (Alkalmazott**) calloc(newSize, sizeof(Alkalmazott*));

    if (!new_buckets)
        return -1;

    for (size_t i = 0; i < oldSize; i++) {
        Alkalmazott *current = ht->buckets[i];

        while (current != NULL) {
            Alkalmazott *next = current->kov;

            uint32_t const newHash = current->storedHash;
            uint32_t const newIndex = newHash % newSize;

            current->kov = new_buckets[newIndex];
            new_buckets[newIndex] = current;

            current = next;

        }
    }

    free(ht->buckets);

    ht->buckets = new_buckets;
    ht->size = newSize;
    return 0;
}


uint32_t calculateHash(Alkalmazott const *alkalmazott) {
    wchar_t const *email = alkalmazott->szemelyes_adatok->email;
    wchar_t const *szul = alkalmazott->szemelyes_adatok->szul_datum;
    wchar_t const *id = alkalmazott->szemelyes_adatok->id;

    size_t const len = wcslen(email) + 1 + wcslen(szul) + 1 + wcslen(id) + 1;
    wchar_t *catStr = (wchar_t*) calloc(len, sizeof(wchar_t));
    if (!catStr) return 0;

    wcscpy(catStr, email);
    wcscat(catStr, L" ");
    wcscat(catStr, szul);
    wcscat(catStr, L" ");
    wcscat(catStr, id);

    uint32_t const hash = FNV1a(catStr);
    free(catStr);
    return hash;
}


int htdelete(HashTable *ht, Alkalmazott const *target) {
    if (!ht || !target) return -1;

    uint32_t const hash = calculateHash(target);
    if (hash==0) return -1;

    uint32_t const index = hash % ht->size;

    Alkalmazott *current = ht->buckets[index];
    Alkalmazott *prev = NULL;

    while (current != NULL) {
        if (wcscmp(current->szemelyes_adatok->id, target->szemelyes_adatok->id) == 0 &&
                wcscmp(current->szemelyes_adatok->email, target->szemelyes_adatok->email) == 0 &&
                wcscmp(current->szemelyes_adatok->szul_datum, target->szemelyes_adatok->szul_datum) == 0) {


            if (prev == NULL) {
                ht->buckets[index] = current->kov;
            } else {
                prev->kov = current->kov;
            }


            free(current->szemelyes_adatok);
            free(current->munka_adatok);
            free(current->penzugyi_adatok);
            free(current);
            return 0;
                }

        prev = current;
        current = current->kov;
    }
    return -1;
}


bool htfind(HashTable const *ht, Alkalmazott const *target) {

    uint32_t const hash = calculateHash(target);

    if (hash) {
        size_t const index = hash % ht->size;

        Alkalmazott const *iter = ht->buckets[index];

        while (iter != NULL) {

            if (wcscmp(iter->szemelyes_adatok->id, target->szemelyes_adatok->id) == 0 &&
                wcscmp(iter->szemelyes_adatok->email, target->szemelyes_adatok->email) == 0 &&
                wcscmp(iter->szemelyes_adatok->szul_datum, target->szemelyes_adatok->szul_datum) == 0) {

                SzemelyesAdat *sz = iter->szemelyes_adatok;
                MunkaAdat *m      = iter->munka_adatok;
                PenzugyiAdat *p   = iter->penzugyi_adatok;

                wprintf(L"A keresett személy megtalálva!\n"
                        "ID: %ls\nNév: %ls\nSzületési dátum: %ls\nNem: %ls\nLakhely: %ls\nE-Mail: %ls\n"
                        "Telefon: %ls\nSzemélyi szám: %ls\nBeosztás: %ls\nRészleg: %ls\nFelettes: %ls\nMunkakezdet: %ls\n"
                        "Munkavége: %ls\nMunkarend: %ls\nBankszámlaszám: %ls\nFizetés: %ls\n",
                        sz->id, sz->nev, sz->szul_datum, sz->nem, sz->lakhely, sz->email, sz->telefon, sz->szemelyi_szam,
                        m->beosztas, m->reszleg, m->felettes, m->munkakezdet, m->munkavege, m->munkarend,
                        p->bankszamla, p->fizetes);
                return true;
            }

            iter = iter->kov;
        }

    }
    wprintf(L"A keresett személy nem található.\n");
    return false;
}


bool htupdate(HashTable *ht, Alkalmazott *target, int const fieldType, wchar_t const *newValue) {
    if (!ht || !target) return false;

    Alkalmazott *foundNode = inHt(ht, target);

    if (!foundNode) return false;

    if (fieldType == 2 || fieldType == 3 || fieldType == 6) {
        Alkalmazott *tempCopy = (Alkalmazott*)malloc(sizeof(Alkalmazott));
        if (!tempCopy) return false;

        tempCopy->szemelyes_adatok = (SzemelyesAdat*) malloc(sizeof(SzemelyesAdat));
        tempCopy->munka_adatok     = (MunkaAdat*) malloc(sizeof(MunkaAdat));
        tempCopy->penzugyi_adatok  = (PenzugyiAdat*) malloc(sizeof(PenzugyiAdat));

        if (!tempCopy->szemelyes_adatok || !tempCopy->munka_adatok || !tempCopy->penzugyi_adatok) {
            freeNode(tempCopy);
            return false;
        }

        *tempCopy->szemelyes_adatok = *foundNode->szemelyes_adatok;
        *tempCopy->munka_adatok     = *foundNode->munka_adatok;
        *tempCopy->penzugyi_adatok  = *foundNode->penzugyi_adatok;
        tempCopy->kov               = NULL;

        if (fieldType == 2) wcscpy(tempCopy->szemelyes_adatok->szul_datum, newValue);
        else if (fieldType == 3) wcscpy(tempCopy->szemelyes_adatok->id, newValue);
        else wcscpy(tempCopy->szemelyes_adatok->email, newValue);

        htdelete(ht, target);
        htinsert(ht, &tempCopy);

        freeNode(tempCopy);
    }

    else {
        switch (fieldType) {
            case 1: wcscpy(foundNode->szemelyes_adatok->nev, newValue); break;
            case 4: wcscpy(foundNode->szemelyes_adatok->nem, newValue); break;
            case 5: wcscpy(foundNode->szemelyes_adatok->lakhely, newValue); break;
            case 7: wcscpy(foundNode->szemelyes_adatok->telefon, newValue); break;
            case 8: wcscpy(foundNode->szemelyes_adatok->szemelyi_szam, newValue); break;

            case 9: wcscpy(foundNode->munka_adatok->beosztas, newValue); break;
            case 10: wcscpy(foundNode->munka_adatok->reszleg, newValue); break;
            case 11: wcscpy(foundNode->munka_adatok->felettes, newValue); break;
            case 12: wcscpy(foundNode->munka_adatok->munkakezdet, newValue); break;
            case 13: wcscpy(foundNode->munka_adatok->munkavege, newValue); break;
            case 14: wcscpy(foundNode->munka_adatok->munkarend, newValue); break;

            case 15: wcscpy(foundNode->penzugyi_adatok->bankszamla, newValue); break;
            case 16: wcscpy(foundNode->penzugyi_adatok->fizetes, newValue); break;
            default: return false;
        }
    }

    return true;
}


Alkalmazott *inHt(HashTable const *ht, Alkalmazott const *target) {
    uint32_t const hash = calculateHash(target);
    size_t const index = hash % ht->size;
    Alkalmazott *iter = ht->buckets[index];
    Alkalmazott *foundNode = NULL;

    while (iter) {
        if (wcscmp(iter->szemelyes_adatok->email, target->szemelyes_adatok->email)           == 0 &&
            wcscmp(iter->szemelyes_adatok->id, target->szemelyes_adatok->id)                 == 0 &&
            wcscmp(iter->szemelyes_adatok->szul_datum, target->szemelyes_adatok->szul_datum) == 0) {
            foundNode = iter;
            break;
            }
        iter = iter->kov;
    }

    if (!foundNode) return NULL;
    return foundNode;
}