#include <iostream>
#include <vector>
#include "Vehicule.h"
#include "Garage.h"
#include "windows.h"

using namespace std;

int main()
{
    Garage vehicule;

    vehicule.nouvelleVoiture(15000,2);
    vehicule.nouvelleVoiture(18000,5);
    vehicule.nouvelleVoiture(30000,5);

    vehicule.nouvelleMoto(4500,235.0);

    vehicule.nouveauCamion(110000, 26000.0);

    for(int i(0); i < vehicule.nombreDeVehicules(); i++)
    {
        vehicule.afficher(i);
    }

    cout << "il y a " << vehicule.nombreDeVehicules() << " vehicules dans le garage." << endl;
    cout << "Le deuxieme vehicule de la liste a " << vehicule.nombreDeRoues(1) << " roues." << endl;
    vehicule.supprimer();

    return 0;
}
