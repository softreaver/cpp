#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>

const int NB_ESSAI_MAX = 10;
const int TIMEOUT = 5;     //Secondes
sigjmp_buf contexte;
int numToGuess;
 
void gestionAlarme(int numSig) {
    if (numSig == SIGALRM) {

        siglongjmp( contexte, 1); /* reprise du programme principal */
    }
}

int main(void) {
    srand( time(NULL) );

    numToGuess = (rand() % 1000) + 1;
    int answer;
    int won = 0;
    int triesLeft = NB_ESSAI_MAX;

    printf("\nVous devez devinez le nombre secret en proposant un nombre entre 1 et 1000 inclus. Pressez entree pour commencer.\n");
    getchar();

    while (triesLeft > 0) {
        /* Installation du handler gestionAlarme pour SIGALRM */
        signal(SIGALRM,gestionAlarme); 

        printf("==> Il vous reste %d essai(s)\n", triesLeft);
        printf("Vous avez %d secondes pour entrer un nombre entier : ", TIMEOUT);

        if (!sigsetjmp(contexte, 1)) { // Point de reprise
            alarm(TIMEOUT);
            scanf("%d", &answer);
            fflush(stdin);
            alarm(0);

            // Vérification de la réponse
            if (answer == numToGuess) {
                won = 1;
                break;
            } 
        } else {
            printf("\nVous avez mis trop de temps pour repondre, vous perdez un essai !\n");
        }

        if (numToGuess < answer) {
            printf("\nFAUX, c'est moins.\n");
        } else {
            printf("\nFAUX, c'est plus.\n");
        }
        triesLeft--;
    }

    if (won) {
        printf("\nC'est gagne !!\n");
    } else {
        printf("\nPerdu, le nombre etait : %d !!\n", numToGuess);
    }

    return EXIT_SUCCESS;
}
