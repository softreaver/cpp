#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void SIGUSR1_action() {
    printf("SIGUSR1 recu\n");
    return;
}

void SIGINT_action() {
    printf("\nSIGINT recu\n");
    exit(EXIT_SUCCESS);
}

void action_signal(int numSig) {
    switch (numSig) {
        case SIGUSR1: SIGUSR1_action();
            break;
        case SIGINT: SIGINT_action();
            break;
        default: // ignore
            break;
    }
}

int main() {
    struct sigaction action;
    action.sa_handler = action_signal;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    // Modifie l'action pour le signal SIGHUP
    if (sigaction(SIGUSR1, &action, NULL) == -1 ||
        sigaction(SIGINT, &action, NULL) == -1    
    ) {
        printf("Impossible d'appeler sigaction\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        pause();
    }
}
