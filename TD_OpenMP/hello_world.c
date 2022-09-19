#include <stdio.h>
#include <omp.h>

int main(int argc, char const *argv[]) {
    int total_thread = 0, thread_num;
    #pragma omp parallel shared(total_thread) private(thread_num)
    {
        #pragma omp atomic
        total_thread++;
        thread_num = omp_get_thread_num();
        printf("Hello from thread : %d\n", thread_num);
    }
    printf("\nNombre total de threads = %d\n\n", total_thread);
    return 0;
}
// Bizarrement, si je met thread_num en shared cela fonctionne bien
