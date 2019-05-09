#include "Joueurs.h"

Joueur::Joueur() :
    m_nom("Inconnu")
{std::cerr << "Le joueur a mal ete initialise !";}

Joueur::Joueur(std::string nom, bool *fin, Grille *grille, int s) :
    m_nom(nom),
    m_fin(fin),
    m_grille(grille),
    m_symbole(s)
{}

Joueur::~Joueur() {}

void Joueur::gestion()
{
        //Key mapping
    const int ARROWKEYS = 224;
    const int LEFT      = 75;
    const int RIGHT     = 77;
    const int UP        = 72;
    const int DOWN      = 80;
    const int ESC       = 27;
    const int SPACE     = 32;
    int c(0), retour(0);
    bool finDuTour(false);
    *m_fin = false;

    m_grille->display(m_nom, m_symbole);

    do
    {
        do
        {
        if(finDuTour) break;
        c = getch();

        if(c == ESC)     //Abandon
        {
            finDuTour = true;
            *m_fin = true;
            system("cls");
            std::cout << m_nom << " a abandonne la partie!" << std::endl;
            break;
        }
        if(c == SPACE)
        {
            retour = m_grille->setSymbole(m_symbole);

            switch(retour)
            {
            case RETOUR::GAGNE:
                m_grille->setResultat(RETOUR::GAGNE);
                m_grille->display(m_nom, m_symbole);
                finDuTour = true;
                *m_fin = true;
                break;

            case RETOUR::IMPOSSIBLE:
                continue;
                break;

            case RETOUR::MATCHNULL:
                m_grille->setResultat(RETOUR::MATCHNULL);
                m_grille->display(m_nom, m_symbole);
                finDuTour = true;
                *m_fin = true;
                break;

            case RETOUR::OK:
                m_grille->display(m_nom, m_symbole);
                finDuTour = true;
                continue;
                break;
            }
        }

        }while(c != ARROWKEYS);

        if(finDuTour) break;
        c = getch();

        switch(c)
        {
        case LEFT:
            m_grille->left();
            break;

        case RIGHT:
            m_grille->right();
            break;

        case UP:
            m_grille->up();
            break;

        case DOWN:
            m_grille->down();
            break;
        }
        m_grille->display(m_nom, m_symbole);
    }while(true);
}
