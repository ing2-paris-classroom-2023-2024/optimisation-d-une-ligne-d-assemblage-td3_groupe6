//
// Created by eliot on 23/11/2023.
//
#include <stdlib.h>
#include <stdio.h>

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD3_GROUPE6_ELIOTT_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD3_GROUPE6_ELIOTT_H

typedef struct station {
    int *tab_operations;
    int nb_operations;
}t_station;

typedef struct graphe {
    t_station **tab_stations;
    int nombre_stations;
}t_graphe;

t_graphe* exclusion(char* nom_fichier, t_graphe *un_graphe);
int nb_operations(char* fichier);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD3_GROUPE6_ELIOTT_H
