//
// Created by Lev on 28.02.2020.
//

#ifndef LABO_3_7FAMILLES_PARTIE_H
#define LABO_3_7FAMILLES_PARTIE_H
#include "Joueur.h"
#include "Carte.h"

class Partie {
private:

   std::vector<Carte> pioche;
   std::vector<Joueur> joueurs;
   std::vector<ushort> familleDisponible;
   bool affichage;
   bool changerJoueurChaquePartie;
   unsigned noTourCourant;
   const size_t NBR_FAMILLES;
   const size_t NBR_MEMBRES;
   const std::vector<std::string> NOMS_JOUEURS;
   

public:

   /**
    * Constructeur
    */
   Partie(bool affichage,bool changerJoueur, size_t nbrFamilles, size_t nbrMembres, std::vector<std::string> nomJoueur);
   
   /**
    * @brief vide puis remplit la pioche de cartes
    */
   void remplitPioche();

   /**
    * @brief distribues des cartes aux joueurs
    */
   void distribCarte();

   /**
    * @brief Affiche le tour courrant
    */
   void show();

   Joueur& joueurCible(const Joueur& joueurActuel);

   /**
    * @brief simule un tour
    */
   void nouveauTour();

   /**
    * @brief simule une partie
    */
   unsigned lancerPartie();

   /**
    * @brief verifie que la partie est finie
    * @return true si la pioche est vide et que les joueurs n'ont plus de cartes
    * false sinon
    */
   bool partieFinie();

   /**
    * @brief: réinitialise une partie
    *   - vide les mains des joueurs
    *   - vide la pioche
    *   - re remplit la pioche
    *   - distribue les cartes
    */
   void initialiserPartie();

   void gagnant();

   void afficherScoresFinaux(size_t nbPartie);


};


#endif //LABO_3_7FAMILLES_PARTIE_H
