#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int execFils( void ) {
    printf("Je suis le fils et mon PID = %d et le pid de mon pere est %d\n", getpid(), getppid());
    sleep(3);
    return 12;
}

int execPere( int const pid ) {
    int sigChild;
    int childPid = wait(&sigChild);
    printf("Je suis le pere et mon PID = %d et le PID de mon fils est %d\n", getpid(), pid);
    if (WIFEXITED(sigChild)){
        printf("Le fils ayant le PID = %d s'est arrêté et a renvoye le statut = %d\n", childPid, WEXITSTATUS(sigChild));
    }
    return (sigChild > 0)? 0 : 1;
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
