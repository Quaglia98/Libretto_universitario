/*
 * libretto.c
 *
 *  Autore: Vincenzo Quagliarella
 *
 */

#include "libretto.h"
#include "main.h"



void setStringa(char stringa[], const char messaggio_input[])
{
	bool flag = false;

	strcpy(stringa, STRINGA_VUOTA); // Reset della stringa

	do
	{
		flag = false;

		printf("\nInserisci %s: ", messaggio_input);
		scanf("%30s", stringa);
		aggiungiFineStringa(stringa);


		//Testo la stringa se e' valida

		flag = isStringaVuota(stringa) || !isStringaAlfabetica(stringa) || !isIncluso(MIN_LENGHT_STRING, MAX_LENGHT_STRING, (int) strlen(stringa));
		if(flag)
		{
			printf("\n%s che hai inserito non e' accettabile dal sistema", messaggio_input);
		}

	}
	while(flag);

}


void setNumeroInput(int *input, const int min, const int max, const char messaggio_input[], const char messaggio_errore[])
{
	bool okay = false;
	char numero_input[MAX_LUNGHEZZA_NUMERO] = STRINGA_VUOTA;

	do
	{
	    okay = false;

		printf("\n%s", messaggio_input);
		scanf("%10s", numero_input);
		aggiungiFineStringa(numero_input);
		clearBuffer();

		//Controllo se la stringa non e' un numero oppure se e' vuota
		okay = !isStringaNumerica(numero_input) || isStringaVuota(numero_input);

		if(!okay)
		{
			//conversione della stringa in int
			*input = (int) strtol(numero_input, NULL, BASE_STRTOL);

			if(!isIncluso(min, max, *input))
			{
			  //il numero non e' incluso nel range
			  okay = true;
			}

		}
		else
		{
			//La stringa non e' un numero
			okay = true;
		}

		if(okay)
		{
			printf("\n%s", messaggio_errore);
		}

	}
	while(okay);

}



bool confrontoIdStudente(const Studente_t *studente, const int *id)
{
	bool uguali = false;

	if(!(studente->cancellato))    //controllo prima se e' cancellato
	{
		if(studente->matricola == *id)    //confronto id e matricola
		{
			uguali = true;
		}
	}

	return uguali;
}



bool confrontoIdInsegnamento(const Insegnamento_t *insegnamento, const int *id)
{
	bool uguali = false;

	if(!(insegnamento->cancellato))    //controllo prima se e' cancellato
	{
		if(insegnamento->id == *id)    //confronto gli id
		{
			uguali = true;
		}
	}

	return uguali;
}


bool confrontoIdLibretto(const Libretto_t *libretto, const int *id)
{
	bool uguali = false;

	if(!(libretto->cancellato))    //controllo prima se e' cancellato
	{
		if(libretto->matricola == *id)    //confronto gli id
			{
				uguali = true;
			}
	}

	return uguali;
}


int prendiIndirizzo(const char percorso_file[], const int *id, int selezione)
{
    Stato_file_t operazione = errore;
	Studente_t studente;
	Insegnamento_t insegnamento;
	Libretto_t libretto;
	int i = 0;
	int indirizzo_id = INDIRIZZO_NON_TROVATO; //inizialmente lo imposto a non trovato

	//resetto tutti gli insiemi
	resetStudenteLibretto(&studente,&libretto);
	resetInsegnamento(&insegnamento);


	if(selezione == STUDENTE)
	{
		do
		{
			//leggo gli studenti
			operazione = leggiFile(percorso_file, &studente, sizeof(studente), i, SEEK_SET);
			if(operazione == okay)
			{
				//verifico se gli id sono uguali e in caso prendo l'indirizzo
				if(confrontoIdStudente(&studente, id))
				{
					indirizzo_id = i;
				}
			}
				i++;
		}
		while(operazione == okay);
	}
	else if(selezione == INSEGNAMENTO)
	{
		do
		{
			//leggo gli insegnamenti
			operazione = leggiFile(percorso_file, &insegnamento, sizeof(insegnamento), i, SEEK_SET);
			if(operazione == okay)
			{
				//verifico se gli id sono uguali e in caso prendo l'indirzzo
				if(confrontoIdInsegnamento(&insegnamento, id))
				{
					indirizzo_id = i;
				}
			}
			i++;
		}
		while(operazione == okay);
	}
	else
	{
		do
		{
            //leggo i libretti
			operazione = leggiFile(percorso_file, &libretto, sizeof(libretto), i, SEEK_SET);
			if(operazione == okay)
			{
				//verifico se gli id sono uguali e in caso prendo l'indirzzo
				if(confrontoIdLibretto(&libretto, id))
				{
					indirizzo_id = i;
				}
			}
			i++;
		}
		while(operazione == okay);
	}

	return indirizzo_id;
}


int prendiIndirizzoInput(const char percorso_file_studente[], const char percorso_file_insegnamento[], const char percorso_file_libretto[], const char messaggio_input[], const char messaggio_errore[], int selezione)
{
	Stato_file_t operazione = errore;
	Studente_t studente;
	Insegnamento_t insegnamento;
	Libretto_t libretto;
	int i = 0;
	int id_input = 0; //e' la variabile che conserverà l'ID che inseriremo da tastiera
	int indirizzo_id = INDIRIZZO_NON_TROVATO;

	//resetto tutti gli insiemi
	resetStudenteLibretto(&studente,&libretto);
    resetInsegnamento(&insegnamento);


	if(selezione == STUDENTE)
	{
			if(mostraRecords(percorso_file_studente, percorso_file_insegnamento, percorso_file_libretto, STUDENTE))
			{
				//Imposta la matricola dello studente (ID)
				setNumeroInput(&id_input, INT_MIN, INT_MAX, messaggio_input, messaggio_errore);
				do
				{
					//Lettura Studenti
					operazione = leggiFile(percorso_file_studente, &studente, sizeof(Studente_t), i, SEEK_SET);
					if(operazione == okay)
					{
						//confronta gli id ed imposta l'id_input da restituire
						if(confrontoIdStudente(&studente, &id_input))
						{
							indirizzo_id = i;
						}
					}
					i++;
				}
				while(operazione == okay);
			}
	}
	else if(selezione == INSEGNAMENTO)
	{
            if(mostraRecords(percorso_file_studente, percorso_file_insegnamento, percorso_file_libretto, INSEGNAMENTO))
			{
				//Imposta l'ID dell'Insegnamento
            	setNumeroInput(&id_input, INT_MIN, INT_MAX, messaggio_input, messaggio_errore);
				do
				{
					//lettura Insegnamenti
					operazione = leggiFile(percorso_file_insegnamento, &insegnamento, sizeof(Insegnamento_t), i, SEEK_SET);
					if(operazione == okay)
					{
						//confronta gli id ed imposta l' indirizzo_id da restituire
						if(confrontoIdInsegnamento(&insegnamento, &id_input))
						{
							indirizzo_id = i;
						}
					}
					i++;
				}
				while(operazione == okay);
			}
	}
	else
	{
		   if(mostraRecords(percorso_file_studente, percorso_file_insegnamento, percorso_file_libretto, LIBRETTO))
		   {
			   //Imposta l'id (matricola) del libretto
			   setNumeroInput(&id_input, INT_MIN, INT_MAX, messaggio_input, messaggio_errore);
			   do
			   {
				   //lettura libretto
				   operazione = leggiFile(percorso_file_libretto, &libretto, sizeof(Libretto_t), i, SEEK_SET);
				   if(operazione == okay)
				   {
					   //confronta gli id ed imposta l'indirizzo_id da restituire
					   if(confrontoIdLibretto(&libretto, &id_input))
					   {
						   indirizzo_id = i;
					   }
				   }
				   i++;
			   }
			   while(operazione == okay);
		   }
	}


	return indirizzo_id;
}



void resetStudenteLibretto(Studente_t*studente,Libretto_t *libretto)
{

	unsigned short i = 0;

	studente->matricola = 0;
	libretto->matricola = 0;

	strcpy(studente -> nome, STRINGA_VUOTA);
	strcpy(libretto -> nome_studente, STRINGA_VUOTA);

	strcpy(studente -> cognome, STRINGA_VUOTA);
	strcpy(libretto -> cognome_studente, STRINGA_VUOTA);

	strcpy(studente -> corso, STRINGA_VUOTA);
	strcpy(libretto -> corso_studente, STRINGA_VUOTA);

	resetData(&studente -> nascita);

	studente->immatricolazione = 0;

	libretto ->numero_esami = 0;

	for(i=0; i<libretto->numero_esami; i++)
	{
		//resetta tutti gli esami del libretto
		resetEsame(&libretto->esame[i]);
	}

	studente->cancellato = false;
	libretto->cancellato = false;
}



void resetStudente(Studente_t*studente)
{

	studente->matricola = 0;

	strcpy(studente -> nome, STRINGA_VUOTA);

	strcpy(studente -> cognome, STRINGA_VUOTA);

	strcpy(studente -> corso, STRINGA_VUOTA);

	resetData(&studente -> nascita);

	studente->immatricolazione = 0;

}




