//
// Created by lin on 11/10/25.
//

#ifndef PROGRAMMING1_NAGYHF_IO_H
#define PROGRAMMING1_NAGYHF_IO_H

#include "datastructs.h"
#include <stdbool.h>
#include <stdio.h>


/**
 * @brief Egy CSV fájlból beolavssa az elemeket egy láncolt listába
 *
 * A bekért elérési úton lévő CSV fájl minden sorából készít egy láncolt lista elemet amelyet belefűz
 * egy dinamikusan foglalt láncolt listába majd a végén visszaadja annak egy az első elemére mutató
 * pointert.
 *
 * @param filePath A CSV fájl melyből be szeretnénk olvasni
 * @return Egy láncolt listára mutató pointer mely tartalmazza a CSV fájl sorait csomópontokként
 */
Alkalmazott *readFromCSV(char const *filePath);

void readFromCSVHelper(char **input_cursor, wchar_t *dest, size_t destSize);

/**
 * @brief Beolvas a szabványos bemenetről egy elérési utat
 *
 * Beolvas a szabványos bemenetről egy dinamikusan foglalt elérési utat.
 *
 * @return Egy elérési út
 */
char *readPath(void);

/**
 * @brief Megvizsgálja, hogy a bekért elérési út létezik-e
 *
 * Megpróbálja megnyitni a bekért elérési úton lévő fájlt, és ha sikeres volt
 * akkor visszaad egy igaz értéket, ha nem, akkor egy hamisat.
 *
 * @param path A vizsgált elérési út
 * @return Egy boole érték arról, hogy az elérési út létezik-e
 */
bool pathExists(const char *path);

/**
 * @brief Bekér egy alkalmazottat a szabványos bemenetről
 *
 * Egyetlen egy Alkalmazott elemet bekér a szabványos bemenetről a bekért mezők megadott értékeivel népesítve.
 *
 * @return Egy Alkalmazott pointer a bekért adatokkal feltöltve
 */
Alkalmazott *readFromInput(void);

/**
 * @brief Kiírja, hogy mit kérünk be, majd beolvassa azt
 *
 * Ez egy segédfüggvény a readFromInput függvény számára.
 * Kiír a szabványos kimenetre egy szöveget, hogy mit kérünk be, majd beolvassa azt a szabványos
 * bemenetről és eltárolja egy bekért változóban.
 *
 * @param prompt A kiírandó szöveg
 * @param dest Ahova menteni szeretnénk a bekért értéket
 * @param destSize A tároló mérete, ahova írni szeretnénk
 */
void readFromInputHelper(const wchar_t *prompt, wchar_t *dest, size_t destSize);

/**
 * @brief Kiírja egy tábla tartalmát fájlba
 *
 * A bekért tábla elemeit rendezetlenül kiírja a megadott elérési úton található fájlba, az elejére beszúrva egy BOM
 * jelzést ezzel jelezve az UTF-8 kódolást az Excel-nek.
 *
 * @param ht A tábla melynek elemeit ki szeretnénk írni
 * @param path Az elérési út melybe írni szeretnénk
 * @return 0 Ha minden rendben
 * @return -1 Ha a paraméterek valamelyike nem elérhető
 * @return -2 Ha nem sikerült megnyitni a fájlt
 */
int writeToCSV(HashTable *ht, char const *path);

/**
 * @brief Kiír egy sort a bekért fájlpointerre lezárva a bekért suffix-szel
 *
 * Ez egy segédfüggvény a writeToCSV függvény számára
 *
 * @param fp Egy mutató a fájlra melybe írni szeretnénk
 * @param str Egy sztring, melyet a fájlba szeretnénk írni
 * @param suffix A sztringet lezáró elem
 */
void printField(FILE *fp, wchar_t *str, char *suffix);

#endif //PROGRAMMING1_NAGYHF_IO_H