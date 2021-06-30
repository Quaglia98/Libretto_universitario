/*
 * main.h
 *
 *   Autore: Vincenzo Quagliarella
 *
 */

#ifndef MAIN_H_
#define MAIN_H_


#include <stdio.h>
#include <stdlib.h>

#include "libretto.h"

#define ID_FILE  "../Files/ID.dat"

#define STUDENTI_FILE "../Files/Studenti.dat"

#define INSEGNAMENTI_FILE "../Files/Insegnamenti.dat"

#define LIBRETTI_FILE "../Files/Libretti.dat"




//enum usata per definire tutte le opzioni del menu

typedef enum
{
	aggiungi_studente, //opzione che consente di aggiungere uno studente e il suo libretto al sistema
	modifica_studente, //opzione che consente di modificare uno studente ed eventualmente il suo libretto dal sistema
	cancella_studente, //opzione che consente di cancellare uno studente e il suo libretto dal sistema
	mostra_studenti, //opzione che consente di mostrare tutti gli studenti del sistema
	aggiungi_insegnamento, //opzione che consente di aggiungere un insegnamento al sistema
	modifica_insegnamento, //opzione che consente di modificare un insegnamento del sistema
	cancella_insegnamento, //opzione che consente di cancellare un insegnamento dal sistema
	mostra_insegnamenti, //opzione che consente di mostrare tutti gli insegnamenti del sistema
	aggiungi_libretto, //opzione che consente di aggiungere un libretto e lo studente associato al sistema
	modifica_libretto, //opzione che consente di modificare un libretto ed eventualmente lo studente associato del sistema
	cancella_libretto, //opzione che consente di cancellare un libretto e lo studente associato dal sistema
	mostra_media, //opzione che consente di mostrare la media di un insegnamento
	mostra_libretto, //opzione che consente di mostrare il libretto di uno specifico studente
	mostra_statistiche, //opzione che consente di mostrare statistiche
	ordina_studenti, //opzione che consente di ordinare tutti gli studenti del sistema
	ordina_insegnamenti, //opzione che consente di ordinare tutti gli insegnamenti del sistema
	aggiungi_esame, //opzione che consente di aggiungere un nuovo esame all'interno del libretto scelto
	esci, //opzione che consente di uscire dal programma
	opzione_nonvalida //opzione che consente di aggiungere una scelta non valida al menu
} menuIniziale_t;


 //Procedura che serve per mostrare il menu iniziale
void menuIniziale(void);


//Procedura che serve per mostrare l'introduzione al programma

void intro(void);


#endif
