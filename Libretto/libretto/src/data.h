/*
 * data.h
 *
 * Autore: Vincenzo Quagliarella
 *
 */

#ifndef DATA_H_
#define DATA_H_

#include <stdbool.h>
#include <string.h>

#include "generali.h"


#define MAX_LUNGHEZZA_DATA 11

#define SEPARATORE_DATA "/"

#define BISESTILE 4

#define SECOLO 100

#define SECOLO_BISESTILE 400

#define MAX_GIORNO 31

#define MIN_GIORNO 1

#define FEBBRAIO 29



//i membri indicano i rispettivi mesi dell'anno
typedef enum {gennaio=1,
	                     febbraio,
		                 marzo,
		                 aprile,
	                     maggio,
		                 giugno,
		                 luglio,
	                	 agosto,
	                 	 settembre,
	 	                 ottobre,
	                 	 novembre,
	                 	 dicembre
} Mese_t;



typedef struct
{
	unsigned short giorno; //membro che serve per memorizzare il giorno della data
	Mese_t mese; //membro che serve per memorizzare il mese della data
	unsigned short anno; //membro che server per memorizzare l'anno della data

} Data_t;




//funzione booleana che consente di capire se anno è bisestile oppure no
bool isAnnoBisestile(const unsigned short anno);



//funzione booleana che determina se data è valida oppure no e se è compresa tra anno minimo e anno massimo
bool isDataValida(const Data_t *data, const unsigned short anno_minimo, const unsigned short anno_massimo);



//procedura che mi consente di resettare la data passata come parametro
void resetData(Data_t *data);



//procedura che mi consente di settare una data che sia valida
void setData(Data_t *data, const unsigned short anno_minimo, const unsigned short anno_massimo, const char valore_input[]);


#endif
