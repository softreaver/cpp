#ifndef DUREE_H_INCLUDED
#define DUREE_H_INCLUDED
#include <iostream>

class Duree
{
public:

    Duree(int heure = 0, int minute = 0, int seconde = 0);
    bool estEgal(Duree const& b) const;
    bool estPlusPetit(Duree const& b) const;

    void afficherDuree();
    void afficher(std::ostream &flux) const;
    void operator+=(Duree const& b);

private:

    int m_heure;
    int m_minute;
    int m_seconde;
};

#endif // DUREE_H_INCLUDED
