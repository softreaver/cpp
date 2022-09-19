#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int add(int op1, int op2);

int main(int argc, char const *argv[]) {
    int A[10] = {2, 5, 3, 8, 5, 4, 2, 1, 75, 15}; // total = 120
    int total = 0;
    #pragma omp parallel shared(A, total)
    {
        #pragma omp for reduction(+:total) // Sans réduction, on pourrait avoir deux résultat qui s'écrasent l'un l'autre
        for (int i = 0; i < 10; i+=2) {
            total += add(A[i], A[i+1]);
        }
    }
    printf("Le total de A = %d\n\n", total);
    return 0;
}

int add(int op1, int op2) {
    sleep(1);
    return op1 + op2;
}
