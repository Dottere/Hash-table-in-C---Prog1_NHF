//
// Created by lin on 11/13/25.
//

#ifndef PROGRAMMING1_NAGYHF_LINKEDLIST_H
#define PROGRAMMING1_NAGYHF_LINKEDLIST_H

#include "datastructs.h"

// Create a new node
Alkalmazott *linkedListNodeCreate(SzemelyesAdat *, MunkaAdat *, PenzugyiAdat *);
// Set every pointer to NULL
Alkalmazott *linkedListInit(Alkalmazott *);
// Append new struct at the end
void linkedListAppend(Alkalmazott **, Alkalmazott *);
// Set previous element pointer to next element pointer and free memory
void linkedListRemove(Alkalmazott **, Alkalmazott *);
// Loop through linked list and free everything
void linkedListFree(Alkalmazott **);

#endif //PROGRAMMING1_NAGYHF_LINKEDLIST_H

