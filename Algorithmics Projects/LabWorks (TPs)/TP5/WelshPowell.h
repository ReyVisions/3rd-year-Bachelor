#ifndef WELSHPOWELL_H_
#define WELSHPOWELL_H_

#define MAX_VERTICES 100000


typedef struct Graph {
    int vertices;
    int **adjMatrix;
}Graph;

void addEdge(Graph* graph, int u, int v);

void welshPowell(Graph* graph);

void addEdgeRandom(Graph* graph);

void afficherAdjacence(long nbsommets, int** matrice);

#endif /* WELSHPOWELL_H_ */