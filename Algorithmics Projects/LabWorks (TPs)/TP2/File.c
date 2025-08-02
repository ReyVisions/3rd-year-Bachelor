#include <stdio.h>
#include <stdlib.h>
#include "File.h"

void initDliste(t_file *dliste){
    dliste->taille=0;
    dliste->debut=(noeud*) malloc(sizeof(noeud));
    dliste->fin=(noeud*) malloc(sizeof(noeud));
    dliste->debut=NULL;
    dliste->fin=NULL;
}

void enfiler(int val, t_file *dliste){
    //Verification si la liste est bien initialisee
    

    if (dliste==NULL){
        printf("La liste doublement chainee n'a pas ete initialisee");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    noeud *node;
    node = (noeud*) malloc(sizeof(noeud));
    
    node->valeur=val;
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


int defiler(t_file *dliste){
    int val=dliste->taille;
    if (dliste==NULL){
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

    temp=dliste->debut;
    for (int i=0;i<val;i++){
        temp = temp->suiv;
    }
    int x = temp->valeur;
    // Etapes pour retirer le noeud
    temp->pred->suiv = temp->suiv;
    temp->suiv->pred = temp->pred;
    //On librere les pointeurs du noeud
    free(temp);
    dliste->taille-=1;
    return(x);
}

void afficherDliste(t_file *dliste){
    int taille=dliste->taille;
    printf("nb elements%d",taille);
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
                printf("%d",temp->valeur);
                fflush(stdout);
                temp=temp->suiv;  
            }
            else{
                printf("%d,",temp->valeur);
                fflush(stdout);
                temp=temp->suiv;
            }           
            i++;
        }
        printf("]\n");
        fflush(stdout);
    }
}
void plusCourtChemin (int**adjacence, int ordre, int s, int *l, int *pred) {
    // Variables locales
    int *marques ; // tableau dynamique indiquant si les sommets sont marqués ou non
    int x, y ; // numéros de sommets intermédiaires
    t_file *f ; // file d’attente de sommets à créer en s’inspirant des listes doublement chaïnée avec un .h
    // un .c dédié

    // Allouer le tableau marques de taille « ordre »
    marques=(int*)malloc(ordre*sizeof(int));
    // Initialiser les marquages et les longueurs minimales à 0
    for (x=0 ; x<ordre ; x++) {
        marques[x] = 0 ;
        l[x] = 0 ;
    }
    // Marquer le sommet s à 1
    marques[s] = 1 ;
    // Créer (allouer) la file f et enfiler s dans f
    t_file* file = (t_file*) malloc(sizeof(file));
    initDliste(file);
    enfiler(s,file);

    while (file->taille>0) { // Tant que la file f n’est pas vide
        x=defiler(file); // Défiler le premier sommet x de la file f
        // Pour tous les sommets y adjacents à x et non marqués
        for (y=0 ; y<ordre ; y++)
            if (adjacence[x][y] && !marques[y]) {
                marques[y] = 1 ; // marquer le sommet y
                enfiler(y,file); // enfiler le sommet y dans f
                pred[y] = x ; // x est le prédécesseur de y
                l[y] = l[x]+1 ; // // incrémenter la longueur de y
            }
    }
}