void setStudenteLibretto(Studente_t *studente, Libretto_t *libretto, const int *matricola)
{

	unsigned short i = 0;
    int conteggio_esami = 0;

	resetStudenteLibretto(studente,libretto);


	studente->matricola=*matricola;
    libretto->matricola=*matricola;

	setStringa(studente -> nome, "Il Nome dello Studente");
	capitalizeStringa(studente -> nome);
	strcpy(libretto->nome_studente,studente->nome);

	setStringa(studente -> cognome, "Il Cognome dello Studente");
	capitalizeStringa(studente -> cognome);
	strcpy(libretto -> cognome_studente, studente -> cognome);

	setStringa(studente -> corso, "Il Corso di studio dello Studente");
	capitalizeStringa(studente -> corso);
    strcpy(libretto -> corso_studente, studente -> corso);

    setNumeroInput((int*) &studente -> immatricolazione, MIN_ANNO_IMMATRICOLAZIONE, MAX_ANNO_IMMATRICOLAZIONE, "Inserisci l'Anno di immatricolazione dello Studente: ","L'anno di immatricolazione inserito non e' valido");

    //lo studente universitario deve per forza essere maggiorenne
	setData(&studente -> nascita, MIN_ANNO_NASCITA, (studente -> immatricolazione  - MAGGIORE_ETA), "Data di nascita dello Studente");



	//imposta il numero di esami che il libretto contiene [0-20]
	setNumeroInput((int*) &conteggio_esami, MIN_ESAMI, MAX_ESAMI, "Inserisci il numero di esami che lo Studente ha sostenuto: ", "Il numero di esami da te inserito non e' valido");

	libretto -> numero_esami = conteggio_esami;

	for(i=0; i<conteggio_esami ; i++)
	{

        setEsame(&libretto->esame[i],libretto,i);
    }

	studente -> cancellato = false;
	libretto -> cancellato = false;
}



void leggiStudente(const Studente_t *studente)
{
	if(!studente -> cancellato) //controlla se lo studente e' cancellato
	{
		printf("\n|%6d     |%14s    |%20s    |%14s              |%5hu                           |  %2.2hu%s%2.2d%s%4.4hu           |",
				studente -> matricola,
				studente -> nome, studente -> cognome, studente -> corso,
			    studente -> immatricolazione, studente->nascita.giorno, SEPARATORE_DATA, studente->nascita.mese, SEPARATORE_DATA, studente->nascita.anno);
		printf("\n+-----------+------------------+------------------------+----------------------------+--------------------------------+-----------------------+");
	}
}


void leggiInsegnamento(const Insegnamento_t *insegnamento)
{
	if(!insegnamento -> cancellato) //controlla se l'insegnamento e' cancellato
	{
		printf("\n|%4d  |%30s         |%5d    |%20s        |%14s         |%2hu              |", insegnamento -> id,insegnamento->nome, insegnamento->cfu,
				insegnamento ->cognome_prof, insegnamento->nome_prof, insegnamento->anno_corso);
		printf("\n+------+---------------------------------------+---------+----------------------------+-----------------------+----------------+");
	}
}


void leggiLibretto(const Libretto_t *libretto)
{

	if(!libretto->cancellato) //controlla se il libretto e' cancellato
	{
		unsigned short i = 0;
		printf("\n");
		printf("\n+--------------+----------------------+------------------------+----------------------+");
		printf("\n|   Matricola  |        Nome          |       Cognome          |    Corso di Studio   |");
	    printf("\n+--------------+----------------------+------------------------+----------------------+");


		printf("\n|%7d       |%14s        |%20s    |%14s        |", libretto->matricola, libretto->nome_studente, libretto->cognome_studente, libretto->corso_studente);
		printf("\n+--------------+----------------------+------------------------+----------------------+");

		printf("\n+-----------+------------------------------------+----------------+----------------+");
		printf("\n|  N.Esame  |              Nome Esame            |    CFU Esame   |    Voto Esame  |");
	    printf("\n+-----------+------------------------------------+----------------+----------------+");

		 //legge tutti gli esami
		for(i=0 ; i<libretto->numero_esami ; i++)
		{
		    printf("\n|%5d      |%30s      |%8d        |%8d        |", i+1, libretto->esame[i].nome, libretto->esame[i].cfu, libretto->esame[i].voto);
		    printf("\n+-----------+------------------------------------+----------------+----------------+");

	    }

		printf("\n");
	}

}


void leggiMediaInsegnamento(const Insegnamento_t *insegnamento, double media)
{

	if(!insegnamento->cancellato) //controlla se l'insegnamento non e' cancellato
	{
		//alle informazioni dell'insegnamento si aggiunge la media

		printf("\n|%4d  |%30s         |%5d    |%20s        |%14s         |%2hu              |%.2f     |", insegnamento -> id, insegnamento->nome,insegnamento->cfu,
				                insegnamento ->cognome_prof, insegnamento->nome_prof, insegnamento->anno_corso, media);
	    printf("\n+------+---------------------------------------+---------+----------------------------+-----------------------+----------------+-------------+");
	}
}


void mostraInfoStudente(void)
{
	    printf("\n\n\n+---------------------+--------------------+");
		printf("\n|  Numero dell'info   |       Info         |");
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |       Nome         |", nome_studente);
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |      Cognome       |", cognome_studente);
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |       Corso        |", corso_studente);
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |  Immatricolazione  |", immatricolazione);
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |   Data di nascita  |", nascita);
		printf("\n+---------------------+--------------------+");
}


void mostraInfoInsegnamento(void)
{
	    printf("\n\n\n+---------------------+--------------------+");
		printf("\n|  Numero dell'info   |       Info         |");
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |        Nome        |", nome_insegnamento);
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |        CFU         |", cfu);
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |    Anno di Corso   |", anno_corso);
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |    Cognome Prof    |", cognome_prof);
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |      Nome Prof     |", nome_prof);
		printf("\n+---------------------+--------------------+");
}

void mostraInfoLibretto()
{
	    printf("\n\n\n+---------------------+--------------------+");
		printf("\n|  Numero dell'info   |       Info         |");
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |    Nome Studente   |", nome_studente_l);
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |  Cognome Studente  |", cognome_studente_l);
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |   Corso di Studio  |", corso_studente_l);
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |        Esame       |", esame);
		printf("\n+---------------------+--------------------+");

}


void mostraInfoEsame()
{

        printf("\n\n\n+---------------------+--------------------+");
		printf("\n|  Numero dell'info   |       Info         |");
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |     Nome Esame     |", nome_esame);
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |     CFU Esame      |", cfu_esame);
		printf("\n+---------------------+--------------------+");
		printf("\n|         %d           |     Voto Esame     |", voto_esame);
		printf("\n+---------------------+--------------------+");

}

void tipoSortStudenti(void)
{
	printf("\n\n\n+----------------------------+-----------------------------------+");
	printf("\n|  Numero Dell'Ordinamento   |          Tipo Ordinamento         |");
	printf("\n+----------------------------+-----------------------------------+");
	printf("\n|          %d                 |        Matricola Crescente        |", cresc_matricola_studente);
	printf("\n+----------------------------+-----------------------------------+");
	printf("\n|          %d                 |       Matricola Decrescente       |", dec_matricola_studente);
	printf("\n+----------------------------+-----------------------------------+");
	printf("\n|          %d                 |           Nome Crescente          |", cresc_nome_studente);
	printf("\n+----------------------------+-----------------------------------+");
	printf("\n|          %d                 |          Nome Decrescente         |", dec_nome_studente);
	printf("\n+----------------------------+-----------------------------------+");
	printf("\n|          %d                 |          Cognome Crescente        |", cresc_cognome_studente);
	printf("\n+----------------------------+-----------------------------------+");
	printf("\n|          %d                 |         Cognome Decrescente       |", dec_cognome_studente);
	printf("\n+----------------------------+-----------------------------------+");


}



void tipoSortInsegnamenti(void)
{
	printf("\n\n\n+----------------------------+-----------------------------------+");
	printf("\n|  Numero Dell'Ordinamento   |          Tipo Ordinamento         |");
	printf("\n+----------------------------+-----------------------------------+");
	printf("\n|          %d                 |            ID Crescente           |", cresc_id_insegnamento);
	printf("\n+----------------------------+-----------------------------------+");
	printf("\n|          %d                 |           ID Decrescente          |", dec_id_insegnamento);
	printf("\n+----------------------------+-----------------------------------+");
	printf("\n|          %d                 |           Nome Crescente          |", cresc_nome_insegnamento);
	printf("\n+----------------------------+-----------------------------------+");
	printf("\n|          %d                 |          Nome Decrescente         |", dec_nome_insegnamento);
	printf("\n+----------------------------+-----------------------------------+");
	printf("\n|          %d                 |            CFU Crescenti          |", cresc_cfu);
	printf("\n+----------------------------+-----------------------------------+");
	printf("\n|          %d                 |           CFU Decrescenti         |", dec_cfu);
	printf("\n+----------------------------+-----------------------------------+");


}


