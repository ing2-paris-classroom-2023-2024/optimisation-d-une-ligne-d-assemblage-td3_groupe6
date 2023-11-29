#include "eliott.h"
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
    while (graphe->tab_perations_reelles[sommetMin] != 1){
        sommetMin++;
    }
    int sommetInitial[graphe->num_operation_max];
    for (int i = sommetMin; i < graphe->num_operation_max; ++i) {
        sommetInitial[i]=1;
        graphe->tab_stations[i]->numeroStation = -1;
    }
    for (int i = sommetMin; i < graphe->num_operation_max; ++i) {
        if (graphe->tab_perations_reelles[i] == 1){
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
        if (graphe->tab_perations_reelles[i] != 1){
            sommetInitial[i] = 0;
        }
    }
    for (int i = sommetMin; i < graphe->num_operation_max; ++i) {
        if (sommetInitial[i] == 1){
            graphe->tab_stations[i]->numeroStation = 0;
            if (qualite <= parcoursBFS(graphe,i,1)){
                qualite = parcoursBFS(graphe,i,1);
                meilleurSommet = i;
            }
        }
    }
    for (int i = sommetMin; i < graphe->num_operation_max; ++i) {
        graphe->tab_stations[i]->numeroStation = -1;
    }
    graphe->tab_stations[meilleurSommet]->numeroStation = 0;
    parcoursBFS(graphe,meilleurSommet,1);
    for (int i = sommetMin; i < graphe->num_operation_max; ++i) {
        if (sommetInitial[i] == 1)
            graphe->tab_stations[i]->numeroStation = 0;
        if (graphe->tab_perations_reelles[sommetMin] == 1)
            printf("operation %d station %d\n",i,graphe->tab_stations[i]->numeroStation);
    }
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
    if (modeAffichage) preds[numSommetInitial]= 0;

    if (modeAffichage) {
        printf("\n******* PARCOURS BFS - Ordre de decouverte des sommets depuis (%d) *******\n", numSommetInitial);
        printf("\t%d", numSommetInitial);
    }
    enfiler(listeSommets, numSommetInitial);

    while(longueurDeLaFile(listeSommets)){
        i=defiler(listeSommets);
        if(graphe->tab_stations[i]->couleur=='B'){
            t_arc *Temparc=graphe->tab_stations[i]->voisins;
            if(Temparc!=NULL){
                enfiler(listeSommets,Temparc->num_station);
                if (preds[Temparc->num_station] == -1) {
                    preds[Temparc->num_station] = i;
                    if (modeAffichage)
                        printf(" ;\t%d ----> %d",i,Temparc->num_station);
                }
                while(Temparc->arc_suivant!=NULL){
                    if (preds[Temparc->arc_suivant->num_station] == -1){
                        preds[Temparc->arc_suivant->num_station] = i;
                        if (modeAffichage)
                            printf(" ;\t%d ----> %d",i,Temparc->arc_suivant->num_station);
                    }
                    Temparc=Temparc->arc_suivant;
                    enfiler(listeSommets,Temparc->num_station);
                }
            }
            //printf("(%d) ",graphe->pSommet[i]->valeur);
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

/*
    if (modeAffichage) {
        printf("\nIl n y aucun chemin du sommet (%d) vers les sommets suivants : ", numSommetInitial);
        for (int j = 0; j < graphe->num_operation_max; ++j) {
            if ((preds[j] == -1) && (j != numSommetInitial))
                printf("%d ; ", j);
        }
        if (preds[numSommetFinal] == -1)
            printf("\nIl n y a aucun chemin pour aller au sommet (%d) depuis le sommet (%d)", numSommetFinal,
                   numSommetInitial);
        else {
            int numSommetParcouru = numSommetFinal;
            printf("\nChemin BFS pour aller au sommet (%d) depuis le sommet (%d) : %d", numSommetFinal,
                   numSommetInitial, numSommetParcouru);
            while (numSommetParcouru != numSommetInitial) {
                printf(" <---- %d ", preds[numSommetParcouru]);
                numSommetParcouru = preds[numSommetParcouru];
            }
        }
    }*/
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