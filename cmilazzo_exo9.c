#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define NBFILS 2

int execFils( void ) {
    srand(getpid());
    int randInt = (rand() % 4) + 1;
    sleep(randInt);
    return randInt;
}

int execPere( void ) {
    int longest = 0;
    int shortest = 0;
    for (int i = 0; i < NBFILS; i++) {
        int sigChild;
        int childPid = wait(&sigChild);

        if (WIFEXITED(sigChild)){
            int waitDuration = WEXITSTATUS(sigChild);
            if (waitDuration > longest) {
                shortest = longest;
                longest = waitDuration;
            } else {
                shortest = waitDuration;
            }
        } else {
            exit(EXIT_FAILURE);
        }
    }

    printf("Le processus le plus cours a duree %d seconde(s) et le plus long %d seconde(s)\n", shortest, longest);

    return EXIT_SUCCESS;
}

int main(void)
{
    int nbFils = 0;
    int childPid;
    do {
        nbFils++;
        childPid = fork();
    } while (nbFils < NBFILS && childPid);

    switch (childPid)
    {
    case -1:
        printf("Erreur");
        exit(1);
    case 0:
        exit(execFils());
    default:
        break;
    }
    return execPere();
}
