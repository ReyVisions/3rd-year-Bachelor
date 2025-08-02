#include <stdio.h>
#include <stdlib.h>

int **adjacence(int nbsommets){
    int **ptr;

    ptr = (int**)malloc(nbsommets * sizeof(*ptr));
    if(ptr == NULL){
        exit(EXIT_FAILURE);
    }

    for(int i=0 ; i < nbsommets ; i++){
        ptr[i] = malloc(nbsommets * sizeof(int));
        if(ptr[i] == NULL){
            for(i = i-1 ; i >= 0 ; i--)
                free(ptr[i]);
            free(ptr);
            exit(EXIT_FAILURE);
        }
        for (int j=0;j<nbsommets;j++){
            ptr[i][j]=0;
        }
        
    }
    int val;
    for (int i=0;i<nbsommets;i++){
        for (int j=0;j<nbsommets;j++){
            do{
                printf("Saisissez une valeur 0 ou 1 pour %d,%d : ",i,j);
                fflush(stdout);
                scanf("%d",&val);

            }while(val!=0 &&val!=1);
            ptr[i][j]=val;
        }
    } 
    return(ptr);
}

void afficherAdjacence(int** matrice,int nbsommets){                      //afficher la matrice
	printf("\nVoici la matrice :");
    fflush(stdout);
    printf("\n[");
    fflush(stdout);
	for (int i=0; i<nbsommets;i++){
		printf("[");
		fflush(stdout);
		for (int j=0; j<nbsommets;j++){
            if (j==nbsommets-1){
                printf("%d",matrice[i][j]);
			    fflush(stdout);
            }else{
			    printf("%d,",matrice[i][j]);
			    fflush(stdout);
            }
		}
        if (i==nbsommets-1){
            printf("]");
            fflush(stdout);
        }else{
            printf("]\n");
            fflush(stdout);
        }        
	}
    printf("]");
    fflush(stdout);
}