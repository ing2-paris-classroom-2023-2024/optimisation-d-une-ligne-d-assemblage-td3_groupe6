//
// Created by eliot on 23/11/2023.
//
#include "eliott.h"

int* creation_tab_op_reelles(char *nom_fichier, t_graphe* un_graphe){
    FILE *fp = fopen(nom_fichier,"r");
    un_graphe->tab_perations_reelles = malloc((un_graphe->num_operation_max) * sizeof(int));

    for(int i = 0; i < un_graphe->num_operation_max;i++){
        un_graphe->tab_perations_reelles[i] = -1;
    }

    if(fp == NULL){
        printf("erreur ouverture fichier operations reelles.\n");
        exit(1);
    }

    int op = 0;
    float temps = 0;

    while(fscanf(fp,"%d%f",&op,&temps) == 2){
        un_graphe->tab_perations_reelles[op] = 1;
    }

    return un_graphe->tab_perations_reelles;
}


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

t_graphe* gestion_donnees_graphe(int nb_operations, int op_max,char* file_name){
    t_graphe *un_graphe = malloc(sizeof(t_graphe));

    if(un_graphe == NULL){
        printf("erreur alloc graphe\n");
        exit(1);
    }

    un_graphe->ordre_sous_graphe = 0;
    un_graphe->num_operation_max = op_max;
    un_graphe->tab_stations = malloc((op_max + 1) * sizeof (t_station*));
    un_graphe->nb_stations = 0;
    un_graphe->nb_paires_exclusion = 0;
    un_graphe->matrice_exclusions = malloc((op_max  + 1) * sizeof(int*));

    for(int i = 0; i < op_max + 1;i++){
        un_graphe->matrice_exclusions[i] = malloc((op_max + 1) * sizeof(int));
        un_graphe->tab_stations[i] = malloc(sizeof(t_station));
        un_graphe->tab_stations[i]->val_station = i;
        un_graphe->tab_stations[i]->voisins = NULL;
        un_graphe->tab_stations[i]->couleur = 0;
        un_graphe->tab_stations[i]->marquage = 0;
    }

    for(int i = 0; i < op_max + 1;i++){
        for(int j = 0; j < op_max + 1;j++){
            un_graphe->matrice_exclusions[i][j] = 0;
        }
    }

    return un_graphe;
}

t_graphe *creer_graphe(int op_max){
    t_graphe *nv_graphe = (t_graphe*)malloc(sizeof(t_graphe));

    if(nv_graphe == NULL){
        printf("erreur d allocation graphe creation.\n");
        exit(1);
    }

    nv_graphe->num_operation_max = op_max + 1;
    nv_graphe->nb_stations = 0;
    nv_graphe->ordre_sous_graphe = 0;
    nv_graphe->sous_sommets = malloc(nv_graphe->num_operation_max * sizeof(int));
    nv_graphe->tab_stations = (t_station **)malloc(nv_graphe->num_operation_max * sizeof(t_station *));

    for(int i = 0;i < nv_graphe->num_operation_max;i++){
        nv_graphe->tab_stations[i] = malloc(sizeof(t_station));
        nv_graphe->sous_sommets[i] = -1;
        nv_graphe->tab_stations[i]->voisins = NULL;
        nv_graphe->tab_stations[i]->val_station = i;
        nv_graphe->tab_stations[i]->couleur = 0;
        nv_graphe->tab_stations[i]->marquage = 0;
        nv_graphe->tab_stations[i]->degre = 0;
        nv_graphe->tab_stations[i]->nb_operations = 0;
    }

    return nv_graphe;
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

    while(fscanf(fichier, "%d %d", &entier1, &entier2) == 2){
        un_graphe->tab_stations = CreerArete(un_graphe->tab_stations, entier2, entier1);
        un_graphe->tab_stations[entier2]->degre++;
        un_graphe->tab_stations = CreerArete(un_graphe->tab_stations, entier1, entier2);
        un_graphe->tab_stations[entier1]->degre++;
        nb_exclu++;
    }

    un_graphe->nb_paires_exclusion = nb_exclu;

    return un_graphe;
}


