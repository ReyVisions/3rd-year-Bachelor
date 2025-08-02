#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Prim.h"

#define INFINI 1000.0
#define PROFONDEUR 5

DListe *prim (float **adjacencePoids, int ordre) {
    // Variables locales
    DListe *arbre ; // arbre d’incidence noeud-arc de poids minimum à retourner
    int indiceA = 0 ; // indice de l’arbre initialisé à 0
    int *marques ; // tableau dynamique indiquant si les sommets sont marqués ou non
    int s, x, y, ymin ; // numéros de sommets intermédiaires
    float min ; // distance minimale du prochain sommet à marquer
    // Allouer l’arbre de « ordre-1 » arêtes et le tableau marque de « ordre » entiers
    arbre= (DListe*) malloc(sizeof(DListe));
    initDliste(arbre);

    marques=(int*)malloc(ordre*sizeof(int));
    // Initialiser le marquage des sommets à 0

    for (x=0 ; x<ordre ; x++) {
        marques[x] = 0 ;
    }
    // Choisir un sommet s aléatoirement compris entre 0 et ordre-1
    s = rand()%ordre ;
    // Marquer le sommet aléatoire s
    marques[s] = 1 ;

    

    // Ce tableau d'entier stockera les valeurs des sommets, a l'indice correspondant a son ordre.
    int *places=(int*)malloc(ordre*sizeof(int));
    // Initialiser le marquage des sommets à 0

    for (x=0 ; x<ordre ; x++) {
        places[x] = 0 ;
    }
    places[0]=s; //le sommet s est place a la racine (ordre0).
    int xmin=0;
    //tant que les arêtes de l’arbre ne sont pas toutes traitées
    while (indiceA<ordre-1) {
    // Initialiser la longueur minimale à l’INFINI
        min = INFINI ;
        // Pour tous les sommets x marqués
        // Chercher le sommet de longueur minimale « ymin » adjacent à x
        // et non marqué
        for (x=0 ; x<ordre ; x++)
            if (marques[x])
                for (y=0 ; y<ordre ; y++)
                    if (adjacencePoids[x][y] && !marques[y] && adjacencePoids[x][y]<min) {
                        min = adjacencePoids[x][y] ; // poids min
                        ymin = y ; // sommet y de poids min
                        xmin=x;
                    }
        // marquer le sommet « ymin » de longueur minimale
        marques[ymin] = 1 ; 

        // Insérer l’arête (x, ymin) de longueur min à la position « indiceA » de l’arbre
        remplirDListe(xmin,ymin,min,arbre);
        // Passer à l’arête suivante de l‘arbre
        indiceA++ ;
    }
    return arbre ; // retourner l’arbre de poids minimum
}

