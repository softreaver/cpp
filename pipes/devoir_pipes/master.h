
/**
 * Contient la logique applicative du master
 * 
 * @param N le nombre jusqu'auquel il faut chercher les nombres premiers. L'intervalle de recherche est [2 - N].
 * @param T l'intervalle de travail. C'est à dire la quantité de nombre que les workers auront à tester pour chaque sous-intervalles
 * @param P le nombre total de worker.
 * @param worker_out_fd le numéro de FD pointant sur le pipe dans lequels tous les workers écrivent leurs résulats
 * @param n_buff la taille maximum des buffers utilisés par le master
 * @param verbose stipule si le programme doit tourner en mode verbeux ou non
 * 
 * @return 0 si la procédure s'est bien terminée sinon 1.
 * 
 * */
int execMaster(int N, int T, int P, int workers_out_fd, int n_buff, int verbose);
