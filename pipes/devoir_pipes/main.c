#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#include "master.h"
#include "worker.h"
#include "mutils.h"

#define MAX_INTERVAL    50  // Taille maximal d'un intervale de travail

int ask_for_number();

int n_buff; // Taille max du buffer pour le pipe du master
int n_workers_buff = 50; // Taille max du buffer pour les FIFOs vers les workers
int verbose = 0;
int n_proc = 0;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "-v") == 0) { // Mode verbeux
            verbose = 1;
        }
    }
    int fds_master[2];
    pipe(fds_master);

    int N = 0;
    printf("Chercher les nombres premiers entre 2 et N.\n");

    // Demander la valeur de N, le nombre max jusqu'auquel il faut chercher les nombres premiers
    while(N < 3) {
        printf("Veuillez entrer une valeur strictement supérieur à 2 pour N : ");
        N = ask_for_number();
    }
    // Demander la valeur de N, le nombre max jusqu'auquel il faut chercher les nombres premiers
    while(n_proc < 1) {
        printf("Veuillez entrer une valeur strictement positive pour n_proc : ");
        n_proc = ask_for_number();
    }
    n_proc = (n_proc > N) ? N : n_proc; // Inutilise d'avoir plus de processus que de nombre à examiner

    // Calcule de la taille du buffer (50 octets par worker)
    n_buff = 50 * n_proc;

    // On calcule l'interval de travail T maximum MAX_INTERVAL
    int T = floor( (N/n_proc) / 2 );
    if (T == 0) { T = 1; }
    while (T > MAX_INTERVAL) {
        T /= 2;
    }
    
    // Créations des workers
    int n_worker, pid;
    int pid_workers[n_proc];
    int index_fifo;
    
    char fifo_name[16], index[5];
    mode_t mode; int tub;
    mode = 0644;
    
    for (int i = 0; i < n_proc; ++i) {
        // On cré un tube nommé pour la communication vers le processus
        strcpy(fifo_name, "fifo_");
        snprintf(index, 5, "%d", i);
        strcat(fifo_name,  index);
        mkfifo(fifo_name, mode);

        pid = fork();
        if (pid <= 0) { // Les fils ne cré pas de worker.
            index_fifo = i;
            break; 
        }
    }

    switch (pid) {
    case -1:
        printf("Erreur lors de la creation des processus worker\n");
        exit(EXIT_FAILURE);
    case 0:
        close(fds_master[0]); // Le worker ne fait qu'écrire dans ce pipe
        exit(execWorker(index_fifo, fds_master[1], n_workers_buff, verbose));
    default:
        break;
    }
    close (fds_master[1]); // Le père ne fait que lire dans ce pipe
    return execMaster(N, T, n_proc, fds_master[0], n_buff, verbose);
}

// Récupère le nombre entré sur l'entrée standard et le retourne.
int ask_for_number() {
    int n;
    scanf("%d", &n);
    fflush(stdin);
    printf("\n");

    return n;
}
