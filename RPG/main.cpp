#include <iostream>
#include "Personnage.h"
#include "Magicien.h"
#include "Guerrier.h"
#include "Arme.h"
#include "windows.h"

using namespace std;

const int ESC = 0x1B;
const int A = 0x41;
const int Z = 0x5A;
const int E = 0x45;

int main()
{
    string choix;

    cout << "Choisissez un perso :" << endl;
    cout << "1 - Magicien" << endl;
    cout << "2 - Guerrier" << endl;

    Personnage *monPerso = NULL;
    Personnage *ennemi = NULL;

    choix1:
    do
    {
        cin >> choix;
    }while(choix.size() < 0 || choix.size() > 1);

    if(choix == "1")
    {
        monPerso = new Magicien("David le mage", "Baton magique", 20);
        ennemi = new Guerrier("Goliath le babare");
    }else if(choix == "2")
    {
        ennemi = new Magicien("David le mage", "Baton magique", 20);
        monPerso = new Guerrier("Goliath le babare");
    }else
    {
        goto choix1;
    }


    monPerso->utilisation();
    monPerso->setCible(ennemi); //&ennemi ne fonctionne pas, ennemi étant déjà un pointeur, si je veux le passer par ref à un autre pointeur je met directement la valeur comprise dans ennemi, pas besoin de & sinon ça fait adresse d'une adresse.

    do
    {
        Sleep(1);

        monPerso->gestion();
        if(!monPerso->estVivant() || !ennemi->estVivant() || GetKeyState(ESC) < 0)
            break;


    }while(true);


    cout << endl << "Fin de partie :" << endl;
    monPerso->afficherEtat();
    ennemi->afficherEtat();

    delete monPerso;
    delete ennemi;
    Sleep(3000);
    return 0;
}
