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

/**
 * @brief Kiírja a menüt
 *
 * Egy segédfüggvény mely kiírja a menü elemeit.
 *
 */
void printHelp(void);

/**
 * @brief Egy már létező hash táblába beszúr új elemeket egy fájlból
 *
 * A bekért elérési úton létező fájlból beolvas egy új láncolt listát
 * melyet beszúr a létező Hash-Táblába a benne lévő elemek mellé.
 *
 * @param ht A hash tábla melybe beolvasni szeretnénk
 * @param path A fájlhoz tartozó mutató melyből beolvasni szeretnénk
 * @return 0 Ha sikeres
 * @return -1 Ha sikertelen
 */
int readingFromFile(HashTable **ht, char **path);

/**
 * @brief Segédfüggvény a táblában való keresés megvalósítására
 *
 * Beolvas a szabványos bemenetről három kulcsfontosságú elemet, és kiírja, hogy az megtalálható-e
 * a táblában.
 *
 * @param ht A tábla melyben keresni szeretnénk
 */
void searchInHashTable(HashTable **ht);

/**
 * @brief Megnézi a tábla telítettségét, és megmondja hány vödörben volt ütközés
 *
 * A bekért Hash-Tábla elemein végigmegy és készít egy statisztikát a tábla telítettségéről,
 * és hogy a vödrök hány százalékában van ütközés.
 *
 * @note Technikai/debug jellegű függvény
 *
 * @param ht A tábla melyről statisztikát szeretnénk készíteni
 */
void statistics(HashTable const *ht);

/**
 * @brief Megkérdezi a felhasználótól, hogy szeretné-e felülírni a bekért elérési utat
 *
 * Ha a bekért elérési út már létezik, akkor a függvény meghívásával lehet kikérni
 * a felhasználó véleményét annak felülírásával kapcsolatban.
 *
 * @param path A vizsgált elérési út
 * @return Egy boole érték arról, hogy a felhasználó szeretne-e vagy sem felülírni
 */
bool confirmOverwrite(const char *path);

/**
 * @brief Egy almenüt ír ki, melyben megadhatjuk, hogyan szeretnénk módosítani a táblát
 *
 * A táblához lehet új elem(ek)et hozzáadni, elemet törölni, vagy elemet módosítani. Ez a függvény
 * egy almenüt ír ki a szabványos kimenetre melyben a felhasználó eldöntheti, hogy ezek közül mit szeretne csinálni.
 *
 * @param ht A hash tábla melyet módosítani szeretnénk
 * @param path Az elérési út melyből esetleg beolvasni szeretnénk
 */
void howToModify(HashTable *ht, char const *path);

/**
 * @brief A hozzáadás logikáját megvalósító segédfüggvény
 *
 * A hozzáadás logikáját valósítja meg ez a segédfüggvény és kizárólag a howToModify() függvényen
 * belül van használva.
 *
 * @param ht A tábla melyhez hozzáadni szeretnénk
 * @param path Az elérési út melyből esetleg beolvasni szeretnénk
 * @param choice A választás melyet a meghívó függvény továbbít
 */
void addLogic(HashTable *ht, char const *path, char *choice);

/**
 * @brief A törlés logikáját megvalósító segédfüggvény
 *
 * A törlés logikáját valósítja meg ez a segédfüggvény és kizárólag a howToModify() függvényen
 * belül van használva.
 *
 * @param ht A tábla melyből törölni szeretnénk
 */
void delLogic(HashTable *ht);

/**
 * @brief A módosítás logikáját megvalósító függvény
 *
 * A módosítás logikáját valósítja meg ez a segédfüggvény és kizárólag a howToModify() függvényen
 * belül van használva.
 *
 * @param ht A tábla melynek az elemeit módosítani szeretnénk
 * @param choice A választást tároló változó melyet a meghívó függvény biztosít
 */
void updateLogic(HashTable *ht, char *choice);

/**
 * @brief A fájlba való kiírás magas szintű kezelését valósítja meg
 *
 * A fájlba való kiírás magas szintű kezelésére alkalmas függvény, kombinálja a szabványos bemenetről
 * való bekérést a fájlkezeléssel.
 *
 * @param ht A tábla melynek tartalmát ki szeretnénk írni
 */
void writeToFile(HashTable **ht);


#endif //PROGRAMMING1_NAGYHF_UTILS_H