#include "Joueur.h"
#include "Carte.h"
#include "Constantes.h"

#include <random>
#include <time.h>


using namespace std;


bool operator==(Joueur const& lhs, Joueur const& rhs){
    return lhs.nom == rhs.nom;
}

ostream& operator<<(ostream& flux, Joueur const& j){
    flux << j.nom << ": ";
    for(Carte c: j.cartesEnMains)
        flux << c << " ";
    flux << "[";
    for (Carte c: j.carteSurTable)
        flux << c << ".";
    flux << "]";
    return flux;
}

Joueur::Joueur(string const& nom): nom(nom), wins(0){};

//faire avec clear
void Joueur::viderCartes() {
    while(!cartesEnMains.empty())
        cartesEnMains.pop_back();
    while (!carteSurTable.empty())
        carteSurTable.pop_back();
}

//REFAIRE AVEC ITERATOR
void Joueur::prendsCarteA(Carte const &carteAPrendre, Joueur &aPrendreA) {
    for(size_t i = 0; i < aPrendreA.cartesEnMains.size(); ++i){
        if((aPrendreA.cartesEnMains.at(i) == carteAPrendre)) {
            Carte temp = aPrendreA.cartesEnMains.at(i);
            cartesEnMains.push_back(temp);
            aPrendreA.cartesEnMains.erase(aPrendreA.cartesEnMains.begin() + i);
        }
    }
    /*
    for (auto i = j.cartesEnMains.begin(); i != j.cartesEnMains.end(); i++){
        if (*i == c) {
            Carte carteAPrendre = *i;
            this->cartesEnMains.push_back(carteAPrendre);
            j.cartesEnMains.erase(i);
        }
    }
     */
}

bool Joueur::aCarte(){return cartesEnMains.size() > 0;};




Carte Joueur::demanderCarte(vector<ushort>& availableFamillies) {
    ushort famillyToAsk;
    //choix au hasard parmi les familles disponible
    famillyToAsk = availableFamillies.at(rand() % availableFamillies.size());
    vector <Carte> membresAbsents;

    //construction du tableau de membres possibles (qu'on a pas déjà)
    for(ushort i = 1; i <= NBR_MEMBRES; ++i){
        Carte c (famillyToAsk, i);
        membresAbsents.push_back(c);
    }
    //un peu dégueu
    Carte toAsk = membresAbsents.at(rand() % membresAbsents.size());
    do {
        toAsk = membresAbsents.at(rand() % membresAbsents.size());
    }while(this->aLaCarte(toAsk));
    return toAsk;

}

ushort Joueur::findBiggestFamilly(std::vector<ushort> availableFam) {
    if (!this->aCarte())
        return availableFam.at(rand() % availableFam.size());
    else{
        ushort famillyCount[] = {0, 0, 0, 0, 0};
        for (size_t i = 0; i < cartesEnMains.size(); ++i){
            famillyCount[cartesEnMains.at(i).getFamille()-1]++;
        }
        
        ushort bestFam = 0;
        for(ushort fam: famillyCount)
            if(fam > bestFam)
                bestFam = fam;

        return bestFam;
    }
}

/*Carte Joueur::demanderCarteBestPlayer(vector<ushort>& availableFamillies) {
    ushort famillyToAsk = findBiggestFamilly(availableFamillies);
    vector <Carte> membresAbsents;
    //construction du tableau de membres possibles (qu'on a pas déjà)
    for(ushort i = 1; i <= NBR_MEMBRES; ++i){
        Carte c (famillyToAsk, i);
        membresAbsents.push_back(c);
    }
    Carte toAsk = membresAbsents.at(rand() % membresAbsents.size());
    do {
        toAsk = membresAbsents.at(rand() % membresAbsents.size());
    }while(this->aLaCarte(toAsk));
    return toAsk;

}
 */

bool Joueur::aLaCarte(Carte const& cardToCheck) {
    //parcours de la main jusqu'à un égal
    for(Carte carteInHand : cartesEnMains)
        if(cardToCheck == carteInHand)
            return true;
    return false;
}

void Joueur::detecterFamille(vector<ushort>& availableFamilies) {
    //compteur sur le nombre de membre d'une famille
    size_t famillyCount = 0;
    //contient la famille a poser
    ushort detectedFamilly = 0;

    //recherche si famille complete
    for(size_t i = 1; (i <= NBR_FAMILLES) && (famillyCount < NBR_MEMBRES); ++i) {
        famillyCount = 0;
        //verifie toutes les cartes pour toutes les familles
        for (Carte c: cartesEnMains) {
            //si on trouve une carte de la bonne famille on incrémente le compteur
            //permet de sortir de la boucle aussi
            if(c.getFamille()==i){
                famillyCount++;
            }
        }
        //si famille complete en conserve le short correspondant
        if (famillyCount == NBR_MEMBRES) {
            detectedFamilly = i;
        }
    }
    //dépose de la famille sur table si complete
    if (famillyCount == NBR_MEMBRES) {
        for (size_t i = 0; i < cartesEnMains.size(); ++i)
            if (cartesEnMains.at(i).getFamille() == detectedFamilly) {
                Carte temp = cartesEnMains.at(i); //valeur tampon
                carteSurTable.push_back(temp);
                cartesEnMains.erase(cartesEnMains.begin() + i); //suppression de la carte de la main
                i--; //décrémente i pour ne pas oublier de carte dans la main
            }

        //on enleve du tableau des familles complété pour indiquer qu'il ne faut plus chercher cette famille
        for(size_t i = 0; i < availableFamilies.size(); i++)
            if (availableFamilies.at(i) == detectedFamilly)
                availableFamilies.erase(availableFamilies.begin()+i);
    }

}

void Joueur::piocherCarte(vector<Carte>& pioche) {
    Carte cPioche = pioche.back();
    cartesEnMains.push_back(pioche.back());
    pioche.pop_back();
}

void Joueur::aGagne(){++wins;};


