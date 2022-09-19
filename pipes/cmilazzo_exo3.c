#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int execPere(int fds[2]);
int execFils(int fds[2]);

const int n_buff = 100;

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
    char buff[n_buff];

    strcpy(buff, "Voici mon message!");

    close(fds[0]);
    write(fds[1], buff, strlen(buff));

    // On attend la fin du fils
    wait(NULL);

    return EXIT_SUCCESS;
}

int execFils(int fds[2]) {
    char buff[n_buff];

    close(fds[1]);
    // On lis le contenu du pipe et on le place dans buff
    int n = read(fds[0], buff, n_buff - 1);
    buff[n] = '\0';

    printf("Message recu du père : %s\n", buff);
    printf("Le message fait %d caracteres\n\n", n);

    return EXIT_SUCCESS;
}