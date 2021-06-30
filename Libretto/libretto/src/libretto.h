/*
 * libretto.h
 *
 *  Autore: Vincenzo Quagliarella
 *
 */

#ifndef LIBRETTO_H_
#define LIBRETTO_H_


#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include "data.h"
#include "file.h"
#include "generali.h"


#define STUDENTE 1

#define INSEGNAMENTO 2

#define LIBRETTO 3

#define MAX_LENGHT_STRING 30

#define MIN_LENGHT_STRING 2

#define MAX_LUNGHEZZA_NUMERO 10

#define MAX_ANNO_IMMATRICOLAZIONE 2020

#define MIN_ANNO_IMMATRICOLAZIONE 1978

#define MAGGIORE_ETA 18

#define MAX_ANNO_NASCITA 2002

#define MIN_ANNO_NASCITA 1960

#define MAX_CFU 18

#define MIN_CFU 3

#define LODE 31

#define MIN_VOTO 18

#define MAX_ESAMI 20

#define MIN_ESAMI 0

#define MAX_ANNO_CORSO 5

#define MIN_ANNO_CORSO 1

#define SORT_TEMP_FILE "../Files/Merge.dat"

#define NO_RECORDS 0

#define UNICO_RECORD 1


typedef enum {matricola_studente = -1, //membro che indica la matricola dello Studente
			 nome_studente, //membro che indica il nome dello Studente
			 cognome_studente, //membro che indica il cognome dello Studente
			 corso_studente, // membro che indica il Corso di studio dello Studente
			 immatricolazione, // membro che indica l'anno di immatricolazione dello studente
			 nascita, //membro che indica la data di nascita dello Studente
			 studente_cancellato //membro che indica se uno studente è cancellato
} infoStudente_t;


typedef enum {id_insegnamento = -1, //membro che indica l'ID dell'insegnamento
			 nome_insegnamento, //membro che indica il nome dell'insegnamento
			 cfu, //membro che indica i cfu dell'insegnamento
			 anno_corso, //membro che indica l'anno del Corso di studio dell'insegnamento
			 cognome_prof, //membro che indica il cognome del Prof titolare dell'insegnamento
			 nome_prof, //membro che indica il nome del Prof titolare dell'insegnamento
			 insegnamento_cancellato //membro che indica se un insegnamento è cancellato
} infoInsegnamento_t;


typedef enum { matricola_studente_l = -1, //membro che indica la matricola dello studente del libretto
               nome_studente_l, //membro che indica il nome dello studente del libretto
			   cognome_studente_l, //membro che indica il cognome dello studente del libretto
			   corso_studente_l, //membro che indica il corso di studio dello studente del libretto
			   esame//membro che indica l'esame del libretto
} infoLibretto_t;


typedef enum {
	           nome_esame, //membro che indica il nome dell'esame
	           cfu_esame, //membro che indica i cfu dell'esame
			   voto_esame //membro che indica il voto dell'esame
} infoEsame_t;


typedef enum {cresc_matricola_studente, //membro che indica l'ordinamento basato sulla matricola crescente dello studente
			 dec_matricola_studente, //membro che indica l'ordinamento basato sulla matricola decrescente dello studente
			 cresc_nome_studente, //membro che indica l'ordinamento basato sul nome crescente dello studente
			 dec_nome_studente, //membro che indica l'ordinamento basato sul nome decrescente dello studente
			 cresc_cognome_studente, //membro che indica l'ordinamento basato sul cognome crescente dello studente
			 dec_cognome_studente, //membro che indica l'ordinamento basato sul nome crescente dello studente
} sortStudenti_t;


typedef enum {cresc_id_insegnamento, //membro che indica l'ordinamento basato sull'ID crescente dell'insegnamento
			 dec_id_insegnamento, //membro che indica l'ordinamento basato sull'ID decrescente dell'insegnamento
			 cresc_nome_insegnamento, //membro che indica l'ordinamento basato sul nome crescente dell'insegnamento
			 dec_nome_insegnamento, //membro che indica l'ordinamento basato sul nome decrescente dell'insegnamento
			 cresc_cfu, //membro che indica l'ordinamento basato sui cfu crescenti dell'insegnamento
			 dec_cfu, //membro che indica l'ordinamento basato sui cfu decrescenti dell'insegnamento
} sortInsegnamenti_t;



typedef enum {
			  percentuale_esami_superati, //membro che indica la statistica della percentuale di esami superati
			  numero_lodi, //membro che indica la statistica del numero totale di 30 e lodi presenti in sistema
              numero_insegnamenti_prof, //membro che indica la statistica del numero di insegnamenti di cui un Prof è titolare
} statistiche_t;