t_station** CreerArete(t_station** tab_stations, int station_1, int station_2)
{
    if(tab_stations[station_1]->voisins == NULL)
    {
        t_arc *Newarc=(t_arc*)malloc(sizeof(t_arc));
        Newarc->num_station = station_2;
        Newarc->arc_suivant = NULL;
        tab_stations[station_1]->voisins = Newarc;
        return tab_stations;
    }

    else
    {
        t_arc* temp = tab_stations[station_1]->voisins;

        while(temp->arc_suivant != NULL)
        {
            temp=temp->arc_suivant;
        }

        t_arc *Newarc=(t_arc*)malloc(sizeof(t_arc));
        Newarc->num_station = station_2;
        Newarc->arc_suivant = NULL;

        if(temp->num_station > station_2)
        {
            Newarc->arc_suivant = temp->arc_suivant;
            Newarc->num_station = temp->num_station;
            temp->num_station = station_2;
            temp->arc_suivant = Newarc;
            return tab_stations;
        }

        temp->arc_suivant = Newarc;
        return tab_stations;
    }
}

t_graphe *init_graphe_station(int nb_stations){
    t_graphe *nv_graphe = malloc(sizeof(t_graphe));

    if(nv_graphe == NULL){
        printf("erreur alloc init graphe\n");
        exit(1);
    }

    nv_graphe->nb_stations = nb_stations;
    nv_graphe->tab_stations = malloc(nb_stations * sizeof(t_station*));

    for(int i = 0; i < nv_graphe->nb_stations;i++){
        nv_graphe->tab_stations[i] = malloc(sizeof(t_station));
        nv_graphe->tab_stations[i]->voisins = NULL;
        nv_graphe->tab_stations[i]->val_station = i;
        nv_graphe->tab_stations[i]->nb_operations = 0;
    }

    return nv_graphe;

}

t_graphe *creation_graphe_stations(t_graphe* graphe_exclusion){


    t_graphe *graphe_stations = init_graphe_station(graphe_exclusion->nb_stations);
    graphe_stations->num_operation_max = graphe_exclusion->num_operation_max;

    for(int i = 0; i < graphe_stations->nb_stations;i++){
        graphe_stations->tab_stations[i]->tab_operations = malloc(graphe_exclusion->num_operation_max * sizeof(int));
        for(int j = 0; j < graphe_exclusion->num_operation_max;j++){

            if(j == 0)
                continue;

            if(graphe_exclusion->tab_stations[j]->couleur == i){
                graphe_stations->tab_stations[i]->nb_operations++;
            }
        }
    }

    for(int i = 0; i < graphe_stations->nb_stations;i++){
        for(int j = 0; j < graphe_exclusion->num_operation_max;j++){
            graphe_stations->tab_stations[i]->tab_operations[j] = -1;
        }
    }

    for(int i = 0; i < graphe_stations->nb_stations;i++){
        for(int j = 0; j < graphe_exclusion->num_operation_max;j++){

            if(j == 0)
                continue;

            if(graphe_exclusion->tab_stations[j]->couleur == i){
                graphe_stations->tab_stations[i]->tab_operations[j] = j;
            }
        }
    }

    int i = 0;

    while(i < graphe_stations->nb_stations - 1){
        graphe_stations->tab_stations = CreerArete(graphe_stations->tab_stations, i, i + 1);
        i++;
    }

    Affichage_stations(graphe_stations);

    return graphe_stations;
}

void afficher_successeurs(t_station** sommet, int num)
{

    printf("station %d : couleur : %d\n",num, sommet[num]->couleur);

    t_arc* arc = sommet[num]->voisins;

    while(arc != NULL)
    {
        printf("%d ",arc->num_station);
        arc = arc->arc_suivant;
    }
}

void graphe_afficher(t_graphe* graphe)
{
    printf("listes d'adjacence :\n");

    for (int i=0; i < graphe->num_operation_max; i++)
    {
        afficher_successeurs(graphe->tab_stations, i);
        printf("\n");
    }
}

