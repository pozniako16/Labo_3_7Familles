cmake_minimum_required(VERSION 3.14)
project(Labo_3_7Familles)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Labo_3_7Familles
        main.cpp
        Carte.cpp
        Carte.h
        Joueur.cpp
        Joueur.h
        Partie.cpp
        Partie.h
        Constantes.h
        )
