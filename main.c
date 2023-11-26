//
// Created by eliot on 23/11/2023.
//

#include "eliott.h"

int main(void){
    int nombre_operations = 0;
    int nb_op_max = 0;

    nombre_operations = nb_operations("../operations.txt");
    nb_op_max = num_opeartion_max("../operations.txt");
    //printf("op max : %d, nombre op : %d\n", nb_op_max, nombre_operations);

    t_graphe *un_graphe = creer_graphe(nb_op_max);

    un_graphe->tab_perations_reelles = creation_tab_op_reelles("../operations.txt", un_graphe);

    un_graphe = fichier_exclusion("../exclusion.txt", un_graphe);
    un_graphe->nb_stations = nb_mini_stations_exclu(un_graphe);

    /*printf("\ngraphe avec couleurs de chaque operation : \n");
    printf("NB STATIONS REQUISES : %d\n",un_graphe->nb_stations);
    printf("graphe d'exclusion\n");
    graphe_afficher(un_graphe);*/

    creation_graphe_stations(un_graphe);

    return 0;
}
