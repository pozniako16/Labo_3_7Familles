//
// Created by Lev on 28.02.2020.
//

#ifndef LABO_3_7FAMILLES_JOUEUR_H
#define LABO_3_7FAMILLES_JOUEUR_H

#include <string>
#include <vector>
#include "Carte.h"

#define ushort unsigned short

class Joueur {

    /**
     * surcharge operateur de flux pour affichage
     * @param flux, le flux à remplir
     * @param j, le joueur à afficher
     * @return le flux remplit
     */
    friend std::ostream& operator<<(std::ostream& flux, Joueur const& j);

    /**
     * surcharge operateur d'égalité
     * @param lhs, membre de gauche
     * @param rhs, membre de droite
     * @return true si les 2 joueurs ont le meme nom [à revoir]
     */
    friend bool operator== (Joueur const& lhs, Joueur const& rhs);

private:
    std::string nom;
    std::vector<Carte> cartesEnMains;
    std::vector<Carte> carteSurTable;
    unsigned int wins;

public:

    /**
     * constructeur par défaut non utilisé [à faire]
     */
    Joueur();

    /**
     * constructeur
     * @param nom: le nom du joueur à initialiser
     */
    Joueur(std::string const& nom);

    /**
     * @brief: vide les mains du joueur
     */
    void viderCartes();

    /**
     * gère la demande de carte, en choisit une au hasard parmi les familles
     * disponible, et les cartes que le joueur n'a pas
     * @param availableFamilies: les familles disponibles
     * @return la carte que le joueur veut
     */
    Carte demanderCarte(std::vector<ushort>& availableFamilies);

    Carte demanderCarteBestPlayer(std::vector<ushort>& availableFamilies);

    /**
     * verifie qu'une famille est complete dans la main
     *   - si oui : la pose sur table et l'enlève des familles disponibles
     *   - si non: ne fait rien
     * @param availableFamilies: les familles dispomibles
     */
    void detecterFamille(std::vector<ushort>& availableFamilies);

    /**
     * verifie qu'un joueur a la carte en paramètre
     * @param c la carte à trouver
     * @return true si le joueur a la carte c
     */
    bool aLaCarte(Carte const& c);

    /**
     * verifier qu'un joueur a des cartes
     * @return true si la main du joueur n'est pas vide
     */
    bool aCarte();

    /**
     * prends la carte pioche.back() et la met dans la main du joueur
     * @param pioche, la pioche du jeu
     */
    void piocherCarte(std::vector<Carte>& pioche);//faire une stack

    /**
     * getter sur le nom du joueur
     * @return le nom du joueur
     */
    const std::string& getNom() {return nom;}

    const std::vector<Carte> getCartesSurTable() {return carteSurTable;};

    /**
     * prends une carte en paramètre au joueur en parametre
     * @param carteAPrendre, la carte à prendre
     * @param aPrendreA, le joueur à qui prendre la carte
     */
    void prendsCarteA(Carte const& carteAPrendre, Joueur& aPrendreA);

    void aGagne();
    const unsigned int getwins() {return wins;};

    ushort findBiggestFamilly(std::vector<ushort> availableFam);


};


#endif //LABO_3_7FAMILLES_JOUEUR_H