void mostraStatistiche(void)
{
	printf("\n\n\n+----------------------------+-----------------------------------+");
		printf("\n|     Numero Statistica      |             Statistica            |");
		printf("\n+----------------------------+-----------------------------------+");
		printf("\n|          %d                 |   Percentuale di esami superati   |", percentuale_esami_superati);
		printf("\n+----------------------------+-----------------------------------+");
		printf("\n|          %d                 |        Numero di 30 e lode        |", numero_lodi);
		printf("\n+----------------------------+-----------------------------------+");
		printf("\n|          %d                 |     Numero di Insegnamenti Prof   |", numero_insegnamenti_prof);
		printf("\n+----------------------------+-----------------------------------+");
}


Stato_file_t sceltaStatistica(const char percorso_file_studente[], const char percorso_file_libretto[], const char percorso_file_insegnamento[])
{
	mostraStatistiche();
	Stato_file_t operazione = okay;
	statistiche_t scelta_statistica = percentuale_esami_superati;


    //Prendo in input la scelta
	setNumeroInput((int *) &scelta_statistica, percentuale_esami_superati, numero_insegnamenti_prof, "Inserisci la tua scelta: ", "La scelta che hai preso non e' valida");

	switch(scelta_statistica)
	{
		  case percentuale_esami_superati:

			  if(conteggioRecords(percorso_file_studente,sizeof(Studente_t)) == NO_RECORDS)
			  {
				  printf("\n\nNon ci sono studenti per poter calcolare la percentuale");

			  }
			  else
			  {
			     //calcola la percentuale di esami superati dello studente passato in input
			     operazione = percentualeEsami(percorso_file_studente,percorso_file_libretto);
			     if(operazione == okay)
			     {

				    printf("\n\nLa percentuali di esami superati dallo Studente e' stata visualizzata");
			     }

			     else
			     {
			    	  printf("\n\nErrore durante la lettura del Libretto");
			     }
			  }

	          printf("\n\n");

		      break;
		  case numero_lodi:

			  if(conteggioRecords(percorso_file_libretto,sizeof(Libretto_t)) == NO_RECORDS)
			  {
			  	  printf("\n\nNon ci sono libretti per poter contare i 30 e lode presenti");
			  }
			  else
			  {
			     //calcola il numero totale di 30 e lodi presenti nel sistema
                 operazione = numeroLodi(percorso_file_libretto);
			     if(operazione != errore)
			     {
				    printf("\n\nIl numero totale di 30 e lode e' stato visualizzato");
			     }
			     else
			     {
			        printf("\n\nErrore durante la lettura del libretto");
			     }
			  }
			  printf("\n\n");

			  break;
		 case numero_insegnamenti_prof:

			 if(conteggioRecords(percorso_file_insegnamento,sizeof(Insegnamento_t)) == NO_RECORDS)
			 {
				 printf("\n\nNon ci sono Insegnamenti, per poter controllare i Prof");
		     }

			 else if(numeroInsegnamentiProf(percorso_file_insegnamento))
			 {
				 //calcola il numero totale di Insegnamenti di cui il Prof passato in input e' titolare
				 printf("\n\nIl numero di Insegnamenti (di cui il Prof e' titolare) e' stato visualizzato");
			 }

			 else
			 {
			   printf("\n\nErrore durante la lettura degli Insegnamenti");
			 }
			 printf("\n\n");

			 break;
		 default:
			 break;
	}

	return operazione;
}



void resetInsegnamento(Insegnamento_t*insegnamento)
{
	insegnamento->id = 0;
	insegnamento->cfu = 0;
	strcpy(insegnamento -> nome, STRINGA_VUOTA);
	strcpy(insegnamento -> cognome_prof, STRINGA_VUOTA);
	strcpy(insegnamento -> nome_prof, STRINGA_VUOTA);
	insegnamento -> anno_corso = 0;
	insegnamento-> cancellato = false;
}


void setInsegnamento(Insegnamento_t *insegnamento, const int *idinsegnamento, const char percorso_file_libretto[])
{
	resetInsegnamento(insegnamento);

	insegnamento->id=*idinsegnamento;

	setStringa(insegnamento -> nome, "Il Nome dell'Insegnamento");
	capitalizeStringa(insegnamento -> nome);

    setNumeroInput(&insegnamento -> cfu, MIN_CFU, MAX_CFU, "Inserisci i CFU dell'Insegnamento: ","I CFU dell'insegnamento inserito non sono validi");

    setStringa(insegnamento -> cognome_prof, "Il Cognome del prof che insegna il Corso");
    capitalizeStringa(insegnamento -> cognome_prof);

    setStringa(insegnamento -> nome_prof, "Il Nome del prof che insegna il Corso");
    capitalizeStringa(insegnamento -> nome_prof);

    setNumeroInput((int*)&insegnamento -> anno_corso, MIN_ANNO_CORSO, MAX_ANNO_CORSO, "Inserisci l'Anno del corso di studi: ","L'anno del corso di studi inserito non e' valido");


	insegnamento -> cancellato = false;
}




Stato_file_t aggiungi(const char percorso_file_studente[], const char percorso_file_insegnamento[], const char percorso_file_libretto[], const int *id, int selezione)
{
	Stato_file_t operazione = okay;
	Stato_file_t operazione2 = okay;

	Studente_t studente;
	Insegnamento_t insegnamento;
	Libretto_t libretto;

	resetStudenteLibretto(&studente,&libretto);
	resetInsegnamento(&insegnamento);

    //Studente e libretto vengono aggiunti allo stesso modo in quanto sono strettamente in relazione
	if((selezione == STUDENTE) || (selezione == LIBRETTO))
	{


		setStudenteLibretto(&studente, &libretto, id); //Prende le informazioni dello studente e del suo libretto
		//Scrive Studente e libretto nei file
		operazione = scriviFile(percorso_file_studente, &studente, sizeof(Studente_t), 0, SEEK_END);
		operazione2 = scriviFile(percorso_file_libretto,&libretto,sizeof(Libretto_t),0,SEEK_END);
	}
	else
	{
		setInsegnamento(&insegnamento, id, percorso_file_libretto); //Prende le informazioni dell'Insegnamento
		//Scrive l'Insegnamento nel file
		operazione = scriviFile(percorso_file_insegnamento, &insegnamento, sizeof(Insegnamento_t), 0, SEEK_END);
	}


    //restituisce 0 solamente se una o entrambe le operazioni danno errore
	return (operazione && operazione2);

}



Stato_file_t mostraMedia(const char percorso_file_insegnamento[], const char percorso_file_libretto[])
{
   Stato_file_t operazione = okay;
   Insegnamento_t insegnamento;
   Libretto_t libretto;

   //resetto gli insiemi interessati
   resetLibretto(&libretto);
   resetInsegnamento(&insegnamento);

   int indirizzo_record = INDIRIZZO_NON_TROVATO;

   //Controllo prima se non ci sono records, in tal caso imposto l'operazione ad errore
   if((conteggioRecords(INSEGNAMENTI_FILE, sizeof(Insegnamento_t)) == NO_RECORDS ))
   {
	   operazione = errore;
   }

   //C'e' almeno un record nel file insegnamento
   else
   {

	   //prendo l'indirizzo nel file dove c'e' l'ID dell'insegnamento preso in input
	     indirizzo_record = prendiIndirizzoInput(NULL,percorso_file_insegnamento,NULL,"Inserisci l'ID dell'Insegnamento di cui vuoi visualizzare la media: ", "L'ID dell'Insegnamento da te inserito non e' valido, riprova",INSEGNAMENTO);

	     //controllo se l'insegnamento e' stato trovato
	     if(indirizzo_record != INDIRIZZO_NON_TROVATO)
	     {


	          printf("\n+------+---------------------------------------+---------+----------------------------+-----------------------+----------------+-------------+");
	          printf("\n|  ID  |             Nome Insegnamento         |   CFU   |        Cognome Prof        |       Nome Prof       | Anno di Corso  |  Media voti |");
	          printf("\n+------+---------------------------------------+---------+----------------------------+-----------------------+----------------+-------------+");

	          //legge l'insegnamento
	          operazione = leggiFile(percorso_file_insegnamento, &insegnamento, sizeof(Insegnamento_t), indirizzo_record, SEEK_SET);
	          if(operazione == okay)
	          {
	     	     unsigned short i = 0;
	             unsigned short j = 0;
	             int numero_insegnamenti = 0;
	             int somma_voti = 0;
	             double media = 0.0;

	     	       do
	     	       {
	     	    	   //legge tutti i libretti per cercare l'insegnamento
	     	    	   operazione = leggiFile(percorso_file_libretto, &libretto, sizeof(Libretto_t),i,SEEK_SET);
	     	    	   if(operazione == okay)
	     	    	   {

	     	    	       for(j=0; j<libretto.numero_esami; j++)
	     	    	       {
	     	    	    	  //confronta il nome dell'esame e il nome dell'insegnamento
	     	    		      if(!strcmp(insegnamento.nome,libretto.esame[j].nome))
	     	    		      {
	     	    		    	 //calcola la somma dei voti e quante volte e' stato trovato l'insegnamento nei libretti
	                           numero_insegnamenti++;
	                           somma_voti += libretto.esame[j].voto;
	     	    		      }
	     	    	       }
	     	    	   }
	     	    	   i++;
	     	       }
	     	       while(operazione == okay);


	     	       if(operazione != errore)
	     	       {

	     	          //calcola media solamente se e' stato trovato almeno una volta l'Insegnamento nel libretto
	     	    	  if(numero_insegnamenti > 0)
	     	    	  {
	     	             media = (double)somma_voti/(double)numero_insegnamenti;
	     	    	  }

	                  leggiMediaInsegnamento(&insegnamento, media);

	     	       }

	          }

	          else
	          {
	           //errore nella lettura del file;
	  	     operazione = errore;
	          }

	     }


	     else
	     {   //l'indirizzo non e' stato trovato
	  	   operazione = errore;
	     }

   }


   return operazione;
}





