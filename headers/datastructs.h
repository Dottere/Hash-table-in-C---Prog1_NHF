//
// Created by lin on 11/7/25.
//

#ifndef PROGRAMMING1_NAGYHF_DATASTRUCTS_H
#define PROGRAMMING1_NAGYHF_DATASTRUCTS_H


#include <stddef.h>
#include <stdint.h>

typedef struct {
    wchar_t id[16];
    wchar_t nev[64];
    wchar_t szul_datum[24]; // (YYYY-MM-DD)
    wchar_t nem[16];
    wchar_t lakhely[64];
    wchar_t email[64];
    wchar_t telefon[20];
    wchar_t szemelyi_szam[16];
} SzemelyesAdat;

typedef struct {
    wchar_t beosztas[64];
    wchar_t reszleg[64];
    wchar_t felettes[64];
    wchar_t munkakezdet[24];
    wchar_t munkavege[24];
    wchar_t munkarend[32];
} MunkaAdat;

typedef struct {
    wchar_t bankszamla[128];
    wchar_t fizetes[32];
} PenzugyiAdat;

typedef struct Alkalmazott {
    SzemelyesAdat *szemelyes_adatok;
    MunkaAdat *munka_adatok;
    PenzugyiAdat *penzugyi_adatok;
    struct Alkalmazott *kov; // láncolt lista miatt
    uint32_t storedHash;
} Alkalmazott;

typedef struct HashTable {
    Alkalmazott **buckets;
    size_t size;
} HashTable;
#endif //PROGRAMMING1_NAGYHF_DATASTRUCTS_H