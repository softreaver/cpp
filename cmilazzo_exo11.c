#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int calc( char const opType, int const op1, int const op2 ) {
    int result;

    switch(opType) {
    case '+':
        result = op1 + op2;
        break;
    case '-':
        result = op1 - op2;
        break;
    case '*':
        result = op1 * op2;
        break;
    case '/':
        result = op1 / op2;
        break;
    default:
        printf("Operateur inconnu : %c\n", opType);
        kill(getpid(), 9);
        break;
    }
    return result;
}

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
    int childPid, op1, op2;
    char opType;
    char buffer[10];
 
    printf("\n\nVeuillez entrer une serie d'operation (<opType> <op1> <op2>) : ");
    while ( true ) {
        scanf("%s", buffer);
        opType = (char) buffer[0];

        if ( opType == '.' ) {
            break;
        }

        scanf("%s", buffer);
        op1 = atoi(buffer);

        scanf("%s", buffer);
        op2 = atoi(buffer);

        childPid = fork();
        nbChild++;

        if ( childPid == 0 ) {
            exit(calc(opType, op1, op2));
        } else if (childPid == -1) {
            exit(EXIT_FAILURE);
        }
    }

    return displayResults( nbChild );
}

/**
 * REPONSE A LA QUESTION :
 * 
 * La valeur representative max possible que peut retourner les processus fils est de 255 car le status code d'un processus est codé sur 1 octet (8bit)
 * 
 */
