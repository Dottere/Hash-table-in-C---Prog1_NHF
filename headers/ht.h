//
// Created by lin on 11/7/25.
//

#ifndef PROGRAMMING1_NAGYHF_HT_H
#define PROGRAMMING1_NAGYHF_HT_H

#include "fnv1a.h"
#include "datastructs.h"
#include "linkedlist.h"

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <wchar.h>

HashTable *htcreate(int);
int htinsert(HashTable *ht, Alkalmazott** linkedListHead);
void printHashTable(HashTable const *ht);
void htfree(HashTable *ht);
int htresize(HashTable *ht);
uint32_t calculateHash(Alkalmazott const *alkalmazott);
int htdelete(HashTable *ht, Alkalmazott const *target);
bool htfind(HashTable const *ht, Alkalmazott const *target);
bool htupdate(HashTable *ht, Alkalmazott *target, int fieldType, wchar_t const *newValue);
Alkalmazott *inHt(HashTable const *ht, Alkalmazott const *target);

#endif //PROGRAMMING1_NAGYHF_HT_H