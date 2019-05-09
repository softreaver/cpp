#include "Magicien.h"

using namespace std;

Magicien::Magicien() : m_mana(100)
{m_typePersonnage = MAGICIEN;}

Magicien::Magicien(string nomPersonnage):
                                                Personnage(nomPersonnage),
                                                m_mana(100)
{m_typePersonnage = MAGICIEN;}

Magicien::Magicien(string nomPersonnage, string nomArme, int degatsArme):
                                                Personnage(nomPersonnage, nomArme, degatsArme),
                                                m_mana(100)
{m_typePersonnage = MAGICIEN;}

Magicien::~Magicien()
{}

void Magicien::bouleDeFeu()
{
    if(m_mana >= 33)
    {
        cout << m_nomPersonnage << " utilise boule de feu sur " << m_cible->getNom() << "!" << endl;
        m_mana -= 33;
        if(m_mana < 0)
            m_mana = 0;
        this->attaquer();
    }
    else
    {
        cout << "Vous n'avez pas assez de mana!" << endl;
    }

}

void Magicien::soins(Personnage *cible)
{
    if(m_mana >= 40)
    {
        cout << m_nomPersonnage << " a soigne " << cible->getNom() << "." << endl;
        m_mana -= 40;
        if(m_mana < 0)
            m_mana = 0;
        cible->boirePotionDeVie(50);
    }
    else
    {
        cout << "Vous n'avez pas assez de mana!" << endl;
    }
}

void Magicien::utilisation() const
{
    cout << "Commandes du magiciens :" << endl;
    cout << "a = attaquer \nz = boule de feu\ne = sort de soins" << endl;
}

void Magicien::gestion()
{
    static int keyPressed = 0;

    if(keyPressed == 0)
    {
        if(GetKeyState(A) < 0)
        {
            keyPressed = A;
            this->attaquer();
        }
        else if(GetKeyState(Z) < 0)
        {
            keyPressed = Z;
            this->bouleDeFeu();
        }
        else if(GetKeyState(E) < 0)
        {
            keyPressed = E;
            this->soins(this);
        }
    }
    else if(GetKeyState(keyPressed) >= 0)
    {
        keyPressed = 0;
    }
}

