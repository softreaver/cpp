#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int PID;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Merci de renseigner un numero PID !\n");
        return 1;
    } else if (( PID = atoi(argv[1]) ) < 0) {
        printf("Erreur : Merci d'entrer un numero PID correcte\n");
        return 1;
    }

    kill(PID, SIGUSR1);

    return EXIT_SUCCESS;
}
