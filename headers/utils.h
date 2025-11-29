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
int readingFromFile(HashTable **ht, char **path);
void searchInHashTable(HashTable **ht);
void statistics(HashTable const *ht);
void howToModify(HashTable *ht, char const *path);
void addLogic(HashTable *ht, char const *path, char *choice);
void delLogic(HashTable *ht);
void updateLogic(HashTable *ht, char *choice);
void writeToFile(HashTable **ht);

bool confirmOverwrite(const char *path);

#endif //PROGRAMMING1_NAGYHF_UTILS_H