/*
 * gestire_rubrica.h
 *
 *  Created on: 12 giu 2024
 *      Author: gruppo 31
 */

#include "gestire_dati.h"
#include "gestire_file.h"

#ifndef GESTIRE_RUBRICA_H_
#define GESTIRE_RUBRICA_H_

rubrica *inserireNuovoContatto(rubrica* rubrica);

contatto* aggiungereARubrica(contatto* contatto_da_aggiungere, rubrica* rubrica);

int verificaNumero(unsigned long long numero_da_cercare, rubrica* rubrica);

unsigned long long int cercareContatto(rubrica* rubrica);

int verificaNomeLettera(char nome1[], char nome2[]);

int cercaNome(char nome_da_cercare[], rubrica* rubrica1, rubrica* rubrica);

void VisualizzareRubrica(rubrica* rub);

void ElencareContattiRubrica(const rubrica* rub, int stato1, int stato2, int stato3);

void OrdinareRubrica(rubrica* rub);

void OrdineCrescente(rubrica* rub, int valore);

void OrdineDecrescente(rubrica* rub, int valore);

void clearInputBuffer();

#endif
