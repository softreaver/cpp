#include <stdio.h>
#include <omp.h>

#define N 3

long produitVec(const long vec1[N], const long vec2[N]) {
    int result = 0;
    #pragma omp parallel shared(result)
    {
        #pragma omp for reduction(+:result)
        for (int n = 0; n < N; n++) {
            result += vec1[n] * vec2[n];
        }
    }
    return result;
}

int main(int argc, char const *argv[])
{
    long a[N] = {1, 2, 3};
    long b[N] = {85, -3, 1};
    long c[N] = {2, -9, 18};
    float rho = -1 * ( (float)produitVec(a, b) / produitVec(a, c) );
    printf("-1 * (%ld / %ld)\n", produitVec(a, b), produitVec(a, c));
    printf("%f\n\n", rho);
    return 0;
}
