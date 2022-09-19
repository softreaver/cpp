#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <wait.h>

#define MAX_INTERVAL    50  // Taille maximal d'un intervale de travail

int is_prime(int num);
int ask_for_number();
int execFils(int index_fifo, int master_in_fd);
int execPere(int N, int T, int P, int workers_out_fd);
int getNextAvailableWorkerID(int workers[], int n);
void stopWorkersAndWaitForTerminations(int workers[], int n);
void closeAndRemoveAllFifo(int tubes[], int fifoQty);
int areWorkersAllIdle(int workers[], int n);
int compare( const void* a, const void* b);
int str_split(char* str, char delimiter, char* strings[], int max_array_size);
void display_numbers(int* prime_numbers, int n);

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
        exit(execFils(index_fifo, fds_master[1]));
    default:
        break;
    }
    close (fds_master[1]); // Le père ne fait que lire dans ce pipe
    return execPere(N, T, n_proc, fds_master[0]);
}

// Renvoie 1 si le nombre passé en paramètre est premier, 0 sinon.
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num % 2 == 0 && num > 2) return 0;
    for(int i = 3; i <= floor(sqrt(num)); i+= 2) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

// Récupère le nombre entré sur l'entrée standard et le retourne.
int ask_for_number() {
    int n;
    scanf("%d", &n);
    fflush(stdin);
    printf("\n");

    return n;
}

int execFils(int index_fifo, int master_in_fd) {
    char fifo_name[16], index[5];
    int n, tub;

    strcpy(fifo_name, "fifo_");
    snprintf(index, 5, "%d", index_fifo);
    strcat(fifo_name,  index);

    tub = open(fifo_name,O_RDONLY);
    
    while (1) {
    	char buff[n_workers_buff];

		// On lis le contenu du pipe et on le place dans buff
		n = read(tub, buff, n_workers_buff - 1);
		buff[n] = '\0';
		
		// On prépare un tableau de chaine de caractère pour séparer les données du buffer
		char* data[n_workers_buff];
		for (int i = 0; i < n_workers_buff; ++i) {
			data[i] = malloc((n_workers_buff + 1) * sizeof(char));
		}
		int total_data = str_split(buff, ' ', data, n_workers_buff);
		
		if (total_data < 2) {
            printf("%d\n", total_data);
            printf("Erreur format de données dans le pipe du worker n°%d\n", index_fifo);
			exit(EXIT_FAILURE);
		}
		
		int from = atoi(data[0]);
		int to = atoi(data[1]);

        // Si le master envoi 0 0 alors le worker doit se stopper
        if (from == 0 && to == 0) { break; }
		
		for (int i = from; i <= to; ++i) {
			if (is_prime(i)) {
				char message[n_workers_buff];
                snprintf(message, n_workers_buff, "%d %d ", index_fifo, i);
                
                if (verbose) printf("=> worker n°%d ecrit %s\n", index_fifo, message);
				
				write(master_in_fd, message, strlen(message));
			}
		}

        // Fin de travail, il faut prévenir le master
        char message[n_workers_buff];
        snprintf(message, n_workers_buff, "%d %d ", index_fifo, 0);
        write(master_in_fd, message, strlen(message));
    }
 
    close(tub);
    return EXIT_SUCCESS;
}

int execPere(int N, int T, int P, int workers_out_fd) {
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

// Retourne l'ID du premier worker disponible, sinon retourne -1
int getNextAvailableWorkerID(int workers[], int n) {
    int worker_id = -1;
    for (int i = 0; i < n; i++) {
        if (workers[i]) {
            worker_id = i;
            break;
        }
    }
    return worker_id;
}

// Ordonne à tous les workers de se terminer et on attend leur fin
void stopWorkersAndWaitForTerminations(int tubes[], int qty) {
    for (int i = 0; i < qty; i++) {
        write(tubes[i], "0 0", 4);
    }
    for (int i = 0; i < qty; ++i) {
        wait(NULL);
    }
}

void closeAndRemoveAllFifo(int tubes[], int fifoQty) {
    for (int i = 0; i < fifoQty; i++) {
        char fifo_name[16], index[5];

        strcpy(fifo_name, "fifo_");
        snprintf(index, 5, "%d", i);
        strcat(fifo_name,  index);

        close(tubes[i]);
        unlink(fifo_name);
    }
}

// Retourne 1 si tous les workers sont oisifs, sinon 0.
int areWorkersAllIdle(int workers[], int n) {
	int allIdle = 1;
	for (int i = 0; i < n; ++i) {
		if ( !workers[i] ) {		
			allIdle = 0;
			break;
		}
	}
	return allIdle;
}

int compare( const void* a, const void* b) {
   int int_a = * ( (int*) a );
   int int_b = * ( (int*) b );

   return (int_a > int_b) - (int_a < int_b);
}

void display_numbers(int* prime_numbers, int n) {
    printf("\n[");
    for (int i = 0; i < n; ++i) {
        if (prime_numbers[i] > 0) {
            if (i > 0) {
                printf(", %d", prime_numbers[i] );
            } else {
                printf("%d", prime_numbers[i] );
            }
        }
    }
    printf("]\n");
}

int str_split(char* str, char delimiter, char* strings[], int max_array_size) {
    int index = 0, group_index = 0, t_index = 0, total_data = 0;
    char letter;
    while((letter = str[index]) && group_index < max_array_size) {
        if (letter == delimiter) {
            strings[group_index][t_index] = '\0';
            group_index++;
            t_index = 0;
        } else {
            strings[group_index][t_index] = letter;
            t_index++;
            total_data = group_index + 1;
        }
        index++;
    }
    return total_data;
}
