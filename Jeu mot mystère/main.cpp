#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cctype>

using namespace std;

/** \brief Permet de mélanger les lettres d'un mot
 *
 * \param <string> Le mot à mélanger
 * \return <bool> True si chargement réussi, sinon false
 *
 */
string melangerLettres(string a);


/** \brief Permet de charger un mot au hasard dans un fichier dictionnaire
 *
 * \param <string> nom du fichier.
 * \return <string> le mot pioché au hasard
 *
 */
bool chargerLeMot(string a);

class lower
{
public:
    char operator()(char c)
    {
        return tolower(c);
    }
};


vector<string> dictionnaire;

int main()
{
    string const dico("dico.txt");
    string motMystere(""), motMelange(""), reponse("");
    bool recommencer, charge;
    int essais, position;
    string choix;
    char rep;

    do
    {
        essais = 0;
        //1 : Choix du mot mystère

        choix1:
        do
        {
            cout << endl << "Jouer seul ? (o/n)" << endl;
            cin >> choix;
        }while(choix.size() < 1 || choix.size() > 1);
        rep = choix[0];

        switch(rep)
        {
        case 'o':
        case 'O':
            if(!charge)
                charge = chargerLeMot(dico);
            if(!charge)
                goto erreur;

            srand(time(0));
            position = rand() % dictionnaire.size();
            position++;
            motMystere = dictionnaire[position];
            reponse = "";
            break;
        case 'n':
        case 'N':
            cout << "Joueur 1, saisissez un mot :"<<endl;
            cin >> motMystere;
            reponse = "";
            for(int i = 0; i < 30; i++)
            {
                cout << endl;
            }
            break;
        default:
            goto choix1;
        }

        //2 : on mélange les lettres du mot
        transform(motMystere.begin(), motMystere.end(), motMystere.begin(), lower()); //On met toutes les lettres en minuscule
        motMelange = melangerLettres(motMystere);

        //3 : On demande à l'utilisateur de retrouver le mot mystère
        cout << "Quel est ce mot ? (" << motMelange << ")" << endl;

        do
        {
            cin >> reponse;
            transform(reponse.begin(), reponse.end(), reponse.begin(), lower());
            if(reponse != motMystere)
            {
                cout << "Ce n'est pas le mot !" << endl;
                essais++;
                if(essais >= 5)
                    break;
                cout << "Il vous reste " << 5-essais << " essai(s)" << endl;
            }
            else
            {
                cout << "Bravo!" << endl;
            }
        }while(reponse != motMystere);

        if(essais >= 5)
            cout << "Perdu ! Le mot mystere etait : " << motMystere << endl;

choix2:
        do
        {
            cout << endl << "Voulez-vous rejouer une partie ? (o/n)" << endl;
            cin >> choix;
        }while(choix.size() < 1 || choix.size() > 1);

        rep = choix[0];
        switch(rep) // les switch ne prennent que des integer ou char(ASCII)
        {
        case 'o':
        case 'O':
            recommencer = true;
            break;
        case 'n':
        case 'N':
            recommencer = false;
            break;
        default:
            goto choix2;
        }

    }while(recommencer);

    cout << "Fin de partie, merci d'avoir joue." << endl;

    return 0;

erreur:
    cout << "Erreur de chargement du fichier dictionnaire, l'execution du programme s'est arrêté." << endl;
    return 1;
}

string melangerLettres(string a)
{
    srand(time(0));
    int curseur;
    string ret("");

    while(a.size() > 0)
    {
        curseur = rand() % a.size();
        ret += a[curseur];
        a.erase(curseur, 1);
    }
    return ret;
}

bool chargerLeMot(string a)
{
    ifstream file(a.c_str());
    string ret;
    istream_iterator<string> it(file);
    istream_iterator<string> fin;
    back_insert_iterator<vector<string> > it2(dictionnaire);

    if(file)
    {
        cout << "Chargement en cours ..." << endl;
        copy(it, fin, it2);

        return true;
    }
    else
    {
        return false;
    }
}

