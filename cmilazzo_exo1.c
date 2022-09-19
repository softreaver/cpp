#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(void)
{
 fork(); printf("fork(1)\n");
 fork(); printf("fork(2)\n");
 fork(); printf("fork(3)\n");
 return(0);
}

/**
 * Explications :
 * 
 * après le premier fork() il y aura 2 processus qui vont printer chacun "fork(1)"
 * Les deux processus à leur tour vont créer 2 processus chacun donc en tout il existe 4 processus chacun d'eux
 * va printer "forker(2)". Puis ensuite les 4 processus vont créer chacun 1 nouveau processus donc en tout il y aura 8 processus
 * qui vont printer chacun "fork(3)"
 * 
 * donc ça fait 2 print(1) + 4 print(2) + 8 print(3) => 14 prints en tout pour 8 processus 
 * 
 * */
