//
// Created by lin on 11/7/25.
//

#ifndef PROGRAMMING1_NAGYHF_HT_H
#define PROGRAMMING1_NAGYHF_HT_H

#include "fnv1a.h"
#include "datastructs.h"
#include "linkedlist.h"

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <wchar.h>

/**
 * @brief Létrehoz egy Hash-Táblát amellyel képes a htinsert() függvény dolgozni
 *
 * Ez a program csak fix méretű Hash-Táblákkal tud dolgozni, ezért szükséges egy kezdeti méret
 * megadása amely változatlan marad a futam végéig.
 *
 * @param initSize A Hash-Tábla mérete.
 * @return Egy pointert ad vissza a létrehozott Hash-Táblához.
 * @note Kapcsolódó függvények: htinsert(), htfree()
 */
HashTable *htcreate(int initSize);

/**
 * @brief Beszúrja egy láncolt lista elemeit a bekért Hash-Táblába
 *
 * Végigmegy a láncolt lista elemein egyesével, mindegyikből csinál egy hasht a név, e-mail cím, és születési dátum
 * felhasználásával, majd veszi a beadott Hash-Tábla méretét és azzal maradékosan leosztva a Hash-t megkapja, hogy melyik
 * indexre kell beszúrni a kért elemet. Abban az esetben, ha ütközés történik, akkor a vödrökön belül láncolja az elemeket.
 *
 * @param ht Egy pointer a Hash-Táblára amelybe beszúrni kívánunk.
 * @param linkedListHead Egy pointer egy láncolt lista első pointerjére, amelynek az elemeit beszúrni kívánjuk.
 * @return 0 Minden rendben.
 * @return -1 Láncolt lista mérete nagyobb mint a Hash-Tábla mérete.
 * @return -2 Nem sikerült a kulcsot felépíteni a név, e-mail cím és születési dátum kombinációjából.
 * @return -3 Nem sikerült egy új Alkalmazott elemet foglalni, amely szükséges a Hash-Táblába való beszúráshoz.
 * @return -4 Nem sikerült az új Alkalmazott struktúra összes elemének memóriát foglalni.
 * @return -5 Valamely a két paraméter közül NULL.
 *
 * @note Az eredeti láncolt lista érintetlen marad.
 * @note Kapcsolódó függvények: htcreate(), htfree()
 *
 */
int htinsert(HashTable *ht, Alkalmazott** linkedListHead);

/**
 * @brief Kiíratja a hash tábla összes elemét
 *
 * Végigmegy a hash tábla összes vödrén és kiírja az ott tárolt
 * alkalmazottakat. Ütközés esetén a láncolt lista elemeit '->' jellel
 * elválasztva jeleníti meg.
 *
 * @param ht Pointer a kiíratni kívánt HashTable struktúrára
 * @return Nincs visszatérési érték
 *
 * @note A kimenet a standard kimenetre (stdout) kerül
 * @warning Ha ht NULL akkor nem csinál semmit.
 *
 * Példa kimenet:
 * @code
 * Bucket[0]: elem1 -> elem2
 * Bucket[2]: elem3
 * @endcode
 */
void printHashTable(HashTable const *ht);

/**
 * @brief Felszabadítja a Hash Tábla által foglalt memóriát.
 *
 * Végigmegy az összes vödrön és felszabadítja először a bennük tárolt adatokat, magukat a vödröket, és végül a Hash-Táblát
 *
 * @param ht Pointer a felszabadítani kívánt ht struktúrára
 * @return Nincs visszatérési érték
 * @warning Ha ht NULL akkor nem csinál semmit, hibakódot sem jelez.
 * @note Kapcsolódó függvények: htcreate), htinsert()
 */
void htfree(HashTable *ht);

/**
 * @brief Megkétszerezi a bekért tábla méretét
 *
 * A bekért tábla vödreiről készít egy másolatot, egy olyan tömbbe amely mérete kétszerese az előzőnek,
 * majd felülírja a Hash-Táblának a régi tömb mutatóját az újjal miután a régit felszabadította. A méretet
 * is változtatja.
 *
 * @param ht Egy mutató arra a Hash-Táblára amelynek a méretét szeretnénk megnövelni
 * @return Egy mutató az új, nagyobb táblára.
 */
int htresize(HashTable *ht);

/**
 * @brief Egy segédfüggvény egy elem hash kiszámítására
 *
 * A bekért elem kulcsfontosságú elemeiből kiszámítja a hash értékét, majd visszaadja azt.
 *
 * @param alkalmazott Az az elem, melynek a hash értékét szeretnénk kiszámítani
 * @return Egy 32 bites hash
 */
uint32_t calculateHash(Alkalmazott const *alkalmazott);

/**
 * @brief Töröl egy elemet a táblából
 *
 * Megkeresi a célpontot a bekért táblában, majd kifűzi a láncból és felszabadítja.
 *
 * @param ht A tábla melyből törölni szeretnénk
 * @param target Az az elem melyet törölni szeretnénk
 * @return 0 Ha minden rendben
 * @return -1 Ha probléma történt
 */
int htdelete(HashTable *ht, Alkalmazott const *target);

/**
 * @brief Megmondja, hogy egy elem megtalálható-e a táblában
 *
 * A keresett elemet megkeresi a hash értékének kiszámításával majd ha egyezést talál a kulcsfontosságú
 * elemeik között akkor igaz értéket ad vissza.
 *
 * @param ht A tábla melyben keresni szeretnénk
 * @param target A célpont melyet meg szeretnénk találni
 * @return Egy boole érték, mely megadja, hogy a keresés sikeres volt-e vagy sem
 */
bool htfind(HashTable const *ht, Alkalmazott const *target);

/**
 * @brief Egy elem mezőjének változtatására alkalmas függvény
 *
 * A bekért táblában megkeresi a bekért célpontot, majd annak a megadott mezőjét felülírja
 * a megadott új értékkel.
 *
 * @note Ha kulcsfontosságú elemet változtatunk akkor az elem törlésre és újra beszúrásra kerül
 *
 * @param ht A tábla melynek szeretnénk az elemét változtatni
 * @param target A célpont melyet változtatni szeretnénk
 * @param fieldType A mező melyet változtatni szeretnénk
 * @param newValue Az új érték mellyel felül szeretnénk írni a régit
 * @return Egy boole érték mely megadja a művelet sikerességét
 */
bool htupdate(HashTable *ht, Alkalmazott *target, int fieldType, wchar_t const *newValue);

/**
 * @brief Megkeres egy elemet a táblában és visszaadja annak a mutatóját
 *
 * Az bekért táblában megkeresi a bekért elemet és ha megtalálta akkor visszaad arra az elemre egy mutatót
 *
 * @warning Ha nem találta meg az elemet akkor a visszatérési érték NULL
 *
 * @param ht A tábla melyet vizsgálunk
 * @param target A célpont melyet keresünk
 * @return Egy Alkalmazott pointer a megtalált elemre
 */
Alkalmazott *inHt(HashTable const *ht, Alkalmazott const *target);



#endif //PROGRAMMING1_NAGYHF_HT_H