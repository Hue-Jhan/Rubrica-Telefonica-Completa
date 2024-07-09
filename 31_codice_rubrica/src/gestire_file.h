/*
 * gestire_file.h
 *
 *  Created on: 12 giu 2024
 *      Author: gruppo 31
 */


#include "gestire_dati.h"

#ifndef GESTIRE_FILE_H_
#define GESTIRE_FILE_H_

void EsportareContattiSuFile(rubrica* rubrica);
void ImportareContattiDaFile(rubrica *rubrica);
void MostrareErrore(int er);
void gotoxy(int x, int y);
void PulireSchermo(int rigaInizio, int colonnaInizio, int rigaFine, int colonnaFine);
void outputSchermo(const char *c);
void setConsoleColor(int color);
void cambiaColore(int colore);
void impostaDimensioneConsole(int colonne, int righe);

#endif
