//
// Created by lin on 11/10/25.
//

#include "headers/io.h"


// debug
int printFromCSV(char const *filePath) {
    FILE *fp = fopen(filePath, "rb");

    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fp)) {
        wprintf(L"%hs", buffer);
    }

    fclose(fp);
    return 0;
}

Alkalmazott *readFromCSV(char const *filePath) {
    FILE *fp = fopen(filePath, "r");
    if (!fp) {
        perror("Failed to open file");
        return NULL;
    }

    Alkalmazott *linkedList = NULL;
    char buff[1024];

    // get rid of first line and checks if file is empty or not
    if (!fgets(buff, sizeof(buff), fp)) {
        fclose(fp);
        return NULL;
    }

    if (!fgets(buff, sizeof(buff), fp)) {
        fclose(fp);
        return NULL;
    }
    do {
        buff[strcspn(buff, "\r\n")] = '\0';

        Alkalmazott *line = (Alkalmazott *) malloc(sizeof(Alkalmazott));
        if (!line){
            perror("Memory allocation failed");
            break;
        }
        line->kov = NULL;

        line->szemelyes_adatok = (SzemelyesAdat *) malloc(sizeof(SzemelyesAdat));
        line->munka_adatok = (MunkaAdat *) malloc(sizeof(MunkaAdat));
        line->penzugyi_adatok = (PenzugyiAdat *) malloc(sizeof(PenzugyiAdat));

        if (!line->szemelyes_adatok || !line->munka_adatok || !line->penzugyi_adatok) {
            perror("Memory allocation failed");
            // Clean up
            free(line->szemelyes_adatok);
            free(line->munka_adatok);
            free(line->penzugyi_adatok);
            free(line);
            break;
        }

        memset(line->szemelyes_adatok, 0, sizeof(SzemelyesAdat));
        memset(line->munka_adatok, 0, sizeof(MunkaAdat));
        memset(line->penzugyi_adatok, 0, sizeof(PenzugyiAdat));

        char const *token = strtok(buff, ",");

        if (token){
            mbstowcs(line->szemelyes_adatok->id, token, sizeof(line->szemelyes_adatok->id)/sizeof(wchar_t) - 1);
        }

        token = strtok(NULL, ",");
        if (token) {
            mbstowcs(line->szemelyes_adatok->nev, token, sizeof(line->szemelyes_adatok->nev)/sizeof(wchar_t) - 1);
        }

        token = strtok(NULL, ",");
        if (token){
            mbstowcs(line->szemelyes_adatok->szul_datum, token, sizeof(line->szemelyes_adatok->szul_datum)/sizeof(wchar_t) - 1);
        }

        token = strtok(NULL, ",");
        if (token){
            mbstowcs(line->szemelyes_adatok->nem, token, sizeof(line->szemelyes_adatok->nem)/sizeof(wchar_t) - 1);

        }

        token = strtok(NULL, ",");
        if (token){
            mbstowcs(line->szemelyes_adatok->lakhely, token, sizeof(line->szemelyes_adatok->lakhely)/sizeof(wchar_t) - 1);

        }

        token = strtok(NULL, ",");
        if (token){
            mbstowcs(line->szemelyes_adatok->email, token, sizeof(line->szemelyes_adatok->email)/sizeof(wchar_t) - 1);
        }

        token = strtok(NULL, ",");
        if (token) {
            mbstowcs(line->szemelyes_adatok->telefon, token, sizeof(line->szemelyes_adatok->telefon)/sizeof(wchar_t) - 1);
        }

        token = strtok(NULL, ",");
        if (token) {
            mbstowcs(line->szemelyes_adatok->szemelyi_szam, token, sizeof(line->szemelyes_adatok->szemelyi_szam)/sizeof(wchar_t) - 1);
        }

        token = strtok(NULL, ",");
        if (token){
            mbstowcs(line->munka_adatok->beosztas, token, sizeof(line->munka_adatok->beosztas)/sizeof(wchar_t) - 1);
        }

        token = strtok(NULL, ",");
        if (token) {
            mbstowcs(line->munka_adatok->reszleg, token, sizeof(line->munka_adatok->reszleg)/sizeof(wchar_t) - 1);
        }

        token = strtok(NULL, ",");
        if (token) {
            mbstowcs(line->munka_adatok->felettes, token, sizeof(line->munka_adatok->felettes)/sizeof(wchar_t) - 1);
        }

        token = strtok(NULL, ",");
        if (token) {
            mbstowcs(line->munka_adatok->munkakezdet, token, sizeof(line->munka_adatok->munkakezdet)/sizeof(wchar_t) - 1);
        }

        token = strtok(NULL, ",");
        if (token) {
            mbstowcs(line->munka_adatok->munkavege, token, sizeof(line->munka_adatok->munkavege)/sizeof(wchar_t) - 1);
        }

        token = strtok(NULL, ",");
        if (token) {
            mbstowcs(line->munka_adatok->munkarend, token, sizeof(line->munka_adatok->munkarend)/sizeof(wchar_t) - 1);
        }

        token = strtok(NULL, ",");
        if (token) {
            mbstowcs(line->penzugyi_adatok->bankszamla, token, sizeof(line->penzugyi_adatok->bankszamla)/sizeof(wchar_t) - 1);
        }

        token = strtok(NULL, ",");
        if (token) {
            mbstowcs(line->penzugyi_adatok->fizetes, token, sizeof(line->penzugyi_adatok->fizetes)/sizeof(wchar_t) - 1);
        }

            linkedListAppend(&linkedList, line);
    } while (fgets(buff, sizeof(buff), fp));


    fclose(fp);
    return linkedList;
}

