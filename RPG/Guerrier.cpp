#include "Guerrier.h"
#include <iostream>

using namespace std;

Guerrier::Guerrier():m_adrenaline(0)
{m_typePersonnage = GUERRIER;}

Guerrier::Guerrier(string nomPersonnage): Personnage(nomPersonnage),
                                        m_adrenaline(0)
{m_typePersonnage = GUERRIER;}

Guerrier::Guerrier(string nomPersonnage, string nomArme, int degatsArme):Personnage(nomPersonnage, nomArme, degatsArme),
                                                                        m_adrenaline(0)
{m_typePersonnage = GUERRIER;}

Guerrier::~Guerrier()
{}

void Guerrier::attaqueMassive()
{
    m_cible->recevoirDegats(m_arme->getDegats()+m_adrenaline);
    m_adrenaline = 0;
    cout << m_nomPersonnage << " effectue une attaque massive sur " << m_cible->getNom() << endl;
}

void Guerrier::utilisation() const
{

}

void Guerrier::gestion()
{

}
