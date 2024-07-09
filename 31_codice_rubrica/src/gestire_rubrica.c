/*
 * gestire_rubrica.c
 *
 *  Created on: 12 giu 2024
 *      Author: gruppo 31
 */

#include "gestire_rubrica.h"

rubrica* inserireNuovoContatto(rubrica* rubrica) {
    char nome[MAXLUNGNOME];
    char cognome[MAXLUNGCOGNOME];
    unsigned long long int numero;
    int lunghezza;
    PulireSchermo(2, 0, 30, 70);
    gotoxy(3, 30);
    printf("\033[1;31m  Inserimento Nuovo Contatto \033[34m\n");
    contatto* nuovo_contatto = nuovoContatto();
    do {
        gotoxy(6, 10);
        printf("Nome: ");
        fgets(nome, MAXLUNGNOME+2, stdin);
        nome[strcspn(nome, "\n")] = '\0'; // Rimuove il newline da fgets
        lunghezza = strlen(nome);
        if (strlen(nome) >= MAXLUNGNOME - 1) {
                    clearInputBuffer();
                }
        if (lunghezza > MAXLUNGNOME) {
            gotoxy(7,8);
            MostrareErrore(1);
            PulireSchermo(6, 0, 6, 90);
        }
    } while (lunghezza > MAXLUNGNOME);
    strncpy(nuovo_contatto->nome, nome, MAXLUNGNOME);
    PulireSchermo(7, 0, 7, 70);
    do {
        gotoxy(8, 10);
        printf("Cognome: ");
        fgets(cognome, MAXLUNGCOGNOME+2, stdin);
        cognome[strcspn(cognome, "\n")] = '\0'; // Rimuove il newline da fgets
        lunghezza = strlen(cognome);
        if (strlen(cognome) >= MAXLUNGCOGNOME - 1) {
                clearInputBuffer();
            }
        if (lunghezza > MAXLUNGCOGNOME) {
            gotoxy(9,8);
            MostrareErrore(1);
            PulireSchermo(8, 1, 8, 100);
        }
    } while (lunghezza > MAXLUNGCOGNOME);
    strncpy(nuovo_contatto->cognome, cognome, MAXLUNGNOME);
    PulireSchermo(9, 0, 9, 50);
    do {
        gotoxy(10, 5);
        printf("\033[37m[Avvertimento per il numero: 10-12 cifre Max, non inserire \"+\" prima del prefisso] \033[34m");
        gotoxy(11,10);
        printf("Numero: ");
        scanf("%llu", &numero);
        while (getchar() != '\n'); // Pulisce il buffer di input
        if (numero > 999999999999) {
            gotoxy(12,8);
            MostrareErrore(2);
            PulireSchermo(10, 0, 11, 100);
        }
        if (numero < 999999999) {
            gotoxy(12,8);
            MostrareErrore(11);
            PulireSchermo(10, 0, 11, 100);
        }
        if (verificaNumero(numero, rubrica) == 1) {
            gotoxy(12,8);
            MostrareErrore(3);
            PulireSchermo(10, 0, 11, 100);
        }
    } while (numero > 999999999999 || numero < 999999999 || verificaNumero(numero, rubrica) == 1);
    nuovo_contatto->numero = numero;
    nuovo_contatto->stato = 1;
    aggiungereARubrica(nuovo_contatto, rubrica);
    gotoxy(15, 10);
    printf("\033[36mContatto creato e aggiunto correttamente \033[34m \n          ");
    system("pause");
    PulireSchermo(2, 0, 40, 87);
    return rubrica;
}

contatto* aggiungereARubrica(contatto* contatto_da_aggiungere, rubrica* rubrica1) {
    contatto* temp = rubrica1->nodoContatti;
    if (rubrica1 == NULL) {
        return NULL;
    }
    contatto_da_aggiungere->next = NULL;
    if (temp == NULL) {
        rubrica1->nodoContatti = contatto_da_aggiungere;
    } else {
        while (temp->next != NULL) {
            temp = temp->next; // Scorre fino all'ultimo contatto
        }
        temp->next = contatto_da_aggiungere;
    }
    rubrica1->dimensione++;
    return rubrica1->nodoContatti; // Restituisce il puntatore al primo contatto della rubrica
}

int verificaNumero(unsigned long long numero_da_cercare, rubrica* rubrica) {
    if (rubrica == NULL || rubrica->nodoContatti == NULL) {
        return 0; // Se la rubrica è vuota, il numero non può essere presente
    }
    contatto* temp = rubrica->nodoContatti;
    while (temp != NULL) {
        if (temp->numero == numero_da_cercare) {
            return 1; // Il numero è stato trovato nella rubrica
        }
        temp = temp->next;
    }
    return 0; // Il numero non è stato trovato
}

