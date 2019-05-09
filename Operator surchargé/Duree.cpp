#include "Duree.h"

using namespace std;

    Duree::Duree(int heure, int minute, int seconde):
        m_heure(heure),
        m_minute(minute),
        m_seconde(seconde){}

    bool Duree::estEgal(Duree const& b) const
    {
        return(m_heure == b.m_heure && m_minute == b.m_minute && m_seconde == b.m_seconde);
    }

    bool Duree::estPlusPetit(Duree const& b) const
    {
        if(m_heure < b.m_heure)
        {
            return true;
        }
        else if(m_heure > b.m_heure)
        {
            return false;
        }
        else if(m_minute < b.m_minute)
        {
            return true;
        }
        else if(m_minute > b.m_minute)
        {
            return false;
        }
        else if(m_seconde < b.m_seconde)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

     void Duree::afficherDuree()
    {
        cout << m_heure << ":" << m_minute << ":" << m_seconde << endl;
    }

    void Duree::afficher(ostream &flux) const
    {
        flux << m_heure << "h" << m_minute << "m" << m_seconde << "s" << endl; // le endl est pris en compte ici aussi
    }

    void Duree::operator+=(Duree const& b)
    {

        int temp;
        m_seconde += b.m_seconde;
        temp = m_seconde - 60;
        if(temp >= 0)
        {
            m_seconde = temp;
            m_minute++;
        }
        m_minute += b.m_minute;
        temp = m_minute - 60;
        if(temp >= 0)
        {
            m_minute = temp;
            m_heure++;
        }
        m_heure += b.m_heure;
        temp = m_heure - 24;
        if(temp >= 0)
            m_heure = temp;

    }
