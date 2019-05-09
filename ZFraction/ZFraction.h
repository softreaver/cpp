#ifndef ZFRACTION_H_INCLUDED
#define ZFRACTION_H_INCLUDED
#include <iostream>

class ZFraction
{
public:

    ZFraction(int numerateur = 0, int denominateur = 1);
    ZFraction operator+(ZFraction const& rhs) const;
    ZFraction operator*(ZFraction const& rhs) const;
    ZFraction operator-(ZFraction const& rhs) const;
    ZFraction operator/(ZFraction const& rhs) const;
    ZFraction& operator+=(ZFraction &rhs); // pour les surcharge d'opérateur raccourci, toujours utiliser un retour de donner par reference combiné avec un return *this;
    ZFraction& operator*=(ZFraction &rhs);
    ZFraction& operator-=(ZFraction &rhs);
    ZFraction& operator/=(ZFraction &rhs);
    void operator-();
    bool operator==(ZFraction const& rhs) const;
    bool operator>(ZFraction const& rhs) const;
    void afficher(std::ostream &flux) const; // Fonction constante indique qu'elle ne modifie en rien l'objet de la class ZFraction
    int numerateur() const;
    int denominateur() const;
    double nombreReel() const;
    void simplifier();


protected:


    int m_numerateur;
    int m_denominateur;
};

std::ostream& operator<<(std::ostream &flux, ZFraction const& fraction);
int pgcd(int a, int b); //fonction static créée juste pour le test

#endif // ZFRACTION_H_INCLUDED
