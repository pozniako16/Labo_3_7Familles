//
// Created by Lev on 01.03.2020.
//
#include "Partie.h"
#include "Carte.h"
#include <ctime>


using namespace std;

int main(){

    srand(time(NULL));



    Partie p;

    for(size_t partie = 0; partie < 100; partie++) {
        p.simulate(false);
        p.winner();
        p.resetGame();
    }
    p.showFinalScore();

    return EXIT_SUCCESS;
}