//
// Created by Lev on 28.02.2020.
//

#include "Partie.h"
#include "Constantes.h"

#include <vector>
#include <algorithm>
#include <string>
#include <ctime>


using namespace std;

Partie::Partie() {
    turn = 0;//initialise le tour courant à 0 (partie pas commencée)
    //Creation de la pioche

    remplitPioche();
    initfamillesDipos();
    //création des joueurs
    for(string name: NOMS_JOUEURS){
        Joueur j(name);
        players.push_back(j);
    }
    //distribution des cartes
    distribCarte();
}

void Partie::initfamillesDipos() {
    vector<ushort> availableFamiliesTemp;
    for(ushort famille = 1; famille <= NBR_FAMILLES; famille++)
        availableFamiliesTemp.push_back(famille);
    availableFamilies = availableFamiliesTemp;

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

void Partie::distribCarte(){
    //pioche successive pour avoir suffisemment de carte pour faire une famille
    for(size_t i = 0; i < NBR_MEMBRES; i++)
        for(Joueur& j: players)
            j.piocherCarte(pioche);


}

void Partie::show(){
    //Affichage des joueurs
    for(Joueur j: players)
        cout << j << endl;
    //Affichage de la pioche
    cout << "Pioche: ";
    for (Carte c: pioche)
        cout << c << " ";
    cout << "\n";

}

void Partie::simulateRound(bool affichage) {
    string s;
    //affichage de l'état de la partie
    if (affichage)
        show();
    size_t playerCount = 0;//compteur de joueur

    //boucle sur les joueurs pour gérer le tour par tour
    for (Joueur& j: players){
        //vérifie que la partie n'est pas fini
        //peut arriver que la partie soit terminer et le jeu continue de tourner
        if(!gameDone()) {
            size_t toAskCardTo = 0;
            //choix random de joueur à qui demander
            do {
                //pour ne pas se demander une carte à soit meme
                toAskCardTo = (playerCount + rand() % NBR_JOUEUR) % players.size();

                //on verifie que le joueur cible a des cartes
            } while (!players.at(toAskCardTo).aCarte());

            //sélection d'une carte
            Carte toAsk = j.demanderCarte(availableFamilies);
            //if(j == BEST_PLAYER)
            //toAsk = j.demanderCarteBestPlayer(availableFamilies);
            s +=  j.getNom() + " demande a " + players.at(toAskCardTo).getNom() + " la carte " + toAsk.toString() + "\n";

            //si la cible n'a pas la carte
            if (!players.at(toAskCardTo).aLaCarte(toAsk)) {
                s += "  Mais " + players.at(toAskCardTo).getNom() + " ne l'a pas. \n";
                //on verifier que la pioche n'est pas vide
                if (!pioche.empty()) {
                    //on pioche
                    s += j.getNom() + " prends la carte (" + pioche.back().toString() + ") dans la pioche\n";
                    j.piocherCarte(this->pioche);
                }

                //si la cible a la carte
            } else {
                s += "  et " + j.getNom() + " prends la carte a " + players.at(toAskCardTo).getNom() + "\n";
                //on prends la carte au joueur cible
                j.prendsCarteA(toAsk, players.at(toAskCardTo));
            }
            //verification si on a une famille complète
            j.detecterFamille(availableFamilies);
            playerCount++;
        }
    }
    s += "\n";
    if(affichage)
        cout << s;

}

void Partie::simulate(bool affichage){
    //simule une partie
    while (!this->gameDone()){
        ++this->turn;
        if(affichage)
            cout << "\n*** Tour " << turn << " ***" << endl;
        simulateRound(affichage);

    }
    if(affichage) {
        cout << "\n*** Tour " << --turn << " ***" << endl;
        show();
        cout << "Partie finie !\n";
    }
}

bool Partie::gameDone() {
    if(pioche.size() != 0)
        return false;
    for(Joueur j: players)
        if(j.aCarte())
            return false;
    return true;
}

void Partie::resetGame() {
    initfamillesDipos();
    for(Joueur& j: players)
        j.viderCartes();

    remplitPioche();
    distribCarte();
    //mélange les joueurs pour égaliser les chances sur plusieurs parties
    //random_shuffle(players.begin(), players.end());
    turn = 0;
}

void Partie::winner(){
    size_t winnerIndex = 0;
    size_t currentPlayer = 0;
    size_t familleMax = 0;
    for (Joueur j: players) {
        if (j.getCartesSurTable().size() > familleMax) {
            familleMax = j.getCartesSurTable().size();
            winnerIndex = currentPlayer;
        }
        currentPlayer++;

    }
    players.at(winnerIndex).aGagne();
}

void Partie::showFinalScore(){
    for(Joueur j:players)
        cout << j.getNom() << ", wins: " << j.getwins()<< endl;
}




