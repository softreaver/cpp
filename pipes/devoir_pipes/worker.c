#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "mutils.h"

int execWorker(int index_fifo, int master_in_fd, int n_workers_buff, int verbose) {
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
