//
// Created by eliot on 23/11/2023.
//
#include <stdlib.h>
#include <stdio.h>

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD3_GROUPE6_ELIOTT_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD3_GROUPE6_ELIOTT_H

typedef struct station {
    int *tab_operations;
}t_station;

typedef struct graphe {
    t_station **tab_stations;
    int ** matrice_exclusions;
    int nb_operations;
    int num_operation_max;
    int nombre_stations;
    int nb_paires_exclusion;
}t_graphe;

t_graphe* fichier_exclusion(char* nom_fichier, t_graphe *un_graphe);
int nb_operations(char* fichier);
t_graphe* creation_graphe(int nb_operations, int op_max);
void afficher_matrice_exclusions(t_graphe *un_graphe);
int num_opeartion_max(char* file);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD3_GROUPE6_ELIOTT_H
