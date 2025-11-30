//
// Created by lin on 11/10/25.
//

#include "headers/io.h"
#include "headers/debugmalloc.h"
#include "headers/linkedlist.h"

#include <wchar.h>

#define READ_FILE(cursor, dest) readFromCSVHelper(&cursor, dest, sizeof(dest)/sizeof(wchar_t))
#define READ_INPUT(prompt, dest) readFromInputHelper(prompt, dest, sizeof(dest)/sizeof(wchar_t))



Alkalmazott *readFromCSV(char const *filePath) {
    FILE *fp = fopen(filePath, "r");
    if (!fp) {
        perror("Failed to open file");
        return NULL;
    }

    Alkalmazott *linkedList = NULL;
    char buff[1024];

    if (!fgets(buff, sizeof(buff), fp)) { fclose(fp); return NULL; }

    if (!fgets(buff, sizeof(buff), fp)) { fclose(fp); return NULL; }

    do {
        buff[strcspn(buff, "\r\n")] = '\0';

        Alkalmazott *line = (Alkalmazott *) calloc(1, sizeof(Alkalmazott));
        if (!line) { perror("Memory allocation failed"); break; }

        line->szemelyes_adatok = (SzemelyesAdat *) calloc(1, sizeof(SzemelyesAdat));
        line->munka_adatok     = (MunkaAdat *)     calloc(1, sizeof(MunkaAdat));
        line->penzugyi_adatok  = (PenzugyiAdat *)  calloc(1, sizeof(PenzugyiAdat));

        if (!line->szemelyes_adatok || !line->munka_adatok || !line->penzugyi_adatok) {
            perror("Memory allocation failed");
            free(line->szemelyes_adatok);
            free(line->munka_adatok);
            free(line->penzugyi_adatok);
            free(line);
            break;
        }

        char *cursor = buff;

        READ_FILE(cursor, line->szemelyes_adatok->id);
        READ_FILE(cursor, line->szemelyes_adatok->nev);
        READ_FILE(cursor, line->szemelyes_adatok->szul_datum);
        READ_FILE(cursor, line->szemelyes_adatok->nev);
        READ_FILE(cursor, line->szemelyes_adatok->lakhely);
        READ_FILE(cursor, line->szemelyes_adatok->email);
        READ_FILE(cursor, line->szemelyes_adatok->telefon);
        READ_FILE(cursor, line->szemelyes_adatok->szemelyi_szam);
        READ_FILE(cursor, line->munka_adatok->beosztas);
        READ_FILE(cursor, line->munka_adatok->reszleg);
        READ_FILE(cursor, line->munka_adatok->felettes);
        READ_FILE(cursor, line->munka_adatok->munkakezdet);
        READ_FILE(cursor, line->munka_adatok->munkavege);
        READ_FILE(cursor, line->munka_adatok->munkarend);
        READ_FILE(cursor, line->penzugyi_adatok->bankszamla);
        READ_FILE(cursor, line->penzugyi_adatok->fizetes);

        linkedListAppend(&linkedList, line);

    } while (fgets(buff, sizeof(buff), fp));

    fclose(fp);
    return linkedList;
}

void readFromCSVHelper(char **input_cursor, wchar_t *dest, size_t const destSize) {
    char const *token = strtok(*input_cursor, ",");

    *input_cursor = NULL;

    if (token) {
        mbstowcs(dest, token, destSize - 1);
        dest[destSize - 1] = L'\0';
    }
}

char *readPath(void) {
    fflush(stdout);

    size_t size = 128;
    size_t len = 0;
    char *buff = (char *) malloc(size);
    if (!buff) return NULL;

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (len + 1 >= size) {
            size *= 2;
            char*newBuff = realloc(buff, size);
            if (!newBuff) {
                free(buff);
                return NULL;
            }
            buff = newBuff;
        }
        buff[len++] = (char) c;
    }
    buff[len] = '\0';
    return buff;
}


