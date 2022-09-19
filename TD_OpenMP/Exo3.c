#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N   3
#define P   3
#define MAX_INT_VALUE 15
#define TASK_QTY      10 // Quantité de tâche

int resultSeq[N], resultParallel[N];
int vector[N] = {5, 3, 7};
int mat[N][P] = {
    {2, 4, 3},
    {4, 1, 6},
    {3, 6, 8}
};

void setMat(int mat[N][P]);
void setVec(int vec[N]);
void initResult(int vec[N]);
void printResults();
void execSeq();
void execParallel();


int main(int argc, char const *argv[]) {
    double startSeq, startParallel; 
    double endSeq, endParallel; 

    srand( time( NULL ) );

    //setMat(mat);
    //setVec(vector);
    initResult(resultSeq);
    initResult(resultParallel);

    startSeq = omp_get_wtime(); 
    execSeq();
    endSeq = omp_get_wtime(); 

    startParallel = omp_get_wtime(); 
    execParallel();
    endParallel = omp_get_wtime(); 
    
    printResults();
    printf("Traitement sequentiel : %f seconds\n", endSeq - startSeq);
    printf("Traitement parallele : %f seconds\n", endParallel - startParallel);

    printf("\n\nGain en performance : %f pour %d threads.\n\n", 1 / ((endSeq - startSeq) / TASK_QTY), TASK_QTY);

    return 0;
}

void execSeq() {
    for (int n = 0; n < N; n++) {
        for (int p = 0; p < P; p++) {
            resultSeq[n] += vector[n] * mat[n][p];
        }
    }
}

void execParallel() {
#pragma omp parallel num_threads(TASK_QTY)
    {
        #pragma omp for
        for (int n = 0; n < N; n++) {
            for (int p = 0; p < P; p++) {
                resultParallel[n] += vector[n] * mat[n][p];
            }
        }
    }
}

void setMat(int mat[N][P]) {
    for (int n = 0; n < N; n++) {
        for (int p = 0; p < P; p++) {
            mat[n][p] = rand() % MAX_INT_VALUE;
        }
    }
}

void setVec(int vec[N]) {
    for (int n = 0; n < N; n++) {
        vec[n] = rand() % MAX_INT_VALUE;
    }
}

void initResult(int vec[N]) {
    for (int n = 0; n < N; n++) {
        vec[n] = 0;
    }
}

void printResults() {
    printf("Resultat : \n[");
    for (int i = 0; i < N; i++) {
        printf("%d", resultSeq[i]);
        if (i+1 < N) {
            printf(", ");
        }
    }
    printf("]\n[");
    for (int i = 0; i < N; i++) {
        printf("%d", resultParallel[i]);
        if (i+1 < N) {
            printf(", ");
        }
    }
    printf("]\n\n");
}
