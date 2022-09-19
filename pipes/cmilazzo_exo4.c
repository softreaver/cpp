#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h> 
#include <string.h>

int execPere(int fds[2], int* childrenPID, int nb_PID);
int execFils(int fds[2]);

const int n_buff = 10;
const int nb_children = 10;
jmp_buf context; 

void SIGUSR1_action() { // Le fils doit récupérer la donnée dans le tube
    longjmp(context, 1);
    return;
}

void action_signal(int numSig) {
    switch (numSig) {
        case SIGUSR1: SIGUSR1_action();
            break;
        default: // ignorer
            break;
    }
}

int main() {
    struct sigaction action;
    action.sa_handler = action_signal;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    int fds[2];
    // Création du pipe
    pipe(fds);

    // Création du tableau qui contiendra tous les processus fils
    int childrenPID[nb_children];

    printf("Creation de %d processus fils\n", nb_children);
    // créer n processus fils
    int n = 0;
    int pid = 1;
    while (pid && n < nb_children) {
        pid = fork();
        if (pid) { // On garde les pid pour leur envoyer un signal plus bas
            childrenPID[n] = pid;
            printf("Processus %d cree\n", pid);
        }
        n++;
    }

    switch (pid) {
    case -1:
        printf("Erreur");
        exit(EXIT_FAILURE);
        break;
    case 0:
        if (sigaction(SIGUSR1, &action, NULL) == -1) {
            printf("Impossible d'appeler sigaction\n");
            exit(EXIT_FAILURE);
        }
        exit(execFils(fds));
        break;
    default:
        break;
    }

    return execPere(fds, childrenPID, n);
}

int execPere(int fds[2], int* childrenPID, int nb_PID) {
    char buff[n_buff];
    // On place le nombre initial (zéro) dans le buffer
    snprintf(buff, sizeof(buff), "%d", 0);

    // Pour chaque fils on passe le nombre à incrémenter via le tube et on attend son retour
    for (int i = 0; i < nb_PID; ++i) {
        write(fds[1], buff, strlen(buff));

        // On prévient le fils pour lui dire qu'il peut récupérer la donnée dans le tube
        kill(childrenPID[i], SIGUSR1);

        // On attend la fin du fils
        int sigChild;
        wait(&sigChild);
        if (!WIFEXITED(sigChild)){
            exit(EXIT_FAILURE);
        }

        // On lis le contenu du tube et on le place dans buff
        int n = read(fds[0], buff, n_buff - 1);
        buff[n] = '\0';
    }
    
    printf("Le total = %s\n", buff);
    return EXIT_SUCCESS;
}

int execFils(int fds[2]) {
    char buff[n_buff];
    int n;

    if (setjmp(context)) { // Executé seulement quand le pere aura emit un signal SIGUSR1
        // On lis le contenu du pipe et on le place dans buff
        n = read(fds[0], buff, n_buff - 1);
        buff[n] = '\0';
    } else { // Executé en premier lieux, on attend que le père autorise à récupérer la donnée dans le tube
        while(1) {
            sleep(1);
        }
    }
    int numberToIncrement = atoi(buff);
    numberToIncrement += getpid();
    snprintf(buff, sizeof(buff), "%d", numberToIncrement);

    // envoyer le nombre incrémenté dans le tube
    write(fds[1], buff, strlen(buff));

    return EXIT_SUCCESS;
}
