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
    std::vector<Joueur> players;
    std::vector<ushort> availableFamilies; //familles disponibls
    unsigned int turn; //tour courant

public:


    /**
     * Constructeur
     */
    Partie();

    /**
     * @brief vide puis remplit la pioche de cartes
     */
    void remplitPioche();

    /**
     * @brief distribues des cartes aux joueurs
     */
    void distribCarte();

    void initfamillesDipos();

    /**
     * @brief Affiche le tour courrant
     */
    void show();

    /**
     * @brief simule un tour
     */
    void simulateRound(bool affichage);

    /**
     * @brief simule une partie
     */
    void simulate(bool affichage);




    /**
     * @brief verifie que la partie est finie
     * @return true si la pioche est vide et que les joueurs n'ont plus de cartes
     * false sinon
     */
    bool gameDone();

    /**
     * @brief: réinitialise une partie
     *   - vide les mains des joueurs
     *   - vide la pioche
     *   - re remplit la pioche
     *   - distribue les cartes
     */
    void resetGame();

    void winner();

    void showFinalScore();


};


#endif //LABO_3_7FAMILLES_PARTIE_H
