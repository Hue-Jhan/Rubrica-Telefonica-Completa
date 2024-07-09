/*
 * gestire_dati.h
 *
 *  Created on: 12 giu 2024
 *      Author: gruppo 31
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#ifndef GESTIRE_DATI_H_
#define GESTIRE_DATI_H_

#define PATH "31_errori.txt"   // Specificare il path in cui si trova il file degli errori C:\\users/utente...31_errori.txt
#define MAXLUNGNOME 20
#define MAXLUNGCOGNOME 30
#define MAXLUNGSTRINGA 80

#define FOREGROUND_LIGHT_BLUE (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define FOREGROUND_RED1 (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define FOREGROUND_YELLOW1 (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_PURPLE1 (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY)




typedef struct contatto {
    char nome[MAXLUNGNOME];
    char cognome[MAXLUNGCOGNOME];
    unsigned long long int numero;
    int stato;
    struct contatto *next;
} contatto;

typedef struct rubrica {
    contatto* nodoContatti;
    int dimensione;
} rubrica;


rubrica* nuovaRubrica();
contatto* nuovoContatto();
void liberaRubrica(rubrica *rubrica);
bool listaVuota(contatto * lista);

void scrivereNome(char nome_c[], contatto* cont, rubrica* rub);
char* leggereNome(contatto* cont, rubrica* rub);

void scrivereCognome(char cognome_c[], contatto* cont, rubrica* rub);
char* leggereCognome(contatto* cont, rubrica* rub);

int leggereStato(contatto* cont, rubrica* rub);
void scrivereStato(int nuovo_stato, contatto* cont, rubrica* rub);

void scrivereNumero(unsigned long long int nuovo_numero, contatto* cont, rubrica* rub);
unsigned long long int leggereNumero(contatto* cont, rubrica* rub);

int leggereDimensione(rubrica* rub);
void scrivereDimensione(int dim, rubrica* rub);

int lunghezzaStringa(char stringa[]);

#endif
