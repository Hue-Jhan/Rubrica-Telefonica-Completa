/*
 * gestire_file.c
 *
 *  Created on: 12 giu 2024
 *      Author: gruppo 31
 */

#include <windows.h>
#include "gestire_file.h"
#include "gestire_rubrica.h"

void EsportareContattiSuFile(rubrica *rubrica) {
    PulireSchermo(2, 1, 30, 100);
    int fine = 0;
    int fine2 = 0;
    gotoxy(2, 30);
    printf("\033[31mEsportare Contatti su File\033[34m");
    FILE *file;
    char nome_file[MAXLUNGNOME]; // Considerando ".txt" e il terminatore null
    while (fine == 0) {
    	gotoxy(5, 5);
    	printf("Digitare il nome del file su cui esportare i contatti");
    	gotoxy(6, 5);
    	printf("Criteri: scrivere .txt alla fine ");
    	gotoxy(7, 5);
    	printf("Inserire nome file: ");
    	scanf("%20s", nome_file);
    	int lung = strlen(nome_file);
    	if (lung < 4 || nome_file[lung-4] != '.' || nome_file[lung-3] != 't' || nome_file[lung-2] != 'x' || nome_file[lung-1] != 't') {
    	            gotoxy(8, 3);
    	            MostrareErrore(13);
    	            PulireSchermo(7,0,7,80);
    	            fine2 = 1;
    	        } else {
    	            fine = 1;
    	            fine2 = 0;
    	        }
    	}
    if (fine2 = 1) {
    file = fopen(nome_file, "w");
    if (file == NULL) {
        gotoxy(8, 1);
        MostrareErrore(10);
        system("pause");
        return;
    }
    contatto *nodoC = rubrica->nodoContatti;
    while (nodoC != NULL) {
        fprintf(file,  "%-30s%-20s%-12llu %d\n", nodoC->nome, nodoC->cognome,
                nodoC->numero, nodoC->stato);
        nodoC= nodoC->next;
    }
    fclose(file);
    gotoxy(9, 5);
    if (leggereDimensione(rubrica) < 1) {
    	printf("\033[31mAvvertenza: rubrica non esportata perche' vuota \033[34m\n     ");
    } else {
    printf("\033[36mContatti esportati correttamente su %s. \033[34m\n     ", nome_file);
    }
    system("pause");
    PulireSchermo(3,0,40,90);
    }
}

void ImportareContattiDaFile(rubrica *rubrica) {
    PulireSchermo(2, 1, 40, 90);
    gotoxy(3, 30);
    printf("\033[31mImportare Contatti da File\033[34m");
    FILE *file;
    char nome_file[MAXLUNGNOME + 5]; // Considerando ".txt" e il terminatore null
    char nome1[MAXLUNGNOME];
    char cognome1[MAXLUNGCOGNOME];
    unsigned long long int numero1;
    int stato1;
    gotoxy(5, 10);
    printf("Digitare il nome del file su cui importare i contatti");
    gotoxy(6,10);
    printf("Criteri: scrivere .txt alla fine");
    gotoxy(7,10);
    printf("Inserire nome file: ");
    scanf("%20s", nome_file);
    file = fopen(nome_file, "r");
    if (file == NULL) {
        gotoxy(8, 8);
        MostrareErrore(12);
        printf("\n ");
        system("pause");
        return;
    }
    while (fscanf(file, "%s %s %llu %d", nome1, cognome1, &numero1, &stato1) == 4) {
        contatto* contatto_temporaneo = nuovoContatto();
        strcpy(contatto_temporaneo->nome, nome1);
        strcpy(contatto_temporaneo->cognome, cognome1);
        contatto_temporaneo->numero = numero1;
        contatto_temporaneo->stato = stato1;
        if (contatto_temporaneo != NULL) {
        aggiungereARubrica(contatto_temporaneo, rubrica);
        }
    }
    fclose(file);
    gotoxy(10,10);
    printf("\033[36mContatti importati correttamente da %s. \033[34m\n ", nome_file);
    system("pause");
    PulireSchermo(3,0,40,90);
}

void MostrareErrore(int er) {
    FILE *file = fopen(PATH, "r");
    if (file == NULL) {
        printf("\033[31m  Impossibile aprire il file degli errori.\033[34m");
        return;
    }
    int i = 0;
    int cont = 1;
    char errore[MAXLUNGSTRINGA];
    while (fgets(errore, MAXLUNGSTRINGA, file) != NULL) {
        if (cont == er) {
            printf("\033[31m %s \033[34m", errore);
            fclose(file);
            return;
        }
        cont++;
    }
    fclose(file);
    errore[i] = '\0';
    printf("%s", errore);
}

void gotoxy(int x, int y) {
    COORD CursorPos = { y, x };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, CursorPos);
    return;
}

void PulireSchermo(int rigaInizio, int colonnaInizio, int rigaFine, int colonnaFine) {
    int i = rigaInizio;
    while (i <= rigaFine) {
        int j = colonnaInizio;
        while (j <= colonnaFine) {
            gotoxy(i, j);
            printf(" ");
            j=j+1;
        }
        i=i+1;
    }
    gotoxy(0, 0);
    return;
}

void cambiaColore(int colore) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colore);
    return;
}

void impostaDimensioneConsole(int colonne, int righe) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Imposta la dimensione della console
    COORD size;
    size.X = colonne;
    size.Y = righe;
    SetConsoleScreenBufferSize(hConsole, size);

    // Imposta la dimensione della finestra della console
    SMALL_RECT rect;
    rect.Left = 0;
    rect.Top = 0;
    rect.Right = colonne - 1;
    rect.Bottom = righe - 1;
    SetConsoleWindowInfo(hConsole, TRUE, &rect);
}


