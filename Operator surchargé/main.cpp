#include <iostream>
#include "Duree.h"

using namespace std;


    bool operator==(Duree const& a, Duree const& b)
    {
        return a.estEgal(b);
    }

    bool operator!=(Duree const& a, Duree const& b)
    {
        return !(a == b); // (a == b) réutilise l'operator== juste au dessus
    }

    bool operator<(Duree const& a, Duree const& b)
    {
        return a.estPlusPetit(b);
    }

    void doubler(int &a)
    {
        a *= 2;
    }

    Duree operator+(Duree const& a, Duree const& b)
    {
        Duree copie(a);
        copie += b;
        return copie;
    }

    ostream& operator<<(ostream &flux, Duree const& duree)
    {
        duree.afficher(flux);
        return flux;
    }

int main()
{

    Duree duree1(3, 33), duree2(3,33,2), duree3(1,2,9);

    if(duree1 < duree2)
        cout << "les durees sont différentes."<<endl;
    else
        cout << "Les durees sont egales."<<endl;


    duree1 = duree1 + duree2 + duree3;

    cout << duree1 << endl;

    int var(3);
    doubler(var);
    cout << var << endl;

    return 0;
}
