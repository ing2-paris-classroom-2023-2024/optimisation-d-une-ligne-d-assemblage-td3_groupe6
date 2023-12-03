//
// Created by eliot on 23/11/2023.
//

#include "exclusion.h"
#include "precedence.h"


int main(void){
    int nombre_operations = 0;
    int nb_op_max = 0;
    int nv_stations = 0;

    nombre_operations = nb_operations("../operations.txt");
    nb_op_max = num_opeartion_max("../operations.txt");

    t_graphe *un_graphe = creer_graphe(nb_op_max);
    t_graphe *graphePreccedence = creerGraphePrecedencce(nb_op_max);

    un_graphe->tab_operations_reelles = creation_tab_op_reelles("../operations.txt", un_graphe);
    un_graphe->tab_operations_reelles = creation_tab_op_reelles("../operations.txt", graphePreccedence);

    printf("op max %d\n", nb_op_max);

    un_graphe->tab_operations_reelles = creation_tab_op_reelles("../operations.txt", un_graphe);

    un_graphe = fichier_exclusion("../exclusion.txt", un_graphe);
    un_graphe->nb_stations = nb_mini_stations_exclu(un_graphe);

    t_graphe * stations = creation_graphe_stations_exclusion(un_graphe, "../operations.txt", "../temps_cycle.txt");

    //debutParcoursBfs(graphePreccedence); ////problème avec la fonction ParcoursBFS

    ///affichage des stations avec contrainte d exclusion seule
    Affichage_stations(stations);

    t_graphe * stations_exclusion = creation_graphe_stations_exclusion(un_graphe, "../operations.txt", "../temps_cycle.txt");
    nv_stations = nb_nv_stations_necessaires_exclusion_temps(stations_exclusion);

    t_graphe *mix_exclu_temps = creation_stations_temps_exclusion(stations_exclusion, nv_stations);

    stations_exclusion->nb_stations = un_graphe->nb_stations;
    mix_exclu_temps->nb_stations = stations_exclusion->nb_stations + nv_stations;

    mix_exclu_temps = associer_operations_exclusion_temps(mix_exclu_temps, nv_stations);

    printf("\n\nGRAPHE EXCLUSION ET TEMPS DE CYCLE : \n");
    printf("Temps cycle : %.2fs", mix_exclu_temps->temps_cycle);
    ////Affichage des stations avec contrainte d exclusion et de temps
    Affichage_stations(mix_exclu_temps);

    free(un_graphe->tab_operations_reelles);
    liberation_memoire_graphe_stations(stations_exclusion);
    libeartion_memoire_graphe_contraintes(un_graphe);

    return 0;
}


