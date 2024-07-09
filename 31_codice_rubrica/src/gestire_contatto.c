/*
 * gestire_contatto.c
 *
 *  Created on: 12 giu 2024
 *      Author: gruppo 31
 */


#include "gestire_contatto.h"
#include "gestire_file.h"
#include "gestire_rubrica.h"

rubrica* cancellaContatto(rubrica *rubrica1) {
    int contatto_trovato = 0;
    unsigned long long int numero_c;
    PulireSchermo(2, 0, 40, 90);
    gotoxy(2, 35);
    printf("\033[31mCancellare Contatto\033[34m");
    while (!contatto_trovato) {
        gotoxy(3, 1);
        printf("Scegliere il contatto da cancellare");
        gotoxy(4, 1);
        numero_c = cercareContatto(rubrica1);
        if (numero_c == 0) {
            PulireSchermo(3,0,10,70);
            return NULL;
        }
        contatto* nodoc = rubrica1->nodoContatti;
        contatto* prev = NULL;
        contatto* contatto_c = NULL;
        while (nodoc != NULL && !contatto_trovato) {
            if (nodoc->numero == numero_c) {
                contatto_c = nodoc;
                contatto_trovato = 1;
            } else {
                prev = nodoc;
                nodoc = nodoc->next;
            }
        }
        if (contatto_c == NULL) {
            gotoxy(5, 1);
            MostrareErrore(6);
            PulireSchermo(3, 1, 5, 100);
        } else {
            gotoxy(6,1);
            printf("Contatto da cancellare: %s %s %llu %d", contatto_c->nome, contatto_c->cognome, contatto_c->numero, contatto_c->stato);
            if (prev == NULL) {
                rubrica1->nodoContatti = contatto_c->next;
            } else {
                prev->next = contatto_c->next;
            }
            free(contatto_c);
            rubrica1->dimensione--;
            gotoxy(7, 1);
            printf("\033[36mContatto cancellato correttamente.\033[34m\n ");
            system("pause");
            PulireSchermo(3,0,40,90);
        }
    }
    return rubrica1;
}

