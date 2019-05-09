/*
Pour réussir pleinement cet exercice, vous devrez :

compléter correctement le foncteur ;
appeler correctement le foncteur ;
utiliser au maximum les algorithmes et conteneurs de la STL ;
ne crypter que les lettres majuscules ;

Resultat voulu: K, G, Y, C, V, Y, C, F, Y,  , N, F, S,  , W, Y,  , T, A, A, L,  , L, +, +,  , P, ', A, L, S,  , !, !,

*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>

using namespace std;

// Foncteur qui effectue un chiffrement par decalage
class ChiffrementSubst {

public:

	// Constructeur prenant le nom fichier contenant les substitutions a utiliser
	ChiffrementSubst(const string& nomFichier)
	{
		ifstream subFile(nomFichier.c_str());
		if (subFile)
		{
			string row;
			while (getline(subFile, row))
			{
				if (row.size() > 2)
				{
					subDico[row[0]] = row[2];
				}
			}
		}
	}

	//Si la lettre est majuscule ET se trouve dans le dico on retourne la lettre chiffrée sinon la lettre originelle
	char operator()(char& letter)
	{
		//return (isupper(letter) && subDico.find(letter) != subDico.end()) ? subDico[letter] : letter;
		//equivalent to:
		if (isupper(letter) && subDico.find(letter) != subDico.end())
		{
			return subDico[letter];
		}
		else
		{
			return letter;
		}
	}

private:
	map<char, char> subDico;
};


void verifierFichier(string &nomFichier);


int main()
{
	// Le message a crypter
	string texte("BIENVENUE SUR LE MOOC C++ D'OCR !!");

	// Demande de la cle a l'utilisateur
	cout << "Quel fichier contenant la cle voulez-vous utiliser ? ";
	string nomFichier;
	cin >> nomFichier;

	verifierFichier(nomFichier);

	// Creation du foncteur
	ChiffrementSubst foncteur(nomFichier);

	// Chaine de caracteres pour le message crypter
	string texte_crypte;

	//Application du foncteur ChiffrementDecal sur la chaine de caractere 'texte' et redirection vers la variable texte_crypte
	texte_crypte.resize(texte.size());
	//transform(texte.begin(), texte.end(), texte_crypte.begin(), foncteur);

	  for(int i = 0; i < texte.length(); ++i)
  {
      texte_crypte[i] = foncteur(texte[i]);
  }

	//iterateur sur le flux sortant (console) formaté
	ostream_iterator<char> it_cout(cout, ", ");

	//Application du foncteur ChiffrementDecal sur la chaine de caractere 'texte' et redirection vers flux sortant
	copy(texte_crypte.begin(), texte_crypte.end(), it_cout);


	string stopconsole;
	cin >> stopconsole;

	return 0;
}

void verifierFichier(string &nomFichier)
{
	ifstream subFile(nomFichier.c_str());
	while (!subFile)
	{
		cout << endl << "Le fichier n'a pas pu etre ouvert." << endl;
		cout << "Quel fichier contenant la cle voulez-vous utiliser ? ";

		cin >> nomFichier;
		subFile = ifstream(nomFichier.c_str());
	}

	cout << endl;
}
