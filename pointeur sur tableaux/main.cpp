#include <iostream>

int main()
{
    int TX = 5;
    int TY = 4;
    int **grille(0);                                         //Pointeur de pointeur

    grille = new int*[TX];                                   // impossible de faire new Z[X][Y];
    for(int i=0; i < TX; i++) { grille[i] = new int[TY]; }   //donc on utilise un pointeur de pointeur

    grille[2][2] = 69;

    std::cout << grille[2][2] << std::endl;                  //L'utilisation du tableau de pointeur est normale

    return 0;
}
