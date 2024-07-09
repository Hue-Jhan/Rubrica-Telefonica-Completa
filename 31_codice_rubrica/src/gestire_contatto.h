/*
 * gestire_contatto.h
 *
 *  Created on: 12 giu 2024
 *      Author: gruppo 31
 */

#include "gestire_dati.h"

#ifndef GESTIRE_CONTATTO_H_
#define GESTIRE_CONTATTO_H_

rubrica* cancellaContatto(rubrica *rubrica1);

void modificareContatto(rubrica *rubrica1);

void AggiungereContattoPreferitiBloccati(rubrica* rub);

void RimuovereContattoPreferiti(rubrica* rub);

void RimuovereContattoBloccati(rubrica* rub);

#endif
