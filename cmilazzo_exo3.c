#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int execFils( void ) {
    printf("Je suis le fils et mon PID = %d et le pid de mon pere est %d\n", getpid(), getppid());
    return 0;
}

int execPere( int const pid ) {
    printf("Je suis le pere et mon PID = %d et le PID de mon fils est %d\n", getpid(), pid);
    sleep(3); // Avec ou sans le sleep() cela reviens au même. Toute fois si le fils finit son execution après sont père, le getppid() renvois 1 comme si le systeme devenait le nouveau père du processus fils.
    return 0;
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
