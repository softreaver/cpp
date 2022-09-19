#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int execFils( void ) {
    srand(getpid());
    int randInt = rand() % 6;
    return randInt;
}

int execPere( int const pid ) {
    int sigChild;
    int childPid = wait(&sigChild);
    if (WIFEXITED(sigChild)){
        printf("Le fils ayant le PID = %d a genere le nombre aleatoir %d\n", childPid, WEXITSTATUS(sigChild));
    } else {
        printf("Pas de valeur de retour\n");
    }
    return (childPid > 0)? 0 : 1;
}

int main(void)
{
    int pid = fork();

    switch (pid)
    {
    case -1:
        printf("Erreur");
        exit(1);
    case 0:
        exit(execFils());
    default:
        break;
    }
    return execPere(pid);
}