void modificareContatto(rubrica *r) {
    int x = -10;
    int fine1 = 0;
    int fine3 = 0;
    int sceltam = 0;
    contatto* contatto_m = NULL;
    char nome_m[MAXLUNGNOME];
    char cognome_m[MAXLUNGCOGNOME];
    unsigned long long int numero_m;
    unsigned long long int numero_t;
    PulireSchermo(2, 0, 40, 60);
    gotoxy(2, 35);
    printf("\033[31mModificare Contatto\033[34m");
    while (x == -10) {
        gotoxy(3, 10);
        printf("Scegliere contatto da modificare");
        gotoxy(4, 10);
        numero_t = cercareContatto(r);
        if (numero_t == 0) {
            PulireSchermo(2,0,10,70);
            return;
        }
        if (verificaNumero(numero_t, r) == 0) {
            gotoxy(5, 9);
            x = -10;
            MostrareErrore(6);
            system("pause");
            PulireSchermo(4, 0, 4, 90);
            system("pause");
            PulireSchermo(6, 0, 30, 70);
            system("pause");
            if (contatto_m == NULL) {
                printf("errore");
            }
        }   else {
            x = 10;
        }
    }
    contatto * temp = r->nodoContatti;
    while (temp != NULL) {
        if (temp->numero == numero_t) {
            contatto_m = temp;
        }
        temp = temp->next;
    }
    if (contatto_m == NULL) {
        gotoxy(5,10);
        MostrareErrore(6);
        PulireSchermo(5, 1, 5, 90);
    }
    do {
        PulireSchermo(5, 0, 5, 90);
        gotoxy(6, 10);
        printf("Scegliere cosa modificare:");
        gotoxy(8, 10);
        printf(" 1) Nome ");
        gotoxy(9, 10);
        printf(" 2) Cognome");
        gotoxy(10, 10);
        printf(" 3) Num. Telefono ");
        gotoxy(11, 10);
        printf(" 4) Chiudi");
        gotoxy(13, 10);
        printf("Inserire opzione: ");
        scanf("%d", &sceltam);
        getchar();
        if (sceltam == 1) {
            do {
                gotoxy(14, 10);
                printf("Inserire nuovo nome: ");
                fgets(nome_m, MAXLUNGNOME, stdin);
                nome_m[strcspn(nome_m, "\n")] = '\0';
                gotoxy(15, 1);
                if (lunghezzaStringa(nome_m) > MAXLUNGNOME) {
                    gotoxy(15, 9);
                    MostrareErrore(1);
                    PulireSchermo(15, 0, 15, 100);
                } else {
                	gotoxy(14, 10);
                    printf("\033[36mIl nuovo nome e': %s \033[34m", nome_m);
                    scrivereNome(nome_m, contatto_m, r);
                }
            } while (lunghezzaStringa(nome_m) > MAXLUNGNOME);
        } else if (sceltam == 2) {
            do {
                gotoxy(14, 10);
                printf("Inserire nuovo cognome: ");
                fgets(cognome_m, MAXLUNGCOGNOME, stdin);
                cognome_m[strcspn(cognome_m, "\n")] = '\0';
                gotoxy(15, 1);
                if (lunghezzaStringa(cognome_m) > MAXLUNGCOGNOME) {
                    gotoxy(15, 9);
                    MostrareErrore(1);
                    PulireSchermo(15, 0, 15, 100);
                } else {
                	gotoxy(14, 10);
                    printf("\033[36mIl nuovo cognome e': %s \033[34m", cognome_m);
                    scrivereCognome(cognome_m, contatto_m, r);
                }
            } while (lunghezzaStringa(cognome_m) > MAXLUNGCOGNOME);
        } else if (sceltam == 3) {
            fine3 = 0;
            do {
                gotoxy(14, 10);
                printf("Inserire nuovo numero: ");
                scanf("%llu", &numero_m);
                gotoxy(15, 1);
                if (numero_m > 999999999999) {
                    gotoxy(15, 9);
                    PulireSchermo(14, 24, 15, 90);
                    MostrareErrore(2);
                } if (numero_m < 999999999) {
                    gotoxy(15, 9);
                    PulireSchermo(14, 24, 15, 90);
                    MostrareErrore(11);
                } if (verificaNumero(numero_m, r) == 1) {
                    gotoxy(15, 9);
                    PulireSchermo(14, 24, 15, 90);
                    MostrareErrore(3);
                }
            } while (numero_m > 999999999999 || numero_m < 999999999 || verificaNumero(numero_m, r) == 1);
            gotoxy(14, 10);
            printf("\033[36mIl nuovo numero e': +%llu \033[34m", numero_m);
            scrivereNumero(numero_m, contatto_m, r);
        } else if (sceltam == 4) {
            fine1 = 1;
        } else {
            gotoxy(15, 9);
            MostrareErrore(7);
        }
        PulireSchermo(0, 0, 14, 90);
        PulireSchermo(16, 0, 40, 90);
    } while (fine1 == 0);
    PulireSchermo(2,0,10,70);
    PulireSchermo(15, 0, 15, 90);
}

void AggiungereContattoPreferitiBloccati(rubrica* r) {
    int x = -10;
    int scelta = 0;
    int fine = 0;
    contatto* contatto_c = NULL;
    unsigned long long int numero_a;
    PulireSchermo(2, 1, 30, 90);
    gotoxy(2, 25);
    printf("\033[31mAggiungere Contatto ai preferiti o bloccati\033[34m");
    while (x == -10) {
        gotoxy(3, 1);
        printf("Scegliere contatto da aggiungere ai preferiti o bloccati");
        gotoxy(4, 1);
        numero_a = cercareContatto(r);
        if (numero_a == 0) {
            PulireSchermo(2,0,10,70);
            return;
        }
        if (verificaNumero(numero_a, r) == 0) {
            gotoxy(5, 1);
            x = -10;
            MostrareErrore(6);
            PulireSchermo(4, 1, 4, 90);
            PulireSchermo(6, 0, 30, 70);
        } else {
            x = 10;
        }
    }
    contatto * temp = r->nodoContatti;
    while (temp != NULL) {
        if (temp->numero == numero_a) {
            contatto_c = temp;
        }
        temp = temp->next;
    }
    if (contatto_c == NULL) {
        gotoxy(5,1);
        MostrareErrore(6);
        PulireSchermo(5, 0, 5, 90);
    }
    gotoxy(7, 10);
    if (contatto_c->stato == 2) {
        printf("\033[31mAvvertenza: questo contatto e' gia' nei preferiti\033[34m");
    } else if (contatto_c->stato == 3) {
        printf("\033[31mAvvertenza: questo contatto e' gia' nei bloccati\033[34m");
    }
    gotoxy(8, 3);
    printf("Scegliere se aggiungerlo ai preferiti (2), o bloccati (3), premere (0) per uscire");
    do {
        PulireSchermo(5, 0, 6, 90);
        gotoxy(9, 3);
        printf("Inserire Opzione: ");
        scanf("%d", &scelta);
        getchar();
        if (scelta == 2) {
            scrivereStato(2, contatto_c, r);
            fine = 1;
        } else if (scelta == 3) {
            scrivereStato(3, contatto_c, r);
            fine = 1;
        } else if (scelta == 0) {
            fine = 1;
        } else {
            gotoxy(10, 1);
            MostrareErrore(7);
            PulireSchermo(9,0,9,80);
        }
    } while (fine == 0);
    gotoxy(11,3);
    printf("\033[36mContatto aggiunto correttamente.\033[34m");
    system("pause");
    PulireSchermo(2, 0, 40, 90);
}

