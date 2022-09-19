#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int execFils( void ) {
    printf("Je suis le fils.\n");
    return 0;
}

int execPere( void ) {
    printf("Je suis le pere.\n");
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
    return execPere();
}
