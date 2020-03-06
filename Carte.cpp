//
// Created by Lev on 28.02.2020.
//

#include "Carte.h"

#define ASCII_CAPS_CAR 64
#define ASCII_NUM_CHAR 48

using namespace std;

ostream& operator<<(ostream &flux, Carte const& rhs) {
    //On convertit le membre en caractere majuscule avec un cast
    flux << rhs.getFamille() << (char) (ASCII_CAPS_CAR + rhs.getMembre());
    return flux;
}

bool operator==(Carte const& lhs, Carte const& rhs){
    return (lhs.famille == rhs.famille and lhs.membre == rhs.membre);
}

Carte::Carte(const ushort famille, const ushort membre): membre(membre), famille(famille){
    //A REVOIR AVEC VARIABLES STATIQUES
}

Carte& Carte::operator=(Carte const &rhs) {
    //affectation membre à membre
    this->membre = rhs.membre;
    this->famille = rhs.famille;
    return *this;
}

string Carte::toString() const {
    string s;
    s += (char) ASCII_NUM_CHAR + famille;
    s += (char) ASCII_CAPS_CAR + membre;
    return s;
}

ushort Carte::getFamille() const {return famille;}
ushort Carte::getMembre() const {return membre;}