#include <iostream>
#include "ZFraction.h"

using namespace std;

int pgcd(int a, int b)
{
    while(b != 0)  //algorithme d'Euclide
    {
        const int t = b;
        b = a%b;
        a=t;
    }
    return a;
}

ZFraction::ZFraction(int numerateur, int denominateur):
                                m_numerateur(numerateur),
                                m_denominateur(denominateur){}

void ZFraction::afficher(ostream &flux) const
{
    if(m_denominateur == 1)
        flux << m_numerateur;
    else
        flux << m_numerateur << "/" << m_denominateur;
}

bool ZFraction::operator>(ZFraction const& rhs) const
{
    return ((m_numerateur/m_denominateur) > (rhs.m_numerateur/rhs.m_denominateur));
}

bool ZFraction::operator==(ZFraction const& rhs) const
{
    return ((m_numerateur/m_denominateur) == (rhs.m_numerateur/rhs.m_denominateur));
}

ostream& operator<<(ostream& flux, ZFraction const& fraction)
{
    fraction.afficher(flux);
    return flux;
}

ZFraction ZFraction::operator+(ZFraction const& rhs) const
{
    ZFraction fraction1(*this); //copie de la fraction a
    ZFraction fraction2(rhs); // copie de la fraction b

    fraction1 += fraction2; // On appel l'operateur surchargé juste en dessous
    return fraction1;
}

ZFraction& ZFraction::operator+=(ZFraction &rhs)
{
    int tmp = m_denominateur;
    m_numerateur *= rhs.m_denominateur;
    m_denominateur *= rhs.m_denominateur;
    rhs.m_numerateur *= tmp;

    m_numerateur += rhs.m_numerateur;
    return *this;
}

ZFraction ZFraction::operator*(ZFraction const& rhs) const
{
    ZFraction fraction1(*this);
    ZFraction fraction2(rhs);

    fraction1 *= fraction2; //on appel l'opérateur surchargé juste en dessous

    return fraction1;
}

ZFraction& ZFraction::operator*=(ZFraction &rhs)
{
    m_numerateur *= rhs.m_numerateur;
    m_denominateur *= rhs.m_denominateur;
    return *this;
}

ZFraction ZFraction::operator/(ZFraction const& rhs) const
{
    ZFraction fraction1(*this);
    ZFraction fraction2(rhs);

    fraction1 /= fraction2;

    return fraction1;
}

ZFraction& ZFraction::operator/=(ZFraction &rhs)
{
    m_numerateur *= rhs.m_denominateur;
    m_denominateur *= rhs.m_numerateur;
    return *this;
}

ZFraction ZFraction::operator-(ZFraction const& rhs) const
{
    ZFraction fraction1(*this);
    ZFraction fraction2(rhs);
    fraction1 -= fraction2;

    return fraction1;
}

ZFraction& ZFraction::operator-=(ZFraction &rhs)
{
    int tmp = m_denominateur;
    m_numerateur *= rhs.m_denominateur;
    m_denominateur *= rhs.m_denominateur;
    rhs.m_numerateur *= tmp;

    m_numerateur -= rhs.m_numerateur;
    return *this;
}

void ZFraction::operator-()
{
    -m_numerateur;
}

void ZFraction::simplifier()
{
    int pgcdValue;
    if(m_numerateur > m_denominateur) // Le premier paramètre de la fonction pgcd() doit être le plus grand
        pgcdValue = pgcd(m_numerateur, m_denominateur);
    else
        pgcdValue = pgcd(m_denominateur, m_numerateur);

    m_numerateur /= pgcdValue;
    m_denominateur /= pgcdValue;

    if(m_numerateur < 0 && m_denominateur < 0)
    {
        m_numerateur = -m_numerateur;
        m_denominateur = -m_denominateur;
    }
    else if(m_denominateur < 0)
    {
        m_numerateur = -m_numerateur;
        m_denominateur = -m_denominateur;
    }
}

int ZFraction::numerateur() const
{
    return m_numerateur;
}

int ZFraction::denominateur() const
{
    return m_denominateur;
}

double ZFraction::nombreReel() const
{
    return m_numerateur/m_denominateur;
}

