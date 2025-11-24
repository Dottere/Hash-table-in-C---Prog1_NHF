//
// Created by lin on 11/10/25.
//

#ifndef PROGRAMMING1_NAGYHF_IO_H
#define PROGRAMMING1_NAGYHF_IO_H

#include "datastructs.h"
#include "debugmalloc.h"
#include "linkedlist.h"


#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

int printFromCSV(char const *);
Alkalmazott *readFromCSV(char const *);
Alkalmazott *readFromInput(void);
char *readPath(void);
bool pathExists(const char *path);
void readFromInputHelper(const wchar_t *prompt, wchar_t *dest, size_t destSize);


#endif //PROGRAMMING1_NAGYHF_IO_H