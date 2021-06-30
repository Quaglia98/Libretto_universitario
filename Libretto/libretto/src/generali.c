/*
 * generali.c
 *
 *
 *      Autore: Vincenzo Quagliarella
 *
 *
 */

#include "generali.h"


void clearBuffer(void)
{
    while(getchar() != CARATTERE_NEWLINE){};
}



void aggiungiFineStringa(char stringa[])
{
	strcat(stringa, STRINGA_VUOTA);  //strcat concatena il secondo parametro alla fine del primo
}


void capitalizeStringa(char stringa[])
{
	unsigned short i = 0;
        //converte il primo carattere in maiuscolo
		stringa[i] = toupper(stringa[i]);

		for(i = 1; i < strlen(stringa); i++)
		{   //tutto il resto della stringa e' in minisculo
			stringa[i] = tolower(stringa[i]);
		}

}


bool isIncluso(const int min, const int max, const int number)
{

	bool incluso = false;

	if((number >= min) && (number <= max))
		incluso = true;

	return incluso;

}


bool isStringaVuota(const char string[])
{
	return (strlen(string) == 0);

}


bool isStringaAlfabetica(const char stringa[])
{
	bool alpha = false;
	unsigned short i = 0;

	for(i = 0; i < strlen(stringa); i++)
	{
		//mi restituisce true se il carattere e' alfabetico
		if(isalpha(stringa[i]))
		{
			alpha = true;
		}
		else
		{
			alpha = false;
			i = strlen(stringa);  //Esce dal for
		}
	}

	return alpha;
}


bool isStringaNumerica(const char stringa[])
{
	bool numero = false;
	unsigned short i = 0;

	for(i = 0; i < strlen(stringa); i++)
	{
		//restituisce true se il carattere e' un numero decimale
		if(isdigit(stringa[i]))
		{
			numero = true;
		}
		else
		{
			numero = false;
			i = strlen(stringa); //Esce dal for
		}
	}

	return numero;
}


