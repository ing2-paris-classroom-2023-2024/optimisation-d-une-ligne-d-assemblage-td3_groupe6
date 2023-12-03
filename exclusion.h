//
// Created by eliot on 23/11/2023.
//
#include <stdlib.h>
#include <stdio.h>

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD3_GROUPE6_ELIOTT_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD3_GROUPE6_ELIOTT_H

typedef struct arc{
    int num_station;
    struct arc* arc_suivant;
}t_arc;

typedef struct op{
    int numero;
    float temps_ope;
    int station;
}t_operation;

typedef struct station {
    int val_station;
    t_operation **tab_operation;
    int marquage;
    int nb_operations;
    int degre;
    t_arc *voisins;
    int couleur;
    int numeroStation;
    int choixStation;
}t_station;

typedef struct graphe {
    t_station **tab_stations;
    int ** matrice_exclusions;
    int ordre_sous_graphe;
    int nb_stations;
    int *sous_sommets;
    int num_operation_max;
    int *tab_operations_reelles;
    int nb_paires_exclusion;
    float temps_cycle;
}t_graphe;

t_graphe* fichier_exclusion(char* nom_fichier, t_graphe *un_graphe);
t_graphe* gestion_donnees_graphe(int nb_operations, int op_max,char* file_name);
int nb_operations(char* fichier);
void afficher_matrice_exclusions(t_graphe *un_graphe);
int num_opeartion_max(char* file);
t_station ** CreerArete(t_station ** sommet, int station_1, int station_2);
t_graphe *creation_graphe_stations_exclusion(t_graphe* un_graphe, char* file_name, char* temps_cycle);
void afficher_successeurs(t_station** sommet, int num);
void graphe_afficher(t_graphe* graphe);
t_graphe *creer_graphe(int op_max);
void ColorationGlouton(t_graphe* graphe);
void DFS(t_graphe *un_graphe, t_graphe * sous_graphe, int s);
int nb_mini_stations_exclu(t_graphe *un_graphe);
int* creation_tab_op_reelles(char *nom_fichier, t_graphe* un_graphe);
void Affichage_stations(t_graphe* un_graphe);
void liberation_memoire_graphe_stations(t_graphe *un_graphe);
void libeartion_memoire_graphe_contraintes(t_graphe *un_graphe);
t_graphe *init_graphe_station(int nb_stations);
int compareDegre(const void* a, const void* b);
t_operation *creer_operation(int num_operation);
t_graphe *creerGraphePrecedencce(int ordre);
t_graphe* lire_temps_cycle(t_graphe* un_graphe, char* nom_fichier, char* fichier_cycle);
int nb_nv_stations_necessaires_exclusion_temps(t_graphe* graphe_exclusion);
t_graphe *creation_stations_temps_exclusion(t_graphe *graphe_exclusion_temps, int nv_stations);
t_graphe* associer_operations_exclusion_temps(t_graphe* graphe_exclusion_temps, int nv_stations);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD3_GROUPE6_ELIOTT_H
