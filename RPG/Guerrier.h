#ifndef GUERRIER_H_INCLUDED
#define GUERRIER_H_INCLUDED
#include "Personnage.h"
#include "Magicien.h"
#include "Arme.h"
#include <string>
#include <iostream>
#include "windows.h"

class Guerrier : public Personnage
{

public:

    virtual ~Guerrier();
    Guerrier();
    Guerrier(std::string nomPersonnage);
    Guerrier(std::string nomPersonnage, std::string nomArme, int degatsArme);
    void attaqueMassive();

    virtual void utilisation()const;
    virtual void gestion();

protected:

    int m_adrenaline;
};

#endif // GUERRIER_H_INCLUDED
