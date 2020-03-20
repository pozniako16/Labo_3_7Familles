/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MeilleurJoueur.h
 * Author: axelv
 *
 * Created on 19. mars 2020, 09:24
 */

#ifndef MEILLEURJOUEUR_H
#define MEILLEURJOUEUR_H

#include "Joueur.h"

class MeilleurJoueur : public Joueur{
public:
    MeilleurJoueur(std::string const& nom);
    Carte carteADemander(std::vector<unsigned short>& familleDisponible, size_t nbrMembres);

};

#endif /* MEILLEURJOUEUR_H */

