#include <iostream>
#include "Vehicule.h"

using namespace std;

Vehicule::Vehicule(int prix)
    :m_prix(prix)
{}

void Vehicule::affiche() const
//J'en profite pour modifier un peu les fonctions d'affichage
{
    cout << "Ceci est un vehicule coutant " << m_prix << " euros." << endl;
}

Vehicule::~Vehicule() //Même si le destructeur ne fait rien, on doit le mettre ! un destructeur n'est jamais virtuel pure
{cout << "Destructeur vehicule" << endl;}

Voiture::Voiture(int prix, int portes)
    :Vehicule(prix), m_portes(portes)
{}

void Voiture::affiche() const
{
    cout << "Ceci est une voiture avec " << m_portes << " portes et coutant " << m_prix << " euros." << endl;
}

Voiture::~Voiture()
{}

int Voiture::nbrRoues() const
{
    return 4;
}

Moto::Moto(int prix, double vitesseMax)
    :Vehicule(prix), m_vitesse(vitesseMax)
{}

void Moto::affiche() const
{
    cout << "Ceci est une moto allant a " << m_vitesse << " km/h et coutant " << m_prix << " euros." << endl;
}

Moto::~Moto()
{}

int Moto::nbrRoues() const
{
    return 2;
}

Camion::Camion(int prix, double charge):
                Vehicule(prix),
                m_chargeMax(charge)
{}

void Camion::affiche() const
{
    cout << "Ceci est un camion pouvant tranporter jusqu'à " << m_chargeMax << " KG de charge et coutant " << m_prix << " euros." << endl;
}

int Camion::nbrRoues() const
{
    return 4;
}

Camion::~Camion()
{cout << "Destructeur camion" << endl;}

