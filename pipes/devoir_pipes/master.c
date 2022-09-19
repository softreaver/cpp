#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "mutils.h"

int execMaster(int N, int T, int P, int workers_out_fd, int n_buff, int verbose) {
    int interval_qty = floor((double) N / T);
    if ((N % T) != 0) { interval_qty++; }

    // On maintient un tableau qui contient une liste d'intervalle pour avoir un suivi sur les intervalles encores inexplorées.
    int next_interval = 0, index = 0;
    int interval[interval_qty][2];
    for (int i = 1; i <= N; i += T) {
        interval[index][0] = i;
        interval[index][1] = i + T - 1;
        if (interval[index][1] > N) {
            interval[index][1] = N;
        }
        index++;
    }

    // On ouvre les fifo en mode écriture
    int tubes[P];
    for (int i = 0; i < P; i++) {
        char fifo_name[16], index[5];

        strcpy(fifo_name, "fifo_");
        snprintf(index, 5, "%d", i);
        strcat(fifo_name,  index);

        tubes[i] = open(fifo_name,O_WRONLY);
    }

    // On cré un tableau pour savoir si un worker est disponible ou occupé. (1) = dispo, (0) = occupé
    int available_worker[P];
    int count_worker_available = P;
    for (int i = 0; i < P; i++) {
        available_worker[i] = 1;
    }

    int prime_numbers[N / 2]; // Ce tableau est destiné à recevoir la liste des nombres premiers
    int next_prime_number_array_index = 0;
    for (int i = 0; i < N/2; i++) {
        prime_numbers[i] = 0;
    }

    for (int i = 0; i < interval_qty; ++i) {
        if (verbose) printf("interval %d - [%d - %d]\n", i+1, interval[i][0], interval[i][1]);
    }
    int work_finished = 0, worker_has_finished = 0;
    char buff[n_buff];
    while ( !work_finished ) {
        // Chercher un worker dispo
        int worker_id;
        if (count_worker_available > 0 && next_interval < interval_qty) { // S'il existe au moins un worker de disponible ET qu'il reste au moins un intervalle inexploré
            while ( count_worker_available > 0 && next_interval < interval_qty) {
                worker_id = getNextAvailableWorkerID(available_worker, P);
                if (worker_id == -1) { break; }
                count_worker_available--;
                available_worker[worker_id] = 0;

                // envoyer l'intervalle de travail au worker
                char message[25];
                snprintf(message, 25, "%d %d", interval[next_interval][0], interval[next_interval][1]);
                write(tubes[worker_id], message, strlen(message));
                if (verbose) printf("Assignement de l'intervalle [%d - %d] au worker n°%d\n", interval[next_interval][0], interval[next_interval][1], worker_id);
                next_interval++;
            }
        } else { // On récupère les données transférées par les workers
            if (next_interval == interval_qty && areWorkersAllIdle(available_worker, P)) {
                work_finished = 1;
            } else {
                while( !worker_has_finished ) {
                    // On lis le contenu du pipe et on le place dans buff
                    int n = read(workers_out_fd, buff, n_buff - 1);
                    buff[n] = '\0';
                    
                    if (verbose) printf("=> Master lit %s\n", buff);
					
					// On prépare un tableau de chaine de caractère pour séparer les données du buffer
					char* data[n_buff];
					for (int i = 0; i < n_buff; ++i) {
						data[i] = malloc((n_buff + 1) * sizeof(char));
					}
					int total_data = str_split(buff, ' ', data, n_buff);
					
					if (total_data % 2 != 0) {
					printf("Erreur format de données dans le pipe du master\n");
						exit (EXIT_FAILURE);
					}
					
                    for (int i = 0; i + 1 < total_data; i+=2) {
                        int val1 = atoi(data[i]);
                        int val2 = atoi(data[i + 1]);
                        
                        if (val2 == 0) { // Le worker a finit sont travail
                            if (verbose) printf("=> Le worker n°%d est disponible\n", val1);
                            available_worker[val1] = 1;
                            count_worker_available++;
                            worker_has_finished = 1;
                        } else {
                            if (verbose) printf("=> Le worker n°%d a trouve le nombre premier %d\n", val1, val2);
                            prime_numbers[next_prime_number_array_index] = val2;
                            next_prime_number_array_index++;
                        }
                    }
                }
                worker_has_finished = 0;
            }
        }
    }

    stopWorkersAndWaitForTerminations(tubes, P);
    closeAndRemoveAllFifo(tubes, P);

    int primeNbFound = next_prime_number_array_index;
    qsort( prime_numbers, primeNbFound, sizeof(int), compare );

    printf("Il y a %d nombres premiers entre %d et %d :\n", primeNbFound, 2, N);
    display_numbers(prime_numbers, (N/2));

    return EXIT_SUCCESS;
}
