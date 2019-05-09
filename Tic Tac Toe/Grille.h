#ifndef GRILLE_H_INCLUDED
#define GRILLE_H_INCLUDED

#include <string>

class Grille
{
    public:
        Grille();                                                         //Création d'une grille par defaut 3x3
        Grille(int TX, int TY);                                           //Création d'une grille personnalisée
        ~Grille();                                                        //Destruction de la grille
        int getObjectif() const;                                          //Objectif = nombre de symbole à aligner pour gagner
        void display(std::string nom, int s) const;                       //Met à jour la grille
        int setSymbole(int s);                                            //Permet d'ajouter un X ou un O à la grille et renvois un état :
                                                                          //(0 = rien de spéciale, 1 = joueur gagne, 2 = grille pleine match null | 3 = pas d'actio possible).
        void setResultat(int res);                                        //permet de definir le resultat de la partie.
        bool isFull() const;                                              //Vérifie si la grille est pleine.
        void fillIn();                                                    //Remplissage de la grille avec des 0
        void left();
        void right();
        void up();
        void down();

        static int to_integer(std::string x);                             //Convertion d'une chaine de caractère en nombre entier


    private:
        enum RETOUR
        {OK, GAGNE, MATCHNULL, IMPOSSIBLE};

        int     m_resultat;
        int     m_TX;
        int     m_TY;
        int   **m_grille;
        int     m_objectif;
        int     m_cursorX;
        int     m_cursorY;
        enum SYMBOLE        {X = -1, O = 1};
};


#endif // GRILLE_H_INCLUDED
