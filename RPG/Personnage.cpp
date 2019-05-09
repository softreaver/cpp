#include "Personnage.h"

using namespace std;

string Personnage::getNom() const
{
    return m_nomPersonnage;
}

Personnage::~Personnage()
{
    delete m_arme;
}

Personnage::Personnage() : m_vie(100), m_arme(0), m_nomPersonnage("Inconnu"), m_cible(0)
{
    m_arme = new Arme(); //Création d'un objet Arme et référencement de son adresse dans le pointeur
}

Personnage::Personnage(string nomPersonnage) : m_vie(100), m_arme(0), m_nomPersonnage(nomPersonnage), m_cible(0)
{
    m_arme = new Arme();
}

Personnage::Personnage(string nomPersonnage, string nomArme, int degatsArme) : m_nomPersonnage(nomPersonnage), m_vie(100), m_arme(0), m_cible(0)
{
    m_arme = new Arme(nomArme, degatsArme); //Appel du constructeur surchargé de la class Arme
}

Personnage::Personnage(Personnage const& personnageCopie):
                            m_vie(personnageCopie.m_vie),
                            m_arme(0),
                            m_cible(personnageCopie.m_cible)
{
    m_arme = new Arme(*(personnageCopie.m_arme)); // il faut utiliser le * car le constructeur de Arme veut referencer un objet
}

void Personnage::recevoirDegats(int nbDegats)
{
    m_vie -= nbDegats;
    // on enlève lenombre de dégats reçus à la vie du personnage

    if(m_vie < 0)//on évite d'avoir une vie négative
    {
        m_vie = 0;//On met la vie à 0 (mort)
    }
}

void Personnage::attaquer()
{
    cout << m_nomPersonnage << " attaque " << m_cible->getNom() << endl;
    m_cible->recevoirDegats(m_arme->getDegats());
    // On inflige à la cible les dégats que cause notre arme
}

void Personnage::boirePotionDeVie(int quantitePotion)
{
    m_vie += quantitePotion;

    if(m_vie > 100)
        m_vie = 100;
}

void Personnage::changerArme(string nomNouvelleArme, int degatsNouvelleArme)
{
    m_arme->changer(nomNouvelleArme, degatsNouvelleArme);
}

bool Personnage::estVivant() const
{
    return m_vie > 0;
}

void Personnage::afficherEtat() const
{
    string typePersonnage;
    switch(m_typePersonnage)
    {
    case MAGICIEN:
        typePersonnage = "Magicien";
        break;
    case GUERRIER:
        typePersonnage = "Guerrier";
        break;
    default:
        typePersonnage = "Inconnu";
    }
    cout << m_nomPersonnage << " est un " << typePersonnage << endl;
    cout << " Il lui reste " << m_vie << " points de vie." << endl;
    cout << m_nomPersonnage << " est equipe de : "; m_arme->afficher();
}

void Personnage::setCible(Personnage *cible)
{
    m_cible = cible;
}
