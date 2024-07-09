/*
 * gestire_dati.c
 *
 *  Created on: 12 giu 2024
 *      Author: gruppo 31
 */




#include "gestire_dati.h"

// FUNZIONI DI INIZIALIZZAZIONE

rubrica* nuovaRubrica() {
    rubrica* rubrica1 = malloc(sizeof(rubrica));
    if (rubrica1 == NULL) {
        printf("Errore nell'allocazione della memoria");
        return NULL;
    }
    rubrica1->nodoContatti = NULL;
    rubrica1->dimensione = 0;
    return rubrica1;
}
contatto* nuovoContatto() {
    contatto* contatto1 = malloc(sizeof(contatto));
    if (contatto1 == NULL) {
        printf("Errore nell'allocazione della memoria");
        return NULL;
    }
    contatto1->next = NULL;
    return contatto1;
}

void liberaRubrica(rubrica *rubrica) {
    contatto* temp = rubrica->nodoContatti;
    contatto* next = NULL;
    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }
    free(rubrica);
}
bool listaVuota(contatto * lista) {
return lista == NULL;
}

// FUNZIONI D'ACCESSO

void scrivereNome(char nome_c[], contatto* cont, rubrica* rub) {
    contatto* temp = rub->nodoContatti;
    while (temp != NULL && temp->numero != cont->numero) {
        temp = temp->next;
    }
    if (temp != NULL) {
        strncpy(temp->nome, nome_c, MAXLUNGNOME - 1);
        temp->nome[MAXLUNGNOME - 1] = '\0';
    }
}
char* leggereNome(contatto* cont, rubrica* rub) {
    contatto* temp = rub->nodoContatti;
    static char nome1[MAXLUNGNOME];
    nome1[0] = '\0';
    while (temp != NULL && temp->numero != cont->numero) {
        temp = temp->next;
    }
    if (temp != NULL) {
        strncpy(nome1, temp->nome, MAXLUNGNOME - 1);
        nome1[MAXLUNGNOME - 1] = '\0'; // Assicura che la stringa sia terminata correttamente
        return nome1;
    }
    return NULL;
    free(temp);
}


void scrivereCognome(char cognome_c[], contatto* cont, rubrica* rub) {
    contatto* temp = rub->nodoContatti;
    while (temp != NULL && temp->numero != cont->numero) {
        temp = temp->next;
    }
    if (temp != NULL) {
        strncpy(temp->cognome, cognome_c, MAXLUNGCOGNOME - 1);
        temp->cognome[MAXLUNGCOGNOME - 1] = '\0'; // Assicura che la stringa sia terminata correttamente
    }
}
char* leggereCognome(contatto* cont, rubrica* rub) {
    contatto* temp = rub->nodoContatti;
    static char cognome1[MAXLUNGCOGNOME];
    cognome1[0] = '\0';
    while (temp != NULL && temp->numero != cont->numero) {
        temp = temp->next;
    }
    if (temp != NULL) {
        strncpy(cognome1, temp->cognome, MAXLUNGNOME - 1);
        cognome1[MAXLUNGNOME - 1] = '\0'; // Assicura che la stringa sia terminata correttamente
        return cognome1;
    }
    return NULL;
    free(temp);
}


int leggereStato(contatto* cont, rubrica* rub) {
    contatto* temp = rub->nodoContatti;
    int stato;
    while (temp != NULL && temp->numero != cont->numero) {
        temp = temp->next;
    }
    stato = temp->stato;
    return stato;
    free(temp);
}
void scrivereStato(int nuovo_stato, contatto* cont, rubrica* rub) {
    if (rub == NULL || rub->nodoContatti == NULL) {
        return;
    }
    contatto* temp = rub->nodoContatti;
    while (temp != NULL && temp->numero != cont->numero) {
        temp = temp->next;
    }
    if (temp == NULL) {
        MostrareErrore(6);
        return;
    }
    temp->stato = nuovo_stato;
}


void scrivereNumero(unsigned long long int nuovo_numero, contatto* cont, rubrica* rub) {
    if (rub == NULL || rub->nodoContatti == NULL) {
        printf("errore");
        return;
    }
    contatto* temp = rub->nodoContatti;
    while (temp != NULL && temp->numero != cont->numero) {
        temp = temp->next;
    }
    if (temp == NULL) {
    	MostrareErrore(6);
        return;
    }
    temp->numero = nuovo_numero;
}
unsigned long long int leggereNumero(contatto* cont, rubrica* rub) {
    contatto* temp = rub->nodoContatti;
    unsigned long long int num;
    while (temp->numero != cont->numero) {
        temp = temp->next;
    }
    num = temp->numero;
    return num;
}


int leggereDimensione(rubrica* rubrica) {
    return rubrica->dimensione;
}
void scrivereDimensione(int dim, rubrica* rubrica) {
    rubrica->dimensione = dim;
}

int lunghezzaStringa(char stringa[]) {
    int ln=0;
    int i=0;
    while (i<MAXLUNGNOME) {
	    if (stringa[i] != ' ') {
		    ln = ln + 1;
        }
        i = i + 1;
    }
    return ln;
}
