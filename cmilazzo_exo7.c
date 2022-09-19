#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int execFils( void ) {
    printf("Je suis le fils et mon PID = %d et le pid de mon pere est %d\n", getpid(), getppid());
    printf("fin du processus fils il deviens zombie pour 10 secondes\n");
    return 0;
}

int execPere( int const pid ) {
    sleep(10);
    int sigChild;
    int childPid = wait(&sigChild);
    
    printf("Fin du processus pere\n");
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
