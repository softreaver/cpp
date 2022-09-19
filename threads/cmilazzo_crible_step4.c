/*
Étape n°1 : La valeur de N sera passée via la ligne de commande lors du lancement du programme
et on vérifiera dans le programme principal que N est bien un entier et que sa valeur est ≥ à 2.

Étape n°2 : Ne connaissant pas cette valeur a priori on ne pourra dimensionner la table que lors de
l’exécution ce qui va entraîner la nécessité de variables dynamiques. Tout appel système devra être
contrôlé en respect des informations données dans les pages de man.

Étape n°3 : On aborde le cœur du problème. Une boucle va parcourir la table des nombres. À
chaque fois qu’un nombre premier est rencontré on va lancer un thread joignable qui va marquer
tous les multiples de ce nombre. On ne connaît pas le nombre de threads à lancer et il n’est pas
raisonnable de penser que: « qui peut le plus, peut le moins » et de ce fait penser qu’il y en aura au
plus N.

Étape n°4 : On attend la fin de tous les threads et ensuite on affiche les nombres restant dans la
table.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int N;
int** numbers;

void* eratosthene(void* arg) {
    int* primeNumber = malloc(sizeof(int));
    *primeNumber = *(int*) arg;

    if ( (*primeNumber * *primeNumber) >= N) {
        return NULL;
    } else {
        int* index = (int*) malloc(sizeof(int));
        for (*index = (*primeNumber * *primeNumber) - 2; *index < N - 1; *index += *primeNumber) {
            free(numbers[*index]);
            numbers[*index] = NULL;
        }
        for (*index = *primeNumber - 1; *index < (*primeNumber * 2) - 2; *index += 1) {
            if (numbers[*index] != NULL) {
                int* startNumber = (int*) malloc(sizeof(int));

                *startNumber = *numbers[*index];
                pthread_t* threads_id = (pthread_t*) malloc(sizeof(pthread_t));
                if (pthread_create(threads_id, NULL, eratosthene, (void*) startNumber) == -1) {
                    perror ("pb pthread_create\n");

                    free(startNumber);
                    free(primeNumber);
                    free(index);
                    exit(EXIT_FAILURE);
                }
                pthread_join(*threads_id, NULL);
                free(threads_id);
                free(startNumber);
                break;
            }
        }
        
        free(primeNumber);
        free(index);
    }

    return NULL;
}

void displayPrimeNumbers() {
    printf("\n[");
    for (int i = 0; i < N - 1; ++i) {
        if (numbers[i] != NULL) {
            if (i > 0) {
                printf(",");
            }
            printf("%d", *numbers[i]);
        }
    }
    printf("]\n\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Merci de renseigner la valeur de N !\n");
        return 1;
    } else if (( N = atoi(argv[1]) ) < 2) {
        printf("Erreur : N doit etre un nombre entier supérieur a 2 !\n");
        return 1;
    }

    printf("N = %d\n", N);

    // création d'un tableau de nombre de 1 à N
    numbers = (int**) malloc((N - 1) * sizeof(int*));
    for (int i = 2; i <= N; ++i) {
        numbers[i - 2] = (int*) malloc(sizeof(int));
        *(numbers[i - 2]) = i;
    }

    int startNum = 2;
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, eratosthene, (void*) &startNum) == -1) {
        perror ("pb pthread_create\n");
        exit(EXIT_FAILURE);
    }
    pthread_join(thread_id, NULL);

    displayPrimeNumbers();

    return EXIT_SUCCESS;
}