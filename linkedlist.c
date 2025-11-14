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

void linkedListFree(Alkalmazott **head) {
    if (!head || !*head) return;

    Alkalmazott *iter = *head;
    while (iter != NULL) {
        Alkalmazott *next = iter->kov;
        free(iter->szemelyes_adatok);
        free(iter->munka_adatok);
        free(iter->penzugyi_adatok);
        free(iter);
        iter = next;
    }
    *head = NULL;
}