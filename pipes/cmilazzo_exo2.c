#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int execPere(int fds[2]);
int execFils(int fds[2]);

int main() {
    int fds[2];
    // Création du pipe
    pipe(fds);

    int pid = fork();

    switch (pid) {
    case -1:
        printf("Erreur");
        exit(EXIT_FAILURE);
    case 0:
        exit(execFils(fds));
    default:
        break;
    }

    return execPere(fds);
}

int execPere(int fds[2]) {
    close(fds[0]);

    // On attend 3 secondes
    sleep(3);
    printf("Je suis le pere\n");
    write(fds[1], "GO", 2);

    // On attend la fin du fils
    wait(NULL);

    return EXIT_SUCCESS;
}

int execFils(int fds[2]) {
    close(fds[1]);
    // Procedure bloquante, elle atend que le pipe contienne sufisament de données avant de lire le contenu
    int n = read(fds[0], NULL, 2);

    printf("Je suis le fils\n");

    return EXIT_SUCCESS;
}
