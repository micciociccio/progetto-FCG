# Progetto FCG: Documentazione

### Build, tappe ed esecuzione

Per salvare i vari stages durante il corso del progetto ho utilizzato il file `stages.sh` fornito dal professore.
In particolare, per esportare e compilare tutte le tappe del progetto che finiranno in `FCG_Stages/`, usiamo il comando:

```bash
./stages.sh all
```

Per eseguire ogni tappa singola basta entrare nella folder corrispondente (`Stage_XX`) e successivamente eseguire il comando:

```bash
./build/bin/aa_game
```

Per compilare ed eseguire invece il progetto finale (corrispondente all'ultima tappa della cartella `FCG_Stages`) si può usare, dalla root del progetto, il comando:

```bash
cmake --build build && ./build/bin/aa_game
```

### Comandi UI

Per quanto riguarda l'UI, simulando un gioco mobile, il mouse non è intercettato come evento.

- **Navigazione nei Menu:** Utilizzare i tasti **Arrow up** (↑) e **Arrow down** (↓) per scorrere le opzioni a scelta multipla.
- **Conferma:** Utilizzare il tasto **Enter** (↵) per selezionare l'opzione.
- **Uscita:** L'opzione *Exit* presente nei menu richiede la chiusura della finestra. La chiusura non può avvenire tramite la classica `✖` nella topBar. Sulla finestra non è inoltre possibile fare il resize, mantenendo così una mobile viewport fissa.
- **Tasto di sblocco (Esc):** In ogni stato dell'applicazione è possibile tornare al Menu iniziale tramite il tasto **Esc** (Escape). Questa funzionalità è stata introdotta nella tappa 11 che aggiunge `LevelsState`, con la possibilità di digitare il livello da rigiocare tramite tastiera numerica e confermarlo premendo **Enter** (↵).
