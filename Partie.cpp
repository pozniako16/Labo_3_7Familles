//
// Created by Lev on 28.02.2020.
//

#include "Partie.h"
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <ctime>
#include <numeric>

using namespace std;

Partie::Partie(bool affichage, bool changerJoueur, size_t nbrFamilles, size_t nbrMembres,
        vector<string> nomJoueur) : affichage(affichage),  NOMS_JOUEURS(nomJoueur),
        changerJoueurChaquePartie(changerJoueur),
   NBR_FAMILLES(nbrFamilles), NBR_MEMBRES(nbrMembres) {
   //création des joueurs
   for (string name : NOMS_JOUEURS) {
      Joueur j(name);
      joueurs.push_back(j);
   }
}

void Partie::remplitPioche() {
   //On ajoute tous les membres de toutes les familles
   for (ushort famille = 1; famille <= NBR_FAMILLES; ++famille) {
      for (ushort membre = 1; membre <= NBR_MEMBRES; ++membre) {
         Carte c(famille, membre);
         pioche.push_back(c);
      }
   }
   random_shuffle(pioche.begin(), pioche.end());
}

void Partie::distribCarte() {
   //pioche successive pour avoir suffisemment de carte pour faire une famille
   for (size_t i = 0; i < NBR_MEMBRES; i++)
      for (Joueur& j : joueurs)
         j.piocherCarte(pioche);
}

void Partie::show() {
   //Affichage des joueurs
   for (Joueur j : joueurs)
      cout << j << endl;
   //Affichage de la pioche
   cout << "Pioche: ";
   for (Carte c : pioche)
      cout << c << " ";
   cout << endl;
}

Joueur& Partie::joueurCible(const Joueur& joueurActuel) {
   vector<size_t> joueursValide;
   for (size_t i = 0; i < joueurs.size(); i++) {
      if (!(joueurs[i] == joueurActuel) && joueurs[i].aCarte()) {
         joueursValide.push_back(i);
      }
   }
   return joueurs[joueursValide[rand() % joueursValide.size()]];
}

void Partie::nouveauTour() {
   //affichage de l'état de la partie
   if (affichage)
      show();
   
   //boucle sur les joueurs pour gérer le tour par tour
   for (Joueur& j : joueurs) {
      if (!partieFinie() && j.aCarte()) {
         Joueur& cible(joueurCible(j));
         //sélection d'une carte
         bool priseOK;
         do {
            Carte carteSouhaitee = j.carteADemander(familleDisponible, NBR_MEMBRES);
            if (affichage)
               cout << j.getNom() << " demande a " << cible.getNom() << " la carte "
               << carteSouhaitee << endl;
            priseOK = j.prendsCarteA(carteSouhaitee, cible);
            if (priseOK) {
               j.detecterFamilleComplete(familleDisponible, carteSouhaitee, NBR_MEMBRES);
               if (affichage)
                  cout << "  et " << cible.getNom() << " donne la carte a "
                  << j.getNom() << endl;
            } else {
               if (affichage)
                  cout << "  mais " << cible.getNom() << " ne l'a pas." << endl;
               if (!pioche.empty()) {
                  if (affichage)
                     cout << j.getNom() << " prend une carte dans la pioche ("
                     << pioche.back() << ')' << endl;
                  j.detecterFamilleComplete(familleDisponible, j.piocherCarte(pioche), NBR_MEMBRES);
               }
            }
         } while (priseOK && j.aCarte());
      }
   }
   if (affichage)
      cout << endl;
}

unsigned Partie::lancerPartie() {
   //simule une partie
   while (!(this->partieFinie())) {
      if (affichage)
         cout << "\n*** Tour " << noTourCourant << " ***" << endl;
      ++noTourCourant;
      nouveauTour();
   }
   
   for (Joueur& j : joueurs) {
      j.affectationPoint(j.getPoints(NBR_MEMBRES));
   }
   
   if (affichage) {
      cout << "\n*** Tour " << noTourCourant << " ***" << endl;
      show();
      cout << "Partie finie !\n";
   }
   
   if (changerJoueurChaquePartie)
      rotate(joueurs.begin(), joueurs.begin() + 1, joueurs.end());
   return noTourCourant;
}

bool Partie::partieFinie() {
   return familleDisponible.empty();
}

void Partie::initialiserPartie() {
   familleDisponible.resize(NBR_FAMILLES);
   iota(familleDisponible.begin(), familleDisponible.end(), 1);
   for (Joueur& j : joueurs)
      j.viderCartes();
   remplitPioche();
   distribCarte();
   //mélange les joueurs pour égaliser les chances sur plusieurs parties
   //random_shuffle(players.begin(), players.end());
   noTourCourant = 0;
}

void Partie::afficherScoresFinaux(size_t nbPartie) {
   cout << "Score sur " << nbPartie << " partie" << (nbPartie > 1 ? "s." : ".") << endl << endl;
   for (Joueur j : joueurs) {
      cout << j.getNom() << " a gagne " << j.getNbVictoire() << " fois.";
      cout << fixed << setprecision(3) << " (" <<
              (double) j.getNbVictoire() / (NBR_FAMILLES * nbPartie) * 100
              << "%)" << endl;
   }
}