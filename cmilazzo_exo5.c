#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int globalInt = 10;

int main(void)
{
    int localInt = 11;

    int pid = fork();

    if (pid == 0) {
        printf("FILS (avant modifs) : globale = %d | locale = %d\n", globalInt, localInt);
        localInt = 21; globalInt = 20;
        printf("FILS (apres modifs) : globale = %d | locale = %d\n", globalInt, localInt);
        printf("\nfin du fils\n\n");
        exit(0);
    } else if(pid == -1) {
        printf("Erreur");
        exit(1);
    } else {
        int ret;
        wait(&ret);
        printf("PERE (avant modifs) : globale = %d | locale = %d\n", globalInt, localInt);
        localInt = 31; globalInt = 30;
        printf("PERE (apres modifs) : globale = %d | locale = %d\n", globalInt, localInt);
    }
    return 0;
}

/**
 * CONCLUSION
 * 
 * Lors de la création d'un processus fils, les variables globales et locales sont toutes copiées mais elles ne sont pas partagées entre les processus.
 */
