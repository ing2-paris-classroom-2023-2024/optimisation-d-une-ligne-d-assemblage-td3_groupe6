//
// Created by eliot on 23/11/2023.
//

#include "eliott.h"

int main(void){
    int nombre_operations = 0;
    int nb_op_max = 0;
    nombre_operations = nb_operations("../operations.txt");
    nb_op_max = num_opeartion_max("../operations.txt");

    t_graphe *un_graphe = creation_graphe(nombre_operations,nb_op_max);

    printf("NOMBRE D OPERATIONS : %d\n",nombre_operations);
    printf("NUM OP MAX : %d\n",nb_op_max);

    un_graphe = fichier_exclusion("../exclusion.txt", un_graphe);

    afficher_matrice_exclusions(un_graphe);

    return 0;
}
