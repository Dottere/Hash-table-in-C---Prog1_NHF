//
// Created by lin on 11/13/25.
//

#ifndef PROGRAMMING1_NAGYHF_LINKEDLIST_H
#define PROGRAMMING1_NAGYHF_LINKEDLIST_H

#include "datastructs.h"



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

