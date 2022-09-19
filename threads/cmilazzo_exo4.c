#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NB_THREAD   10
#define ARRAY_SIZE      20
#define MIN_VALUE       1
#define MAX_VALUE       1000

// declaration des fonctions
int calculNbThreadNeeded();
int generateRandomValue(const int, const int);
void displayArray(const int*);
void* lookForGreatestBetweenOffsets(void*);

// atributs globaux
int numbers[ARRAY_SIZE];

int main() {
    typedef struct { int from ; int to ;} params_struct;
    srand( time( NULL ) );
    int nbThread = calculNbThreadNeeded();

    // On calcule le pas d'avancement en fonction du nombre de thread
    int step = floor(ARRAY_SIZE / nbThread);
    params_struct* paramsList[nbThread];

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        numbers[i] = generateRandomValue(MIN_VALUE, MAX_VALUE);
    }

    pthread_t threads_numbers[nbThread];
    int from = 0;
    for (int i = 0; i < nbThread; ++i) {
        paramsList[i] = malloc(sizeof(params_struct));
        paramsList[i]->from = from;
        paramsList[i]->to = from + step - 1;
        // Sur le dernier thread il faut s'assurer de lui donner les elements du tableau dans le cas où 
        // le nombre d'elements du tableau et le nombre de thread ne serait pas congrus au modulo du pas
        if (i == nbThread - 1) {
            paramsList[i]->to += (ARRAY_SIZE - 1 - paramsList[i]->to);
        }

        if (pthread_create(&threads_numbers[i], NULL, lookForGreatestBetweenOffsets, (void*) paramsList[i]) == -1) {
            perror ("pb pthread_create\n");
            return EXIT_FAILURE;
        }

        from += step;
    }

    int greatestNumber = 0;
    for (int i = 0; i < nbThread; ++i) {
        void * responseFromthread;

        pthread_join(threads_numbers[i], &responseFromthread);
        if (  responseFromthread == PTHREAD_CANCELED ) {
            printf("Fin anormale : thread %d annulé\n", i);
            return EXIT_FAILURE;
        } else {
            if ( ((*(int*) responseFromthread)) > greatestNumber ) {
                greatestNumber = (*(int*) responseFromthread);
            }
        }
    }

    displayArray(numbers);
    printf("nbThread = %d, traitant chacun %d elements\n\n", nbThread, step);
    printf("\nLe plus grand nombre du tableau est %d\n", greatestNumber);

    // Libération mémoire
    for (int i = 0; i < nbThread; ++i) {
        free(paramsList[i]);
    }

    return EXIT_SUCCESS;
}

int calculNbThreadNeeded() {
    // On essai de répartir la charge de travail de manière égale entre tous les thread en faisant la racine carrée du nb d'elements
    int maxNeeded = floor(sqrt(ARRAY_SIZE));

    // On vérifie s'il ne reste pas de quoi affecter les elements restants (suite à l'arrondi) à un thread supplementaire
    if (ARRAY_SIZE - (maxNeeded * maxNeeded) >= maxNeeded) {
        maxNeeded++;
    }

    // On veille à ne pas dépasser le nb de thread dispo
    int nbThreadNeeded = (maxNeeded > MAX_NB_THREAD)? MAX_NB_THREAD : maxNeeded;

    return nbThreadNeeded;
}

int generateRandomValue(const int min, const int max) {
    return (rand() % (max - min + 1)) + min;
}

void displayArray(const int* numbers) {
    printf("\n[");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%d", numbers[i]);
        if (i < (ARRAY_SIZE - 1)) {
            printf(",");
        }
    }
    printf("]\n");
}


void* lookForGreatestBetweenOffsets(void* arg) {
    typedef struct { int from ; int to ; } params_struct ;
    params_struct* params = (params_struct*) arg;

    static int greatestNb = -1;
    int* index = malloc(sizeof(int));
    for (*index = params->from; *index <= params->to; *index += 1) {
        if (greatestNb < numbers[*index]) {
            greatestNb = numbers[*index];
        }
    }
    free(index);
    pthread_exit((void*) &greatestNb);
}
