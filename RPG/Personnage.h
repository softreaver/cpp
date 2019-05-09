#ifndef DEF_PERSONNAGE
#define DEF_PERSONNAGE
#include <string>
#include "Arme.h"

class Personnage
{
public:

    virtual ~Personnage();
    Personnage();
    Personnage(std::string nomPersonnage);
    Personnage(std::string nomPersonnage, std::string nomArme, int degatsArme);
    Personnage(Personnage const& personnageCopie);

    void recevoirDegats(int nbDegats);
    void attaquer();
    void boirePotionDeVie(int quantitePotion);
    void changerArme(std::string nomNouvelleArme, int degatsNouvelleArme);
    bool estVivant() const; //définition d'une méthode constante, on assure qu'elle ne modifie aucun attribus de la class à laquelle est appartient. en plus ça offre un code de meilleur qualité que d'utilise un maximum les variables constantes qui peuvent l'être
    void afficherEtat() const;
    std::string getNom() const;
    void setCible(Personnage *cible); // on demande un type Personnage et cela englobe tous les type de perso (magicien, guerrier, etc....)
    virtual void utilisation() const = 0;
    virtual void gestion() = 0;

    static const int ESC = 0x1B;
    static const int A = 0x41;
    static const int Z = 0x5A;
    static const int E = 0x45;

protected:

    enum type
    {
        MAGICIEN,
        GUERRIER
    };
    type m_typePersonnage;
    int m_vie;
    std::string m_nomPersonnage;
    Arme *m_arme;//Notre personnage possède une Arme
    Personnage *m_cible;
};

#endif // DEF_PERSONNAGE
