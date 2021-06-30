/*
 * generali.h
 *
 *  Autore: Vincenzo Quagliarella
 *
 */

#ifndef generali_h
  #define generali_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>


#define STRINGA_VUOTA "\0"

#define STRINGA_NEWLINE "\n"

#define CARATTERE_NEWLINE '\n'

#define STRINGA_SPAZIO " "

#define PERCENTUALE 100

#define BASE_STRTOL 10



//procedura che consente di convertire il primo carattere in maiuscolo e tutto il resto in minuscolo
void capitalizeStringa(char stringa[]);

//semplice procedura che aggiunge il carattere nullo alla fine della stringa per indicare la fine
void aggiungiFineStringa(char stringa[]);

//pulisce il buffer
void clearBuffer(void);

//funzione booleana che consente di stabilire se il numero è nel range [min,max]
bool isIncluso(const int min, const int max, const int numero);

//funzione booleana che consente di stabilire se la stringa è vuota
bool isStringaVuota(const char string[]);

//funzione booleana che consente di stabilire se la stringa è composta da solamente caratteri alfabetici
bool isStringaAlfabetica(const char stringa[]);

//funzione booleana che consente di stabilire se la stringa è composta da solamente caratteri numerici
bool isStringaNumerica(const char stringa[]);


#endif
