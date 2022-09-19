#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h> 
#include <string.h>
#include <time.h>

#define HIGHER      1
#define LOWER       2
#define WON         3
#define LOOSE       4
#define MIN_NUMBER  1
#define MAX_NUMBER  100
#define MAX_TRIES   10

int execPere(int fds[2], int childPID);
int execFils(int fds[2]);
const int n_buff = 10;

void action_signal() {
    //NOP
}

int main() {
    struct sigaction action;
    action.sa_handler = action_signal;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    printf("Le but du jeu est de deviner le nombre secret compris entre %d et %d inclus en maximum %d essais :\n\n", MIN_NUMBER, MAX_NUMBER, MAX_TRIES);

    int fds[2];
    // Création du pipe
    pipe(fds);

    if (sigaction(SIGUSR1, &action, NULL) == -1) {
        printf("Impossible d'appeler sigaction\n");
        exit(EXIT_FAILURE);
    }
    // Création du joueur (le processus fils représente le joueur et le pere représente l'ordinateur)
    int pid = fork();

    switch (pid) {
    case -1:
        printf("Erreur");
        exit(EXIT_FAILURE);
        break;
    case 0:
        exit(execFils(fds));
        break;
    default:
        break;
    }
    // On attend que le fils soit créé
    sleep(1);
    return execPere(fds, pid);
}

int execPere(int fds[2], int childPID) {
    srand( time(NULL) );

    char buff[n_buff];
    int numToGuess = (rand() % (MAX_NUMBER - ( MIN_NUMBER - 1 ))) + MIN_NUMBER;
    int proposition = MIN_NUMBER - 1;
    int gameOver = 0, won = 0, higher = 1, n_try = 1;

    snprintf(buff, sizeof(buff), "%d", HIGHER);
    write(fds[1], buff, strlen(buff));
    kill(childPID, SIGUSR1);

    while (1) {
        printf("ORDI ==> Essai %d/%d\n", n_try, MAX_TRIES);
        pause();

        sleep(1);

        int n = read(fds[0], buff, n_buff - 1);
        buff[n] = '\0';
        proposition = atoi(buff);

        // On vérifie si la réponse donnée est juste
        if (proposition == numToGuess) {
            printf("ORDI ==> C'est juste !\n");
            gameOver = 1;
            won = 1;
        } else if (proposition < numToGuess) {
            printf("ORDI ==> FAUX ! C'est plus\n");
            higher = 1;
        } else {
            printf("ORDI ==> FAUX ! C'est moins\n");
            higher = 0;
        }
        printf("=================================\n");
        if (gameOver || n_try == MAX_TRIES) {
            break;
        } else {
            if (higher) {
                snprintf(buff, sizeof(buff), "%d", HIGHER);
            } else {
                snprintf(buff, sizeof(buff), "%d", LOWER);
            }
            write(fds[1], buff, strlen(buff));
            kill(childPID, SIGUSR1);
        }

        n_try++;
    }
    
    if (won) {
        snprintf(buff, sizeof(buff), "%d", WON);
    } else {
        snprintf(buff, sizeof(buff), "%d", LOOSE);
        printf("ORDI ==> Fin de partie, tu as perdu, le nombre secret etait : %d\n", numToGuess);
    }
    write(fds[1], buff, strlen(buff));
    kill(childPID, SIGUSR1);

    wait(NULL);
    
    return EXIT_SUCCESS;
}

int execFils(int fds[2]) {
    srand( time(NULL) );

    char buff[n_buff];
    int n, lastTry = MIN_NUMBER - 1, stopProc = 0, mini = MIN_NUMBER, maxi = MAX_NUMBER;

    while(!stopProc) {
        pause();

        sleep(2);

        // On lis le contenu du pipe et on le place dans buff
        n = read(fds[0], buff, n_buff - 1);
        buff[n] = '\0';
        int gameStatus = atoi(buff);
        int try_number;

        switch (gameStatus) {
        case HIGHER: // proposer un nombre aléatoire plus grand que la dernière proposition (lastTry)
            mini = lastTry + 1;
            break;
        case LOWER: // proposer un nombre aléatoire plus petit que la dernière proposition (lastTry)
            maxi = lastTry - 1;
            break;
        case WON: // Partie gagnée, afficher un message et stopper le processus
            printf("JOUEUR ==> Chouette j'ai gagne !\n");
            stopProc = 1;
            break;
        case LOOSE: // Partie perdue, afficher un message et stopper le processus
            printf("JOUEUR ==> Ho non j'ai perdu !\n");
            stopProc = 1;
            break;
        default:
            printf("ERREUR : Status inconnu : %d\n", gameStatus);
            exit(EXIT_FAILURE);
            break;
        }
        if (!stopProc) {
            try_number = (rand() % (maxi - ( mini - 1 ))) + mini;

            snprintf(buff, sizeof(buff), "%d", try_number);
            printf("JOUEUR ==> Je propose le nombre %d\n", try_number);
            lastTry = try_number;

            // envoyer le nombre proposé
            write(fds[1], buff, strlen(buff));

            // Prévenir le père
            kill(getppid(), SIGUSR1);
        }
    }

    return EXIT_SUCCESS;
}
