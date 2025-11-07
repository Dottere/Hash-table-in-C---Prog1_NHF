//
// Created by lin on 11/7/25.
//

#ifndef PROGRAMMING1_NAGYHF_FNV1A_H
#define PROGRAMMING1_NAGYHF_FNV1A_H

#include "debugmalloc.h"
#include <stdint.h>

#define FNV_OFFSET 2166136261u
#define FNV_PRIME 16777619u

uint32_t FNV1a(const wchar_t *);

#endif //PROGRAMMING1_NAGYHF_FNV1A_H