Stato_file_t mostraLibretto(const char percorso_file_studente[], const char percorso_file_libretto[])
{
   Libretto_t libretto;
   Studente_t studente;
   Stato_file_t operazione = okay;
   resetLibretto(&libretto);
   int indirizzo_libretto = INDIRIZZO_NON_TROVATO;
   //variabile che mi serve per capire la matricola contenuta nel record del file
   int matricola = 0;

   if((conteggioRecords(percorso_file_studente,sizeof(Studente_t))== NO_RECORDS))
   {

	   operazione = errore;
   }

   else
   {
	  int indirizzo_record = prendiIndirizzoInput(percorso_file_studente,NULL,NULL,"Inserisci la Matricola dello Studente di cui vuoi visualizzare il libretto: ", "La matricola da te inserita non e' valida, riprova",STUDENTE);

	      if(indirizzo_record != INDIRIZZO_NON_TROVATO)
	      {
	    	   //leggo il file a quell'indirizzo e salvo la matricola
	    	   operazione = leggiFile(percorso_file_studente, &studente, sizeof(Studente_t), indirizzo_record, SEEK_SET);
               if(operazione == okay)
               {
            	    matricola = studente.matricola;
                   //prendo l'indirizzo dove si trova il libretto con la stessa matricola
                   indirizzo_libretto = prendiIndirizzo(percorso_file_libretto,&matricola,LIBRETTO);

                   operazione = leggiFile(percorso_file_libretto, &libretto, sizeof(Libretto_t), indirizzo_libretto, SEEK_SET);
                   if(operazione == okay)
                   {
                      leggiLibretto(&libretto);
                   }
                   else
                   {   //Errore nella lettura del libretto
               	       operazione = errore;
                   }
                }

               else
               {   //errore nella lettura dello studente
            	   operazione = errore;
               }
	      }


	      else
	      {   //L'indirizzo non e' stato trovato
	   	   operazione = errore;
	      }
   }


    return operazione;
}



