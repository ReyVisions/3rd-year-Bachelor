#include <stdio.h>
#include <stdlib.h>

#include "matriceAdjacence.c"


int main(){
    int nbsommets;
    do{
        printf("Saisissez le nombre de sommets pour la matrice d'adjacence : ");
        fflush(stdout);
        scanf("%d",&nbsommets);
    }while(nbsommets<0);
    int** matrice=adjacence(nbsommets);
    afficherAdjacence(matrice,nbsommets);

    //Liberation de la memoire
    for (int i = 0; i < nbsommets; i++) {
        free(matrice[i]);
    }
    free(matrice);
    return(0);
}