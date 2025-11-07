//
// Created by lin on 11/7/25.
//

#include "headers/ht.h"



//insert into hash table
extern int htinsert(const wchar_t *str, uint32_t *ht) {
    for (int i = 0; i < sizeof(ht) / sizeof(wchar_t); i++) {
        if (ht[FNV1a(str) % sizeof(ht)/sizeof(wchar_t)] == 0){
            wcscpy(ht[FNV1a(str)], str);
            return 0;
        }
    }
    return 1;
}
