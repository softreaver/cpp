#ifndef VEHICULE_H_INCLUDED
#define VEHICULE_H_INCLUDED

class Vehicule
{
    public:
    Vehicule(int prix);           //Construit un v�hicule d'un certain prix
    virtual void affiche() const;
    virtual ~Vehicule();          //Remarquez le 'virtual' ici
    virtual int nbrRoues() const = 0; //On ajoute =  0 pour definir la methode comme �tant une fonction virtuelle pure.
    // Il y a au moins une m�hode virtuelle pure donc la classe est dite abstraite = impossible donc de cr�er un objet de type Vehicule.

    protected:
    int m_prix;
};
// !!NE PAS OUBLIER D'IMPLEMENTER TOUTES LES METHODES VIRTUELLES DEFINIES DANS CE HEADER SINON LA CLASSE FILLE HERITERA AUTOMATIQUEMENT DE LA SPECIFICITE ABSTRAIT

class Voiture: public Vehicule
{
    public:
    Voiture(int prix, int portes);
    //Construit une voiture dont on fournit le prix et le nombre de portes
    virtual void affiche() const;
    virtual ~Voiture();
    virtual int nbrRoues() const;

    private:
    int m_portes;
};

class Moto : public Vehicule
{
    public:
    Moto(int prix, double vitesseMax);
    //Construit une moto d'un prix donn� et ayant une certaine vitesse maximale
    virtual void affiche() const;
    virtual ~Moto();
    virtual int nbrRoues() const;

    private:
    double m_vitesse;
};

class Camion : public Vehicule
{
public:
    Camion(int prix, double chargeMax);
    // construit un camion ayant un prix donn� et une capacit� de transport max
    virtual void affiche() const;
    virtual ~Camion();
    virtual int nbrRoues() const;

private:
    double m_chargeMax;
};

#endif // VEHICULE_H_INCLUDED
