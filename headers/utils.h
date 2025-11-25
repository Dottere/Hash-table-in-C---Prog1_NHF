//
// Created by lin on 11/24/25.
//

#ifndef PROGRAMMING1_NAGYHF_UTILS_H
#define PROGRAMMING1_NAGYHF_UTILS_H

#include "datastructs.h"
#include "ht.h"
#include "linkedlist.h"
#include "io.h"

#include <stdbool.h>
#include <stdio.h>
#include <wchar.h>

void printHelp(void);
void statistics(HashTable *ht);
bool confirmOverwrite(const char *path);
void howToModify(HashTable *ht, char const *path);

#endif //PROGRAMMING1_NAGYHF_UTILS_H