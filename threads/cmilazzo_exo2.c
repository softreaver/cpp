#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* functionThreadA(void* arg) {
    printf("%s\n", (char*) arg);
    pthread_exit((void*) "Je suis A et j'ai fini\n");
}

void* functionThreadB(void* arg) {
    printf("%s\n", (char*) arg);
    pthread_exit((void*) "Je suis B et j'ai fini\n");
}

int main() {
    pthread_t num_threadA, num_threadB;

    if (pthread_create(&num_threadA, NULL, functionThreadA, (void*) "Un message pour A") == -1)
        perror ("pb pthread_create\n");

    if (pthread_create(&num_threadB, NULL, functionThreadB, (void*) "Un message pour B") == -1)
        perror ("pb pthread_create\n");
    
    void * responseFromA;
    void * responseFromB;
    pthread_join(num_threadB, &responseFromA);
    if (  responseFromA == PTHREAD_CANCELED ) printf("Fin anormale : thread A annulé\n");  
    else printf("%s\n", (char*) responseFromA);

    pthread_join(num_threadA, &responseFromB);
    if (  responseFromA == PTHREAD_CANCELED ) printf("Fin anormale : thread B annulé\n");  
    else printf("%s\n", (char*) responseFromB);

    return 0;
} 
