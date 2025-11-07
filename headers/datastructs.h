//
// Created by lin on 11/7/25.
//

#ifndef PROGRAMMING1_NAGYHF_DATASTRUCTS_H
#define PROGRAMMING1_NAGYHF_DATASTRUCTS_H

typedef struct {
    char id[16];
    char nev[64];
    char szul_datum[11]; // (YYYY-MM-DD)
    char nem[6];
    char lakhely[64];
    char email[64];
    char telefon[20];
    char szemelyi_szam[12];
} SzemelyesAdat;

typedef struct {
    char beosztas[64];
    char reszleg[64];
    char felettes[64];
    char munkakezdet[11];
    char munkavege[11];
    char munkarend[32];
} MunkaAdat;

typedef struct {
    char bankszamla[34];
    double fizetes;
} PenzugyiAdat;

typedef struct Alkalmazott {
    SzemelyesAdat *szemelyes_adatok;
    MunkaAdat *munka_adatok;
    PenzugyiAdat *penzugyi_adatok;
    struct Alkalmazott *kov; // láncolt lista miatt
} Alkalmazott;

#endif //PROGRAMMING1_NAGYHF_DATASTRUCTS_H