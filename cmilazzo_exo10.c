#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define NBFILS 2

int execFils( int const nbChild ) {
    int from = 1 + ( (nbChild - 1) * 25);
    int to = 25 + ( (nbChild - 1) * 25);

    for (int i = from; i <= to; ++i) {
        printf("%d\n", i);
        usleep(25);
    }

    printf("Fin du processus fils numero %d\n", nbChild);
    return nbChild;
}

int execPere( void ) {
    sleep(7);

    printf("Fin du processus pere.\n");

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
        exit(execFils(nbFils));
    default:
        break;
    }
    return execPere();
}

/**
 * OBSERVATIONS:
 * 
 * Les deux processus fils fonctionne en simultannés, il y a un accès concurent sur la sortie standard.
 * Les deux processus fils avancent a peut près à la même vitesse. Il y a un cotés aléatoire qui fait que
 * la primitive usleep() peut mettre le processus en veille pendant un tout petit peu plus que 25 microsecondes
 * en fonction de la disponibilité du CPU et de la granularité des temporisations du système.
 * 
 * 
 */
