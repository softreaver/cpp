#include <iostream>

class Class
{
public:

    int fonctionClass(int x)
    {
        return x*2;
    }
};

float fonction(float x)
{
    return x/2.0;
}

int main()
{
    // cr�ation d'un pointeur sur m�thode fonctionClass
    int (Class::*ptr1) (int) = &Class::fonctionClass; // important : le & est obligatoire pour pointer sur une m�thode !

    //Cr�ation d'un pointeur sur la fonction "fonction"
    float (*ptr2) (float) = fonction;

    typedef int (Class::*pointeurMethode) (int);
    pointeurMethode ptr3 = &Class::fonctionClass;

    Class objet;
    std::cout << "Methode(4) = " << (objet.*ptr1)(4) << std::endl; //ne pas oublier d'encadrer objet.*ptr entre parenth�se sinon cela ne fonctionne pas.
    std::cout << "Fonction(4) = " << ptr2(4) << std::endl;
    std::cout << "Methode(4) = " << (objet.*ptr3)(4) << std::endl;
    return 0;
}
