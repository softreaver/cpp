#include "Grille.h"
#include <string>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>

Grille::Grille()
{
    m_TX        = 3;
    m_TY        = 3;
    m_cursorX   = 0;
    m_cursorY   = 0;
    m_grille    = new int*[3];
    for(int i(0); i < 3; i++) { m_grille[i] = new int[3]; }
    m_objectif  = 3;
    this->fillIn();
}

Grille::Grille(int TX, int TY)
{
    m_TX        = TX;
    m_TY        = TY;
    m_cursorX   = 0;
    m_cursorY   = 0;
    m_grille    = new int*[m_TX];
    for(int i(0); i < m_TX; i++) { m_grille[i] = new int[m_TY]; }
    if(TX + TY > 7)
        m_objectif = 4;
    else
        m_objectif = 3;
    this->fillIn();
}

Grille::~Grille()
{
    for(int i(0); i < m_TX; i++) { delete m_grille[i]; }
    delete[] *m_grille;
}

void Grille::fillIn()
{
    for(int ix(0); ix < m_TX; ix++)
    {
        for(int iy(0); iy < m_TY; iy++)
        {
            m_grille[ix][iy] = 0;
        }
    }
}

int Grille::getObjectif() const
{
    return m_objectif;
}

int Grille::setSymbole(int s)
{
    if(m_grille[m_cursorX][m_cursorY] == 0)
    {
        m_grille[m_cursorX][m_cursorY] = s;

        int ix, iy;
        int compteur = 0;

        iy = m_cursorY;

        for(ix = 0; ix < m_TX; ix++)
        {
            if(m_grille[ix][iy] == s)
                compteur++;
            else
                compteur = 0;
            if(compteur >= m_objectif) return RETOUR::GAGNE;
        }

        ix = m_cursorX;

        for(iy = 0; iy < m_TY; iy++)
        {
            if(m_grille[ix][iy] == s)
                compteur++;
            else
                compteur = 0;
            if(compteur >= m_objectif) return RETOUR::GAGNE;
        }


        ix          = m_cursorX;
        iy          = m_cursorY;
        compteur    = 0;
        if(ix <= iy)
        {
            iy -= ix;
            ix = 0;
        }
        else
        {
            ix -= iy;
            iy = 0;
        }
        while(ix < m_TX && iy < m_TY)
        {
            if(m_grille[ix][iy] == s)
                compteur++;
            else
                compteur = 0;
            if(compteur >= m_objectif) return RETOUR::GAGNE;
            ix++;
            iy++;
        }


        ix          = m_cursorX;
        iy          = m_cursorY;
        compteur    = 0;
        if(m_TX-ix-1 <= iy)
        {
            iy -= m_TX-ix-1;
            ix = m_TX-1;
        }
        else
        {
            ix += iy;
            iy = 0;
        }
        while(ix > 0 && iy < m_TY)
        {
            if(m_grille[ix][iy] == s)
                compteur++;
            else
                compteur = 0;
            if(compteur >= m_objectif) return RETOUR::GAGNE;
            ix--;
            iy++;
        }

        if(this->isFull()) return RETOUR::MATCHNULL;

        return RETOUR::OK;
    }
    return RETOUR::IMPOSSIBLE;
}

void Grille::display(std::string nom, int s) const
{
    int mid(m_TY/2);
    system("cls");
    std::cout << "+";
    for(int i(0); i < m_TX; i++)
    {
        std::cout << "---+";
    }

    std::cout << std::endl;

    for(int iy(0); iy < m_TY; iy++)
    {
        std::cout << "|";
        for(int ix(0); ix < m_TX; ix++)
        {
            switch(m_grille[ix][iy])
            {
            case (-1):
                (ix == m_cursorX && iy == m_cursorY)? std::cout << "[" : std::cout << " ";
                std::cout << "X";
                (ix == m_cursorX && iy == m_cursorY)? std::cout << "]" : std::cout << " ";
                std::cout << "|";
                break;
            case 1:
                (ix == m_cursorX && iy == m_cursorY)? std::cout << "[" : std::cout << " ";
                std::cout << "O";
                (ix == m_cursorX && iy == m_cursorY)? std::cout << "]" : std::cout << " ";
                std::cout << "|";
                break;
            default:
                (ix == m_cursorX && iy == m_cursorY)? std::cout << "[" : std::cout << " ";
                std::cout << " ";
                (ix == m_cursorX && iy == m_cursorY)? std::cout << "]" : std::cout << " ";
                std::cout << "|";
                break;
            }
        }

        if(iy == mid)
        {
            std::cout << "   <== " << nom;
            switch(m_resultat)
            {
                case RETOUR::GAGNE : std::cout << " gagne la partie !"; break;
                case RETOUR::MATCHNULL : std::cout << ". Matche null, fin de partie."; break;
                default: break;
            }
        }
        if(iy == mid+1) std::cout << "Objectif : aligner " << m_objectif << " symboles.";
        std::cout << std::endl;

        std::cout << "+";
        for(int i(0); i < m_TX; i++)
        {
            std::cout << "---+";
        }
        std::cout << std::endl;
    }
    std::cout << "FLECHES : se deplacer | ECHAP : quitter | ESPACE : dessiner un ";
    (s == SYMBOLE::O)? std::cout << "O" : std::cout << "X";
    std::cout << std::endl;
}

int Grille::to_integer(std::string x){
    int ret = 0;
    float i2 = pow(10, x.length());

    for(int i = 0; i < x.length(); i++){
        switch(x[i]){
            case '1':
                ret += i2 * 1;
            break;
            case '2':
                ret += i2 * 2;
            break;
            case '3':
                ret += i2 * 3;
            break;
            case '4':
                ret += i2 * 4;
            break;
            case '5':
                ret += i2 * 5;
            break;
            case '6':
                ret += i2 * 6;
            break;
            case '7':
                ret += i2 * 7;
            break;
            case '8':
                ret += i2 * 8;
            break;
            case '9':
                ret += i2 * 9;
            break;
            case '0':
            break;
            default:
                return 0;
        }
        i2 /= 10;
    }
    return ret/10;
}

void Grille::left()
{
    if(m_cursorX > 0) m_cursorX--;
}

void Grille::right()
{
    if(m_cursorX < m_TX-1) m_cursorX++;
}

void Grille::up()
{
    if(m_cursorY > 0) m_cursorY--;
}

void Grille::down()
{
    if(m_cursorY < m_TY-1) m_cursorY++;
}

void Grille::setResultat(int res)
{
    m_resultat = res;
}

bool Grille::isFull() const
{
    for(int ix(0); ix < m_TX; ix++)
    {
        for(int iy(0); iy < m_TY; iy++)
        {
            if(m_grille[ix][iy] == 0) return false;
        }
    }
    return true;
}
