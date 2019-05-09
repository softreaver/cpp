#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <map>
#include <fstream>
#include <utility>

using std::string;
using std::istream_iterator;
using std::map;
using std::cout;
using std::cin;
using std::endl;

// Foncteur qui effectue un chiffrement par decalage
class ChiffrementSubst{

public:

  // Constructeur prenant le nom fichier contenant les substitutions a utiliser
  ChiffrementSubst(const string& nomFichier)
  {
     std::ifstream fichier(nomFichier.c_str()); //A VOIR !! Transform semble ne pas fonctionner si je déclare le membre std::ifstream fichier dans private
     it = fichier; // initialisation de l'iterateur pour la lectre du fichier NOTE : ne fonctionne pas si je le met dans la liste d'initialisation

     while(it != fin)
     {
         string f(*it); // initialisation de first
         ++it;
         string s(*it);// initialisation de second
         ++it;
         m_cle.insert(std::make_pair(f[0], s[0])); //insertion d'une nouvelle paire dans la map m_cle
     }
  }


  char operator()(char arg)
  {
      trouve = m_cle.find(arg);

      if(trouve == m_cle.end()) return arg;
      return trouve->second;
  }

private:
    map<char, char> m_cle;
    istream_iterator<string> it;
    istream_iterator<string> fin;
    map<char, char>::iterator trouve;
};


int main()
{

  // Le message a crypter
  string texte("BIENVENUE SUR LE MOOC C++ D'OCR !!");

  // Demande de la cle a l'utilisateur
  cout << "Quel fichier contenant la cle voulez-vous utiliser ? ";
  string nomFichier;
  cin >> nomFichier;

  // Creation du foncteur
  ChiffrementSubst foncteur(nomFichier);

  // Chaine de caracteres pour le message crypter
  string texte_crypte;
// Un iterateur permettant l'insertion a la fin
  //std::back_insert_iterator<string> it(texte_crypte); //soit ça soit utiliser resize() au choix
texte_crypte.resize(texte.length());
transform(texte.begin(), texte.end(), texte_crypte.begin(), foncteur);

 /* for(int i = 0; i < texte.length(); ++i)
  {
      texte_crypte[i] = foncteur(texte[i]);
  }*/

  std::copy(texte_crypte.begin(), texte_crypte.end(), std::ostream_iterator<char>(cout, ","));

  return 0;
}

