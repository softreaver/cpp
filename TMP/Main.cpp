#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

string melangerLettres(string mot)
{
    string melange;
    int position(0);

    // Tant que nous n'avons pas extrait toutes les lettres du mot
    while (mot.size() != 0)
    {
        // On choisit un numéro de lettre au hasard dans le mot
        position = rand() % mot.size();
        // On ajoute la lettre dans le mot mélangé
        melange += mot[position];
        // On retire cette lettre du mot mystère pour ne pas la prendre une 2e fois
        mot.erase(position, 1);
    }

    // On renvoie le mot mélangé
    return melange;
}

int main()
{
    char reponseJouer;
    do
    {

        string motMystere, motMelange, motUtilisateur;

        // Initialisation des nombres aléatoires
        srand(time(0));


        // 1 : On recupere un mot dans le document "dico.txt"


        ifstream monFlux("dico.txt");  //Ouverture d'un fichier en lecture

        if(monFlux)
        {
            string ligne;
            // on compte le nombre total de lignes du document
            int compteur2 (0);
               while(getline(monFlux, ligne)) //Tant qu'on n'est pas à la fin, on lit
              {
                 compteur2 +=1;
              }

            monFlux.clear();
            monFlux.seekg(0,ios::beg);

            //on cherche la Nieme ligne du document au hasard

            for(int i(0); i<= rand() % compteur2  ; i++)
            {
                getline(monFlux,motMystere);
            }



        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        }



        // 2 : On récupère le mot avec les lettre mélangées dans motMelange
        motMelange = melangerLettres(motMystere);

        // 3 : On demande à l'utilisateur quel est le mot mystère
        int compteur (0);
        do
        {
            cout << endl << "Quel est ce mot ? " << motMelange << endl;
            cout << "Vous avez encore "<< 5-compteur <<" essais!" << endl;
            cin >> motUtilisateur;

            if (motUtilisateur == motMystere)
            {
                cout << "Bravo !" << endl;
            }
            else
            {
                cout << "Ce n'est pas le mot !" << endl;
            }
            compteur +=1;
        }while (motUtilisateur != motMystere && compteur<5); // On recommence tant qu'il n'a pas trouvé

        cout << " La solution est: " <<motMystere<< endl;
        reponseJouer = 'N';
        cout << endl << "**************" << endl;
        cout << "Voulez-vous faire une autre partie ? Si oui entrez 'o' sinon entrez 'N'" << endl;
        cin >> reponseJouer;

    }while (reponseJouer=='o');


    return 0;
}
