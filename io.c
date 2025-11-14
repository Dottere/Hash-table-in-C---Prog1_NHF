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

// Read in line per line from provided CSV and create Alkalmazott structs from it and store it in an array
Alkalmazott *createAlkalmazott(void) {
    Alkalmazott *csvContent = (Alkalmazott*)malloc(sizeof(Alkalmazott));
    if (csvContent == NULL) return NULL;

    csvContent->szemelyes_adatok = (SzemelyesAdat*)malloc(sizeof(SzemelyesAdat));
    csvContent->munka_adatok = (MunkaAdat*)malloc(sizeof(MunkaAdat));
    csvContent->penzugyi_adatok = (PenzugyiAdat*)malloc(sizeof(PenzugyiAdat));

    if (csvContent->szemelyes_adatok == NULL || csvContent->munka_adatok == NULL || csvContent->penzugyi_adatok == NULL){
        free(csvContent->penzugyi_adatok);
        free(csvContent->munka_adatok);
        free(csvContent->szemelyes_adatok);
        free(csvContent);
        return NULL;
    }

    memset(csvContent->szemelyes_adatok, 0, sizeof(SzemelyesAdat));
    memset(csvContent->munka_adatok, 0, sizeof(MunkaAdat));
    memset(csvContent->penzugyi_adatok, 0, sizeof(PenzugyiAdat));
    csvContent->kov = NULL;

    return csvContent;
}

void parseCSVFile(char *line, Alkalmazott *alkalmazott){
    if (line == NULL || alkalmazott == NULL)
        return;

    SzemelyesAdat *sz = alkalmazott->szemelyes_adatok;
    MunkaAdat *m = alkalmazott->munka_adatok;
    PenzugyiAdat *p = alkalmazott->penzugyi_adatok;

    char field_buffer[64];
    int field_pos = 0;
    int field_index = 0;
    int in_quotes = 0;

    char *p_char = line;

    while (1) {
        char c = *p_char;

        if (in_quotes) {
            if (c == '"') {
                in_quotes = 0;
            } else {
                field_buffer[field_pos++] = c;
            }
        } else {
            if (c == '"') {
                in_quotes = 1;
            } else if (c == ',' || c == '\0') {
                // --- End of a field ---
                field_buffer[field_pos] = '\0';

                // Use a switch to map the field index to the correct struct member
                switch (field_index) {
                    // --- SzemelyesAdat ---
                    case 0: strncpy(sz->id, field_buffer, sizeof(sz->id) - 1); break;
                    case 1: strncpy(sz->nev, field_buffer, sizeof(sz->nev) - 1); break;
                    case 2: strncpy(sz->szul_datum, field_buffer, sizeof(sz->szul_datum) - 1); break;
                    case 3: strncpy(sz->nem, field_buffer, sizeof(sz->nem) - 1); break;
                    case 4: strncpy(sz->lakhely, field_buffer, sizeof(sz->lakhely) - 1); break;
                    case 5: strncpy(sz->email, field_buffer, sizeof(sz->email) - 1); break;
                    case 6: strncpy(sz->telefon, field_buffer, sizeof(sz->telefon) - 1); break;
                    case 7: strncpy(sz->szemelyi_szam, field_buffer, sizeof(sz->szemelyi_szam) - 1); break;
                    // --- MunkaAdat ---
                    case 8: strncpy(m->beosztas, field_buffer, sizeof(m->beosztas) - 1); break;
                    case 9: strncpy(m->reszleg, field_buffer, sizeof(m->reszleg) - 1); break;
                    case 10: strncpy(m->felettes, field_buffer, sizeof(m->felettes) - 1); break;
                    case 11: strncpy(m->munkakezdet, field_buffer, sizeof(m->munkakezdet) - 1); break;
                    case 12: strncpy(m->munkavege, field_buffer, sizeof(m->munkavege) - 1); break;
                    case 13: strncpy(m->munkarend, field_buffer, sizeof(m->munkarend) - 1); break;
                    // --- PenzugyiAdat ---
                    case 14: strncpy(p->bankszamla, field_buffer, sizeof(p->bankszamla) - 1); break;
                    case 15: p->fizetes = atof(field_buffer); break; // Use atof() for double
                }

                field_pos = 0;   // Reset for next field
                field_index++; // Move to next field index
            } else {
                field_buffer[field_pos++] = c;
            }
        }

        if (c == '\0') {
            break; // Exit loop at end of string
        }
        p_char++; // Move to next character
    }
}

void free_list(Alkalmazott *head) {
    Alkalmazott *current = head;
    while (current != NULL) {
        Alkalmazott *temp = current;
        current = current->kov;

        free(temp->szemelyes_adatok);
        free(temp->munka_adatok);
        free(temp->penzugyi_adatok);
        free(temp);
    }
}