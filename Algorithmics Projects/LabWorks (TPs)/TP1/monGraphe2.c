#include<stdio.h>
#include<stdlib.h>

#include "graphe2.c"

int main(){	
	printf("On charge la matrice en BFS : \n"); 
	fflush(stdout);
	Graphe* graphe= chargeGraphe(graphe);
	printf("\n\nOn affiche le graphe sous forme de liste d'adjacence: ");
	fflush(stdout);
	afficherGraphe(graphe);
	free(graphe);
	return(0);
}

