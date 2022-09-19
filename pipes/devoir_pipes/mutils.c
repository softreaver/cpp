#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

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

int str_split(const char* str, char delimiter, char* strings[], int max_array_size) {
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
