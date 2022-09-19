#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N               3
#define MAX_INT_VALUE   10
#define EPSILON         0.001
#define TASK_QTY        1 // Quantité de tâches parallèles
#define MAX_ITERATION   N

float A[N][N] = {
    {2, 4, 3},
    {4, 1, 6},
    {3, 6, 8}
};
float b[N] = {45, 33, 119};
float x[N], g[N];
float h[N];

void setSymetricMat( float mat[N][N]);
void setVec( float vec[N]);
void produitMatVec(const float mat[N][N], const float vector[N], float result[N]);
float produitVec(const float vec1[N], const float vec2[N]);
void produitVecScalar(const  float vec[N], const float scalar, float result[N]);
void addVec(const float vec1[N], const float vec2[N], float result[N]);
void copyArr( float orig[N],  float dest[N]);
void invVec( float vec[N]);
void printResult(const  float result[N]);

int main( float argc, char const *argv[]) {
    srand( time( NULL ) );

    //setVec(b);
    //setSymetricMat(A);

    // g0 = Ax0 - b
    produitMatVec(A, x, g);
    float g_tmp[N], b_inv[N];
    copyArr(g, g_tmp);
    copyArr(b, b_inv);
    invVec(b_inv);
    addVec(g_tmp, b_inv, g);

    // h0 = -g0
    copyArr(g, h);
    invVec(h);

    int totalIt = 0;
    for (int i = 0; i < MAX_ITERATION; i++) {
        totalIt = i+1;
        float Ah[N];
        produitMatVec(A, h, Ah);

        float rho = -1 * ( produitVec(g, h) / produitVec(h, Ah) );

        float rhoh[N];
        produitVecScalar(h, rho, rhoh);

        float x_next[N];
        addVec(x, rhoh, x_next);

        float rhoAh[N];
        produitVecScalar(Ah, rho, rhoAh);
        float g_next[N];
        addVec(g, rhoAh, g_next);

        float gamma = produitVec(g_next, g_next) / produitVec(g, g);

        float h_next[N], g_next_inv[N], gammah[N];
        produitVecScalar(h, gamma, gammah);

        copyArr(g_next, g_next_inv);
        invVec(g_next_inv);

        addVec(g_next_inv, gammah, h_next);

        copyArr(x_next, x);
        copyArr(g_next, g);
        copyArr(h_next, h);

        if (produitVec(g, g) < EPSILON) {
            break;
        }
    }
    printf("Fin après %d iterations sur %d\n\n", totalIt, MAX_ITERATION);

    // x est la solution du problème
    printResult(x);
    return 0;
}

void setSymetricMat( float mat[N][N]) {
    int start = 0;
    for (int n = 0; n < N; n++) {
        for (int p = start; p < N; p++) {
            start++;
            mat[n][p] = rand() % MAX_INT_VALUE;
            if (n != p) { // Copie de l'element de la partie supérieur sur la partie inférieur
                mat[p][n] = mat[n][p];
            }
        }
    }
}

void setVec( float vec[N]) {
    for (int n = 0; n < N; n++) {
        vec[n] = rand() % MAX_INT_VALUE;
    }
}

void produitMatVec(const float mat[N][N], const float vector[N], float result[N]) {
    #pragma omp parallel num_threads(TASK_QTY)
    {
        #pragma omp for
        for (int n = 0; n < N; n++) {
            for (int p = 0; p < N; p++) {
                result[n] += vector[n] * mat[n][p];
            }
        }
    }
}

float produitVec(const float vec1[N], const float vec2[N]) {
    float result = 0;
    #pragma omp parallel shared(result) num_threads(TASK_QTY)
    {
        #pragma omp for reduction(+:result)
        for (int n = 0; n < N; n++) {
            result += vec1[n] * vec2[n];
        }
    }
    return result;
}

void addVec(const float vec1[N], const float vec2[N], float result[N]) {
    #pragma omp parallel num_threads(TASK_QTY)
    {
        #pragma omp for
        for (int n = 0; n < N; n++) {
            result[n] += vec1[n] + vec2[n];
        }
    }
}

void produitVecScalar(const float vec[N], const  float scalar,  float result[N]) {
    #pragma omp parallel num_threads(TASK_QTY)
    {
        #pragma omp for
        for (int n = 0; n < N; n++) {
            result[N] += vec[n] * scalar;
        }
    }
}

void copyArr( float orig[N],  float dest[N]) {
    for (int i = 0; i < N; i++) {
        dest[i] = orig[i];
    }
}

void invVec( float vec[N]) {
    for (int i = 0; i < N; i++) {
        vec[i] = -1 * (vec[i]);
    }
}

void printResult(const float result[N]) {
    printf("Resultat : \n[");
    for (int i = 0; i < N; i++) {
        printf("%f", result[i]);
        if (i+1 < N) {
            printf(", ");
        }
    }
    printf("]\n\n");
}