Stato_file_t modifica(const char percorso_file_studente[], const char percorso_file_insegnamento[], const char percorso_file_libretto[], int selezione)
{
	Stato_file_t operazione = okay;

	Studente_t studente;
	Insegnamento_t insegnamento;
    Libretto_t libretto;
    Data_t data;

    //variabili che servono per la modifica dell'informazione richiesta

	infoStudente_t info_input_studente = matricola_studente -1;
	infoInsegnamento_t info_input_insegnamento = id_insegnamento -1;
	infoLibretto_t info_input_libretto = matricola_studente_l -1;
	infoEsame_t info_input_esame = nome_esame;

	long int indirizzo_record = INDIRIZZO_NON_TROVATO;
    long int indirizzo_studente = INDIRIZZO_NON_TROVATO;
    long int indirizzo_libretto = INDIRIZZO_NON_TROVATO;

    int matricola = 0;

    unsigned short i = 0;

    //resetta tutti gli insiemi
	resetStudenteLibretto(&studente, &libretto);
	resetInsegnamento(&insegnamento);



	if(selezione == STUDENTE)
	{

		//Prende l'indirizzo dello Studente che l'utente vuole modificare
		indirizzo_record = prendiIndirizzoInput(percorso_file_studente, percorso_file_insegnamento, percorso_file_libretto, "Inserisci la Matricola dello Studente che vuoi modificare: ", "L'ID dello Studente che vuoi modificare non ï¿½ valido", STUDENTE);

		if(indirizzo_record != INDIRIZZO_NON_TROVATO)
		{

			//legge lo studente e il libretto da file
			operazione = leggiFile(percorso_file_studente, &studente, sizeof(Studente_t), indirizzo_record, SEEK_SET);
			if(operazione == okay)
			{
				mostraInfoStudente();

				//Prende l'informazione dello Studente che l'utente vuole modificare
				setNumeroInput((int *) &info_input_studente, nome_studente, nascita, "Inserisci il numero dell'informazione che vuoi modificare: ", "Il numero dell'informazione da te inserito non e' valido");

				switch(info_input_studente)
				{
					case nome_studente:
						setStringa(studente.nome, "Il Nome dello Studente aggiornato");
						capitalizeStringa(studente.nome);
						//prendo l'indirizzo del libretto dove c'e' la stessa matricola
						matricola = studente.matricola;
						indirizzo_libretto = prendiIndirizzo(percorso_file_libretto,&matricola,LIBRETTO);
						//legge il libretto dove si trova la stessa matricola
						operazione = leggiFile(percorso_file_libretto,&libretto,sizeof(Libretto_t), indirizzo_libretto, SEEK_SET);
						if(operazione == okay)
						{
							strcpy(libretto.nome_studente,studente.nome);
						}
						else
						{
							//errore nella lettura del libretto
							operazione = errore;
						}

						break;
					case cognome_studente:
						setStringa(studente.cognome, "Il Cognome dello Studente aggiornato");
						capitalizeStringa(studente.cognome);
						//prendo l'indirizzo del libretto dove c'e' la stessa matricola
					    matricola = studente.matricola;
						indirizzo_libretto = prendiIndirizzo(percorso_file_libretto,&matricola,LIBRETTO);
						//legge il libretto dove si trova la stessa matricola
						operazione = leggiFile(percorso_file_libretto,&libretto,sizeof(Libretto_t), indirizzo_libretto, SEEK_SET);
						if(operazione == okay)
						{
						   strcpy(libretto.cognome_studente,studente.cognome);
						}
						else
						{
						  //errore nella lettura del libretto
						  operazione = errore;
						}

						break;
					case corso_studente:
						setStringa(studente.corso,"Il Corso di studio aggiornato");
						capitalizeStringa(studente.corso);
						//prendo l'indirizzo del libretto dove c'e' la stessa matricola
						matricola = studente.matricola;
						indirizzo_libretto = prendiIndirizzo(percorso_file_libretto,&matricola,LIBRETTO);
						//legge il libretto al corretto indirizzo dove si trova la stessa matricola
						operazione = leggiFile(percorso_file_libretto,&libretto,sizeof(Libretto_t), indirizzo_libretto, SEEK_SET);
						if(operazione == okay)
						{
						   strcpy(libretto.corso_studente,studente.corso);
						}
						else
						{
						  //errore nella lettura del libretto
						  operazione = errore;
						}
						break;
					case immatricolazione:
						data = studente.nascita;
						//lo studente universitario deve essere almeno maggiorenne.
						setNumeroInput((int*)&studente.immatricolazione, (studente.nascita.anno + MAGGIORE_ETA), MAX_ANNO_IMMATRICOLAZIONE , "Inserisci l'anno di immatricolazione aggiornato: ","L'anno di immatricolazione da te inserito non e' valido");
                        studente.nascita = data;
						break;
					case nascita:
						//lo studente deve essere almeno maggiorenne.
						setData(&studente.nascita, MIN_ANNO_NASCITA, (studente.immatricolazione - MAGGIORE_ETA), "Data di nascita aggiornata dello Studente");
						break;
					default:
						break;
				}

				//Scrive lo studente e il suo libretto modificato nei rispettivi file
				operazione = scriviFile(percorso_file_studente, &studente, sizeof(Studente_t), indirizzo_record, SEEK_SET);
				if(operazione == okay)
				{   //scrive nel file libretti solamente se e' stata modificata una delle sottostanti informazioni
					if((info_input_studente == nome_studente) || (info_input_studente == cognome_studente) || (info_input_studente == corso_studente))
					{
						 operazione = scriviFile(percorso_file_libretto,&libretto, sizeof(Libretto_t), indirizzo_libretto, SEEK_SET);
					}

				}
				else
				{   //errore nella scrittura dello studente
					operazione = errore;
				}
			}
		    else
		    {
				//Errore durante la lettura dello studente
				operazione = errore;
		    }
		}
	    else
        {
		//L'indirizzo non e' stato trovato
		operazione = errore;
	    }
	}

	else if (selezione == INSEGNAMENTO)
	{
		//Prende l'indirizzo dell'Insegnamento che l'utente vuole modificare
		indirizzo_record = prendiIndirizzoInput(percorso_file_studente, percorso_file_insegnamento, percorso_file_libretto, "Inserisci l'ID dell'insegnamento che vuoi modificare: ", "L'ID dell'insegnamento che vuoi modificare non ï¿½ valido", INSEGNAMENTO);

		if(indirizzo_record != INDIRIZZO_NON_TROVATO)
		{
			//indirizzo trovato

			//legge l'insegnamento da file
			operazione= leggiFile(percorso_file_insegnamento, &insegnamento, sizeof(Insegnamento_t), indirizzo_record, SEEK_SET);
			if(operazione == okay)
			{
				mostraInfoInsegnamento();

				//Prende l'informazione dell'Insegnamento che l'utente vuole modificare
				setNumeroInput((int *) &info_input_insegnamento, nome_insegnamento, nome_prof, "Inserisci il numero dell'informazione che vuoi modificare: ", "Il numero dell'informazione da te inserito non e' valido");

				switch(info_input_insegnamento)
				{
					case nome_insegnamento:
						setStringa(insegnamento.nome, "Il Nome dell'Insegnamento aggiornato");
						capitalizeStringa(insegnamento.nome);
						break;
					case cfu:
						setNumeroInput((int*) &insegnamento.cfu, MIN_CFU,MAX_CFU,"Inserisci i CFU dell'Insegnamento aggiornati: ","I CFU dell'Insegnamento che hai inserito non sono validi");
						break;
					case anno_corso:
						setNumeroInput((int*) &insegnamento.anno_corso, MIN_ANNO_CORSO, MAX_ANNO_CORSO, "Inserisci l'Anno del corso di Insegnamento aggiornato: ","L'anno del corso che hai inserito non Ã¨ valido");
						break;
					case cognome_prof:
						setStringa(insegnamento.cognome_prof, "Il Cognome del Prof titolare dell'Insegnamento aggiornato");
						capitalizeStringa(insegnamento.cognome_prof);
						break;
					case nome_prof:
						setStringa(insegnamento.nome_prof, "Il Nome del Prof titolare dell'Insegnamento aggiornato");
						capitalizeStringa(insegnamento.nome_prof);
						break;
					default:
						break;
				}

				//Scrive l'insegnamento modificato nel file
				operazione = scriviFile(percorso_file_insegnamento, &insegnamento, sizeof(Insegnamento_t), indirizzo_record, SEEK_SET);
			}
			else
			{
				//Errore durante la lettura dell'insegnamento
				operazione = errore;
			}
		}
		else
		{
			//Indirizzo non trovato
			operazione = errore;
		}
	}

	else
	{
		//Prende la matricola del Libretto che l'utente vuole modificare
		indirizzo_record = prendiIndirizzoInput(percorso_file_studente, percorso_file_insegnamento, percorso_file_libretto, "Inserisci la matricola del libretto che vuoi modificare: ", "La matricola del libretto che vuoi modificare non e' valida", LIBRETTO);

		if(indirizzo_record != INDIRIZZO_NON_TROVATO)
		{
		   //indirizzo trovato


		   operazione = leggiFile(percorso_file_libretto, &libretto, sizeof(Libretto_t), indirizzo_record, SEEK_SET);
		   if(operazione == okay)
		   {
				mostraInfoLibretto();

				//Prende l'informazione del libretto che l'utente vuole modificare
				setNumeroInput((int *) &info_input_libretto, nome_studente_l, esame, "Inserisci il numero dell'informazione che vuoi modificare: ", "Il numero dell'informazione da te inserito non e' valido");

				switch(info_input_libretto)
				{
					case nome_studente_l:
						setStringa(libretto.nome_studente, "Il Nome dello Studente associato al libretto aggiornato");
						capitalizeStringa(libretto.nome_studente);
						//prende l'indirizzo degli studenti dove si trova la stessa matricola
						matricola = libretto.matricola;
					    indirizzo_studente = prendiIndirizzo(percorso_file_studente,&matricola,STUDENTE);
						//legge lo studente al corretto indirizzo dove si trova la stessa matricola
						operazione = leggiFile(percorso_file_studente,&studente,sizeof(Studente_t), indirizzo_studente, SEEK_SET);
						if(operazione == okay)
						{
						 strcpy(studente.nome,libretto.nome_studente);
						}
						else
						{
						  //errore nella lettura del libretto
						  operazione = errore;
						}
					    break;
				    case cognome_studente_l:
				    	setStringa(libretto.cognome_studente, "Il Cognome dello Studente associato al libretto aggiornato");
				    	capitalizeStringa(libretto.cognome_studente);
				    	//prende l'indirizzo degli studenti dove si trova la stessa matricola
				    	matricola = libretto.matricola;
				    	indirizzo_studente = prendiIndirizzo(percorso_file_studente,&matricola,STUDENTE);
				    	//legge lo studente al corretto indirizzo dove si trova la stessa matricola
				    	operazione = leggiFile(percorso_file_studente,&studente,sizeof(Studente_t), indirizzo_studente, SEEK_SET);
				    	if(operazione == okay)
				    	{
				    	   strcpy(studente.cognome,libretto.cognome_studente);
				    	}
				    	else
				    	{
				    		//errore nella lettura del libretto
				    		 operazione = errore;
				    	}

				    	break;
				    case corso_studente_l:
				    	setStringa(libretto.corso_studente, "Il Corso di studio dello Studente associato al libretto aggiornato");
				    	capitalizeStringa(libretto.corso_studente);
				    	//prende l'indirizzo degli studenti dove si trova la stessa matricola
				    	matricola = libretto.matricola;
				    	indirizzo_studente = prendiIndirizzo(percorso_file_studente,&matricola,STUDENTE);
				    	//legge lo studente al corretto indirizzo dove si trova la stessa matricola
				    	operazione = leggiFile(percorso_file_studente,&studente,sizeof(Studente_t), indirizzo_studente, SEEK_SET);
				    	if(operazione == okay)
				    	{
				    	   strcpy(studente.corso,libretto.corso_studente);
				    	}
				    	else
				    	{
				    	   //errore nella lettura del libretto
				    	   operazione = errore;
				    	}

				    	break;
				    case esame:
		                if(libretto.numero_esami > 0)
		                {
				    	    mostraInfoEsame();

				    	    //Prende in input l'informazione dell'esame che l'utente vuole modificare
				    	    setNumeroInput((int*)&info_input_esame,nome_esame,voto_esame,"Inserisci il numero dell'informazione che vuoi modificare: ", "Il numero dell'informazione da te inserito non e' valido");


                            switch(info_input_esame)
                            {

                                 case nome_esame:

                                	//Imposta l'esame che l'utente vuole modificare
                                	setNumeroInput((int *) &i,MIN_ESAMI + 1 , libretto.numero_esami, "Inserisci il numero dell'esame che vuoi modificare: ","Il numero dell'esame da te inserito non e' valido");

                            	    setStringa(libretto.esame[i-1].nome,"Il nome aggiornato dell'Esame in libretto: ");
                            	    capitalizeStringa(libretto.esame[i-1].nome);
                            	    break;
                                 case cfu_esame:


                                	 setNumeroInput((int *) &i,MIN_ESAMI + 1 , libretto.numero_esami, "Inserisci il numero dell'esame che vuoi modificare: ","Il numero dell'esame da te inserito non e' valido");

                                	 setNumeroInput(&libretto.esame[i-1].cfu, MIN_CFU, MAX_CFU,"Inserisci il quantitivo di CFU aggiornato dell'Esame presente in libretto: ","Il quantivo di CFU dell'Esame da te inserito non e' valido");
                                	 break;
                                 case voto_esame:


                                	 setNumeroInput((int *) &i,MIN_ESAMI + 1 , libretto.numero_esami, "Inserisci il numero dell'esame che vuoi modificare: ","Il numero dell'esame da te inserito non e' valido");

                                	 setNumeroInput(&libretto.esame[i-1].voto, MIN_VOTO, LODE,"Inserisci il voto aggiornato dell'Esame presente in libretto: ","Il voto da te inserito non e' valido");
                                	 break;
                                 default:
                                     break;
                            }
		                }
		               break;
				    default:
				       break;

				  }

				//scrive il libretto e lo studente aggiornati nei rispettivi file
				operazione = scriviFile(percorso_file_libretto, &libretto, sizeof(Libretto_t), indirizzo_record, SEEK_SET);
				if(operazione == okay)
				{   //scrive nel file studente solamente se e' stata modificata una delle sottostanti informazioni
					if((info_input_libretto == nome_studente_l) || (info_input_libretto == cognome_studente_l) || (info_input_libretto == corso_studente_l))
					{
					    operazione = scriviFile(percorso_file_studente, &studente, sizeof(Studente_t), indirizzo_studente, SEEK_SET);
					}
				}
				else
				{   //errore nella scrittura del libretto
					operazione = errore;
				}
		   }

		   else
		   {   //errore durante la lettura del file
			   operazione = errore;
		   }
		}

		else
		{
            //Non e' stato trovato il libretto dello studente
			operazione = errore;
		}

	}


	return operazione;
}





