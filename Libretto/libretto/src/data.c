/*
 * data.c
 *
 *  Autore: Vincenzo Quagliarella
 *      
 */


#include "data.h"


bool isAnnoBisestile(const unsigned short anno)
{
	bool bisestile = false;

	if(((anno % BISESTILE == 0) && !(anno % SECOLO == 0))  || (anno % SECOLO_BISESTILE == 0))
		bisestile = true;

	return bisestile;
}


bool isDataValida(const Data_t *data, const unsigned short anno_minimo, const unsigned short anno_massimo)
{
	bool valida = false;

	/*se il mese non e' compreso tra gennaio e dicembre e/o se
	l'anno non e' compreso tra minimo e massimo allora non e' una data valida*/
	if (isIncluso(gennaio,dicembre, data->mese) && isIncluso(anno_minimo,anno_massimo,data->anno))
	{
		      if(data->mese == febbraio)
		      {
		    	  if(isAnnoBisestile(data->anno))
		    	  {
		    		  valida = isIncluso(MIN_GIORNO,FEBBRAIO,data->giorno);   //se bisestile controllo con Febbraio da 29 giorni
		    	  }

		    	  else
		    	  {
		    		  valida = isIncluso(MIN_GIORNO,FEBBRAIO-1,data->giorno);  //non bisestile controllo con Febbraio da 28 giorni
		    	  }
		      }

	          else if(data->mese == aprile || data->mese == giugno || data->mese == settembre || data->mese == novembre)
              {
		          valida = isIncluso(MIN_GIORNO,MAX_GIORNO - 1 , data->giorno); //30 giorni
              }

	          else
	          {
		          valida = isIncluso(MIN_GIORNO,MAX_GIORNO,data->giorno);  //31 giorni
	          }

	}

  return valida;

}




void resetData(Data_t *data)
{
	data->giorno = 0;
	data->mese = 0;
	data->anno = 0;

}


void setData(Data_t *data, const unsigned short anno_minimo, const unsigned short anno_massimo, const char valore_input[])
{
	bool valida = false;

	char data_input[MAX_LUNGHEZZA_DATA] = STRINGA_VUOTA;

	char *giorno = NULL;
	char *mese = NULL;
	char *anno = NULL;

	resetData(data);

    do
    {
    	 valida = false;

    	 printf("\nInserisci la %s (gg%smm%saaaa): ", valore_input, SEPARATORE_DATA, SEPARATORE_DATA);
    	 scanf("%10[^\n]s", data_input);
    	 aggiungiFineStringa(data_input);
    	 clearBuffer();

    	 //Separa la data in giorno/mese/anno
    	 giorno = strtok(data_input, SEPARATORE_DATA);
    	 mese = strtok(NULL, SEPARATORE_DATA);
    	 anno = strtok(NULL, STRINGA_VUOTA);

    	 if(mese && giorno)
    	 {
    	 	//La stringa ha il giusto formato numerico
    	 	if(isStringaNumerica(giorno) && isStringaNumerica(mese) && isStringaNumerica(anno))
    	 	{
                //imposta i rispettivi valori di cui e' composta la data
    	 		data -> giorno = (unsigned short) strtoul(giorno, NULL, BASE_STRTOL);
    	 		data -> mese = (unsigned short) strtoul(mese, NULL, BASE_STRTOL);
    	 		data -> anno = (unsigned short) strtoul(anno, NULL, BASE_STRTOL);
    	 	}
    	 }

	     valida = !isDataValida(data, anno_minimo, anno_massimo);
	     if(valida)
	     {
	        printf("\nLa %s inserita non e' valida", valore_input);
	     }

    }
    while(valida);

}
