#ifndef MAGICIEN_H_INCLUDED
#define MAGICIEN_H_INCLUDED
#include "Personnage.h"
#include "Guerrier.h"
#include "Arme.h"
#include <string>
#include <iostream>
#include "windows.h"


class Magicien : public Personnage
{

public:

    virtual ~Magicien();
    Magicien();
    Magicien(std::string nomPersonnage);
    Magicien(std::string nomPersonnage, std::string nomArme, int degatsArme);
    void bouleDeFeu();
    void soins(Personnage *cible);

    virtual void utilisation() const;
    virtual void gestion();

protected:

    int m_mana;
};


#endif // MAGICIEN_H_INCLUDED
