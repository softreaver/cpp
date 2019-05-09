#include "Garage.h"

using namespace std;

Garage::Garage()
{

}

Garage::~Garage()
{
    for(int i(0); i < m_liste.size(); i++)
    {
        delete m_liste[i];
    }
}

void Garage::nouvelleVoiture(int prix, int nombreDePorte)
{
    m_liste.push_back(new Voiture(prix, nombreDePorte));
}

void Garage::nouvelleMoto(int prix, double vitesseMax)
{
    m_liste.push_back(new Moto(prix, vitesseMax));
}

void Garage::nouveauCamion(int prix, double chargeMax)
{
    m_liste.push_back(new Camion(prix, chargeMax));
}

void Garage::supprimer(int index)
{
    delete m_liste[index];
    m_liste[index] = 0;
}

void Garage::supprimer()
{
    for(int i(0); i<m_liste.size(); i++)
    {
        delete m_liste[i];
        m_liste[i] = 0;
    }
}

void Garage::afficher(int index) const
{
    m_liste[index]->affiche();
}

int Garage::nombreDeVehicules() const
{
    return m_liste.size();
}

int Garage::nombreDeRoues(int index) const
{
    return m_liste[index]->nbrRoues();
}
