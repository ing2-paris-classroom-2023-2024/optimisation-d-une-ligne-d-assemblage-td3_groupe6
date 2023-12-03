#include "exclusion.h"
#include "precedence.h"

pFile initialisationFileVide() {
    pFile fileSommets;
    fileSommets = (pFile)malloc(sizeof(struct file));
    if (fileSommets == NULL) printf("erreur allocation fileVide");
    fileSommets->longueur = 0;
    fileSommets->tete = NULL;
    fileSommets->fin = NULL;
    return(fileSommets);
}

int longueurDeLaFile(pFile fileSommets) {
    if (fileSommets == NULL)
        printf("La file n'existe pas - longueur");
    return(fileSommets->longueur);
}

void enfiler(pFile fileSommets, int numSommet) {
    pMaillon unMaillon;

    if (fileSommets == NULL)
        printf ("La file n'existe pas - enfiler");

    unMaillon = (pMaillon)malloc(sizeof(pMaillon));
    if (unMaillon == NULL)
        printf("Erreur d'allocation memoire - enfiler");

    unMaillon->num = numSommet;
    unMaillon->suiv = NULL;
    if (longueurDeLaFile(fileSommets) == 0){
        fileSommets->tete = unMaillon;
        fileSommets->fin = unMaillon;
    }
    else {
        fileSommets->fin->suiv = unMaillon;
        fileSommets->fin = unMaillon;
    }
    ++(fileSommets->longueur);
}

int teteDeLaFile(pFile listeSommets) {
    if (listeSommets == NULL || longueurDeLaFile(listeSommets) == 0)
        printf("La file n'existe pas - tete");
    return(listeSommets->tete->num);
}

int defiler(pFile listeSommets) {
    pMaillon unMaillon;
    int numSommet;

    if (listeSommets == NULL || longueurDeLaFile(listeSommets) == 0)
        printf("La file n'existe pas - defiler");

    unMaillon = listeSommets->tete;
    numSommet = unMaillon->num;

    if (longueurDeLaFile(listeSommets) == 1){
        listeSommets->tete = NULL;
        listeSommets->fin = NULL;
    }
    else {
        listeSommets->tete = listeSommets->tete->suiv;
    }

    //free(unMaillon);
    --(listeSommets->longueur);
    return(numSommet);
}

void ecrireFile(pFile listeSommets) {
    pMaillon unMaillon;

    if (listeSommets == NULL)
        printf("Erreur ecrireFile - File null");
    unMaillon = listeSommets->tete;
    while (unMaillon != NULL) {
        printf("%d ", unMaillon->num);
        unMaillon = unMaillon->suiv;
    }
    printf("\n");
}

void debutParcoursBfs(t_graphe* graphe){
    int sommetMin = 0;
    int meilleurSommet = 0;
    int qualite = 0;

    while (graphe->tab_operations_reelles[sommetMin] != 1){
        sommetMin++;
    }

    int sommetInitial[graphe->num_operation_max];
    for (int i = sommetMin; i < graphe->num_operation_max; ++i) {
        sommetInitial[i]=1;
        graphe->tab_stations[i]->numeroStation = -1;
    }

    for (int i = sommetMin; i < graphe->num_operation_max; ++i) {
        if (graphe->tab_operations_reelles[i] == 1){
            t_arc *Temparc=graphe->tab_stations[i]->voisins;
            while (Temparc !=NULL){
                for (int j = 0; j < graphe->num_operation_max; ++j) {
                    if (j == Temparc->num_station){
                        sommetInitial[j]=0;
                    }
                }
                Temparc=Temparc->arc_suivant;
            }
        }
    }

    for (int i = sommetMin; i < graphe->num_operation_max; ++i) {
        if (graphe->tab_operations_reelles[i] != 1){
            sommetInitial[i] = 0;
        }
    }

    graphe->nb_stations++;
    t_station stationInitiale;

    stationInitiale.val_station = 0;
    graphe->tab_operations_reelles[stationInitiale.val_station] = 1;
    stationInitiale.couleur = 0;
    stationInitiale.marquage = 0;
    stationInitiale.degre = 0;
    stationInitiale.nb_operations = 0;
    stationInitiale.voisins = NULL;

    for (int i = stationInitiale.val_station; i < graphe->num_operation_max; ++i) {
        if (sommetInitial[i]==1){
            graphe->tab_stations = CreerArete(graphe->tab_stations, stationInitiale.val_station, i);
            graphe->tab_stations[stationInitiale.val_station]->degre++;
        }
    }

    parcoursBFS(graphe,stationInitiale.val_station,1);

    for (int i = sommetMin; i < graphe->num_operation_max; ++i) {
        graphe->tab_stations[i]->choixStation = 0;
    }

    int fin = 0;
    int station = 1;
    printf("\n\nStation avec contrainte de precedence : \n\n");
    while (fin == 0){
        printf("\n----------------------------------------------------------------------------------------\n\t\t\tstation %d\n",station-1);
        fin = 1;
        for (int i = sommetMin; i < graphe->num_operation_max; ++i) {
            if (graphe->tab_operations_reelles[i] == 1) {
                if (graphe->tab_stations[i]->numeroStation == station){
                    graphe->tab_stations[i]->numeroStation--;
                    printf(" %d\t", i);
                    graphe->tab_stations[i]->choixStation=1;
                }
            }
        }
        for (int i = sommetMin; i < graphe->num_operation_max; ++i) {
            if (graphe->tab_operations_reelles[i] == 1) {
                if (graphe->tab_stations[i]->choixStation == 0)
                    fin = 0;
            }
        }
        station++;
    }
    printf("\n\n");
}