void RimuovereContattoPreferiti(rubrica* rub) {
    int x = -10;
    contatto* contatto_c = NULL;
    unsigned long long int numero_r;
    PulireSchermo(2, 1, 40, 90);
    gotoxy(2, 30);
    printf("\033[31mRimuovere contatto dai preferiti\033[34m");
    while (x == -10) {
        gotoxy(3, 1);
        printf("Scegliere il contatto da rimuovere dai preferiti");
        gotoxy(4, 1);
        numero_r = cercareContatto(rub);
        if (numero_r == 0) {
            PulireSchermo(2,0,10,70);
            return;
        }
        if (verificaNumero(numero_r, rub) == 0) {
            gotoxy(5, 1);
            x = -10;
            MostrareErrore(6);
            PulireSchermo(4, 1, 4, 90);
            PulireSchermo(6, 0, 30, 70);
        } else {
            x = 10; // Uscita dal ciclo se il contatto è stato trovato
        }
    }
    contatto *temp = rub->nodoContatti;
    while (temp != NULL && contatto_c == NULL) {
        if (temp->numero == numero_r) {
            contatto_c = temp;
        }
        temp = temp->next;
    }
    if (contatto_c == NULL) {
        gotoxy(5, 1);
        MostrareErrore(6);
        PulireSchermo(5, 0, 5, 90);
        return;
    }
    int contatto_trovato = 0;
    temp = rub->nodoContatti;
    while (temp != NULL && !contatto_trovato) {
        if (temp->numero == numero_r) {
            if (temp->stato == 2) {
                contatto_trovato = 1;
            }
        }
        temp = temp->next;
    }
    if (!contatto_trovato) {
        gotoxy(6, 1);
        MostrareErrore(8);
        printf("  ");
        system("pause");
        PulireSchermo(3, 0, 7, 90);
        return;
    }
    scrivereStato(1, contatto_c, rub);
    gotoxy(7,1);
    printf("\033[36mContatto rimosso correttamente dai preferiti. \n \033[34m");
    system("pause");
    PulireSchermo(2, 1, 40, 100);
}

void RimuovereContattoBloccati(rubrica* rub) {
    int x = -10;
    contatto* contatto_c = NULL;
    unsigned long long int numero_r;
    PulireSchermo(2, 1, 40, 90);
    gotoxy(2, 30);
    printf("\033[31mRimuovere contatto dai bloccati\033[34m");
    while (x == -10) {
        gotoxy(3, 1);
        printf("Scegliere il contatto da rimuovere dai bloccati");
        gotoxy(4, 1);
        numero_r = cercareContatto(rub);
        if (numero_r == 0) {
            PulireSchermo(2,0,10,70);
            return;
        }
        if (verificaNumero(numero_r, rub) == 0) {
            gotoxy(5, 1);
            x = -10;
            MostrareErrore(6);
            PulireSchermo(4, 1, 4, 90);
            PulireSchermo(6, 0, 30, 70);
        } else {
            x = 10;
        }
    }
    contatto *temp = rub->nodoContatti;
    while (temp != NULL && contatto_c == NULL) {
        if (temp->numero == numero_r) {
            contatto_c = temp;
        }
        temp = temp->next;
    }
    if (contatto_c == NULL) {
        gotoxy(5, 1);
        MostrareErrore(6);
        PulireSchermo(5, 0, 5, 90);
        return;
    }
    int contatto_trovato = 0;
    temp = rub->nodoContatti;
    while (temp != NULL && !contatto_trovato) {
        if (temp->numero == numero_r) {
            if (temp->stato == 3) {
                contatto_trovato = 1;
            }
        }
        temp = temp->next;
    }
    if (!contatto_trovato) {
        gotoxy(6, 1);
        MostrareErrore(9);
        printf("  ");
        system("pause");
        PulireSchermo(3, 0, 8, 90);
        return;
    }
    scrivereStato(1, contatto_c, rub);
    gotoxy(7,1);
    printf("\033[36mContatto rimosso correttamente dai Bloccati.\033[34m");
    system("pause");
    PulireSchermo(2, 1, 30, 90);
}

