#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NB_THREAD 10

void* functionThread(void* int_nb) {
    int* thread_number = malloc(sizeof(int));
    *thread_number = *(int*) int_nb;
    printf("Je suis le thread numero %d\n", *thread_number);
    *thread_number *= 2;
    pthread_exit((void*) thread_number);
}

int main() {
    pthread_t threads_numbers[NB_THREAD];

    for (int i = 0; i < NB_THREAD; ++i) {
        int* thread_nb = malloc(sizeof(int));
        *thread_nb = (i + 1);
        if (pthread_create(&threads_numbers[i], NULL, functionThread, (void*) thread_nb) == -1)
            perror ("pb pthread_create\n");
    }

    for (int i = 0; i < NB_THREAD; ++i) {
        void * responseFromthread;

        pthread_join(threads_numbers[i], &responseFromthread);
        if (  responseFromthread == PTHREAD_CANCELED ) printf("Fin anormale : thread %d annulé\n", i);  
        else printf("Thread terminé, valeur de retour = %d\n", *(int*) responseFromthread);   
    }

    return 0;
}
