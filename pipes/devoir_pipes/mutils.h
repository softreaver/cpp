
// Retourne l'ID du premier worker disponible, sinon retourne -1
int getNextAvailableWorkerID(int workers[], int n);

// Ordonne à tous les workers de se terminer puis attend leur fin
void stopWorkersAndWaitForTerminations(int workers[], int n);

void closeAndRemoveAllFifo(int tubes[], int fifoQty);

// Retourne 1 si tous les workers sont oisifs, sinon 0.
int areWorkersAllIdle(int workers[], int n);

// Utilisé pour trier le tableau des nombre premiers
int compare( const void* a, const void* b);

/**
 * Permet de découper la chaine de caractères str en fonction du delimiter puis valorise le tableau de chaine de caractère strings avec chaque sous-chaines.
 * 
 * @param str la chaine de caractère à découper
 * @param delimiter le caractère etant identifié comme le délimiteur
 * @param strings le tableau de chaine de caractère qui va contenir toutes les sous chaines
 * @param max_array_size la taille max du tableau de chaine de caractères. Le tableau aura de dimensions ; max_array_size x max_array_size.
 * 
 * @return le nombre de sous-chaînes extraites de la chaîne str.
 * 
 * */
int str_split(const char* str, char delimiter, char* strings[], int max_array_size);

// Affiche tous les nombres contenus dans le tableau
void display_numbers(int* prime_numbers, int n);

// Renvoie 1 si le nombre passé en paramètre est premier, 0 sinon.
int is_prime(int num);
