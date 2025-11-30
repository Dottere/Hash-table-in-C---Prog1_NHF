//
// Created by lin on 11/13/25.
//

#ifndef PROGRAMMING1_NAGYHF_LINKEDLIST_H
#define PROGRAMMING1_NAGYHF_LINKEDLIST_H

#include "datastructs.h"
#include "fnv1a.h"
#include "debugmalloc.h"

#include <wchar.h>

/**
 * @brief Létrehoz egy új Alkalmazott elemet a bekért struktúrákból
 *
 * A bekért struktúrákat belefűzi egy új láncolt lista elembe és a következő pointert NULL-ra állítja.
 *
 * @param sz A személyes adatokat tartalmazó struktőrára egy mutató
 * @param m A munkaügyi adatokat tartalmazó struktúrára egy mutató
 * @param p A pénzügyi adatokat tartalmazó struktúrára egy mutató
 * @return Egy Alkalmazott struktúrára mutató pointer amely tartalmazza a bekért elemeket
 */
Alkalmazott *linkedListNodeCreate(SzemelyesAdat *sz, MunkaAdat *m, PenzugyiAdat *p);

/**
 * @brief Létrehoz egy láncolt lista elemet
 *
 * Egy olyan láncolt lista elemet hoz létre, mely önmaga inicializálva van, viszont
 * a belső elemei közül egyik sincs.
 *
 * @param alkalmazott Létrehoz egy teljesen üres láncolt lista elemet
 * @return Egy mutató a láncolt listára
 */
Alkalmazott *linkedListInit(Alkalmazott *alkalmazott);

/**
 * @brief Beszúr egy új elemet a láncolt lista végére
 *
 * Bekér egy láncolt lista mutatójára mutató pointert majd azt dereferálva annak a végére
 * beszúrja a bekért elemet.
 *
 * @warning Ha sikertelen a beszúrás, vagy nem létezik valamelyik paraméter akkor NULL a visszatérési érték
 * @param head A láncolt lista eleje, melybe beszúrni szeretnénk
 * @param newElement Az elem melyet beszúrni szeretnénk
 */
void linkedListAppend(Alkalmazott **head, Alkalmazott *newElement);

/**
 * @brief Kitöröl egy elemet a láncolt listából
 *
 * Bekér egy láncolt lista mutatójára mutató pointert, majd azt dereferálva
 * megkeresi, hogy benne van-e a bekért elem, és ha megtalálta akkor azt kifűzi
 *
 * @warning Ez a függvény nem ad vissza semmit, ha sikeres volt, ha nem
 *
 * @param head A láncolt lista eleje, melyből törölni szeretnénk
 * @param element Az elem melyet törölni szeretnénk
 */
void linkedListRemove(Alkalmazott **head, Alkalmazott *element);

/**
 * @brief Felszabadít egy láncolt lista elemet
 *
 * Egy egyedülálló láncolt lista elemet felszabadít
 *
 * @param node Az elem melyet fel szeretnénk szabadítani
 */
void freeNode(Alkalmazott *node);

/**
 * @brief Felszabadít egy egész láncolt listát
 *
 * Végigmegy az egész láncolt listán és minden elemet felszabadít egyesével.
 *
 * @param head A láncolt lista melyet fel szeretnénk szabadítani
 */
void linkedListFree(Alkalmazott **head);

/**
 * @brief Kiírja egy láncolt lista elemeit
 *
 * @brief Végigmegy egy láncolt listán majd minden elemét kiírja a szabványos kimenetre.
 *
 * @param head A láncolt lista melyet ki szeretnénk írni
 */
void linkedListPrint(Alkalmazott **head);

/**
 * @brief Megmondja, hogy egy láncolt lista milyen hosszú
 *
 * A bekért láncolt lista mutatójára mutató pointert dereferálja, és azt bejárja, majd minden
 * nem NULL érték találása esetén növel egy számlálót melyet a végén visszaad.
 *
 * @param head A láncolt lista melynek hosszát vizsgáljuk
 * @return Egy int mely tartalmazza a lista méretét
 */
int linkedListLen(Alkalmazott **head);

#endif //PROGRAMMING1_NAGYHF_LINKEDLIST_H

