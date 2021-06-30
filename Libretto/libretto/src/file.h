/*
 * file.h
 *
 *  Autore: Vincenzo Quagliarella
 *
 */

#ifndef FILE_H_
#define FILE_H_

#include <stdbool.h>
#include <stdio.h>
#include <errno.h> //consente di stabilire se esiste la directory del file
#include <direct.h> //consente di creare la directory se non esistesse


#define PERCORSO_FILE "../Files"

#define INDIRIZZO_NON_TROVATO -1

#define NUMERO_RECORDS_FILE 1



typedef enum {errore = 0, //valore che indica che c'è stato un errore tale da fermare il programma
			 fail, //valore che indica che c'è stato un errore ma non tale da fermare il programma feof(file)
			 okay //valore che indica che non c'è stato alcun errore
}Stato_file_t;




//permette di leggere il file
Stato_file_t leggiFile(const char percorso_file[], void* puntatore, size_t dim_puntatore, int offset, int whence);



//permette di cancellare il file
Stato_file_t cancellaFile(const char percorso_file[]);



//permette di scrivere nel file
Stato_file_t scriviFile(const char percorso_file[], void* puntatore, size_t dim_puntatore, long int offset, int whence);



//definisce se il file è valido oppure no
Stato_file_t isFileValido(const char percorso_file[]);



//restituisce l'ultimo indirizzo del file
long int ultimoIndirizzo(const char percorso_file[]);



//conta il numero di Records presenti nel file
int conteggioRecords(const char percorso_file[], size_t dim_records);



#endif
