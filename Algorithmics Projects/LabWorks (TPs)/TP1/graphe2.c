#include <stdio.h>
#include <stdlib.h>
#include "graphe2.h"

#define VOISINSMAX 5
#define SOMMETSMAX 10

void initGraphe(Graphe *graphe){
    graphe->taille=0;
    noeud* sommets[SOMMETSMAX];
}

int SommetExiste(char name, Graphe* graphe){
    int i=0;
    if (graphe->taille!=0){
        for (i=0;i<graphe->taille;i++){
            noeud* node=graphe->sommets[i];
            if (node->nom==name){
                return(i);
            };
        }
        return(-1);
    }
    else{return(-1);}
}

void creerSommet(char name, Graphe* graphe){
    if (SommetExiste(name,graphe)==-1){
        noeud* node = (noeud*) malloc(sizeof(noeud));
        for (int i=0;i<VOISINSMAX;i++){
            node->voisins[i]=(noeud*) malloc(sizeof(noeud));
        }
        node->nom = name;
        graphe->sommets[graphe->taille]=node;
        graphe->taille+=1;
        node->nbVoisins=0;
    }else{
        printf("\nLe sommet existe deja!");
        fflush(stdout);
    }
}



void lierDeuxSommets(char nomNode1, char nomNode2, Graphe* graphe){
    int taille=graphe->taille;
    int i=0;
    int indice1,indice2;
    noeud* node1;
    noeud* node2;
    printf("\nOn essaie de lier les deux arretes :");
    fflush(stdout);
    if (nomNode1==nomNode2){
        //Pour traiter le cas ou on veut faire une arrete sur le sommet lui meme
        indice1=SommetExiste(nomNode1,graphe);
        indice2=indice1;
    }else{
        indice1=SommetExiste(nomNode1,graphe);
        indice2=SommetExiste(nomNode2,graphe); 
    }
    if (indice1==-1){
        printf(" [%c,",nomNode1);
        fflush(stdout);
        node2=graphe->sommets[indice2];
        printf("%c]",nomNode2);
        fflush(stdout); 
        printf("\nMais %c n'existe pas...",nomNode1);
        fflush(stdout);
    }
    else if(indice2==-1){
        printf(" [%c,",node1->nom);
        fflush(stdout);
        node2=graphe->sommets[indice2];
        printf("%c]",node2->nom);
        fflush(stdout); 
        printf("\nMais %c n'existe pas...",nomNode2);
        fflush(stdout);
    }
    else if (nomNode1==nomNode2){
        node1=graphe->sommets[indice1];
        printf(" [%c,%c]",node1->nom,node1->nom);
        fflush(stdout);
        node1->voisins[node1->nbVoisins]=node1;
        node1->nbVoisins+=1;
    } 
    else{
        node1=graphe->sommets[indice1];
        //Si on enleve ces prints, le programme n'affiche plus le graphe.
        printf(" [%c,",node1->nom);
        fflush(stdout);
        node2=graphe->sommets[indice2];
        printf("%c]",node2->nom);
        fflush(stdout); 
        node1->voisins[node1->nbVoisins]=node2;
        node2->voisins[node2->nbVoisins]=node1;
        node1->nbVoisins+=1;
        node2->nbVoisins+=1;
    }
}
void afficherGraphe(Graphe* graphe){
    if (graphe->taille!=0){
            printf("\n[");
            fflush(stdout);    
        for (int i=0;i<graphe->taille;i++){
            noeud* node=graphe->sommets[i];
            printf("%c",node->nom);
            fflush(stdout);
            printf("[");
            fflush(stdout);
            for (int j=0;j<node->nbVoisins;j++){
                if (j<node->nbVoisins-1){
                    printf("%c,",node->voisins[j]->nom);
                    fflush(stdout); 
                }else{
                    printf("%c",node->voisins[j]->nom);
                    fflush(stdout); 
                }
            }if (i<graphe->taille-1){
            printf("],");
            fflush(stdout);   
            }else{
                printf("]");
                fflush(stdout);  
            }
        }
        printf("]\n");
        fflush(stdout); 
    }
    else{
        printf("\nLe graphe est vide.");
        fflush(stdout);
    }
 
}   

Graphe* chargeGraphe(){
    Graphe* graphe= (Graphe*) malloc(sizeof(Graphe));
	initGraphe(graphe);

    int val;
    int nbsommets;
    do{
        printf("Saisissez le nombre de sommets pour la matrice d'adjacence : ");
        fflush(stdout);
        scanf("%d",&nbsommets);
    }while(nbsommets<0);
    for (int i=0;i<nbsommets;i++){
        char nom=i+'0';
        creerSommet(nom,graphe);
    } 
    for (int i=0;i<nbsommets;i++){
        for (int j=0;j<nbsommets;j++){
            do{
                printf("Saisissez une valeur 0 ou 1 pour %d,%d : ",i,j);
                fflush(stdout);
                scanf("%d",&val);

            }while(val!=0 &&val!=1);
            if (val==1){
                noeud* node1=graphe->sommets[i];
                noeud* node2=graphe->sommets[j];
                node1->voisins[node1->nbVoisins]=node2;
                node1->voisins[node1->nbVoisins]->nom=node2->nom;
                node1->nbVoisins+=1;
            }
        }
    }
    return(graphe);

}