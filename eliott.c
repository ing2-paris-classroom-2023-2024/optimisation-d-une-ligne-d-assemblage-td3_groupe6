//
// Created by eliot on 23/11/2023.
//
#include "eliott.h"

void afficher_matrice_exclusions(t_graphe *un_graphe){
    for(int i = 0 ;i < (un_graphe->num_operation_max + 1);i++){
        for(int j = 0; j < (un_graphe->num_operation_max + 1);j++){
            printf("[%d]",un_graphe->matrice_exclusions[i][j]);
        }
        printf("\n");
    }
}

int num_opeartion_max(char* file){
    FILE * fp = fopen(file, "r");

    if(fp == NULL){
        printf("erreur ouverture fichier operation_max.\n");
        exit(1);
    }

    int entier_max = 0;
    int op_1 = 0;
    float temps = 0;

    while(fscanf(fp,"%d%f",&op_1,&temps) == 2){
        if(op_1 > entier_max)
            entier_max = op_1;
    }

    return entier_max;
}

t_graphe* creation_graphe(int nb_operations, int op_max){
    t_graphe *un_graphe = malloc(sizeof(t_graphe));

    if(un_graphe == NULL){
        printf("erreur alloc graphe\n");
        exit(1);
    }

    un_graphe->nb_operations = nb_operations;
    un_graphe->num_operation_max = op_max;
    un_graphe->nombre_stations = 0;
    un_graphe->nb_paires_exclusion = 0;
    un_graphe->matrice_exclusions = malloc((op_max  + 1) * sizeof(int*));
    for(int i = 0; i < op_max + 1;i++){
        un_graphe->matrice_exclusions[i] = malloc((op_max + 1) * sizeof(int));
    }

    for(int i = 0; i < op_max + 1;i++){
        for(int j = 0; j < op_max + 1;j++){
            un_graphe->matrice_exclusions[i][j] = 0;
        }
    }

    return un_graphe;
}

int nb_operations(char* fichier){
    FILE *fp = fopen(fichier,"r");

    if(fp == NULL){
        printf("erreur ouverture fichier operations.\n");
        exit(1);
    }

    int qte_op = 0;
    int op = 0;
    float temps = 0;

    while(fscanf(fp,"%d%f",&op,&temps) == 2){
        qte_op++;
    }

    return qte_op;
}

t_graphe* fichier_exclusion(char* nom_fichier,t_graphe *un_graphe){
    FILE *fichier = fopen(nom_fichier, "r");

    if(fichier == NULL){
        printf("erreur ouverture fichier exclusion.\n");
        exit(1);
    }

    int entier1, entier2;
    int nb_exclu = 0;

    fflush(stdin);
    // Lire deux entiers à partir de chaque ligne du fichier
    while (fscanf(fichier, "%d %d", &entier1, &entier2) == 2) {
        un_graphe->matrice_exclusions[entier1][entier2] = 1;
        un_graphe->matrice_exclusions[entier2][entier1] = 1;
        nb_exclu++;
    }

    un_graphe->nb_paires_exclusion = nb_exclu;

    return un_graphe;

}
