//
// Created by lin on 11/7/25.
//

#ifndef PROGRAMMING1_NAGYHF_HT_H
#define PROGRAMMING1_NAGYHF_HT_H

#include "fnv1a.h"
#include "datastructs.h"
#include "linkedlist.h"

#include <stdlib.h>
#include <inttypes.h>
#include <wchar.h>
#include <inttypes.h>

HashTable *htcreate(int);
int htinsert(HashTable const *ht, Alkalmazott** linkedListHead);
void printHashTable(HashTable const *ht);
void htfree(HashTable *ht);

#endif //PROGRAMMING1_NAGYHF_HT_H