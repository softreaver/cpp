// gcc -o ./Exo7 ./Exo7.c -fopenmp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAX_INT_VALUE   15
#define NUM_THREADS     9
#define SIZE_OF_N       10
#define Nt              3 * SIZE_OF_N/2

double START_SINGLE;
double END_SINGLE;
double START_PARALLEL;
double END_PARALLEL;

/**
 * 1) Les deux boucles peuvent être parallèlisées.
 * 
 * 2) Aucune variable n'a l'obligation d'être partagée puisque :
 * N n'est accedé qu'en lecture seule, tandis que X et Y sont des pointeur donc même
 * en mode FIRSTPRIVATE, l'adresse mémoire pointée serait toujours valable.
 * (ATTENTION pas PRIVATE pour X et Y car ils pointeraient sur une adresse aléatoire).
 * Quant aux variables i et l ; i est privée car déclarée dans chaque thread, et l est initialisé indépendament dans chaque threads.
 * 
 * 3) Voir l'implémentation DWT_Parralele() plus bas.
 * 
 * 4) Pour SIZE_OF_N valorisé à 24800, j'ai obtenu Ts = 0.433 et Tp = 0.194
 * De là on calcule S(Nt) = 1 / (Ts + Tp/Nt) = 1 / (0.433 + 0.194 / 37200) = 2.31
 */ 

void DWT(int* X,int* Y,int N);
void DWT_parallel(int* X,int* Y,int N);

void setVec(int *vec, int n) {
    for (int i = 0; i < n; i++) {
        *(vec+i) = rand() % MAX_INT_VALUE;
    }
}

void dumpVec(int *vec, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        if (i > 0) { printf(", "); }
        printf("%d", *(vec+i));
    }
    printf("]\n");
}

int main(int argc, char const *argv[]) {
    int N = SIZE_OF_N;
    srand( time( NULL ) );
    int *X = malloc(sizeof(int) * N);
    int *Y = malloc(sizeof(int) * N);
    setVec(X, N);

    printf("\n== Single ==\n");
    DWT(X, Y, N);
    dumpVec(X, N);
    dumpVec(Y, N);

    printf("\n\n== Parallel ==\n");

    DWT_parallel(X, Y, N);
    dumpVec(X, N);
    dumpVec(Y, N);

    printf("\nTemps Ts = %.3f\n", END_SINGLE - START_SINGLE);
    printf("Temps Tp = %.3f\n", END_PARALLEL - START_PARALLEL);
    
    return 0;
}


void DWT(int* X,int* Y,int N){
    START_SINGLE = omp_get_wtime();
    int l;
    for (l=N/2;l>1;l--){
        int i ;
        for (i=0;i<l;i++){
            Y[i] = X[2*i] + X[2*i+1] ;
            Y[i+1] = X[2*i] - X[2*i+1] ;
        }
    }
    END_SINGLE = omp_get_wtime();
}

void DWT_parallel(int* X,int* Y,int N){
    START_PARALLEL = omp_get_wtime();
    int l;
    #pragma omp parallel
    {   
        #pragma omp for schedule(runtime) private(l) nowait
        for (l=N/2;l>1;l--){
            int i ;
            for (i=0;i<l;i++){
                Y[i] = X[2*i] + X[2*i+1] ;
                Y[i+1] = X[2*i] - X[2*i+1] ;
            }
        }
    }
    END_PARALLEL = omp_get_wtime();
}
