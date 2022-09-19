#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// OBSERVATIONS : Que ce soit le fils qui kill le père ou le père qui kill le fils
//                  sur mon système cela ne fait aucune différence.

// Action effectuée lors de la réception du signal
void action_signal (int num) {
    if (num == SIGHUP) {
        printf("Signal SIGHUP reçu\n");
        exit(EXIT_SUCCESS);
    }
}

void waitAndKill (int PIDToKill) {
    printf("J'attend 5 secondes...\n");
    sleep(5);
    printf("Envoi du SIGHUP au process n°= %d\n", PIDToKill);
    kill(PIDToKill, SIGHUP);
    return;
}

void infiniteLoop () {
    struct sigaction action;
    action.sa_handler = action_signal; // action_signal sera appelée
    sigemptyset(&action.sa_mask);      // Aucun signal n'est ignoré
    action.sa_flags = SA_RESTART;      // Compatibilité BSD
    
    // Modifie l'action pour le signal SIGHUP
    if (sigaction(SIGHUP, &action, NULL) == -1) {
        printf("Impossible d'appeler sigaction\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf(".\n");
        sleep(1);
    }
}

int execFils( void ) {
    //infiniteLoop();
    waitAndKill(getppid());
    return 0;
}

int execPere( int childPID ) {
    //waitAndKill(childPID);
    infiniteLoop();
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    int pid = fork();

    switch (pid)
    {
    case -1:
        printf("Erreur");
        exit(EXIT_FAILURE);
    case 0:
        exit(execFils());
    default:
        break;
    }
    return execPere(pid);
}