Stato_file_t cancella(const char percorso_file_studente[], const char percorso_file_insegnamento[], const char percorso_file_libretto[], int selezione)
{
	Stato_file_t operazione = okay;

	Studente_t studente;
	Insegnamento_t insegnamento;
	Libretto_t libretto;

	long int indirizzo_record = INDIRIZZO_NON_TROVATO;
    long int indirizzo_libretto = INDIRIZZO_NON_TROVATO;
    long int indirizzo_studente = INDIRIZZO_NON_TROVATO;

    int matricola = 0;
	resetStudenteLibretto(&studente,&libretto);
	resetInsegnamento(&insegnamento);

    //la cancellazione dello studente porta alla cancellazione del libretto e viceversa
	if(selezione == STUDENTE)
	{

		//Prendi l'indirizzo dello studente che vuoi cancellare insieme al suo libretto
		indirizzo_record = prendiIndirizzoInput(percorso_file_studente, NULL,NULL, "Inserisci la matricola dello Studente e del suo libretto che vuoi cancellare : ", "La matricola inserita non e' valida", STUDENTE);

		if(indirizzo_record != INDIRIZZO_NON_TROVATO)
		{
			operazione = leggiFile(percorso_file_studente, &studente, sizeof(Studente_t), indirizzo_record, SEEK_SET);
			if(operazione == okay)
			{
				matricola = studente.matricola;
			   indirizzo_libretto = prendiIndirizzo(percorso_file_libretto,&matricola,LIBRETTO);
			   operazione = leggiFile(percorso_file_libretto, &libretto, sizeof(Libretto_t), indirizzo_libretto, SEEK_SET);
			   if(operazione == okay)
			   {
				  studente.cancellato = true;
				  libretto.cancellato = true;
				  //dopo aver cancellato studente e libretto vengono aggiornati i rispettivi file
				  operazione = scriviFile(percorso_file_studente, &studente, sizeof(Studente_t), indirizzo_record, SEEK_SET);
				  if(operazione == okay)
				  {
				      operazione = scriviFile(percorso_file_libretto, &libretto, sizeof(Libretto_t), indirizzo_libretto, SEEK_SET);
			      }
                  else
			      {   //errore nella scrittura dello studente
				      operazione = errore;
			      }
			   }
			   else
			   {   //errore nella lettura del libretto
				   operazione = errore;
			   }
			}
			else
			{  //errore nella lettura dello studente
				operazione = errore;
			}

		}
		else
		{
			//Indirizzo non trovato
			operazione = errore;
		}

	}

	else if(selezione == INSEGNAMENTO)
	{
		//Prendi l'indirizzo dell'Insegnamento che vuoi cancellare
		indirizzo_record = prendiIndirizzoInput(percorso_file_studente, percorso_file_insegnamento, percorso_file_libretto, "Inserisci l'ID dell'Insegnamento che vuoi cancellare: ","L'ID dell'Insegnamento che vuoi cancellare non ï¿½ valido", INSEGNAMENTO);

		if(indirizzo_record != INDIRIZZO_NON_TROVATO)
		{
			//L'Insegnamento e' stato trovato e quindi verrà cancellato
			operazione = leggiFile(percorso_file_insegnamento, &insegnamento, sizeof(Insegnamento_t), indirizzo_record, SEEK_SET);
			if(operazione == okay)
			{
				insegnamento.cancellato = true;
				//aggiornamento del file dopo la cancellazione
				operazione = scriviFile(percorso_file_insegnamento, &insegnamento, sizeof(Insegnamento_t), indirizzo_record, SEEK_SET);
			}
		}
		else
		{
			//L'insegnamento non e' stato trovato
			operazione = errore;
		}
	}

	else
	{
		indirizzo_record = prendiIndirizzoInput(NULL, NULL,percorso_file_libretto, "Inserisci la matricola dello Studente e del suo libretto che vuoi cancellare : ", "La matricola inserita non e' valida", LIBRETTO);

		if(indirizzo_record != INDIRIZZO_NON_TROVATO)
		{
			operazione = leggiFile(percorso_file_libretto, &libretto, sizeof(Libretto_t), indirizzo_record, SEEK_SET);
		    if(operazione == okay)
		    {
			    matricola = libretto.matricola;
			    indirizzo_studente = prendiIndirizzo(percorso_file_studente,&matricola,STUDENTE);
			    operazione = leggiFile(percorso_file_studente,&studente,sizeof(Studente_t),indirizzo_studente,SEEK_SET);
		        if(operazione == okay)
		        {
		        	libretto.cancellato = true;
		        	studente.cancellato = true;
		        	operazione = scriviFile(percorso_file_libretto,&libretto, sizeof(Libretto_t),indirizzo_record,SEEK_SET);
		        	if(operazione == okay)
		        	{
		        		operazione = scriviFile(percorso_file_studente,&studente,sizeof(Studente_t),indirizzo_studente,SEEK_SET);
		        	}
		        	else
		        	{   //errore nella scrittura del libretto
		        		operazione = errore;
		        	}
		        }
		        else
		        {   //errore nella lettura dello studente
		        	operazione = errore;
		        }
		    }
		    else
		    {   //errore nella lettura del libretto
		    	operazione = errore;
		    }
		}
		else
		{   //indirizzo non trovato
			operazione = errore;
		}
	}

    return operazione;

}




Stato_file_t mostraRecords(const char percorso_file_studente[], const char percorso_file_insegnamento[], const char percorso_file_libretto[], int selezione)
{
	Stato_file_t operazione = errore;
	Studente_t studente;
	Insegnamento_t insegnamento;
	Libretto_t libretto;
	long int i = 0;

	resetStudenteLibretto(&studente,&libretto);
	resetInsegnamento(&insegnamento);

	if(selezione == STUDENTE)
	{

		printf("\n+-----------+------------------+------------------------+----------------------------+--------------------------------+-----------------------+");
		printf("\n| Matricola |       Nome       |         Cognome        |       Corso di Studio      |     Anno Immatricolazione      |    Data di Nascita    |");
		printf("\n+-----------+------------------+------------------------+----------------------------+--------------------------------+-----------------------+");

		do
		{   //legge tutti gli studenti
			operazione = leggiFile(percorso_file_studente, &studente, sizeof(Studente_t), i, SEEK_SET);
			if(operazione == okay)
			{

				leggiStudente(&studente);
			}
			i++;
		}
		while(operazione == okay);
	}
	else if(selezione == INSEGNAMENTO)
	{
		printf("\n+------+---------------------------------------+---------+----------------------------+-----------------------+----------------+");
		printf("\n|  ID  |          Nome  Insegnamento           |   CFU   |       Cognome Prof         |        Nome Prof      |  Anno di Corso |");
		printf("\n+------+---------------------------------------+---------+----------------------------+-----------------------+----------------+");

		do
		{   //legge tutti gli insegnamenti
			operazione = leggiFile(percorso_file_insegnamento, &insegnamento, sizeof(Insegnamento_t), i, SEEK_SET);
			if(operazione == okay)
			{

				leggiInsegnamento(&insegnamento);
			}
			i++;
		}
		while(operazione == okay);
	}
	else
	{

		do
		{
            //legge tutti i libretti
			operazione = leggiFile(percorso_file_libretto, &libretto, sizeof(Libretto_t), i, SEEK_SET);
			if(operazione == okay)
			{



				leggiLibretto(&libretto);
			}
			i++;
		}
		while(operazione == okay);
	}

	return operazione;
}





Stato_file_t aggiornaID(const char percorso_file[], const long int offset, int *id)
{
	Stato_file_t operazione = errore;

	(*id)++;
	operazione = scriviFile(percorso_file, id, sizeof(int), offset, SEEK_SET);

	return operazione;
}





//FUNZIONI E PROCEDURE PER L'ORDINAMENTO




Stato_file_t mergeSort(const char percorso_file[], long int inizio, long int fine, int selezione, int tipo_ordinamento)
{
	long int centro = 0;
    Stato_file_t operazione = errore;

	if(inizio < fine)
	{
		 //calcolo del perno per splittare il file e fare la ricorsione sulle due parti.
		 centro = (inizio + fine) / 2;
		 mergeSort(percorso_file, inizio, centro, selezione, tipo_ordinamento);
		 mergeSort(percorso_file, centro + 1, fine, selezione, tipo_ordinamento);

		if(selezione == STUDENTE)
		{
			//ordina studenti
			operazione = mergeStudenti(percorso_file, inizio, centro, fine, tipo_ordinamento);
		}
		else
		{   //ordina insegnamenti
			operazione = mergeInsegnamenti(percorso_file, inizio, centro, fine, tipo_ordinamento);
		}
	}

	return operazione;
}