int parcoursBFS(t_graphe * graphe, int numSommetInitial, int modeAffichage){
    //Initialisation de la couleur des sommets
    //N=Noir, deja vu.  B=Blanc a voir
    int i=0;
    int preds[graphe->num_operation_max];

    for (int j = 0; j < graphe->num_operation_max; ++j) {
        graphe->tab_stations[j]->choixStation = 0;
        if (graphe->tab_stations[j]->numeroStation == 0)
            graphe->tab_stations[j]->choixStation = 1;
    }

    pFile listeSommets = initialisationFileVide();

    for(i=0;i<graphe->num_operation_max;i++){
        graphe->tab_stations[i]->couleur='B';
        preds[i] = -1;
    }
    if (modeAffichage) preds[numSommetInitial]= -1;

    enfiler(listeSommets, numSommetInitial);

    while(longueurDeLaFile(listeSommets)){
        i=defiler(listeSommets);
        if(graphe->tab_stations[i]->couleur=='B'){
            t_arc *Temparc=graphe->tab_stations[i]->voisins;
            if(Temparc != NULL){
                enfiler(listeSommets,Temparc->num_station);
                preds[Temparc->num_station] = i;
                if (modeAffichage)
                while(Temparc->arc_suivant != NULL){
                    preds[Temparc->arc_suivant->num_station] = i;
                    if (modeAffichage)
                    Temparc=Temparc->arc_suivant;
                    enfiler(listeSommets,Temparc->num_station);
                }
            }
            graphe->tab_stations[i]->couleur='N';
        }
    }

    int station = 0;
    int fin = 0;

    while (fin == 0){
        fin = 1;
        for (int j = 0; j < graphe->num_operation_max; ++j) {
            if (preds[j] != -1){
                if (graphe->tab_stations[preds[j]]->numeroStation == station){
                    graphe->tab_stations[j]->numeroStation = station+1;
                    graphe->tab_stations[j]->choixStation = 1;
                }
            }
        }
        for (int j = 0; j < graphe->num_operation_max; ++j) {
            if (preds[j] != -1){
                if (graphe->tab_stations[j]->choixStation == 0)
                    fin = 0;
            }
        }
        station++;
    }
    return station;
}

t_graphe *creerGraphePrecedencce(int ordre){
    t_graphe * graphePrecedence;
    FILE * ifs = fopen("../precedence.txt","r");

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    int entier1 = 0;
    int entier2 = 0;

    graphePrecedence = creer_graphe(ordre); // créer le graphe d'ordre sommets

    // créer les arêtes du graphe
    while(fscanf(ifs, "%d %d", &entier1, &entier2) == 2){
        graphePrecedence->tab_stations = CreerArete(graphePrecedence->tab_stations, entier1, entier2);
        graphePrecedence->tab_stations[entier1]->degre++;
    }

    return graphePrecedence;
}