unsigned long long int cercareContatto(rubrica* rubrica1) {
    int j = 0, fine = 0, err1 = 1, err2 = 1;
    int p;
    char nome1[MAXLUNGNOME], cognome1[MAXLUNGCOGNOME];
    unsigned long long int numero_c;
    rubrica* rubrica_temporanea = nuovaRubrica();
    PulireSchermo(3, 0, 40, 80);
    gotoxy(3,37);
    printf("\033[1;31mCercare Contatto\033[34m\n");
    while (fine == 0) { // 0 per uscire
        err1 = 1;
        while (err1 == 1) {
            gotoxy(5,5);
            printf("Digitare il nome del contatto da cercare (0 per uscire)");
            gotoxy(6,5);
            printf("Nome: ");
            fgets(nome1, MAXLUNGNOME, stdin);
            nome1[strcspn(nome1, "\n")] = '\0'; // Rimuove il newline da fgets
            if (strcmp(nome1, "0") == 0)  {
                return 0;
                fine = 1; // Uscita se l'utente digita 0
                err1 = 0;
            } else if (cercaNome(nome1, rubrica1, rubrica_temporanea) == 0) {
                err1 = 1;
                gotoxy(7,3);
                MostrareErrore(4);
                PulireSchermo(6, 0, 6, 100);
            } else {
                err1 = 0;
            }
        }
        gotoxy(8, 5);
        printf("Ecco i risultati della ricerca per nome: ");
        gotoxy(9, 1);
        contatto * temp3 = rubrica_temporanea->nodoContatti;
        while (temp3 != NULL) {
            printf("    %s ", leggereNome(temp3, rubrica_temporanea));
            printf("%s ", leggereCognome(temp3, rubrica_temporanea));
            printf("+%llu \n", leggereNumero(temp3, rubrica_temporanea));
            temp3 = temp3->next;
            gotoxy(10 + j, 1);
            j++;
        }
        p = j;
        do {
            j=p;
            gotoxy(12 + j, 5);
            printf("Scrivere il cognome del contatto che si vuole selezionare (0 per uscire)");
            gotoxy(13+j, 5);
            printf("Cognome: ");
            fgets(cognome1, MAXLUNGCOGNOME, stdin);
            cognome1[strcspn(cognome1, "\n")] = '\0'; // Rimuove il newline da fgets
            if (strcmp(cognome1, "0") == 0)  {
                return 0;
            }
            contatto * temp = rubrica_temporanea->nodoContatti;
            while (temp != NULL && err2 != 0) {
                if (verificaNomeLettera(leggereCognome(temp, rubrica_temporanea), cognome1) == 1) {
                    numero_c = temp->numero;
                    err2 = 0;
                } else {
                    err2 = 1;
                    temp = temp->next;
                }
            }
            if (err2==1) {
                gotoxy(14+j, 3);
                MostrareErrore(5);
                PulireSchermo(12+j, 0, 13+j, 90);
            }
        } while (err2 == 1);
        rubrica_temporanea->nodoContatti = NULL;
        scrivereDimensione(0, rubrica_temporanea);
        fine = 1;
    }
    PulireSchermo(3, 0, 40, 90);
    return numero_c;
}

contatto* copiaContatto(contatto* originale) {
    if (originale == NULL) return NULL;
    contatto* nuovo = malloc(sizeof(contatto));
    strcpy(nuovo->nome, originale->nome);
    strcpy(nuovo->cognome, originale->cognome);
    nuovo->numero = originale->numero;
    nuovo->next = NULL;
    return nuovo;
}

void aggiungereARubricaTemporanea(contatto* contatto_originale, rubrica* rubrica_temporanea) {
    contatto* contatto_copia = copiaContatto(contatto_originale);
    aggiungereARubrica(contatto_copia, rubrica_temporanea);
}

int cercaNome(char nome_da_cercare[], rubrica* rubrica1, rubrica * rubrica_temporanea) {
    int i = 1;
    int esito = 0;
    contatto* temp = rubrica1->nodoContatti;
    while (temp != NULL) {
        if (verificaNomeLettera(nome_da_cercare, leggereNome(temp, rubrica1)) == 1) {
            esito = 1;
            aggiungereARubricaTemporanea(temp, rubrica_temporanea);
        }
        temp = temp->next;
        i++;
    }
    return esito;
}

int verificaNomeLettera(char nome1[], char nome2[]) {
    int esito = -1;
    if (strcmp(nome1, nome2) == 0) {
    esito = 1; // uguali
    } else {
    esito = 0; // diverse
    }
    return esito;
}

