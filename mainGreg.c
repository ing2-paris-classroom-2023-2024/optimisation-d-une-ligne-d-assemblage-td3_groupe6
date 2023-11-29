//
// Created by grego on 26/11/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_valid(int graph[5][5], int vertex, int color) {
    for (int i = 0; i < 5; i++) {
        if (graph[vertex][i] == 1 && color == graph[i][5]) {
            return false;
        }
    }
    return true;
}

bool graph_coloring(int graph[5][5], int colors[5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            if (is_valid(graph, i, j)) {
                colors[i] = j;
                break;
            }
            if (j == 3) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int graph[5][5] = {{0, 1, 1, 0, 0},
                       {1, 0, 1, 0, 0},
                       {1, 1, 0, 1, 0},
                       {0, 0, 1, 0, 1},
                       {0, 0, 0, 1, 0}};
    int colors[5];

    if (graph_coloring(graph, colors)) {
        printf("graph colore avec cette couleur:\n");
        for (int i = 0; i < 5; i++) {
            printf("Vertex %d: %d\n", i, colors[i]);
        }
    } else {
        printf("ne peux pas etre colore.\n");
    }

    return 0;
}