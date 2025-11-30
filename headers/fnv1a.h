//
// Created by lin on 11/7/25.
//

#ifndef PROGRAMMING1_NAGYHF_FNV1A_H
#define PROGRAMMING1_NAGYHF_FNV1A_H

#include <stddef.h>
#include <stdint.h>

#define FNV_OFFSET 2166136261u
#define FNV_PRIME 16777619u

/**
 * @brief Generál egy 32 bites számot a bekért sztringből
 *
 *  A bekért wchar_t karakterekből álló sztringet először átkonvertálja UTF-8 kompatibilis
 *  multibájt karakterekből álló sztringgé, majd azt bájtonként feldolgozza. Két konstanssal dolgozik, egy FNV offset és
 *  egy FNV prím értékkel. Első lépésként a kimenetet beállítja az offset értékére, majd minden a bekért szöveg minden
 *  bájtjával azt először XOR-olja majd beszorozza a prímmel. A végső érték egy 32 bites szám lesz amelyet visszaad a program.
 *
 *  @param str Ez egy pointer azokra a wchar_t karakterekből álló sztringre amelyből a hash készül.
 *
 *  @returns Bemenettől függetlenül mindig egy uint32_t típusú 32 bites számot ad vissza.
 *
 */
uint32_t FNV1a(const wchar_t *str);

#endif //PROGRAMMING1_NAGYHF_FNV1A_H