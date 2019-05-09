#ifndef JOUEURS_H_INCLUDED
#define JOUEURS_H_INCLUDED
#include <string>
#include <iostream>
#include "Grille.h"
#include "windows.h"
#include "conio.h"      //getch()

class Joueur
{
public:
    Joueur();
    Joueur(std::string nom, bool *fin, Grille *grille, int s);
    ~Joueur();

    void gestion();                 //Permet de gérer les touches

private:
    enum RETOUR
    {OK, GAGNE, MATCHNULL, IMPOSSIBLE};
    std::string m_nom;
    bool       *m_fin;
    Grille     *m_grille;
    int         m_symbole;
    enum SYMBOLE        {X = -1, O = 1};
};

#endif // JOUEURS_H_INCLUDED
