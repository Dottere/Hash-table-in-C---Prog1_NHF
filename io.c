//
// Created by lin on 11/10/25.
//

#include "headers/io.h"
#include <stdlib.h>

// debug
int printFromCSV(char const *filePath) {
    FILE *fp = fopen(filePath, "rb");

    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fp)) {
        wprintf(L"%hs", buffer);
    }

    fclose(fp);
    return 0;
}
