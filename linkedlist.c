//
// Created by lin on 11/13/25.
//

#include "headers/linkedlist.h"
#include "headers/fnv1a.h"
#include "headers/debugmalloc.h"

#include <wchar.h>

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


int linkedListLen(Alkalmazott **head) {
    int cnt = 0;
    Alkalmazott const *iter = *head;
    while (iter) {
        cnt++;
        iter = iter->kov;
    }
    return cnt;
}

