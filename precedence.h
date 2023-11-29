#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

//structures pour une file dynamique implémentée par liste chainée

//structure pour un maillon
typedef struct maillon{
    //numéro du sommet
    int num;
    //pointeur sur le maillon suivant
    struct maillon *suiv;
}t_maillon;

typedef struct maillon* pMaillon;

//structure regroupant les ancres de tete et de fin de liste
typedef struct file{
    pMaillon tete; //pointeur sur le premier maillon
    pMaillon fin; //pointeur sur le dernier maillon
    int longueur;
}t_file;

typedef struct file* pFile;

//sous-programme qui enfile (ajoute) un nouveau numéro (de sommet)
void enfiler(pFile fileSommets,int numSommet);

//sous-programme qui défile (supprime et retourne)
//le prochain numéro de la file
int defiler(pFile fileSommets);

// création d'une file vide
pFile initialisationFileVide();
int longueurDeLaFile(pFile fileSommets);
int teteDeLaFile(pFile listeSommets);
void ecrireFile(pFile listeSommets);
void debutParcoursBfs(t_graphe* graphe);
int parcoursBFS(t_graphe * graphe, int numSommetInitial, int modeAffichage);

#endif // FILE_H_INCLUDED