Stato_file_t mergeStudenti(const char percorso_file[], long int inizio, long int centro, long int fine, int tipo_ordinamento)
{
	Studente_t primo_studente;
	Studente_t secondo_studente;

	long int i = inizio;
	long int j = centro + 1;
	long int k = 0;

	resetStudente(&primo_studente);
	resetStudente(&secondo_studente);

	Stato_file_t operazione = errore;

	if(isFileValido(SORT_TEMP_FILE))
	{
		while(i <= centro && j <= fine)
		{
			operazione = leggiFile(percorso_file, &primo_studente, sizeof(Studente_t), i, SEEK_SET);
			operazione = leggiFile(percorso_file, &secondo_studente, sizeof(Studente_t), j, SEEK_SET);

			//ordinamento basato dal tipo di ordinamento scelto
			switch(tipo_ordinamento)
			{
				case cresc_matricola_studente:
					if(primo_studente.matricola <= secondo_studente.matricola)
					{
						operazione = scriviFile(SORT_TEMP_FILE, &primo_studente, sizeof(Studente_t), k, SEEK_SET);
						i++;
					}
					else
					{
						operazione = scriviFile(SORT_TEMP_FILE, &secondo_studente, sizeof(Studente_t), k, SEEK_SET);
						j++;
					}
					break;
				case dec_matricola_studente:
					if(primo_studente.matricola >= secondo_studente.matricola)
					{
						operazione = scriviFile(SORT_TEMP_FILE, &primo_studente, sizeof(Studente_t), k, SEEK_SET);
						i++;
					}
					else
					{
						operazione = scriviFile(SORT_TEMP_FILE, &secondo_studente, sizeof(Studente_t), k, SEEK_SET);
						j++;
					}
					break;
				case cresc_nome_studente:
					if(strcmp(primo_studente.nome, secondo_studente.nome) <= 0)
					{
						operazione = scriviFile(SORT_TEMP_FILE, &primo_studente, sizeof(Studente_t), k, SEEK_SET);
						i++;
					}
					else
					{
						operazione = scriviFile(SORT_TEMP_FILE, &secondo_studente, sizeof(Studente_t), k, SEEK_SET);
						j++;
					}
					break;
				case dec_nome_studente:
					if(strcmp(primo_studente.nome, secondo_studente.nome) >= 0)
					{
						operazione = scriviFile(SORT_TEMP_FILE, &primo_studente, sizeof(Studente_t), k, SEEK_SET);
						i++;
					}
					else
					{
						operazione = scriviFile(SORT_TEMP_FILE, &secondo_studente, sizeof(Studente_t), k, SEEK_SET);
						j++;
					}
					break;
				case cresc_cognome_studente:
					if(strcmp(primo_studente.cognome, secondo_studente.cognome) <= 0)
					{
						operazione = scriviFile(SORT_TEMP_FILE, &primo_studente, sizeof(Studente_t), k, SEEK_SET);
						i++;
					}
					else
					{
						operazione = scriviFile(SORT_TEMP_FILE, &secondo_studente, sizeof(Studente_t), k, SEEK_SET);
						j++;
					}
					break;
				case dec_cognome_studente:
					if(strcmp(primo_studente.cognome, secondo_studente.cognome) >= 0)
					{
						operazione = scriviFile(SORT_TEMP_FILE, &primo_studente, sizeof(Studente_t), k, SEEK_SET);
						i++;
					}
					else
					{
						operazione = scriviFile(SORT_TEMP_FILE, &secondo_studente, sizeof(Studente_t), k, SEEK_SET);
						j++;
					}
					break;
				default:
					break;
			}
			k++;
		}

		while(i <= centro)
		{
			operazione = leggiFile(percorso_file, &primo_studente, sizeof(Studente_t), i, SEEK_SET);
			operazione = scriviFile(SORT_TEMP_FILE, &primo_studente, sizeof(Studente_t), k, SEEK_SET);
			i++;
			k++;
		}

		while(j <= fine)
		{
			operazione = leggiFile(percorso_file, &primo_studente, sizeof(Studente_t), j, SEEK_SET);
			operazione = scriviFile(SORT_TEMP_FILE, &primo_studente, sizeof(Studente_t), k, SEEK_SET);
			j++;
			k++;
		}

		for(i = inizio, j = 0; i <= fine; i++, j++)
		{
			operazione = leggiFile(SORT_TEMP_FILE, &primo_studente, sizeof(Studente_t), j, SEEK_SET);
			operazione = scriviFile(percorso_file, &primo_studente, sizeof(Studente_t), i, SEEK_SET);
		}

		//cancello il file temporaneo creato per effettuare l'ordinamento
		operazione = cancellaFile(SORT_TEMP_FILE);
	}

	return operazione;
}




