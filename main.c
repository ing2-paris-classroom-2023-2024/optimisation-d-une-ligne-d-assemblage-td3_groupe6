//
// Created by eliot on 23/11/2023.
//

#include "eliott.h"

int main(void){
    t_graphe *un_graphe = malloc(sizeof(t_graphe));
    int nombre_operations = 0;

    un_graphe = exclusion("../exclusion.txt", un_graphe);

    printf("///------------------///\n");

    nombre_operations = nb_operations("../operations.txt");

    printf("NOMBRE D OPERATIONS : %d\n",nombre_operations);

    return 0;
}
