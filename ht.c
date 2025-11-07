//
// Created by lin on 11/7/25.
//

#include "headers/ht.h"
#include <stdarg.h>

//Takes in how many elements to hold initially and returns a hash table with that size
Alkalmazott *htinit(size_t initSize) {
    Alkalmazott *ht = (Alkalmazott *)malloc(sizeof(Alkalmazott) * initSize);
    ht[0].kov = &ht;

    return ht;
}

void htinsert(Alkalmazott *ht, Alkalmazott alkalmazott) {
    int nextFreeIndex = 0;
    while (ht->kov != NULL) {
        nextFreeIndex++;
    }
}