typedef struct
{
	int matricola; //membro che memorizza la matricola dello Studente
	char nome[MAX_LENGHT_STRING];  //membro che memorizza il nome dello Studente
	char cognome[MAX_LENGHT_STRING]; //membro che memorizza il cognome dello Studente
	char corso[MAX_LENGHT_STRING]; //membro che memorizza il Corso di studio dello Studente
	unsigned short immatricolazione; //membro che memorizza l'anno di immatricolazione dello Studente
	Data_t nascita; //membro che memorizza la data di nascita dello Studente
	bool cancellato; //membro che serve per capire se lo studente è cancellato oppure no
} Studente_t;


typedef struct
{
	int id; //membro che memorizza l'id dell'Insegnamento
	char nome[MAX_LENGHT_STRING]; //membro che memorizza il nome dell'Insegnamento
	int cfu; //membro che memorizza i cfu dell'Insegnamento
	char cognome_prof[MAX_LENGHT_STRING]; //membro che memorizza il cognome del Prof titolare dell'Insegnamento
	char nome_prof[MAX_LENGHT_STRING]; //membro che memorizza il nome del Prof titolare dell'Insegnamento
	unsigned short anno_corso; //membro che memorizza l'anno del Corso di studio
	bool cancellato; //membro che serve per capire se lo studente è cancellato oppure no
} Insegnamento_t;


typedef struct
{
	char nome [MAX_LENGHT_STRING]; //membro che memorizza il nome dell'esame
    int  cfu; //membro che memorizza i cfu dell'esame
    int  voto; //membro che memorizza il voto dell'esame
} Esame_t;


typedef struct
{
    int matricola; //membro che memorizza la matricola dello Studente
    char nome_studente[MAX_LENGHT_STRING]; //membro che memorizza il nome dello Studente
    char cognome_studente[MAX_LENGHT_STRING]; //membro che memorizza il cognome dello Studente
    char corso_studente[MAX_LENGHT_STRING]; //membro che memorizza il Corso di studio dello Studente
    int numero_esami; //membro che memorizza il numero di esami presente in libretto
    Esame_t esame[MAX_ESAMI]; //membro che memorizza gli esami
    bool cancellato; //membro che serve per capire se il libretto è cancellato oppure no
} Libretto_t;



//procedure per visualizzare opzioni e informazioni che l'utente può scegliere



void mostraInfoStudente(void);

void tipoSortStudenti(void);

void mostraInfoInsegnamento(void);

void tipoSortInsegnamenti(void);

void mostraStatistiche(void);

void mostraInfoLibretto(void);

void mostraInfoEsame(void);



/*procedure e funzioni per impostare stringhe valide, numeri validi
  e ottenere l'indirizzo di un elemento contenuto nel file */



//procedura che consente di impostare un valore valido alla stringa passata come puntatore
void setStringa(char stringa[], const char messaggio_input[]);



//procedura che consente di impostare un nomero che sia valido e compreso tra min e max
void setNumeroInput(int *input, const int min, const int max, const char messaggio_input[], const char messaggio_errore[]);



//funzione che consente di prendere l'indirizzo corrispondende all'id passato come parametro
int prendiIndirizzo(const char percorso_file[], const int *id, int selezione);



//funzione che consente di prendere l'indirizzo corrispondente all'id che è inserito dall'utente
int prendiIndirizzoInput(const char percorso_file_studente[], const char percorso_file_insegnamento[], const char percorso_file_libretto[], const char messaggio_input[], const char messaggio_errore[], int selezione);



//funzioni e procedure sugli Studenti



//procedura che consente di impostare valori validi allo Studente e al suo libretto
void setStudenteLibretto(Studente_t *studente, Libretto_t *libretto, const int *matricola);



//procedura che consente di resettare tutti i valori dello Studente e del suo libretto
void resetStudenteLibretto(Studente_t *studente, Libretto_t *libretto);



//procedura che consente di resettare tutti i valori dello Studente ma non del suo libretto
void resetStudente(Studente_t *studente);



//procedura che consente di leggere lo studente passato come parametro
void leggiStudente(const Studente_t *student);



//funzione booleana che consente di confrontare l'ID passato da parametro e la matricola dello Studente
bool confrontoIdStudente(const Studente_t *studente, const int *id);



//funzione che consente di ordinare gli Studenti secondo un certo tipo di ordinamento
Stato_file_t mergeStudenti(const char percorso_file[], long int inizio, long int centro, long int fine, int tipo_ordinamento);