char *readPath(void) {
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
    buff[len] = L'\0';
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

    readFromInputHelper(L"ID: ",
        uj->szemelyes_adatok->id,
        sizeof(uj->szemelyes_adatok->id)/sizeof(wchar_t));

    readFromInputHelper(L"Név: ",
        uj->szemelyes_adatok->nev,
        sizeof(uj->szemelyes_adatok->nev)/sizeof(wchar_t));

    readFromInputHelper(L"Születési dátum: ",
    uj->szemelyes_adatok->szul_datum,
    sizeof(uj->szemelyes_adatok->szul_datum)/sizeof(wchar_t));

    readFromInputHelper(L"Nem: ",
    uj->szemelyes_adatok->nem,
    sizeof(uj->szemelyes_adatok->nem)/sizeof(wchar_t));

    readFromInputHelper(L"Lakhely: ",
    uj->szemelyes_adatok->lakhely,
    sizeof(uj->szemelyes_adatok->lakhely)/sizeof(wchar_t));

    readFromInputHelper(L"E-Mail: ",
    uj->szemelyes_adatok->email,
    sizeof(uj->szemelyes_adatok->email)/sizeof(wchar_t));

    readFromInputHelper(L"Telefon: ",
    uj->szemelyes_adatok->telefon,
    sizeof(uj->szemelyes_adatok->telefon)/sizeof(wchar_t));

    readFromInputHelper(L"Személyi szám: ",
    uj->szemelyes_adatok->szemelyi_szam,
    sizeof(uj->szemelyes_adatok->szemelyi_szam)/sizeof(wchar_t));

    readFromInputHelper(L"Beosztás: ",
    uj->munka_adatok->beosztas,
    sizeof(uj->munka_adatok->beosztas)/sizeof(wchar_t));

    readFromInputHelper(L"Részleg: ",
    uj->munka_adatok->reszleg,
    sizeof(uj->munka_adatok->reszleg)/sizeof(wchar_t));

    readFromInputHelper(L"Felettes: ",
    uj->munka_adatok->felettes,
    sizeof(uj->munka_adatok->felettes)/sizeof(wchar_t));

    readFromInputHelper(L"Munkakezdet: ",
    uj->munka_adatok->munkakezdet,
    sizeof(uj->munka_adatok->munkakezdet)/sizeof(wchar_t));

    readFromInputHelper(L"Munka vége: ",
    uj->munka_adatok->munkavege,
    sizeof(uj->munka_adatok->munkavege)/sizeof(wchar_t));

    readFromInputHelper(L"Munkarend: ",
    uj->munka_adatok->munkarend,
    sizeof(uj->munka_adatok->munkarend)/sizeof(wchar_t));

    readFromInputHelper(L"Bankszámlaszám: ",
    uj->penzugyi_adatok->bankszamla,
    sizeof(uj->penzugyi_adatok->bankszamla)/sizeof(wchar_t));

    readFromInputHelper(L"Fizetés: ",
    uj->penzugyi_adatok->fizetes,
    sizeof(uj->penzugyi_adatok->fizetes)/sizeof(wchar_t));

    return uj;
}

void readFromInputHelper(const wchar_t *prompt, wchar_t *dest, size_t destSize) {
    char buff[256]; // Lokális buffer, nem kell átadni kívülről

    wprintf(L"%ls", prompt);
    fflush(stdout);

    if (fgets(buff, sizeof(buff), stdin) != NULL) {
        // Enter levágása
        buff[strcspn(buff, "\n")] = '\0';

        // Konvertálás a célterületre
        // A destSize-t kívülről kapjuk, mert pointeren a sizeof() nem működik!
        mbstowcs(dest, buff, destSize - 1);

        // Biztonsági lezárás, ha a mbstowcs esetleg pont teleírta volna
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
        Alkalmazott *current = ht->buckets[i];

        while (current != NULL) {
            if (current->szemelyes_adatok && current->munka_adatok && current->penzugyi_adatok) {
                fprintf(fp, "%ls,%ls,%ls,%ls,%ls,%ls,%ls,%ls,%ls,%ls,%ls,%ls,%ls,%ls,%ls,%ls\n",
                    // Személyes
                    current->szemelyes_adatok->id,
                    current->szemelyes_adatok->nev,
                    current->szemelyes_adatok->szul_datum,
                    current->szemelyes_adatok->nem,
                    current->szemelyes_adatok->lakhely,
                    current->szemelyes_adatok->email,
                    current->szemelyes_adatok->telefon,
                    current->szemelyes_adatok->szemelyi_szam,
                    // Munka
                    current->munka_adatok->beosztas,
                    current->munka_adatok->reszleg,
                    current->munka_adatok->felettes,
                    current->munka_adatok->munkakezdet,
                    current->munka_adatok->munkavege,
                    current->munka_adatok->munkarend,
                    // Pénzügyi
                    current->penzugyi_adatok->bankszamla,
                    current->penzugyi_adatok->fizetes
                );
            }
            current = current->kov;
        }
    }
    fclose(fp);
    return 0;
}