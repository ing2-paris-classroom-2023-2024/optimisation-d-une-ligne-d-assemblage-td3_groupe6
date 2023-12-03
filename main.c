//
// Created by ccass on 27/11/2023.
//

#include <stdio.h>


int main() {
    int a = 0;
    printf("%d", a );
    return 0 ;

};

#define true 1
#define false 0
#define MAX_VERTICES 100

// Fonction pour imprimer la coloration du graphe
void printColoring(int coloring[], int V) {
    printf("Vertex\tColor\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, coloring[i]);
    }
}

// Fonction pour vérifier si la couleur 'c' peut être attribuée à un sommet 'v'
int isSafe(int v, int graph[MAX_VERTICES][MAX_VERTICES], int coloring[], int c, int V) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && c == coloring[i]) {
            return false;
        }
    }
    return true;
}

// Fonction récursive pour colorer le graphe en utilisant l'algorithme glouton
int graphColoringUtil(int graph[MAX_VERTICES][MAX_VERTICES], int m, int coloring[], int v, int V) {
    if (v == V) {
        // Tous les sommets ont été colorés
        return true;
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, coloring, c, V)) {
            coloring[v] = c;

            // Récursivement colorer les sommets restants
            if (graphColoringUtil(graph, m, coloring, v + 1, V)) {
                return true;
            }

            // Si l'attribution de la couleur 'c' ne conduit pas à une solution, essayer une autre couleur
            coloring[v] = 0;
        }
    }

    return false;
}

// Fonction principale pour colorer le graphe
void graphColoring(int graph[MAX_VERTICES][MAX_VERTICES], int m, int V) {
    int coloring[MAX_VERTICES];
    for (int i = 0; i < V; i++) {
        coloring[i] = 0;
    }

    if (!graphColoringUtil(graph, m, coloring, 0, V)) {
        printf("Impossible de colorer le graphe avec %d couleurs.\n", m);
    } else {
        printf("Le graphe peut être coloré avec %d couleurs.\n", m);
        printColoring(coloring, V);
    }
}

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int V; // Nombre de sommets
    Node** adjList; // Liste d'adjacence
} Graph;

Node* createNode(int data) {