void VisualizzareRubrica(rubrica* rub) {
    int sceltav = 0;
    int esci = 0;
    int fine = 0;
    PulireSchermo(2, 0, 40, 90);
    gotoxy(2, 20);
    printf("\033[31mVisualizzare rubrica, preferiti o bloccati\033[34m");
    gotoxy(4, 2);
    printf("Scegliere se mostrare la rubrica (1), solo i preferiti (2) o bloccati (3), (0) uscire");
    do {
        PulireSchermo(5, 0, 8, 90);
        gotoxy(6, 5);
        printf("Inserire Opzione: ");
        scanf("%d", &sceltav);
        getchar();
        gotoxy(7,1);
        if (sceltav == 1) {
            ElencareContattiRubrica(rub, 1, 2, 2);
            fine = 1;
        } else if (sceltav == 2) {
            ElencareContattiRubrica(rub, 2, 2, 2);
            fine = 1;
        } else if (sceltav == 3) {
            ElencareContattiRubrica(rub, 3, 3, 3);
            fine = 1;
        } else if (sceltav == 0) {
            fine = 1;
        } else {
            gotoxy(8, 8);
            MostrareErrore(7);
        }
        sceltav = 0;
        printf("\n     ");
        system("pause");
    } while (fine != 1);
    PulireSchermo(2, 0, 40, 90);
}

void ElencareContattiRubrica(const rubrica* rub, int stato1, int stato2, int stato3) {
    contatto* nodoC = rub->nodoContatti;
    gotoxy(7,1);
    int z = 7;
    while (nodoC != NULL) {
        if (nodoC->stato == stato1 || nodoC->stato == stato2 || nodoC->stato == stato3) {
            gotoxy(z,4);
            printf("\033[36m %s ", nodoC->nome);
            gotoxy(z, MAXLUNGNOME + 4);
            printf(" %s ", nodoC->cognome);
            gotoxy(z, MAXLUNGCOGNOME + MAXLUNGNOME - 1);
            printf(" +%llu\n\033[34m", nodoC->numero);
            z++;
        }
        nodoC = nodoC->next;
    }
}

void OrdinareRubrica(rubrica* rub) {
    int scelta = -2;
    PulireSchermo(2, 1, 40, 90);
    gotoxy(2, 15);
    printf("\033[31mOrdinare Rubrica\033[34m");
    while (scelta != -1) {
        gotoxy(4, 7);
        printf("Scegliere come ordinare la rubrica");
        gotoxy(6, 1);
        printf(" 1) Ordine crescente");
        gotoxy(7, 1);
        printf(" 2) Ordine decrescente");
        gotoxy(8, 1);
        printf(" 0) Esci");
        gotoxy(10, 1);
        printf(" Inserire opzione: ");
        scanf("%d", &scelta);
        getchar();
        if (scelta == 1) {
            gotoxy(12, 1);
            printf("Scegliere l'ordine: ");
            gotoxy(14, 1);
            printf(" 3) Ordine per Nome ");
            gotoxy(15, 1);
            printf(" 4) Ordine per Cognome ");
            gotoxy(16, 1);
            printf(" 0) Uscire ");
            gotoxy(18, 1);
            printf(" Inserire opzione: ");
            scanf("%d", &scelta);
            if (scelta == 3) {
                OrdineCrescente(rub, 0);
                gotoxy(20,1);
                printf("\033[36mRubrica ordinata correttamente\033[34m \n ");
                system("pause");
            } else if (scelta == 4) {
                OrdineCrescente(rub, 1);
                gotoxy(20,1);
                printf("\033[36mRubrica ordinata correttamente\033[34m \n ");
                system("pause");
            } else if (scelta == 0) {
                scelta = -1;
            }
        } else if (scelta == 2) {
            gotoxy(12, 1);
            printf("Scegliere l'ordine: ");
            gotoxy(14, 1);
            printf(" 3) Ordine per Nome ");
            gotoxy(15, 1);
            printf(" 4) Ordine per Cognome ");
            gotoxy(16, 1);
            printf(" 0) Uscire ");
            gotoxy(18, 1);
            printf(" Inserire opzione: ");
            scanf("%d", &scelta);
            if (scelta == 3) {
                OrdineDecrescente(rub, 0);
                gotoxy(20,1);
                printf("\033[36mRubrica ordinata correttamente\033[34m \n ");
                system("pause");
            } else if (scelta == 4) {
                OrdineDecrescente(rub, 1);
                gotoxy(20,1);
                printf("\033[36mRubrica ordinata correttamente\033[34m \n ");
                system("pause");
            } else if (scelta == 0) {
                scelta = -1;
            }
        } else if (scelta == 0) {
            PulireSchermo(2, 0, 30, 90);
            scelta = -1;
        } else {
            gotoxy(12, 1);
            MostrareErrore(7);
            system("pause");
            PulireSchermo(10, 0, 11, 100);
        }
        PulireSchermo(2, 0, 30, 100);
    }
}

