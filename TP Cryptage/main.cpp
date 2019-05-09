#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>

using namespace std;

// Foncteur qui effectue un chiffrement par decalage
class ChiffrementDecal{

public:

  // Constructeur prenant le decalage voulu en argument
  ChiffrementDecal(int decalage) : m_decalage(decalage % 26) // grace au modulo on s'assure que l'on auras jamais un décalage plus grand que 25
  {}

  char operator()(char &c) const
  {
      if(c > 64 && c < 91) // On vérifie que "c" est bien une lettre majuscule (les lettre majuscule sont comprises entre 65 et 90 inclus en code ASCII)
      {
          c += m_decalage;

          if(c > 90) // Si on dépasse la lettre "Z", alors on repart à la lettre "A", qui est à 26 charactere de Z, d'où le -26
            c -= 26;
      }

      return c;
  }

private:

  int m_decalage; // Le decalage a appliquer au texte

};

int main()
{

  // Le message a crypter
  string texte("BIENVENUE SUR LE MOOC C++ D'OCR !!");

  // Demande du decalage a l'utilisateur
  cout << "Quel decalage voulez-vous utiliser ? ";
  int decalage;
  choix:
  cin >> decalage;
  if(decalage < 0)
  {
      cout << "Veuillez entrer une valeur positive." << endl;
      goto choix;
  }

  // Creation du foncteur
  ChiffrementDecal foncteur(decalage);

  // Chaine de caracteres pour le message crypté
  //ici on ecrit dans texte_crypte en utilisant l'algo transform et en passant par le foncteur de la class ChiffremetDecal

  string texte_crypte;
  texte_crypte.resize(texte.length()); // L'algo ne redimenssionne pas la cible donc il est très important que la capacité du recptacle soit au moins égale que le premier iterateur sinon le programme crash
  transform(texte.begin(), texte.end(), texte_crypte.begin(), foncteur);

  // Afficher le message crypté en utilisant l'algo copy() et un iterateur sur flux sortant.


  copy(texte_crypte.begin(), texte_crypte.end(), ostream_iterator<char>(cout, ","));

  return 0;
}

