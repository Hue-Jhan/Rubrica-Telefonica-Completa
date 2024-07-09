/*
 * rubrica.c
 *
 *  Created on: 12 giu 2024
 *      Author: gruppo 31
 */



#include <stdio.h>
#include <stdlib.h>
#include "gestire_dati.h"
#include "gestire_file.h"
#include "gestire_contatto.h"
#include "gestire_rubrica.h"

void menu(rubrica* rub1);

int main(void) {
    system("pause");
    PulireSchermo(0,0,1,90);
    impostaDimensioneConsole(90, 25);
    rubrica* rub1 = nuovaRubrica();
    menu(rub1);
    liberaRubrica(rub1);
    return 0;
}

void menu(rubrica* rub1) {
    char scelta = '0';
    int esci = 0;
    while (esci == 0) {
        PulireSchermo(0, 0, 50, 70);
        gotoxy(1, 40);
        cambiaColore(FOREGROUND_PURPLE1);
        printf(" RUBRICA \n");
        cambiaColore(FOREGROUND_LIGHT_BLUE);
        gotoxy(5, 13);
        printf("\033[1;35m 0) \033[34m Inserire nuovo contatto\n");
        gotoxy(6, 13);
        printf("\033[1;35m 1) \033[36m Modificare contatto esistente\n");
        gotoxy(7, 13);
        printf("\033[1;35m 2) \033[34m Cancellare contatto esistente\n");
        gotoxy(8, 13);
        printf("\033[1;35m 3) \033[36m Ordinare la rubrica\n");
        gotoxy(9, 13);
        printf("\033[1;35m 4) \033[34m Visualizzare la rubrica\n");
        gotoxy(10, 13);
        printf("\033[1;35m 5) \033[36m Aggiungere ai preferiti o bloccati\n");
        gotoxy(11, 13);
        printf("\033[1;35m 6) \033[34m Rimuovere dai preferiti");
        gotoxy(12, 13);
        printf("\033[1;35m 7) \033[36m Rimuovere dai bloccati");
        gotoxy(13, 13);
        printf("\033[1;35m 8) \033[34m Esportare rubrica su file");
        gotoxy(14, 13);
        printf("\033[1;35m 9) \033[36m Importare rubrica su file");
        gotoxy(15, 13);
        printf("\033[1;35m e) \033[34m Uscire\n");
        gotoxy(19, 20);
        printf("Inserire opzione: ");
        scanf(" %c", &scelta);
        getchar();
        if (scelta == '0') {
            inserireNuovoContatto(rub1);
            scelta = 0;
        } else if (scelta == '1') {
            modificareContatto(rub1);
            scelta = 0;
        } else if (scelta == '2') {
            cancellaContatto(rub1);
            scelta = 0;
        } else if (scelta == '3') {
            OrdinareRubrica(rub1);
            scelta = 0;
        } else if (scelta == '4') {
            VisualizzareRubrica(rub1);
            scelta = 0;
        } else if (scelta == '5') {
            AggiungereContattoPreferitiBloccati(rub1);
            scelta = 0;
        } else if (scelta == '6') {
            RimuovereContattoPreferiti(rub1);
            scelta = 0;
        } else if (scelta == '7') {
            RimuovereContattoBloccati(rub1);
            scelta = 0;
        } else if (scelta == '8') {
            EsportareContattiSuFile(rub1);
            scelta = 0;
        } else if (scelta == '9') {
            ImportareContattiDaFile(rub1);
            scelta = 0;
        } else if (scelta == 'e') {
            esci = 1;
        } else {
            scelta = 0;
            gotoxy(20, 7);
            MostrareErrore(7);
            PulireSchermo(19, 0, 19, 50);
        }
    }
    PulireSchermo(0, 0, 30, 90);
}
