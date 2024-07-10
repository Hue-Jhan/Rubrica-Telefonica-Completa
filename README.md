# Rubrica-Telefonica-Completa
Rubrica Telefonica Completa in C (Progetto Universitario), build di Eclipse (il prof ci ha costretto a usare sto compiler del c), purtroppo ci ha obbligato a non usare break, for, switch, e alcune funzioni già esistenti in librerie varie. Allo stesso modo dovev(am)o limitare l'uso di return vari nelle funzioni, e gestire i dati/variabili globali/costanti in modi particolari. Almeno ci ha fatto usare i colori :  )   

# 🔧 PseudoCodice, Consegne e Test
Il progetto è una semplice interfaccia per una classica rubrica telefonica, si possono aggiungere e gestire un numero illimitato di contatti. Sono presenti anche valori come stato di un contatto (preferito/bloccato) e l'intera rubrica può essere esportata su file di testo o importata. Il progetto è diviso in 4 moduli:
- **Gestire Rubrica**:   gestisce funzioni iniziali e principali (es. inserire nuovo contatto, copiare o cercare contatti);
- **Gestire Contatto**:   gestisce sottofunzioni relative ai contatti singoli (es. modificare o cancellare contatti, aggiungerli ai preferiti, bloccare contatto);
- **Gestire File**:   gestisce importazione da file, esportazione su file, gestione file errori e alcune funzioni di interfaccia;
- **Gestire Dati**:   gestisce variabili globali, costanti, tipi di dato, alcune funzioni di schermata e interfaccia, e funzioni d'accesso;

I casi di test coinvolgono solo le funzioni accessibili dall'utente, ovvero quelle presenti nella Funzione Principale. Le consegne sono le consegne intermedie effettuate di tanto in tanto prima di consegnare il progetto completo.

# 💻 Codice e funzionamento
<img align="right" src="rubrica.png" width="400" />
Il codice parte da un interfaccia semplice (in foto) dalla quale si possono eseguire le operazioni principali, la rubrica è gestita come una lista a puntatori, ogni contatto è un nodo costituito da nome, cognome, numero di telefono, stato (normale/preferito/bloccato) e il puntatore.  <br />  <br />

Ecco l'elenco delle operazioni:
- Inserire Nuovo Contatto;
- Modificare Contatto;
- Cancellare Contatto;
- Ordinare rubrica;
- Visualizzare rubrica;
- Aggiungere/Rimuovere preferiti;
- Aggiungere/Rimuovere bloccati;
- Esportare rubrica su file;
- Importare rubrica da file;

La sottofunzione **`Cercare Contatto`** è molto particolare: per cercare un contatto prima bisogna digitarne il nome, subito dopo tutti i contatti in rubrica con lo stesso nome verranno copiati, aggiunti a una rubrica temporanea e mostrati all'utente; in seguito l'utente digita il cognome del contatto che vuole cercare e viene selezionato il primo contatto con quel cognome nella rubrica temporanea (in teoria dovrebbe essere il primo e anche l'unico); infine la rubrica temporanea viene svuotata (memoria non deallocata).

La funzione **`Mostrare Errore`**` invece consiste semplicemente in mostrare un errore specifico ogni volta che è necessario: il file "31_errori.txt" contiene una serie di errori elencati uno dopo l'altro, un errore per rigo; Dato un valore in input, la funzione non fa altro che leggere la riga corrispondente a quel valore e printa il rigo intero.  

Le funzioni di **`Interfaccia`** sono anch'esse contentue in Gestire File, e sono due. La prima, "GOTOXY" non fa altro che posizionare il cursore in delle coordinate specifiche nel terminale. La seconda, "PulireSchermo" printa spazi in ogni cella del terminale usando GOTOXY. Quest'ultima funzione era abbastanza lenta a seconda di diversi fattori, non solo la quantità di celle da pulire, per questo abbiamo introdotto una terza funzione ovvero "ImpostaDimensioneConsole", che nel Main setta la dimensione del terminale a dei valori abbastanza piccoli da rendere PulireSchermo quasi immediato.


# 🕷 Bug e errori 
Gli errori sono gestiti da vari cicli e input buffer vari, e sono mostrati all'utente dalla funzione MostrareErrore. Nel progetto mi pare ci sia un solo "errore" nella sottofunzione **`CercareContatto`**, ovvero se l'utente inserisce 2 contatti con lo stesso nome e cognome, ogni volta che cercherà di modificare il secondo che ha inserito (in ordine di aggiunta) non potrà farlo, in quanto come già menzionato in precedenza, "CercareContatto" preleva il primo nodo che trova il quale abbia nome e cognome specificati dall'utente.
<br />
Quindi bisognerebbe introdurre un ciclo aggiuntivo che permette all'utente di scegliere anche in base al numero di telefono o semplicemente associando un numeretto ai contatti uguali, e dunque l'utente sceglie in base al numeretto, ma non ho la minima voglia di farlo.
