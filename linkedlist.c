//
// Created by lin on 11/13/25.
//

#include "headers/linkedlist.h"


Alkalmazott *linkedListNodeCreate(SzemelyesAdat *sz, MunkaAdat *m, PenzugyiAdat *p) {
    Alkalmazott *newElement = (Alkalmazott *) malloc(sizeof(Alkalmazott));
    if (newElement == NULL) return NULL;

    newElement->szemelyes_adatok = sz;
    newElement->munka_adatok = m;
    newElement->penzugyi_adatok = p;
    newElement->kov = NULL;

    return newElement;
}

Alkalmazott *linkedListInit(Alkalmazott *alkalmazott) {
    alkalmazott->szemelyes_adatok = NULL;
    alkalmazott->munka_adatok = NULL;
    alkalmazott->penzugyi_adatok = NULL;
    alkalmazott->kov = NULL;

    return alkalmazott;
}

void linkedListAppend(Alkalmazott **head, Alkalmazott *newElement) {
    if (head == NULL || newElement == NULL) {
        return;
    }

    if (*head == NULL) {
        *head = newElement;
        newElement->kov = NULL;
        return;
    }

    Alkalmazott *iter = *head;
    while (iter->kov != NULL) {
        iter = iter->kov;
    }

    iter->kov = newElement;
    newElement->kov = NULL;
}

void linkedListRemove(Alkalmazott **head, Alkalmazott *element) {
    if (!head || !*head || !element) return;

    if (*head == element) {
        *head = element->kov;
        free(element);
        return;
    }

    Alkalmazott *prev = *head;
    while (prev->kov) {
        if (prev->kov == element) {
            prev->kov = element->kov;
            free(element);
            return;
        }
        prev = prev->kov;
    }
}

void freeNode(Alkalmazott *node) {
    if (!node) return;
    free(node->szemelyes_adatok);
    free(node->munka_adatok);
    free(node->penzugyi_adatok);
    free(node);
}

void linkedListFree(Alkalmazott **head) {
    if (!head || !*head) return;

    Alkalmazott *iter = *head;
    while (iter != NULL) {
        Alkalmazott *next = iter->kov;
        freeNode(iter);
        iter = next;
    }
    *head = NULL;
}

void linkedListPrint(Alkalmazott **head) {
    Alkalmazott *iter = *head;
    while (iter) {
        wchar_t const *nev = iter->szemelyes_adatok->nev;
        wchar_t const *email = iter->szemelyes_adatok->email;
        wchar_t const *szul = iter->szemelyes_adatok->szul_datum;
        wchar_t *catStr = malloc(sizeof(wchar_t) * (64+64+24+1)); memset(catStr, 0, sizeof(wchar_t) * 64+64+24+1);
        wcscpy(catStr, nev); wcscat(catStr, email), wcscat(catStr, szul);
        wprintf(LR"(név: %ls, email: %ls, születési dátum: %ls, hash: 0x%08X
)", (const unsigned short *)nev,
            (const unsigned short *)email, (const unsigned short *)szul, FNV1a(catStr));
        free(catStr);
        iter = iter->kov;
    }
}

int linkedListLen(Alkalmazott **head) {
    int cnt = 0;
    Alkalmazott const *iter = *head;
    while (iter) {
        cnt++;
        iter = iter->kov;
    }
    return cnt;
}

