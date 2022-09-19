#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void SIGINT_action() {
    printf("\nSIGINT recu\n");
    exit(EXIT_SUCCESS);
}

void action_signal(int numSig) {
    printf("\nsignal n°%d recu\n", numSig);
    printf("J'attend 10 secondes...\n");
    sleep(10);
}

int main() {
    struct sigaction action;
    action.sa_handler = action_signal;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    // Modifie l'action pour le signal SIGHUP
    if (sigaction(SIGINT, &action, NULL) == -1) {
        printf("Impossible d'appeler sigaction\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("J'attend un signal...\n");
        pause();
    }
}
