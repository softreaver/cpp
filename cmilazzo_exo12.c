#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <signal.h>

#define BUFFER_SIZE     10
#define PROG_NAME_CALC  "./cmilazzo_exo12_calc.exe"

int displayResults( int const nbChild ) {

    for (int i = 0; i < nbChild; ++i) {
        int sigChild;
        wait(&sigChild);

        if (WIFEXITED(sigChild)){
            int result = WEXITSTATUS(sigChild);
            printf("%d\n", result);
        } else {
            exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}

int main(void)
{
    int nbChild = 0;
    int childPid;
    char buffer[BUFFER_SIZE];
    char* opType = malloc(BUFFER_SIZE * sizeof(char));
    char* op1 = malloc(BUFFER_SIZE * sizeof(char));
    char* op2 = malloc(BUFFER_SIZE * sizeof(char));
 
    printf("\n\nVeuillez entrer une serie d'operation (<opType> <op1> <op2> [etc....]) puis finir par un point : ");
    while ( true ) {
        scanf("%s", buffer);
        strcpy(opType, buffer);
        char opTypeChar = (char) opType[0];
        if ( opTypeChar == '.' ) {
            break;
        }

        scanf("%s", buffer);
        strcpy(op1, buffer);

        scanf("%s", buffer);
        strcpy(op2, buffer);

        childPid = fork();
        nbChild++;

        if ( childPid == 0 ) {
            char* const argv[] = {
                PROG_NAME_CALC,
                opType,
                op1,
                op2,
                NULL
            };
            int res = execv(PROG_NAME_CALC, argv);
            if (res == -1) {
                printf("Erreur lors de l'execution du programme : %s\n", PROG_NAME_CALC);
                kill(getpid(), SIGKILL);
            }
            exit(EXIT_SUCCESS);
        } else if (childPid == -1) {
            exit(EXIT_FAILURE);
        }
    }

    return displayResults( nbChild );
}