void OrdineCrescente(rubrica* rub, int valore) {
    contatto* nodoC = rub->nodoContatti;
    contatto* nodoSucc = NULL;
    contatto temp;
    int swap;
    do {
    swap = 0;
    nodoC = rub->nodoContatti;
    while (nodoC->next != NULL) {
        nodoSucc = nodoC->next;
        if (valore == 0) {
            if (strcmp(nodoC->nome, nodoSucc->nome) > 0) {
                // salva i valori di primo (maggiore) in temp
                strcpy(temp.nome, nodoC->nome);
                strcpy(temp.cognome, nodoC->cognome);
                temp.numero = nodoC->numero;
                temp.stato = nodoC->stato;
                // porta i valori del secondo (minore) nel primo
                strcpy(nodoC->nome, nodoSucc->nome);
                strcpy(nodoC->cognome, nodoSucc->cognome);
                nodoC->numero = nodoSucc->numero;
                nodoC->stato = nodoSucc->stato;
                // porta i valori del primo salvati in temp, nel secondo, scambio concluso
                strcpy(nodoSucc->nome, temp.nome);
                strcpy(nodoSucc->cognome, temp.cognome);
                nodoSucc->numero = temp.numero;
                nodoSucc->stato = temp.stato;
                swap = 1;
            }
        } else if (valore == 1) {
            if (strcmp(nodoC->cognome, nodoSucc->cognome) > 0) {
                // salva i valori di primo (maggiore) in temp
                strcpy(temp.nome, nodoC->nome);
                strcpy(temp.cognome, nodoC->cognome);
                temp.numero = nodoC->numero;
                temp.stato = nodoC->stato;
                // porta i valori del secondo (minore) nel primo
                strcpy(nodoC->nome, nodoSucc->nome);
                strcpy(nodoC->cognome, nodoSucc->cognome);
                nodoC->numero = nodoSucc->numero;
                nodoC->stato = nodoSucc->stato;
                // porta i valori del primo salvati in temp, nel secondo, scambio concluso
                strcpy(nodoSucc->nome, temp.nome);
                strcpy(nodoSucc->cognome, temp.cognome);
                nodoSucc->numero = temp.numero;
                nodoSucc->stato = temp.stato;
                swap = 1;
            }
        }
        nodoC = nodoC->next;
    }
    } while (swap);
}

void OrdineDecrescente(rubrica* rub, int valore) {
    int swap;
    contatto *nodoC;
    contatto *nodoSucc;
    contatto temp;
    do {
    swap = 0;
    nodoC = rub->nodoContatti;
    while (nodoC != NULL && nodoC->next != NULL) {
        nodoSucc = nodoC->next;
        if (valore == 0) {  // Ordine per nome
                if (strcmp(nodoC->nome, nodoSucc->nome) < 0) {
                    // Scambia i dati dei contatti
                    strcpy(temp.nome, nodoC->nome);
                    strcpy(temp.cognome, nodoC->cognome);
                    temp.numero = nodoC->numero;
                    temp.stato = nodoC->stato;

                    strcpy(nodoC->nome, nodoSucc->nome);
                    strcpy(nodoC->cognome, nodoSucc->cognome);
                    nodoC->numero = nodoSucc->numero;
                    nodoC->stato = nodoSucc->stato;

                    strcpy(nodoSucc->nome, temp.nome);
                    strcpy(nodoSucc->cognome, temp.cognome);
                    nodoSucc->numero = temp.numero;
                    nodoSucc->stato = temp.stato;
                    swap = 1;
                }
            } else if (valore == 1) {  // Ordine per cognome
                if (strcmp(nodoC->cognome, nodoSucc->cognome) < 0) {
                    // Scambia i dati dei contatti
                    strcpy(temp.nome, nodoC->nome);
                    strcpy(temp.cognome, nodoC->cognome);
                    temp.numero = nodoC->numero;
                    temp.stato = nodoC->stato;
                    // porta i valori del secondo (minore) nel primo
                    strcpy(nodoC->nome, nodoSucc->nome);
                    strcpy(nodoC->cognome, nodoSucc->cognome);
                    nodoC->numero = nodoSucc->numero;
                    nodoC->stato = nodoSucc->stato;
                    // porta i valori del primo salvati in temp, nel secondo, scambio concluso
                    strcpy(nodoSucc->nome, temp.nome);
                    strcpy(nodoSucc->cognome, temp.cognome);
                    nodoSucc->numero = temp.numero;
                    nodoSucc->stato = temp.stato;
                    swap = 1;
                }
            }
            nodoC = nodoC->next;
        }
    } while (swap);
}

void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
