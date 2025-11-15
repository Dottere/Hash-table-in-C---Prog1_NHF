//
// Created by lin on 11/10/25.
//

#include "headers/io.h"
#include "headers/linkedlist.h"
#include <stdlib.h>
#include <unistd.h>

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

    // get rid of first line
    if (!fgets(buff, sizeof(buff), fp)) {
        fclose(fp);
        return NULL;
    }

    while (fgets(buff, sizeof(buff), fp)) {
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

        char *token = strtok(buff, ",");

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
    }


    fclose(fp);
    return linkedList;
}