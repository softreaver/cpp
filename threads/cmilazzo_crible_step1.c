/*
Étape n°1 : La valeur de N sera passée via la ligne de commande lors du lancement du programme
et on vérifiera dans le programme principal que N est bien un entier et que sa valeur est ≥ à 2.
*/
#include <stdio.h>
#include <stdlib.h>

int N;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Merci de renseigner la valeur de N !\n");
        return 1;
    } else if (( N = atoi(argv[1]) ) < 2) {
        printf("Erreur : N doit etre un nombre entier supérieur a 2 !\n");
        return 1;
    }

    printf("N = %d\n", N);

    return EXIT_SUCCESS;
}
