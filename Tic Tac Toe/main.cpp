#include <iostream>
#include <string>
#include "Grille.h"
#include "Joueurs.h"
#include "conio.h"

// Initialisation des variables
bool                finDePartie(false);
bool                nouvellePartie(false);
bool                choix(true);
int                 grilleTX(0), grilleTY(0), rep(0);
std::string         nomJ1("Joueur 1"), nomJ2("Joueur 2");
std::string         reponse;
Grille              *grille(nullptr);
Joueur              *joueur1(nullptr);
Joueur              *joueur2(nullptr);

int main()
{

    enum SYMBOLE        {X = -1, O = 1};
    do
    {
        finDePartie = false;

        //Création de la grille de jeu
        std::cout << "Veuillez entrer la taille X de la grille :" << std::endl;
        std::cin >> reponse;
        grilleTX = Grille::to_integer(reponse);
        std::cout << std::endl << "Veuillez entrer la taille Y :" << std::endl;
        std::cin >> reponse;
        grilleTY = Grille::to_integer(reponse);

        std::cout << std::endl;
        if(grilleTX < 3)
        {
            std::cout << "Erreur : le taille minimum pour x doit etre 3, X = 3" << std::endl;
            grilleTX = 3;
        }
        if(grilleTY<3)
        {
            std::cout << "Erreur : la taille minimum pour y doit etre 3, Y = 3" << std::endl;
            grilleTY = 3;
        }

        std::cout << std::endl;
        std::cout << "Création d'une grille de [" << grilleTX << "]"
                                      << " par [" << grilleTY << "]."
                                      << std::endl;
        grille = new Grille(grilleTX, grilleTY);


        //Choix des noms de joueur
        std::cout << "Nom du joueur 1 : " << std::endl;
        std::cin >> reponse;
        if(reponse.length() < 3)
        {
            std::cout << "ERREUR : Le nom du joueur doit avoir au moins 4 caracteres. Nom du joueur : Joueur1" << std::endl;
        }
        else
        {
            nomJ1 = reponse;
        }

        std::cout << "Nom du joueur 2 : " << std::endl;
        std::cin >> reponse;
        if(reponse.length() < 3)
        {
            std::cout << "ERREUR : Le nom du joueur doit avoir au moins 4 caracteres. Nom du joueur : Joueur2" << std::endl;
        }
        else
        {
            nomJ2 = reponse;
        }

        //Création des deux joueurs :
        joueur1 = new Joueur(nomJ1, &finDePartie, grille, SYMBOLE::X);
        joueur2 = new Joueur(nomJ2, &finDePartie, grille, SYMBOLE::O);

        //La partie:
        do
        {
            joueur1->gestion();         //Le joueur 1 commence toujours la partie
            if(!finDePartie)
            joueur2->gestion();

        }while(!finDePartie);  //Si ce n'est pas la fin de la partie le jeu continue

        delete joueur1;     joueur1 = nullptr;      //On supprime les joueurs et la grille pour en refaire une nouvelle
        delete joueur2;     joueur2 = nullptr;      //ou pour pouvoir quitter sans avoir de fuite de mémoire
        delete grille;      grille  = nullptr;      // puis on fait pointer les pointeur sur rien.

        std::cout << "APPUYEZ SUR UNE TOUCHE POUR CONTINUER..." << std::endl;
        getch();
        system("cls");

        std::cout << "Voulez-vous rejouer une nouvelle partie ? (o/n)" << std::endl;

        choix = true;
        do
        {
            rep = getch();
            switch(rep)
            {
            case 78:
            case 110:
                nouvellePartie = false;
                choix = false;
                break;
            case 79:
            case 111:
                nouvellePartie = true;
                choix = false;
                break;
            }
        }while(choix);

    }while(nouvellePartie); // Si on choisit de refaire une nouvelle partie on recrée un nouveau jeu

    std::cout << "Merci d'avoir joue :)";
    return 0;
}
