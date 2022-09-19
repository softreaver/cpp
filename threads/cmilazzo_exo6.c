/*

OBSERVATION: Sans les mutex, les thread efffectuait de temps en temps les opérations de manière croisée en fonction des temps d'attente.
Malgré les opérations identiques sur X et Y, vu que l'odre changait, le résultat final pouvait être différent.

Pour s'assurer que le resultat de X et Y soit identique, il faut également s'assurer que les opérations se font dans le même ordre.
Il faut donc utiliser des mutex pour synchroniser les threads.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

int x = 1;
int y = 1;
pthread_mutex_t lock;

void my_usleep(int MIN, int MAX) {
    double s;
    s=(rand() % (MAX-MIN+1) + MIN);
    usleep(s);

    return;
}

void* thread1 (void* arg) {
    pthread_mutex_lock(&lock);
    x++;
    printf("thread1 - x = %d, y = %d\n", x, y);
    my_usleep(4000, 8000);
    y++;
    printf("thread1 - x = %d, y = %d\n", x, y);

    pthread_mutex_unlock(&lock);
    return NULL;
}

void* thread2 (void* arg) {
    pthread_mutex_lock(&lock);
    x *= 2;
    printf("thread2 - x = %d, y = %d\n", x, y);
    my_usleep(4000, 8000);
    y *= 2;
    printf("thread2 - x = %d, y = %d\n", x, y);

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    srand(time(NULL));
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    pthread_t threads_numbers[2];
    if (pthread_create(&threads_numbers[0], NULL, thread1, NULL) == -1) {
        perror ("pb pthread_create\n");
        return EXIT_FAILURE;
    }
    if (pthread_create(&threads_numbers[1], NULL, thread2, NULL) == -1) {
        perror ("pb pthread_create\n");
        return EXIT_FAILURE;
    }

    pthread_join(threads_numbers[0], NULL);
    pthread_join(threads_numbers[1], NULL);

    printf("===========================================\n\n");

    pthread_mutex_destroy(&lock);
    return 0;
}
