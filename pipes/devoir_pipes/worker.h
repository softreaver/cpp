/**
 * Contient la logique applicative d'un worker.
 * 
 * @param index_fifo le numéro du fifo associé à ce worker
 * @param master_in_df le numéro du FD permettan d'écrire dans le pipe vers le master
 * @param n_workers_buff la taille des buffers utilisés par les worker
 * @param verbose stipule si le programme doit être verbeux ou non
 * */
int execWorker(int index_fifo, int master_in_fd, int n_workers_buff, int verbose);
