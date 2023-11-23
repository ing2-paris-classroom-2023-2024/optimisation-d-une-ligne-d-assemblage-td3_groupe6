//
// Created by eliot on 23/11/2023.
//
#include "eliott.h"

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
        printf("operation numero : %d\n",op);
        qte_op++;
    }

    return qte_op;
}

t_graphe* exclusion(char* nom_fichier,t_graphe *un_graphe){
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
        // Traiter les entiers lus ici
        printf("Entier 1 : %d, Entier 2 : %d\n", entier1, entier2);
        nb_exclu++;
    }

    ///algo d'exclusion

}