void Affichage_stations(t_graphe* un_graphe){
    printf("\n-----------------------Graphe de stations-----------------------\n");

    for(int i = 0; i < un_graphe->nb_stations;i++){
        t_arc *temp = un_graphe->tab_stations[i]->voisins;
        printf("station %d : \n", i);
        printf("reliee vers station : ");

        if(temp == NULL)
            printf("station de fin\n");

        while(temp != NULL){
            printf("%d",temp->num_station);
            temp = temp->arc_suivant;
        }

        printf("\noperations executees : ");
        for(int j = 0; j < un_graphe->num_operation_max;j++){
            if(un_graphe->tab_stations[i]->tab_operations[j] > 0)
                printf("[%d]", un_graphe->tab_stations[i]->tab_operations[j]);
        }
        printf("\n\n");
    }
}

void DFS(t_graphe *un_graphe, t_graphe * sous_graphe, int s){

    if(un_graphe->tab_stations[s]->marquage == 0){///si le sommet est pas découvert alors on affiche son numéro et on le marque
        un_graphe->ordre_sous_graphe++;
        un_graphe->tab_stations[s]->marquage = 1;
        sous_graphe->tab_stations[s] = un_graphe->tab_stations[s];

        t_arc* Temparc = un_graphe->tab_stations[s]->voisins;///on accède à un sommet adjacent de notre sommet

        while(Temparc!=NULL){
            DFS(un_graphe, sous_graphe,Temparc->num_station);///appel récrusif de DSF depuis le sommet adjacent de notre sommet précédent
            Temparc = Temparc->arc_suivant;///on passe au sommet adjacent suivant
        }
    }
}

void ColorationGlouton(t_graphe* graphe){
    // Créer un tableau d'indices pour représenter l'ordre des sommets
    int* indices = (int*)malloc(graphe->num_operation_max * sizeof(int));
    for(int i = 0; i < graphe->num_operation_max; i++){
        indices[i] = i;
    }

    // Trie les indices par degré décroissant
    for(int i = 0; i < graphe->num_operation_max; i++){
        for (int j = i + 1; j < graphe->num_operation_max; j++){
            if(graphe->tab_stations[indices[j]]->degre > graphe->tab_stations[indices[i]]->degre){
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Coloration gloutonne
    for(int i = 0; i < graphe->num_operation_max; i++){
        t_station* sommet = graphe->tab_stations[indices[i]];
        int couleur_disponible = 0;

        // Trouver la première couleur disponible
        while(1){
            int couleur_valide = 1;
            t_arc* voisin = sommet->voisins;

            // Vérifier les couleurs des voisins
            while(voisin != NULL){
                if(graphe->tab_stations[voisin->num_station]->couleur == couleur_disponible) {
                    couleur_valide = 0;
                    break;
                }
                voisin = voisin->arc_suivant;
            }

            if(couleur_valide){
                sommet->couleur = couleur_disponible;
                break;
            }

            couleur_disponible++;
        }
    }

    // Libérer la mémoire allouée pour le tableau d'indices
    free(indices);
}

int nb_mini_stations_exclu(t_graphe *un_graphe){

    t_graphe *sous_graphe;
    int nb_stations = 0;

    for(int c = 1; c < un_graphe->num_operation_max; c++){
        sous_graphe = creer_graphe(un_graphe->num_operation_max);

        un_graphe->ordre_sous_graphe = 0;

        for(int i = 0; i < un_graphe->num_operation_max;i++){
            un_graphe->sous_sommets[i] = -1;
        }

        if(un_graphe->tab_stations[c]->marquage == 1 || un_graphe->tab_perations_reelles[c] < 0 || un_graphe->tab_stations[c]->voisins == NULL)
            continue;

        else {
            DFS(un_graphe, sous_graphe, c);

            for (int i = 0; i < un_graphe->num_operation_max; i++) {
                sous_graphe->tab_stations[i]->marquage = un_graphe->tab_stations[i]->marquage;
            }

            ColorationGlouton(sous_graphe);
        }
    }

    for(int i = 0; i < un_graphe->num_operation_max;i++){
        if(nb_stations < un_graphe->tab_stations[i]->couleur){
            nb_stations = un_graphe->tab_stations[i]->couleur;
        }
    }

    return nb_stations + 1;
}

