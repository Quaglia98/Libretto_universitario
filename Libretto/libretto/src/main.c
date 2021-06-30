/*
 ============================================================================
 Name        : Libretto.c
 Autore      : Vincenzo Quagliarella
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "main.h"

int main()
{
	    setvbuf(stdout, NULL, _IONBF, 0);
	    bool ok = true;    //booleano usato per il ciclo while
		menuIniziale_t scelta_menu = opzione_nonvalida;

		int id_studenti = 0;
		int id_insegnamenti = 0;
        int id_libretti = 0;

		intro();
		printf("\n\n");
		system("PAUSE");

		if(!isFileValido(STUDENTI_FILE))
		{
			printf("\nErrore durante l'apertura del file degli studenti");
			ok = false;
		}
		if(!isFileValido(INSEGNAMENTI_FILE))
		{
			printf("\nErrore durante l'apertura del file degli insegnamenti");
			ok= false;
		}
		if(!isFileValido(LIBRETTI_FILE))
		{
			printf("\nErrore durante l'apertura del file dei libretti");
			ok = false;
		}
		if(!isFileValido(ID_FILE))
		{
		   printf("\nErrore durante l'apertura del file degli ID");
		   ok = false;
		}

		if(ok)
		{
			if(!leggiFile(ID_FILE, &id_studenti, sizeof(id_studenti), 0, SEEK_SET))
			{
				//La matricola dello studente non e' stato letta
				ok = false;
			}
			if(!leggiFile(ID_FILE, &id_insegnamenti, sizeof(id_insegnamenti), 0, SEEK_SET) && ok)
			{
				//L'ID dell'insegnamento non e' stato letto
				ok = false;
			}

		}

		while(ok)
			{
				// Resetta la scelta
				scelta_menu = opzione_nonvalida;

				menuIniziale();

				//Prendo in input la scelta
				setNumeroInput((int *) &scelta_menu, aggiungi_studente, esci, "Inserisci la tua scelta: ", "La scelta che hai preso non e' valida");

				switch(scelta_menu)
				{
					 case aggiungi_studente:

						//Aggiunge uno studente e di conseguenza il suo libretto
						if(aggiungi(STUDENTI_FILE, INSEGNAMENTI_FILE, LIBRETTI_FILE, &id_studenti, STUDENTE))
						{
							printf("\n\nLo studente e il suo libretto sono stati aggiunti al sistema");


							if(!aggiornaID(ID_FILE, 0, &id_studenti))
							{
								printf("\n\nErrore durante l'aggiornamento della Matricola dello studente");
								ok = false;
							}


						}

						else
						{
							printf("\n\nErrore durante l'aggiunta del nuovo studente/libretto");
						}

						printf("\n\n");
						system("PAUSE");
						break;
					case modifica_studente:

						//Modifica uno speciico Studente ed eventualmente parte del libretto associato.
						if(modifica(STUDENTI_FILE, INSEGNAMENTI_FILE, LIBRETTI_FILE, STUDENTE))
						{
							printf("\nLo studente ed eventualmente parte del suo libretto sono stati modificati");
						}
						else
						{
							printf("\n\nErrore durante la modifica dello studente/libretto");
						}

						printf("\n\n");
						system("PAUSE");
						break;
					case cancella_studente:

						//Cancella lo Studente e il suo libretto.
						if(cancella(STUDENTI_FILE, INSEGNAMENTI_FILE, LIBRETTI_FILE, STUDENTE))
						{
							printf("\n\nLo studente e il suo libretto sono stati cancellati dal sistema");
						}
						else
						{
							printf("\n\nErrore durante la cancellazione dello studente/libretto");
						}

						printf("\n\n");
						system("PAUSE");
						break;
					case mostra_studenti:

						//Mostra tutti gli studenti presenti nel sistema
						if(mostraRecords(STUDENTI_FILE, INSEGNAMENTI_FILE, LIBRETTI_FILE, STUDENTE))
						{
							printf("\n\nGli studenti sono stati letti");
						}
						else
						{
							printf("\n\nErrore durante la lettura degli studenti");
						}
						printf("\n\n");
						system("PAUSE");
						break;
					case aggiungi_insegnamento:

						//Aggiungi un nuovo insegnamento al sistema
						if(aggiungi(STUDENTI_FILE, INSEGNAMENTI_FILE, LIBRETTI_FILE, &id_insegnamenti, INSEGNAMENTO))
						{
							printf("\n\nL'Insegnamento e' stato aggiunto al sistema");


							if(!aggiornaID(ID_FILE, 0, &id_insegnamenti))
							{
								printf("\n\nErrore durante l'aggiornamento dell'ID dell'Insegnamento");
								ok = false;
							}
						}
						else
						{
							printf("\n\nErrore durante l'aggiunta del nuovo Insegnamento");
						}

						printf("\n\n");
						system("PAUSE");
						break;
					case modifica_insegnamento:

						//Modifica l'Insegnamento scelto
						if(modifica(STUDENTI_FILE, INSEGNAMENTI_FILE, LIBRETTI_FILE, INSEGNAMENTO))
						{
							printf("\nL'insegnamento e' stato modificato");
						}
						else
						{
							printf("\n\nErrore durante la modifica dell'Insegnamento");
						}

						printf("\n\n");
						system("PAUSE");
						break;
					case cancella_insegnamento:

						//Cancella l'Insegnamento dal sistema
						if(cancella(STUDENTI_FILE, INSEGNAMENTI_FILE, LIBRETTI_FILE, INSEGNAMENTO))
						{
							printf("\n\nL'Insegnamento e' stato cancellato dal sistema");
						}
						else
						{
							printf("\n\nErrore durante la cancellazione dell'Insegnamento");
						}

						printf("\n\n");
						system("PAUSE");
						break;
					case mostra_insegnamenti:

						//Mostra tutti gli Insegnamenti presenti nel sistema
		                if(mostraRecords(STUDENTI_FILE, INSEGNAMENTI_FILE, LIBRETTI_FILE, INSEGNAMENTO))
		                {
		                	printf("\n\nGli Insegnamenti sono stati letti");
		                }
		                else
		                {
		                	printf("\n\nErrore durante la lettura degli Insegnamenti");
		                }
		                printf("\n\n");
		                system("PAUSE");
		                break;
					case aggiungi_libretto:

						//Aggiunge il libretto e lo studente associato al sistema
						if(aggiungi(STUDENTI_FILE, INSEGNAMENTI_FILE, LIBRETTI_FILE, &id_libretti, LIBRETTO))
						{
							printf("\n\nIl libretto e il suo studente sono stati aggiunti al sistema");


							if(!aggiornaID(ID_FILE, 0, &id_libretti))
							{
								printf("\n\nErrore durante l'aggiornamento della matricola del libretto");
								ok = false;
							}
						}
					    else
						{
					    	printf("\n\nErrore durante l'aggiunta del nuovo libretto/studente");
						}

						printf("\n\n");
						system("PAUSE");
						break;
					case modifica_libretto:

						//Modifica il libretto ed eventualmente parte dello Studente associato
						if(modifica(STUDENTI_FILE, INSEGNAMENTI_FILE, LIBRETTI_FILE, LIBRETTO))
						{
							printf("\nIl libretto ed eventualmente lo Studente sono stati modificati");
						}
						else
						{
							printf("\n\nErrore durante la modifica del libretto/studente");
						}

						printf("\n\n");
						system("PAUSE");
						break;
					case cancella_libretto:

						//Cancella il libretto e lo studente associato
						if(cancella(STUDENTI_FILE, INSEGNAMENTI_FILE, LIBRETTI_FILE, LIBRETTO))
						{
								printf("\n\nIl libretto e lo Studente sono stati cancellati dal sistema");
						}
						else
						{
							printf("\n\nErrore durante la cancellazione del libretto/studente");
						}

						printf("\n\n");
						system("PAUSE");
						break;
					case mostra_media:

						//Mostra la media e ulteriori informazioni dell'Insegnamento scelto
						if(mostraMedia(INSEGNAMENTI_FILE, LIBRETTI_FILE))
						{



						printf("\n\nL'Insegnamento con la media e' stato letto");
						}
						else
						{
							printf("\n\nErrore durante la lettura dell'Insegnamento");
						}

						printf("\n\n");
						system("PAUSE");
						break;
					case mostra_libretto:

						//caso in cui non c'e' alcun libretto
						if((conteggioRecords(STUDENTI_FILE,sizeof(Studente_t))== NO_RECORDS))
						{
                           printf("\n\nNon si puo mostrare alcun libretto, non ci sono studenti nel sistema");
						}
						//Mostra il libretto associato allo Studente scelto.
						else if(mostraLibretto(STUDENTI_FILE,LIBRETTI_FILE))
						{
							printf("\n\nIl libretto dello Studente e' stato letto");
						}
						else
						{
							printf("\n\nErrore durante la lettura del Libretto");
						}

						printf("\n\n");
						system("PAUSE");
						break;
					case mostra_statistiche:

						//Mostra la statistica che e' stata scelta
                        if(sceltaStatistica(STUDENTI_FILE, LIBRETTI_FILE, INSEGNAMENTI_FILE))
                        {
                        	printf("\n\nLa statistica scelta e' stata visualizzata");
                        }
                        else
                        {
                        	printf("\n\nErrore durante la scelta della statistica");
                        }
						printf("\n\n");
						system("PAUSE");
						break;
					case ordina_studenti:

						 //ordina gli studenti secondo il criterio scelto
						if((conteggioRecords(STUDENTI_FILE, sizeof(Studente_t)) == UNICO_RECORD))
						{
							printf("\n\nC'e' un solo studente, ordinamento non necessario");
						}

						else if(ordinaStudenti(STUDENTI_FILE))
						{
							printf("\n\nGli studenti sono stati ordinati con successo");
						}
						else
					    {   //file non presente oppure 0 studenti
							printf("\n\nErrore durante l'ordinamento degli studenti");
					    }
						printf("\n\n");
						system("PAUSE");
					    break;
					case ordina_insegnamenti:

						//verifica se c'e' solamente un record nel file in tal caso non serve ordinare
						if((conteggioRecords(INSEGNAMENTI_FILE, sizeof(Insegnamento_t)) == UNICO_RECORD))
						{
							printf("\n\nC'e' un solo insegnamento, ordinamento non necessario");
						}
						else if(ordinaInsegnamenti(INSEGNAMENTI_FILE))
						{
							printf("\n\nGli Insegnamenti sono stati ordinati con successo");
						}
						else
						{   //file non presente oppure 0 insegnamenti
							printf("\n\nErrore nell'ordinamento degli Insegnamenti");
					    }

						printf("\n\n");
						system("PAUSE");
						break;
					case aggiungi_esame:
                        //verifico la presenza dei libretti
						if((conteggioRecords(LIBRETTI_FILE, sizeof(Libretto_t)) == NO_RECORDS))
						{
							printf("\n\nNon c'e' alcun libretto nel sistema");
						}
						//verifico se l'esame e' stato aggiunto
					    else if(aggiungiEsame(LIBRETTI_FILE))
						{
							printf("\n\nIl nuovo esame e' stato aggiunto al libretto");
						}
						else
						{
							printf("\n\nErrore nell'aggiunta del nuovo esame");
						}

						printf("\n\n");
						system("PAUSE");
						break;
					case esci:
						//termina il programma (esci dal while)
						ok = false;
						break;
					default:
						break;
				}
			}



    printf("\n\n");
	system("PAUSE");
    exit(EXIT_SUCCESS);

}








void menuIniziale(void)
{
	printf("\n\nMenu Iniziale:");
	printf("\n+---------------------+----------------------+");
	printf("\n|  Numero di Scelte   |        Opzioni       |");
	printf("\n+---------------------+----------------------+");
	printf("\n|         %d           |   Aggiungi Studente  |", aggiungi_studente);
	printf("\n+---------------------+----------------------+");
	printf("\n|         %d           |   Modifica Studente  |", modifica_studente);
	printf("\n+---------------------+----------------------+");
	printf("\n|         %d           |   Cancella Studente  |", cancella_studente);
	printf("\n+---------------------+----------------------+");
	printf("\n|         %d           |    Mostra Studenti   |", mostra_studenti);
	printf("\n+---------------------+----------------------+");
	printf("\n|         %d           |Aggiungi Insegnamento |", aggiungi_insegnamento);
	printf("\n+---------------------+----------------------+");
	printf("\n|         %d           |Modifica Insegnamento |", modifica_insegnamento);
	printf("\n+---------------------+----------------------+");
	printf("\n|         %d           |Cancella Insegnamento |", cancella_insegnamento);
	printf("\n+---------------------+----------------------+");
	printf("\n|         %d           | Mostra Insegnamenti  |", mostra_insegnamenti);
	printf("\n+---------------------+----------------------+");
	printf("\n|         %d           |  Aggiungi Libretto   |", aggiungi_libretto);
	printf("\n+---------------------+----------------------+");
	printf("\n|         %d           |  Modifica libretto   |", modifica_libretto);
	printf("\n+---------------------+----------------------+");
	printf("\n|        %d           |  Cancella libretto   |", cancella_libretto);
	printf("\n+---------------------+----------------------+");
	printf("\n|        %d           |     Mostra Media     |", mostra_media);
	printf("\n+---------------------+----------------------+");
	printf("\n|        %d           |     Mostra Libretto  |", mostra_libretto);
	printf("\n+---------------------+----------------------+");
	printf("\n|        %d           | Mostra Statistiche   |", mostra_statistiche);
	printf("\n+---------------------+----------------------+");
	printf("\n|        %d           |   Ordina Studenti    |", ordina_studenti);
	printf("\n+---------------------+----------------------+");
	printf("\n|        %d           | Ordina Insegnamenti  |", ordina_insegnamenti);
	printf("\n+---------------------+----------------------+");
	printf("\n|        %d           |    Aggiungi Esame    |", aggiungi_esame);
	printf("\n+---------------------+----------------------+");
	printf("\n|        %d           |        Esci          |", esci);
	printf("\n+---------------------+----------------------+");
}




void intro(void)
{
		printf("\n +----------------------------------------------------+");
		printf("\n | ************************************************** |");
		printf("\n | * +--------------------------------------------+ * |");
		printf("\n | * |                                            | * |");
		printf("\n | * |                                            | * |");
		printf("\n | * |                                            | * |");
		printf("\n | * |                                            | * |");
		printf("\n | * |            LIBRETTO UNIVERSITARIO          | * |");
		printf("\n | * |                                            | * |");
		printf("\n | * |                   MADE BY		  | * |");
		printf("\n | * |                                            | * |");
		printf("\n | * |            VINCENZO QUAGLIARELLA           | * |");
		printf("\n | * |                                            | * |");
		printf("\n | * |                                            | * |");
		printf("\n | * |                                            | * |");
		printf("\n | * |                                            | * |");
		printf("\n | * |                                            | * |");
		printf("\n | * |                                            | * |");
		printf("\n | * +--------------------------------------------+ * |");
		printf("\n | ************************************************** |");
		printf("\n +----------------------------------------------------+");


}