Stato_file_t mergeInsegnamenti(const char percorso_file[], long int inizio, long int centro, long int fine, int tipo_ordinamento)
{
	Insegnamento_t primo_insegnamento;
	Insegnamento_t secondo_insegnamento;

	long int i = inizio;
	long int j = centro + 1;
	long int k = 0;

	resetInsegnamento(&primo_insegnamento);
	resetInsegnamento(&secondo_insegnamento);

	Stato_file_t operazione = errore;

	if(isFileValido(SORT_TEMP_FILE))
	{
		while(i <= centro && j <= fine)
		{
			operazione = leggiFile(percorso_file, &primo_insegnamento, sizeof(Insegnamento_t), i, SEEK_SET);
			operazione = leggiFile(percorso_file, &secondo_insegnamento, sizeof(Insegnamento_t), j, SEEK_SET);

			//Ordinamento basato dal tipo di ordinamento scelto
			switch(tipo_ordinamento)
			{
				case cresc_id_insegnamento:
					if(primo_insegnamento.id <= secondo_insegnamento.id)
					{
						operazione = scriviFile(SORT_TEMP_FILE, &primo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
						i++;
					}
					else
					{
						operazione = scriviFile(SORT_TEMP_FILE, &secondo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
						j++;
					}
					break;
				case dec_id_insegnamento:
					if(primo_insegnamento.id >= secondo_insegnamento.id)
				    {
						operazione = scriviFile(SORT_TEMP_FILE, &primo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
						i++;
					}
					else
					{
						operazione = scriviFile(SORT_TEMP_FILE, &secondo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
						j++;
					}
					break;
				case cresc_nome_insegnamento:
					if(strcmp(primo_insegnamento.nome, secondo_insegnamento.nome) <= 0)
					{
						operazione = scriviFile(SORT_TEMP_FILE, &primo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
						i++;
					}
					else
					{
						operazione = scriviFile(SORT_TEMP_FILE, &secondo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
						j++;
					}
					break;
				case dec_nome_insegnamento:
					if(strcmp(primo_insegnamento.nome, secondo_insegnamento.nome) >= 0)
			        {
						operazione = scriviFile(SORT_TEMP_FILE, &primo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
						i++;
					}
					else
					{
						operazione = scriviFile(SORT_TEMP_FILE, &secondo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
						j++;
			     	}
					break;
				case cresc_cfu:
					if(primo_insegnamento.cfu <= secondo_insegnamento.cfu)
					{
						operazione = scriviFile(SORT_TEMP_FILE, &primo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
					    i++;
					}
					else
					{
						operazione = scriviFile(SORT_TEMP_FILE, &secondo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
						j++;
					}
					break;
				case dec_cfu:
					if(primo_insegnamento.cfu <= secondo_insegnamento.cfu)
					{
						operazione = scriviFile(SORT_TEMP_FILE, &primo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
					    i++;
					}
					else
					{
						operazione = scriviFile(SORT_TEMP_FILE, &secondo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
						j++;
					}
					break;
				default:
					break;
			}
			k++;
		}

		while(i <= centro)
		{
			operazione = leggiFile(percorso_file, &primo_insegnamento, sizeof(Insegnamento_t), i, SEEK_SET);
			operazione = scriviFile(SORT_TEMP_FILE, &primo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
			i++;
			k++;
		}

		while(j <= fine)
		{
			operazione = leggiFile(percorso_file, &primo_insegnamento, sizeof(Insegnamento_t), j, SEEK_SET);
			operazione = scriviFile(SORT_TEMP_FILE, &primo_insegnamento, sizeof(Insegnamento_t), k, SEEK_SET);
			j++;
			k++;
		}

		for(i = inizio, j = 0; i <= fine; i++, j++)
		{
			operazione = leggiFile(SORT_TEMP_FILE, &primo_insegnamento, sizeof(Insegnamento_t), j, SEEK_SET);
			operazione = scriviFile(percorso_file, &primo_insegnamento, sizeof(Insegnamento_t), i, SEEK_SET);
		}

		//cancello il file temporaneo creato per effettuare l'ordinamento
		operazione = cancellaFile(SORT_TEMP_FILE);
	}

	return operazione;
}





//FUNZIONI E PROCEDURE PER IL CALCOLO DELLA M



void resetLibretto(Libretto_t *libretto)
{
    unsigned short i = 0;

	libretto -> matricola = 0;

	strcpy(libretto -> nome_studente, STRINGA_VUOTA);
	strcpy(libretto -> cognome_studente, STRINGA_VUOTA);
	strcpy(libretto -> corso_studente, STRINGA_VUOTA);

	libretto -> numero_esami = 0;

    for(i=0;i<(libretto->numero_esami);i++)
    {
    	resetEsame(&libretto->esame[i]);
    }

	libretto -> cancellato = false;
}



void setEsame(Esame_t *esame, Libretto_t*libretto, int numero_esame)
{
	resetEsame(esame);

	unsigned short i = 0;
	bool trovato = false;
	char nome_esame[MAX_LENGHT_STRING];

	do
	{
	   i=0;
	   bool okay = true;

       setStringa(nome_esame, "Il Nome dell'Esame");
       capitalizeStringa(nome_esame);

       while(i<numero_esame && okay)
       {
    	   if(!(strcmp(libretto->esame[i].nome,nome_esame)))
    	   {
    		          okay = false;
    		          printf("\nL'esame e' gia presente nel libretto, inserisci un nuovo esame\n");
    	   }
    	   i++;
       }


       if(okay)
    	   trovato = true;

    }
    while(!trovato);

   strcpy(esame->nome,nome_esame);
   setNumeroInput(&esame -> cfu, MIN_CFU, MAX_CFU, "Inserisci il quantitativo di CFU dell'esame: ", "Il quantitativo di CFU inserito non e' valido");
   setNumeroInput(&esame -> voto, MIN_VOTO, LODE, "Inserisci il voto dell'esame: ", "Il voto inserito non e' valido");

   printf("\nL'esame e' stato inserito con successo\n");


}


void resetEsame(Esame_t *esame)
{

	strcpy(esame -> nome, STRINGA_VUOTA);
	esame->cfu = 0;
	esame->voto = 0;
}





Stato_file_t numeroLodi(const char percorso_file_libretto[])
{

	Stato_file_t operazione = errore;
	Libretto_t libretto;
	unsigned long i = 0;
	unsigned long j = 0;

	int conteggio_lodi = 0;

	resetLibretto(&libretto);

	do
	{   //legge tutti i libretti e conteggia il numero di 30 e lode
		operazione = leggiFile(percorso_file_libretto,&libretto,sizeof(Libretto_t),i,SEEK_SET);
		if(operazione == okay)
		{
            for(j=0;j<libretto.numero_esami;j++)
            {
            	if(libretto.esame[j].voto == 31)
            	{
            		conteggio_lodi++;
            	}
            }
		}
		i++;
	}
	while(operazione == okay);


	if(operazione != errore)
	{
		printf("Il numero totale di 30 e lode presenti nel sistema e': %d", conteggio_lodi);
	}


	return operazione;
}



Stato_file_t percentualeEsami(const char percorso_file_studente[], const char percorso_file_libretto[])
{
	Stato_file_t operazione = okay;


	Libretto_t libretto;
	Studente_t studente;
	resetLibretto(&libretto);
    resetStudente(&studente);

	float base = 0;
    int percentuale = 0;
    int matricola = 0;
    int indirizzo_libretto = INDIRIZZO_NON_TROVATO;


    int indirizzo_studente = prendiIndirizzoInput(percorso_file_studente,NULL,NULL, "Inserisci la Matricola dello Studente di cui vuoi visualizzare la percentuale di esami superati: ","La Matricola da te inserita non e' valida",STUDENTE);

    if(indirizzo_studente != INDIRIZZO_NON_TROVATO)
    {
    	operazione = leggiFile(percorso_file_studente,&studente,sizeof(Studente_t),indirizzo_studente,SEEK_SET);
    	if(operazione == okay)
    	{

    		matricola = studente.matricola;
    	    indirizzo_libretto = prendiIndirizzo(percorso_file_libretto,&matricola,LIBRETTO);

    		operazione = leggiFile(percorso_file_libretto,&libretto,sizeof(Libretto_t),indirizzo_libretto,SEEK_SET);
    		if(operazione == okay)
    		{
    		   base = (((float)libretto.numero_esami/(float)MAX_ESAMI)*(float)PERCENTUALE);

    		   percentuale = (int)base;

    		    printf("\n\n%s %s ha superato il %d%c degli esami", libretto.nome_studente,libretto.cognome_studente,percentuale,'%');

    		}
    	    else
    	    {
    		 //Errore durante la lettura del libretto
    	     operazione = errore;
    	    }

    	}
    	else
    	{   //Errore durante la lettura dello studente
    		operazione = errore;
    	}

    }

    else
    {   //Indirizzo non trovato
    	operazione = errore;
    }


    return operazione;
}




Stato_file_t ordinaStudenti(const char percorso_file_studente[])
{


	Stato_file_t operazione = okay;

	sortStudenti_t scelta_ordinamentoS = cresc_matricola_studente;
	tipoSortStudenti();

	//prende in input la scelta del tipo di ordinamento degli Studenti e poi ordina con il mergeSort
    setNumeroInput((int*) &scelta_ordinamentoS, cresc_matricola_studente, dec_cognome_studente, "Inserisci la tua scelta: ", "La scelta che hai preso non e' valida");

    operazione = mergeSort(percorso_file_studente,0,(conteggioRecords(percorso_file_studente, sizeof(Studente_t)) - 1),STUDENTE,scelta_ordinamentoS);



    return operazione;

}


Stato_file_t ordinaInsegnamenti(const char percorso_file_insegnamento[])
{
	tipoSortInsegnamenti();

	Stato_file_t operazione = errore;
	sortInsegnamenti_t scelta_ordinamentoI = cresc_id_insegnamento;
	//prende in input la scelta del tipo di ordinamento degli Insegnamenti e poi ordina con il mergeSort
	setNumeroInput((int *) &scelta_ordinamentoI, cresc_id_insegnamento, dec_cfu, "Inserisci la tua scelta: ", "La scelta che hai preso non e' valida");

	operazione = mergeSort(percorso_file_insegnamento,0,(conteggioRecords(percorso_file_insegnamento,sizeof(Insegnamento_t)) - 1),INSEGNAMENTO,scelta_ordinamentoI);

	return operazione;
}



Stato_file_t numeroInsegnamentiProf(const char percorso_file_insegnamento[])
{
	Stato_file_t operazione = errore;
	Insegnamento_t insegnamento;

    char nome[MAX_LENGHT_STRING] = STRINGA_VUOTA;
    char cognome[MAX_LENGHT_STRING] = STRINGA_VUOTA;
    char identificativo[MAX_LENGHT_STRING*2] = STRINGA_VUOTA;

    int indirizzo_insegnamento = prendiIndirizzoInput(NULL,percorso_file_insegnamento,NULL, "Inserisci l'ID dell'Insegnamento per calcolare il numero totale di insegnamenti di cui il Prof e' titolare: ", "L'ID inserito non e' valido", INSEGNAMENTO);

    if(indirizzo_insegnamento != INDIRIZZO_NON_TROVATO)
    {

	   //lettura file insegnamento all'indirizzo, per prendere le informazioni del Prof
       operazione = leggiFile(percorso_file_insegnamento,&insegnamento,sizeof(Insegnamento_t),indirizzo_insegnamento,SEEK_SET);
       if(operazione == okay)
       {
    	  int numero_insegnamenti = 0;
    	  unsigned long i = 0;
    	  strcpy(cognome,insegnamento.cognome_prof);
    	  strcpy(nome, insegnamento.nome_prof);
    	  //l'indentificativo sarà formato dal cognome concatenato al nome per fare la ricerca.
    	  strcpy(identificativo,strcat(cognome,nome));



          do
          {    //lettura di tutti gli insegnamenti per contare il numero di insegnamenti di cui il prof e' titolare
    	       operazione = leggiFile(percorso_file_insegnamento,&insegnamento,sizeof(Insegnamento_t),i,SEEK_SET);
    	       if(operazione == okay)
    	       {
    	    	   //confronta gli identificativi ed in caso incrementa il numero
    	    	   if(!strcmp(identificativo,strcat(insegnamento.cognome_prof,insegnamento.nome_prof)))
    	    	   {
    	    		   numero_insegnamenti++;
    	    	   }
    	       }
    	       i++;
          }
          while(operazione == okay);


          if(operazione != errore)
          {
        		printf("\n\n%s e' titolare di %d Insegnamenti", identificativo, numero_insegnamenti);
          }


       }

       else
       {   //errore durante la lettura dell'insegnamento
    	  operazione = errore;
       }

    }
    else
    {   //l'indirizzo non e' stato trovato
    	operazione = errore;
    }
	return operazione;

}


Stato_file_t aggiungiEsame(const char percorso_file_libretto[])
{
	Stato_file_t operazione = okay;
	Libretto_t libretto;
	long int indirizzo_record = INDIRIZZO_NON_TROVATO;
	unsigned short conta_esami;
	resetLibretto(&libretto);

	indirizzo_record =  prendiIndirizzoInput(NULL, NULL, percorso_file_libretto, "Inserisci la matricola del libretto alla quale vuoi aggiungere un nuovo esame: ", "La matricola del libretto non e' valida", LIBRETTO);

	if(indirizzo_record != INDIRIZZO_NON_TROVATO)
	{
		operazione = leggiFile(percorso_file_libretto,&libretto,sizeof(Libretto_t),indirizzo_record,SEEK_SET);
		if(operazione == okay)
		{
			//aggiunge un nuovo esame solamente se ce ne sono meno di 20 nel libretto
			if(libretto.numero_esami < MAX_ESAMI)
			{
			   //indice dell'esame che inserirà
			   conta_esami = libretto.numero_esami;
			   //aggiorno il campo numero esami del libretto
			   libretto.numero_esami += 1;

			   setEsame(&libretto.esame[conta_esami],&libretto,conta_esami);

			   operazione = scriviFile(percorso_file_libretto,&libretto,sizeof(Libretto_t),indirizzo_record,SEEK_SET);
			}

			else
			{   //libretto pieno
				operazione = errore;
			}
		}
	}

	else
	{   //indirizzo non trovato
		operazione = errore;
	}

	return operazione;
}