float** matriceAdjPoids(int ordre) {

    float** adjacencePoids = (float**)malloc(ordre * sizeof(float*));

    for (int i = 0; i < ordre; i++) {
        adjacencePoids[i] = (float*)malloc(ordre * sizeof(float));
        for (int j = 0; j < ordre; j++) {
            printf("\nVeuillez saisir la valeur en float des coordonees %d,%d de la matrice",i,j);
            fflush(stdout);
            scanf("%f",&adjacencePoids[i][j]);
            fflush(stdin);
        }
    }

    return(adjacencePoids);
}
void afficherAdjacence(float** matrice,int nbsommets){                      //afficher la matrice
	printf("\nVoici la matrice d'adjacence de poids :");
    fflush(stdout);
    printf("\n[");
    fflush(stdout);
	for (int i=0; i<nbsommets;i++){
		printf("[");
		fflush(stdout);
		for (int j=0; j<nbsommets;j++){
            if (j==nbsommets-1){
                printf("%f",matrice[i][j]);
			    fflush(stdout);
            }else{
			    printf("%f,",matrice[i][j]);
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

void initDliste(DListe *dliste){
    dliste->taille=0;
    dliste->debut=(noeud*) malloc(sizeof(noeud));
    dliste->fin=(noeud*) malloc(sizeof(noeud));
    dliste->debut=NULL;
    dliste->fin=NULL;
}

void ajoutNoeudDebut(int val1, int val2,int poids,DListe *dliste){
    //Verification si la liste est bien initialisee
    

    if (!dliste){
        printf("La liste doublement chainee n'a pas ete initialisee");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    noeud *node;
    node = (noeud*) malloc(sizeof(noeud));
    
    node->x=val1;
    node->ymin=val2;
    node->poids=poids;
    node->pred=NULL;
    
    node->suiv=dliste->debut;

    if (dliste->debut!=NULL){
        dliste->debut->pred=node;
    }else{
        dliste->fin=node;
    }
    dliste->debut=node;
    dliste->taille+=1;
    
}

void ajoutNoeudFin(int val1, int val2, int poids, DListe *dliste){
    //Verification si la liste est bien initialisee
    if (!dliste){
        printf("La liste doublement chainee n'a pas ete initialisee");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    noeud *node;
    node = (noeud*) malloc(sizeof(noeud));

    node->x=val1;
    node->ymin=val2;
    node->poids=poids;
    node->suiv=NULL;

    node->pred=dliste->fin;

    if (dliste->fin!=NULL){
        dliste->fin->suiv=node;
    }else{
        dliste->debut=node;
    }

    dliste->fin=node;
    dliste->taille+=1;
}

void inserNoeud(int val1,int val2, int poids, int indice, DListe *dliste){
    //Verification si la liste est bien initialisee
    if (!dliste){
        printf("La liste doublement chainee n'a pas ete initialisee");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    //cas ou l'on insere le noeud en premier element ou en dernier element.
    int taille=dliste->taille;

    if (indice==0||taille==0){
        ajoutNoeudDebut(val1, val2, poids, dliste);
    }
    else if (indice==taille){
        ajoutNoeudFin(val1, val2, poids, dliste);
    }
    else{
        noeud *node;
        node = (noeud*) malloc(sizeof(noeud));
        
        node->suiv=NULL;
        node->pred=NULL;
        int taille=dliste->taille;
        node->x=val1;
        node->ymin=val2;
        node->poids=poids;
        noeud* temp;

        // Si l'indice est dans la premiere moitiee de la liste, on parcourt par le debut,...
        if (indice<=taille/2){
            temp=dliste->debut;
            int i=0;
            while (i<indice-1 && temp!=NULL){
                temp = temp->suiv;
                i++;
            }
        }
        // Sinon on la parcourt par la fin.
        else{ 
            temp=dliste->fin;
            int i=0;
            while (i<taille-indice && temp!=NULL){
                temp = temp->pred;
                i++;
            }
        }
        // Etapes pour inserer le noeud
        temp->suiv->pred = node;
        node->suiv = temp->suiv;
        node->pred = temp;
        temp->suiv = node;
    
    }
    dliste->taille+=1;
    
}

void retirerNoeud(int indice, DListe *dliste){
    if (!dliste){
        printf("La liste doublement chainee n'a pas ete initialisee");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    noeud* temp;
    int taille=dliste->taille;

    //s'il n'y a aucun noeud, on ne peut pas en retirer.
    if (taille==0){
        printf("La liste doublement chainee est vide, on ne peut pas retirer un element");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    // Si l'indice est dans la premiere moitiee de la liste, on parcourt par le debut,...
    if (indice<=taille/2){
        temp=dliste->debut;
        for (int i=0;i<indice;i++){
            temp = temp->suiv;
        }
    }
    // Sinon on la parcourt par la fin.
    else{ 
        temp=dliste->fin;
        for (int i=0;i<taille-indice-1;i++){
            temp = temp->pred;
        }
    }
    // Etapes pour retirer le noeud
    temp->pred->suiv = temp->suiv;
    temp->suiv->pred = temp->pred;
    //On librere les pointeurs du noeud
    free(temp);
    dliste->taille-=1;
}

void afficherDliste(DListe *dliste){
    int taille=dliste->taille;
    printf("nb elements: %d\n",taille);
    fflush(stdout);
    if (taille==0){
        printf("[]\n");
        fflush(stdout);
    }
    else{
        noeud* temp= dliste->debut;
        printf("[");
        fflush(stdout);
        int i=0;
        while (i<taille){
            if (i==taille-1){
                printf("[x=%d,ymin=%d,poids=%d]",temp->x,temp->ymin,temp->poids);
                fflush(stdout);
                temp=temp->suiv;  
            }
            else{
                printf("[x=%d,ymin=%d,poids=%d],\n",temp->x,temp->ymin,temp->poids);
                fflush(stdout);
                temp=temp->suiv;
            }           
            i++;
        }
        printf("]\n");
        fflush(stdout);
    }
}




void remplirDListe(int x, int ymin, int poids, DListe* arbre){
    if (arbre->taille==0){
        ajoutNoeudDebut(x, ymin, poids, arbre);
    }
    else{
        ajoutNoeudFin(x,ymin, poids, arbre);
    }
}