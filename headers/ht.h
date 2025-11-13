//
// Created by lin on 11/7/25.
//

#ifndef PROGRAMMING1_NAGYHF_HT_H
#define PROGRAMMING1_NAGYHF_HT_H

#include "fnv1a.h"
#include "datastructs.h"

#include <stdlib.h>
#include <inttypes.h>
#include <wchar.h>
#include <inttypes.h>

HashTable *htinit(size_t);
void htinsert(HashTable *, Alkalmazott *, size_t);

#endif //PROGRAMMING1_NAGYHF_HT_H