#ifndef GARAGE_H_INCLUDED
#define GARAGE_H_INCLUDED
#include "Vehicule.h"
#include <vector>

class Garage
{
public:
    Garage();
    ~Garage();
    void nouvelleMoto(int prix, double vitesseMax);
    void nouvelleVoiture(int prix, int nombreDePorte);
    void nouveauCamion(int prix, double chargeMax);
    void supprimer(int index);
    void supprimer();
    void afficher(int index) const;
    int nombreDeVehicules() const;
    int nombreDeRoues(int index) const;

private:
    std::vector<Vehicule*> m_liste;
};

#endif // GARAGE_H_INCLUDED
