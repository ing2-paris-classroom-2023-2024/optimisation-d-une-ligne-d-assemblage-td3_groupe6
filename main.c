//
// Created by eliot on 23/11/2023.
//

#include "eliott.h"

int main(void){
    int nombre_operations = 0;
    int nb_op_max = 0;

    nombre_operations = nb_operations("../operations.txt");
    nb_op_max = num_opeartion_max("../operations.txt");

    t_graphe *un_graphe = creer_graphe(nb_op_max);

    un_graphe->tab_perations_reelles = creation_tab_op_reelles("../operations.txt", un_graphe);

    un_graphe = fichier_exclusion("../exclusion.txt", un_graphe);
    un_graphe->nb_stations = nb_mini_stations_exclu(un_graphe);

    t_graphe * stations = creation_graphe_stations(un_graphe);

    Affichage_stations(stations);

    free(un_graphe->tab_perations_reelles);
    liberation_memoire_graphe_stations(stations);
    libeartion_memoire_graphe_contraintes(un_graphe);

    return 0;
}
