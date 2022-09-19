#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int calc( char const opType, int const op1, int const op2 );

int main( int argc, char* argv[] ) {
    if ( argc < 4) {
        printf("Erreur, il manque des arguments. Usage : <operateur> <operande1> <operande2>");
        kill(getpid(), SIGKILL);
    }
    char opType = (char) argv[1][0];
    int op1 = atoi(argv[2]);
    int op2 = atoi(argv[3]);

    return calc(opType, op1, op2);
}

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
        kill(getpid(), SIGKILL);
        break;
    }
    return result;
}
