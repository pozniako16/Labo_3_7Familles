#include "Joueur.h"
#include "Carte.h"

#include <random>
#include <algorithm>
#include <time.h>
#include <vector>

using namespace std;

ostream& operator<<(ostream& flux, const Joueur& joueur) {
   flux << joueur.nom << ": ";
   for (Carte c : joueur.cartesEnMains)
      flux << c << " ";
   flux << "[";
   for (Carte c : joueur.famillesSurTable)
      flux << c << ".";
   flux << "]";
   return flux;
}

bool operator==(Joueur const& lhs, Joueur const& rhs) {
   return lhs.nom == rhs.nom;
}

Joueur::Joueur(string const& nom) : nom(nom), nbVictoire(0) {
}

unsigned int Joueur::getNbVictoire() const {
   return nbVictoire;
}

size_t Joueur::getPoints(size_t nbrMembres) const {
   return famillesSurTable.size() / nbrMembres;
}

unsigned Joueur::nbCarte() {
   return cartesEnMains.size();
}

string& Joueur::getNom() {
   return nom;
}

//faire avec clear

void Joueur::viderCartes() {
   cartesEnMains.clear();
   famillesSurTable.clear();
}

Carte Joueur::carteADemander(vector<ushort>& familleDisponible, size_t nbrMembres) {
   vector<ushort> familleEnMains;
   for (ushort famille : familleDisponible) {
      for (size_t i = 0; i < cartesEnMains.size(); i++) {
         if (cartesEnMains[i].getFamille() == famille)
            familleEnMains.push_back(famille);
            break;
      }
   }
   ushort noFamille = familleEnMains[rand() % familleEnMains.size()];
   
   bool tmp;
   for (unsigned i = 1; i <= nbrMembres; i++) {
      tmp = true;
      for (size_t j = 0; j < cartesEnMains.size(); j++) {
         if (cartesEnMains[j].getFamille() == noFamille &&
                 cartesEnMains[j].getMembre() == i) {
            tmp = false;
            break;
         }
      }
      if (tmp){
         Carte carteADemander(noFamille, i);
         return carteADemander;
      }
   }
}

bool Joueur::prendsCarteA(const Carte& carteCible, Joueur& joueurCible) {
   for (size_t i = 0; i < joueurCible.cartesEnMains.size(); ++i) {
      if (joueurCible.cartesEnMains.at(i) == carteCible) {
         cartesEnMains.push_back(carteCible);
         joueurCible.cartesEnMains.erase(joueurCible.cartesEnMains.begin() + i);
         return true;
      }
   }
   return false;
}

void Joueur::detecterFamilleComplete(vector<ushort>& familleDisponible, const Carte& carteObtenue, size_t nbrMembres) {
   unsigned short famille = carteObtenue.getFamille();
   //compteur sur le nombre de membre d'une famille
   unsigned compteurFamille = 0;
   for (unsigned i = 0; i < cartesEnMains.size(); i++) {
      if (famille == cartesEnMains[i].getFamille())
         compteurFamille++;
   }

   //dépose de la famille sur table si complete
   if (compteurFamille == nbrMembres) {
      for (size_t i = 0; i < cartesEnMains.size(); ++i)
         if (cartesEnMains[i].getFamille() == famille) {
            Carte temp = cartesEnMains[i]; //valeur tampon
            famillesSurTable.push_back(temp);
            cartesEnMains.erase(cartesEnMains.begin() + i); //suppression de la carte de la main
            i--; //décrémente i pour ne pas oublier de carte dans la main
         }
      remove(familleDisponible.begin(), familleDisponible.end(), famille);
      familleDisponible.pop_back();
   }
}

Carte& Joueur::piocherCarte(vector<Carte>& pioche) {
   Carte cPioche = pioche.back();
   cartesEnMains.push_back(cPioche);
   pioche.pop_back();
   return cartesEnMains.back();
}

bool Joueur::aCarte() {
   return !cartesEnMains.empty();
}

void Joueur::affectationPoint(unsigned nbVictoire) {
   this->nbVictoire += nbVictoire;
}