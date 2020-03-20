/* ---------------------------
Laboratoire : 00
Fichier :
Auteur(s) : Axel Vallon
Date :

But : Ce programme doit afficher à la sortie standard
      "Bonjour, Monde!" et passer à la ligne.

Remarque(s) :

Compilateur : MinGW-g++ 6.3.0

--------------------------- */


#include "MeilleurJoueur.h"
#include <string>
#include <iostream>

using namespace std;

Carte MeilleurJoueur::carteADemander(std::vector<unsigned short>& familleDisponible, size_t nbrMembres){
   unsigned nbCarteMaxFamille = 0;
   unsigned short noFamille;

   for (ushort famille : familleDisponible) {
      unsigned compteur = 0;
      for (size_t i = 0; i < cartesEnMains.size(); i++) {
         if (cartesEnMains[i].getFamille() == famille)
            compteur++;
      }
      if (compteur > nbCarteMaxFamille) {
         nbCarteMaxFamille = compteur;
         noFamille = famille;
      }
   }
   bool tmp;
   for (unsigned i = 1; i <= nbrMembres; i++) {
      tmp = true;
      for (size_t j = 0; j < this->cartesEnMains.size(); j++) {
         if (MeilleurJoueur::cartesEnMains[j].getFamille() == noFamille &&
                 MeilleurJoueur::cartesEnMains[j].getMembre() == i) {
            tmp = false;
            break;
         }
      }
      if (tmp)
      {
         Carte carteADemander(noFamille, i);
         return carteADemander;
      }
   }
}

MeilleurJoueur::MeilleurJoueur(string const& nom): Joueur(nom) {}

