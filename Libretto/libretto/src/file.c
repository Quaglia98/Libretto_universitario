/*
 * file.c
 *
 *      Autore: Vincenzo Quagliarella
 */

#include "file.h"

Stato_file_t isFileValido(const char percorso_file[])
{
	Stato_file_t file_valido = okay;
    FILE*file = NULL;
	errno = 0; //Settiamo momentaneamente errno a 0

	if(mkdir(PERCORSO_FILE)) //Crea la directory "Files" se non dovesse esistere
	{
	/* mkdir e' una funzione che si occupa di creare una directory nel percorso specificato se non dovesse esistere,
	 in particolare restituisce 0 se dovesse completare con successo , altrimenti -1 e in tal caso errno verrà settato
	 in base alla tipologia di errore, ad esempio EEXIST ci indica che la directory esiste già */
		if(errno != EEXIST)
		{
		   file_valido = errore;
		}
	}

	errno = 0;

	//Creo il file allo stesso percorso se non dovesse esistere
	file = fopen(percorso_file, "ab");

	if(!file)
	{  //errore nell'apertura
		file_valido = errore;
	}

	fclose(file);

	return file_valido;

}


Stato_file_t cancellaFile(const char percorso_file[])
{
	Stato_file_t file_cancellato = errore;

	if(!remove(percorso_file))
	{
		file_cancellato = okay;
	}

	return file_cancellato;
}



Stato_file_t leggiFile(const char percorso_file[], void* puntatore, size_t dim_puntatore, int offset, int whence)
{
	Stato_file_t lettura_file = okay;

	int numero_letture = 0;
	FILE*file = NULL;

	file = fopen(percorso_file, "rb");

	if(file)
	{
		//cambio posizione all'interno del file dove punta il puntatore
 		fseek(file, (offset * (long int) dim_puntatore), whence);
        //numero di elementi letti nel file
 		numero_letture = fread(puntatore, dim_puntatore, 1, file);

		if(numero_letture < 1)
		{
			if(feof(file))
			{
				//Il file e' finito
				lettura_file = fail;
			}
			else
			{
				//Errore durante la lettura del file
				lettura_file = errore;
			}
		}
	}
	else
	{
		//Il file non puo essere aperto
		lettura_file = errore;
	}

	fclose(file);

	return lettura_file;
}


Stato_file_t scriviFile(const char percorso_file[], void* puntatore, size_t dim_puntatore, long int offset, int whence)
{
	Stato_file_t scrittura_file = okay;
	FILE *file = NULL;
	int numero_scritture = 0;

	file = fopen(percorso_file, "rb+");
	if(file)
	{
		//cambio posizione all'interno del file dovo punta il puntatore
		fseek(file, (offset * (long int) dim_puntatore), whence);

		//numero di elementi memorizzati nel file
		numero_scritture = fwrite(puntatore, dim_puntatore, NUMERO_RECORDS_FILE, file);

		if(numero_scritture < NUMERO_RECORDS_FILE)
		{
			//fallimento scrittura
			scrittura_file = errore;
		}
	}
	else
	{
		//Non posso aprire il file
		scrittura_file = errore;
	}

	fclose(file);

	return scrittura_file;
}



long int ultimoIndirizzo(const char percorso_file[])
{
	FILE *file = NULL;
	long int indirizzo = INDIRIZZO_NON_TROVATO; //inizializzo a non trovato


	file = fopen(percorso_file, "rb");

	if(file)
	{
		//imposta la posizione alla fine del file in maniera tale da poter restituire l'ultimo indirizzo
	 	fseek(file, 0, SEEK_END);
	 	indirizzo = ftell(file);  //ftell mi indica la posizione corrente del file
	}

	fclose(file);

	return indirizzo;

}


int conteggioRecords(const char percorso_file[], size_t dim_records)
{
	int numero_records = 0;

	//verifica se il file non e' vuoto
	if(ultimoIndirizzo(percorso_file) != INDIRIZZO_NON_TROVATO)
	{
		//conta il numero di records
		numero_records = ultimoIndirizzo(percorso_file) / dim_records;
	}

	return numero_records;
}
