//
// Created by eliot on 23/11/2023.
//

#include "exclusion.h"
#include "precedence.h"


int main(void){
    int nombre_operations = 0;
    int nb_op_max = 0;
    int nv_stations = 0;

    char f_operation[30] = "../operations.txt";
    char f_exclusion[30] = "../exclusion.txt";
    char f_temps_de_cycle[30] = "../temps_cycle.txt";

    nombre_operations = nb_operations(f_operation);
    nb_op_max = num_opeartion_max(f_operation);

    t_graphe *un_graphe = creer_graphe(nb_op_max);//creation du graphe d exclusion contenant num operation max sommets (opérations)
    t_graphe *graphePreccedence = creerGraphePrecedencce(nb_op_max);

    un_graphe->tab_operations_reelles = creation_tab_op_reelles(f_operation, un_graphe); //fonction permettant l obtention des operations existantes
    un_graphe->tab_operations_reelles = creation_tab_op_reelles(f_operation, graphePreccedence);

    un_graphe = fichier_exclusion(f_exclusion, un_graphe);//lecture du fichie exclusion, gestion des données
    un_graphe->nb_stations = nb_mini_stations_exclu(un_graphe);//fonction qui revnoie le nombre de stations necessaires (coloration graphe exclusion)

    t_graphe * stations = creation_graphe_stations_exclusion(un_graphe, "../operations.txt", "../temps_cycle.txt");//creation de la ligne d assemblage
    printf("\n\n\n        STATION AVEC CONTRAINTE DE PRECEDENCE SEULE     \n\n");
    //debutParcoursBfs(graphePreccedence); ////problème avec la fonction ParcoursBFS

    ///affichage des stations avec contrainte d exclusion seule
    printf("\n\n        STATIONS AVEC CONTRAINTE D EXCLUSION SEULE     \n");
    Affichage_stations(stations);

    t_graphe * stations_exclusion = creation_graphe_stations_exclusion(un_graphe, f_operation, f_temps_de_cycle);
    nv_stations = nb_nv_stations_necessaires_exclusion_temps(stations_exclusion);//fonction qui renvoie le nombre de nouvelles stations necessaires pour inclusion temps de cycle

    t_graphe *mix_exclu_temps = creation_stations_temps_exclusion(stations_exclusion, nv_stations);

    stations_exclusion->nb_stations = un_graphe->nb_stations;
    mix_exclu_temps->nb_stations = stations_exclusion->nb_stations + nv_stations;

    mix_exclu_temps = associer_operations_exclusion_temps(mix_exclu_temps, nv_stations);//on associe les operations dans les nouvelles stations créées

    ////affichage temps de cycle seul
    printf("\n\n\n        STATIONS AVEC CONTRAINTE DE TEMPS SEULE     \n\n");
    printf("Temps cycle : %.2fs", mix_exclu_temps->temps_cycle);
    temps_cycle_seul("../operations.txt", nb_op_max + 1, mix_exclu_temps->temps_cycle);

    ////Affichage des stations avec contrainte d exclusion et de temps
    printf("\n\n\n        STATIONS AVEC CONTRAINTES D EXCLUSION ET DE TEMPS     \n");
    Affichage_stations(mix_exclu_temps);

    free(un_graphe->tab_operations_reelles);
    liberation_memoire_graphe_stations(stations_exclusion);
    libeartion_memoire_graphe_contraintes(un_graphe);

    return 0;
}


