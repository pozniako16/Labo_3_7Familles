//
// Created by Lev on 28.02.2020.
//

#ifndef LABO_3_7FAMILLES_CARTE_H
#define LABO_3_7FAMILLES_CARTE_H
#include <string>
#include <iostream>

#define ushort unsigned short //macro pour type

class Carte {

    /**
     * surcharge d'operateur de flux pour affichage
     * @param flux, le flux à remplir
     * @param rhs, le membre à afficher
     * @return le flux remplit
     */
    friend std::ostream& operator<<(std::ostream& flux, Carte const& rhs);

    /**
     * surcharge operateur d'égalité
     * @param lhs, le membre de gauche
     * @param rhs, le membre de droite
     * @return true si les membres et les familles des 2 cartes sont respectivement identiques
     */
    friend bool operator==(Carte const& lhs, Carte const& rhs);

private:
    ushort famille;
    ushort membre;

public:

    /**
     * Constructeur
     * @param famille
     * @param membre
     */
    Carte(const ushort famille, const ushort membre);

    /**
     * getter sur la famille
     * @return la famille
     */
    ushort getFamille() const;

    /**
     * getter sur le membre
     * @return le membre
     */
    ushort getMembre() const;

    /**
     * surcharge operateur d'affectation
     * @param rhs, membre de droite, à copier dans le membre de gauche
     * @return une référence au nouveau membre
     */
    Carte& operator=(Carte const& rhs);

    std::string toString() const;



};


#endif //LABO_3_7FAMILLES_CARTE_H