bool pathExists(const char *path) {
    FILE *file = fopen(path, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}


Alkalmazott *readFromInput(void) {
    wprintf(L"\n--- Új alkalmazott felvétele ---\n");

    Alkalmazott *uj = (Alkalmazott*) malloc(sizeof(Alkalmazott));
    if (!uj) return NULL;

    uj->szemelyes_adatok = (SzemelyesAdat*) malloc(sizeof(SzemelyesAdat));
    uj->munka_adatok = (MunkaAdat*) malloc(sizeof(MunkaAdat));
    uj->penzugyi_adatok = (PenzugyiAdat*) malloc(sizeof(PenzugyiAdat));
    uj->kov = NULL;

    if (!uj->szemelyes_adatok || !uj->munka_adatok || !uj->penzugyi_adatok) {
        wprintf(L"Memória foglalási hiba!\n");
        free(uj->szemelyes_adatok);
        free(uj->munka_adatok);
        free(uj->penzugyi_adatok);
        free(uj);
        return NULL;
    }

    memset(uj->szemelyes_adatok, 0, sizeof(SzemelyesAdat));
    memset(uj->munka_adatok, 0, sizeof(MunkaAdat));
    memset(uj->penzugyi_adatok, 0, sizeof(PenzugyiAdat));

    READ_INPUT(L"ID: ", uj->szemelyes_adatok->id);
    READ_INPUT(L"Név: ", uj->szemelyes_adatok->nev);
    READ_INPUT(L"Születési dátum: ", uj->szemelyes_adatok->szul_datum);
    READ_INPUT(L"Nem: ", uj->szemelyes_adatok->nev);
    READ_INPUT(L"Lakhely: ", uj->szemelyes_adatok->lakhely);
    READ_INPUT(L"E-Mail: ", uj->szemelyes_adatok->email);
    READ_INPUT(L"Telefon: ", uj->szemelyes_adatok->telefon);
    READ_INPUT(L"Személyi szám: ", uj->szemelyes_adatok->szemelyi_szam);
    READ_INPUT(L"Beosztás: ", uj->munka_adatok->beosztas);
    READ_INPUT(L"Részleg: ", uj->munka_adatok->reszleg);
    READ_INPUT(L"Felettes: ", uj->munka_adatok->felettes);
    READ_INPUT(L"Munkakezdet: ", uj->munka_adatok->munkakezdet);
    READ_INPUT(L"Munka vége: ", uj->munka_adatok->munkavege);
    READ_INPUT(L"Munkarend: ", uj->munka_adatok->munkarend);
    READ_INPUT(L"Bankszámlaszám: ", uj->penzugyi_adatok->bankszamla);
    READ_INPUT(L"Fizetés: ", uj->penzugyi_adatok->fizetes);

    return uj;
}


void readFromInputHelper(const wchar_t *prompt, wchar_t *dest, size_t destSize) {
    char buff[256];

    wprintf(L"%ls", prompt);
    fflush(stdout);

    if (fgets(buff, sizeof(buff), stdin) != NULL) {

        buff[strcspn(buff, "\n")] = '\0';

        mbstowcs(dest, buff, destSize - 1);

        dest[destSize - 1] = L'\0';
    }
}


int writeToCSV(HashTable *ht, char const *path) {
    if (!ht || !path) return -1;

    FILE *fp = fopen(path, "w");
    if (!fp) {
        perror("Nem sikerült megnyitni a fájlt!");
        return -2;
    }

    // BOM - Byte Order Mark, jelzi az UTF-8 kódolást
    fprintf(fp, "\xEF\xBB\xBF");

    fprintf(fp, "ID,Nev,SzulDatum,Nem,Lakhely,Email,Telefon,SzemelyiSzam,"
                "Beosztas,Reszleg,Felettes,Munkakezdet,Munkavege,Munkarend,"
                "Bankszamla,Fizetes\n");

    for (size_t i = 0; i < ht->size; i++) {
        Alkalmazott const *current = ht->buckets[i];

        while (current != NULL) {
            if (current->szemelyes_adatok && current->munka_adatok && current->penzugyi_adatok) {

                printField(fp, current->szemelyes_adatok->id, ",");
                printField(fp, current->szemelyes_adatok->nev, ",");
                printField(fp, current->szemelyes_adatok->szul_datum, ",");
                printField(fp, current->szemelyes_adatok->nem, ",");
                printField(fp, current->szemelyes_adatok->lakhely, ",");
                printField(fp, current->szemelyes_adatok->email, ",");
                printField(fp, current->szemelyes_adatok->telefon, ",");
                printField(fp, current->szemelyes_adatok->szemelyi_szam, ",");

                printField(fp, current->munka_adatok->beosztas, ",");
                printField(fp, current->munka_adatok->reszleg, ",");
                printField(fp, current->munka_adatok->felettes, ",");
                printField(fp, current->munka_adatok->munkakezdet, ",");
                printField(fp, current->munka_adatok->munkavege, ",");
                printField(fp, current->munka_adatok->munkarend, ",");

                printField(fp, current->penzugyi_adatok->bankszamla, ",");

                printField(fp, current->penzugyi_adatok->fizetes, "\n");
            }
            current = current->kov;
        }
    }
    fclose(fp);
    return 0;
}


void printField(FILE *fp, wchar_t *str, char *suffix) {
    if (!str) {
        fprintf(fp, "%s", suffix);
        return;
    }

    size_t const len = wcstombs(NULL, str, 0);
    if (len == (size_t)-1) return;

    char *buffer = (char *)malloc(len + 1);
    if (buffer) {
        wcstombs(buffer, str, len + 1);
        fprintf(fp, "%s%s", buffer, suffix);
        free(buffer);
    }
}