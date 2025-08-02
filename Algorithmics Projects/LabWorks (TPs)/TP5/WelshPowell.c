#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "WelshPowell.h"
#define MAX_VERTICES 100000

void initGraph(Graph* graph, long val) {
    graph->vertices = val;
    graph->adjMatrix = (int**) malloc(val * sizeof(int*));
    if (graph->adjMatrix == NULL) {
        printf("Erreur d'allocation de mémoire pour graph->adjMatrix.\n");
        exit(1); // Quitte le programme avec un code d'erreur
    }

    for (long i = 0; i < val; i++) {
        graph->adjMatrix[i] = (int*) malloc(val * sizeof(int));
        if (graph->adjMatrix[i] == NULL) {
            printf("Erreur d'allocation de mémoire pour graph->adjMatrix[%ld].\n", i);
            exit(1); // Quitte le programme avec un code d'erreur
        }
    }

    for (long i = 0; i < val; i++) {
        for (long j = 0; j < val; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
}

void clearGraph(Graph* graph) {
    for (long i = 0; i < graph->vertices; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
}
void addEdge(Graph* graph, int u, int v) {
    graph->adjMatrix[u][v] = 1;
    graph->adjMatrix[v][u] = 1;
}

void welshPowell(Graph* graph) {

    clock_t start_time, end_time;
    double cpu_time_used;

    // Enregistre le temps de début
    start_time = clock();

    long degree[MAX_VERTICES] = {0};
    long i, j; 
    int current_color;

    // Calculate the degree of each vertex
    for (i = 0; i < graph->vertices; i++) {
        for (j = 0; j < graph->vertices; j++) {
            if (graph->adjMatrix[i][j] == 1)
                degree[i]++;
        }
    }

    int sorted_vertices[MAX_VERTICES];

    // Initialize vertices in sorted order of degrees
    for (i = 0; i < graph->vertices; i++)
        sorted_vertices[i] = i;
    
    // Sort vertices in decreasing order of degree using bubble sort
    for (i = 0; i < graph->vertices - 1; i++) {
        for (j = 0; j < graph->vertices - i - 1; j++) {
            if (degree[sorted_vertices[j]] < degree[sorted_vertices[j + 1]]) {
                int temp = sorted_vertices[j];
                sorted_vertices[j] = sorted_vertices[j + 1];
                sorted_vertices[j + 1] = temp;
            }
        }
    }

    long color[MAX_VERTICES] = {-1};
    for (int l=0;l<graph->vertices;l++){
        color[l]=-1;
    }

    current_color = 0;
    color[sorted_vertices[0]] = current_color;
    // Assign colors to the remaining vertices
    while(current_color<graph->vertices){
        for (i = 1; i < graph->vertices; ++i) {
            long vertex = sorted_vertices[i];
            if (color[vertex] == -1) {
                int uncolored_adjacent = 1;
                for (j = 0; j < graph->vertices; j++) {
                    if (graph->adjMatrix[vertex][j] == 1 && color[j] == current_color) {
                        uncolored_adjacent = 0;
                        break;
                    }
                } 
                // Assign a different color to the uncolored adjacent vertices
                if (uncolored_adjacent==1) {
                    color[vertex] = current_color;
                }/* else {
                    current_color++;
                    color[vertex] = current_color;
                }*/
            }
        }
        current_color++;
    }
    long max=color[0];
    for (long p=0;p<graph->vertices-1;p++){
        if (max<color[p+1]){
            max=color[p+1];
        }
    }

    long num_colors = max + 1;


    for (i = 0; i < graph->vertices; i++) { 
        printf("Vertex %d: Color %d\n", i, color[i]);
        fflush(stdout);
    }    
    printf("\nGraph colored using %d colors:\n", num_colors);
    fflush(stdout);

    // Enregistre le temps de fin et calcule le temps
    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Le programme a pris %f secondes pour s'executer.\n", cpu_time_used);
}
//TODO:
//generer uniquement un triangle inferieur.
//Trouver pourquoi ca n'affiche plus rien.
void addEdgeRandom(Graph* graph){
    srand(time(NULL));
    for (long i=0;i<graph->vertices;i++){
        for (long j=0;j<=i;j++){
            if (i==j){
                graph->adjMatrix[i][j]=0;
            }
            else{
                int randomNum = rand()%2;
                graph->adjMatrix[i][j] = randomNum;
                graph->adjMatrix[j][i] = randomNum;
            }
        }
    }
}
void afficherAdjacence(long nbsommets, int** matrice) {
    printf("\nVoici la matrice d'adjacence du graphe. :");
    fflush(stdout);
    printf("\n[");
    fflush(stdout);
    for (long i = 0; i < nbsommets; i++) {
        printf("[");
        fflush(stdout);
        for (long j = 0; j < nbsommets; j++) {
            if (j == nbsommets - 1) {
                printf("%d", matrice[i][j]);
                fflush(stdout);
            } else {
                printf("%d,", matrice[i][j]);
                fflush(stdout);
            }
        }
        if (i == nbsommets - 1) {
            printf("]");
            fflush(stdout);
        } else {
            printf("]\n");
            fflush(stdout);
        }
    }
    printf("]");
    fflush(stdout);
}