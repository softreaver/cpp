/*
Étape n°1 : La valeur de N sera passée via la ligne de commande lors du lancement du programme
et on vérifiera dans le programme principal que N est bien un entier et que sa valeur est ≥ à 2.

Étape n°2 : Ne connaissant pas cette valeur a priori on ne pourra dimensionner la table que lors de
l’exécution ce qui va entraîner la nécessité de variables dynamiques. Tout appel système devra être
contrôlé en respect des informations données dans les pages de man.
*/

#include <stdio.h>
#include <stdlib.h>

int N;
int** numbers;

void displayNumbers() {
    printf("\n[");
    for (int i = 0; i < N - 1; ++i) {
        if (i > 0) {
            printf(",");
        }
        printf("%d", *numbers[i]);
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

    displayNumbers();

    return EXIT_SUCCESS;
}