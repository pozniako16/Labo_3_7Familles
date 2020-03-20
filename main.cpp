//
// Created by Lev on 01.03.2020.
//
#include "Partie.h"
#include "Carte.h"
#include "Joueur.h"
#include <ctime>

using namespace std;

int main() {
   srand(time(NULL));
   const bool AFFICHAGE = false;
   const bool CHANGER_JOUEUR = true;
   const size_t NB_PARTIE = 1000;

   const size_t NBR_FAMILLES = 9;
   const size_t NBR_MEMBRES = 5;
   
   unsigned nbTour = 0;

   Partie p(AFFICHAGE, CHANGER_JOUEUR, NBR_FAMILLES, NBR_MEMBRES,{"Alice", "Bobby", "Carol", "Danny"});

   for (size_t partie = 0; partie < NB_PARTIE; partie++) {
      p.initialiserPartie();
      nbTour += p.lancerPartie();
   }
   p.afficherScoresFinaux(NB_PARTIE);
   cout << "Nb Tour moyen : " << (double)nbTour / NB_PARTIE << endl;
   return EXIT_SUCCESS;
}