//funzione che consente di impostare il tipo di ordinamento per gli Studenti
Stato_file_t ordinaStudenti(const char percorso_file_studente[]);



//funzioni e procedure sugli Insegnamenti



//procedura che consente di resettare l'insegnamento
void resetInsegnamento(Insegnamento_t *insegnamento);



//procedura che consente di impostare valori validi all'insegnamento
void setInsegnamento(Insegnamento_t *insegnamento, const int *idinsegnamento, const char percorso_file_libretto[]);



//procedura che consente di leggere l'insegnamento
void leggiInsegnamento(const Insegnamento_t *insegnamento);



//procedura che consente di leggere l'insegnamento e la sua media
void leggiMediaInsegnamento(const Insegnamento_t *insegnamento, double media);



//funzione booleana che consente di confronta l'ID passato da parametro e quello dell'insegnamento
bool confrontoIdInsegnamento(const Insegnamento_t *insegnamento, const int *id);



//funzione che ordina gli insegnamenti secondo un certo tipo di ordinamento
Stato_file_t mergeInsegnamenti(const char percorso_file[], long int inizio, long int centro, long int fine, int tipo_ordinamento);



//funzione che consente di impostare il tipo di ordinamento per gli insegnamenti
Stato_file_t ordinaInsegnamenti(const char percorso_file_insegnamento[]);



//funzione che consente di calcolare e mostrare il numero di Insegnamenti di cui un Prof passato in input è titolare
Stato_file_t numeroInsegnamentiProf(const char percorso_file_insegnamento[]);



//funzioni e procedure sui libretti



//procedura che consente di impostare valori validi all'esame
void setEsame(Esame_t *esame, Libretto_t*libretto, int numero_esame);



//procedura che consente di resettare l'esame
void resetEsame(Esame_t *esame);



//procedura che consente di resettare il libretto
void resetLibretto(Libretto_t *libretto);



//funzione booleana che consente di confrontare la matricola del libretto con l'id passato da parametro
bool confrontoIdLibretto(const Libretto_t *libretto, const int *id);



//funzione che consente di mostrare il libretto dello studente passato in input
Stato_file_t mostraLibretto(const char percorso_file_studente[], const char percorso_file_libretto[]);



//funzione che consente di calcolare e mostrare il numero totale di 30 e lode del sistema
Stato_file_t numeroLodi(const char percorso_file_libretto[]);



//funzione che consente di aggiungere un nuovo esame al libretto scelto dall'utente
Stato_file_t aggiungiEsame(const char percorso_file_libretto[]);



//procedure e funzioni che coinvolgono i file disponibili



//funzione che consente di aggiungere uno studente/insegnamento/libretto in base al valore di selezione
Stato_file_t aggiungi(const char percorso_file_studente[], const char percorso_file_insegnamento[], const char percorso_file_libretto[], const int *id, int selezione);



//funzione che consente di modificare uno studente/insegnamento/libretto in base al valore di selezione
Stato_file_t modifica(const char percorso_file_studente[], const char percorso_file_insegnamento[], const char percorso_file_libretto[], int selezione);



//funzione che consente di cancellare uno studente/insegnamento/libretto in base al valore di selezione
Stato_file_t cancella(const char percorso_file_studente[], const char percorso_file_insegnamento[], const char percorso_file_libretto[], int selezione);



//funzione che consente di aggiornare l'ID passato come parametro e di salvarlo all'interno del file
Stato_file_t aggiornaID(const char percorso_file[], const long int offset, int *id);



//funzione che mostra tutti i records del file studenti/insegnamenti/libretti in base al valore di selezione
Stato_file_t mostraRecords(const char percorso_file_studente[], const char percorso_file_insegnamento[], const char percorso_file_libretto[], int selezione);



//funzione che consente di splittare i records e fare l'ordinamento
Stato_file_t mergeSort(const char percorso_file[], long int inizio, long int fine, int selezione, int tipo_ordinamento);



//funzione che consente di calcolare e mostrare la percentuale di esami supari da uno Studente passato in input dall'utente
Stato_file_t percentualeEsami(const char percorso_file_studente[], const char percorso_file_libretto[]);



//funzione che consente di scegliere la statistica
Stato_file_t sceltaStatistica(const char percorso_file_studente[], const char percorso_file_insegnamento[],const char percorso_file_libretto[]);



//funzione che consente di calcolare la media di un insegnamento che l'utente puo scegliere
Stato_file_t mostraMedia(const char percorso_file_insegnamento[], const char percorso_file_libretto[]);



#endif
