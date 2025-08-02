#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

#define VOISINSMAX 5
#define SOMMETSMAX 10

void initGraphe(Graphe *graphe){
    graphe->taille=0;
    noeud* sommets[SOMMETSMAX];
}

int SommetExiste(char name, Graphe* graphe){
    int i=0;
    noeud* node;
    if (graphe->taille!=0){
        for (i=0;i<graphe->taille;i++){
            node=graphe->sommets[i];
            if (node->nom==name){
                return(i);
            };
        }
        return(-1);
    }
    else{return(-1);}
}

void creerSommet(char name, Graphe* graphe){
    //Si le sommet n'existe pas: on alloue et initalise le sommet.
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

void supprimerSommet(char name, Graphe* graphe){
    //si le sommet existe dans le graphe
    int indice;
    indice = SommetExiste(name,graphe);
    if (indice!=-1){
        noeud* sommet=graphe->sommets[indice];

        //On traite le cas ou il y a un sommet qui est son propre voisin(boucle)

        for (int i=0; i<sommet->nbVoisins;i++){
            if (sommet->voisins[i]==sommet){
                sommet->voisins[i]=NULL;
                sommet->nbVoisins--;
            }
        }
        for (int i=0;i<sommet->nbVoisins;i++){
            noeud* voisin=sommet->voisins[i];
            for (int j=0; j<voisin->nbVoisins; j++) {
                if (voisin->voisins[j]==sommet) {
                    voisin->voisins[j]=NULL;
                    voisin->nbVoisins--;
                    break;
                }
            }
            free(sommet->voisins[i]);
        }
        free(sommet);
        // Decaler les sommets vers la gauche pour remplir le trou.
        for (int i=indice; i<graphe->taille-1; i++) {
            graphe->sommets[i]=graphe->sommets[i+1];
        }
        graphe->taille--;
    }else{
        printf("Le sommet %c n'existe pas.\n", name);
    }

}
void retirerArete(char nomNode1, char nomNode2, Graphe* graphe){
    int indice1,indice2;
    indice1 = SommetExiste(nomNode1,graphe);
    indice2 = SommetExiste(nomNode2,graphe);

    if (indice1!=-1 && indice2!=-1){
        noeud* sommet1 = graphe->sommets[indice1];
        noeud* sommet2 = graphe->sommets[indice2];

        // Recherche de l'arete et suppression.
        int i;
        for (i = 0; i < sommet1->nbVoisins; i++) {
            if (sommet1->voisins[i] == sommet2) {
                sommet1->voisins[i] = NULL;
                sommet1->nbVoisins--;
                break;
            }
        }
        for (i = 0; i < sommet2->nbVoisins; i++) {
            if (sommet2->voisins[i] == sommet1) {
                sommet2->voisins[i] = NULL;
                sommet2->nbVoisins--;
                break;
            }
        }
    } else {
        printf("L'un des sommets n'existe pas.\n");
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

void UI(){
    printf("\n---------------------------------------------------------------");
    fflush(stdout);
    printf("\nVoici le programme pour tester le programme sur les graphes.");
    fflush(stdout);
    Graphe* graphe= (Graphe*) malloc(sizeof(Graphe));
	initGraphe(graphe);
    printf("\nOn initialise le graphe a chaque debut d'utilisation du programme.");
    fflush(stdout);

    char choix='E';
    while (choix!='Q'){
        do{
            printf("\n\nFaites votre choix : \nC pour creer un sommet, \nL pour lier deux sommets avec une arete, \nS pour supprimer un sommet, \nR pour retirer une arete, \nE pour afficher un exemple, \nQ pour quitter l'interface.");
            fflush(stdout);
            scanf(" %c",&choix);
        } while ( choix!='C' && choix!='L' && choix!='S'&& choix !='R' && choix !='E' && choix!='Q');

        if (choix=='C'){
            printf("\n******************************************");
            printf("\nChoix C : On creer un sommet dans le graphe");
            char sommet;
            do{
                printf("\n Quel est le nom du noeud (en char)? ");
                fflush(stdout);
                scanf(" %c",&sommet);
                fflush(stdin);
            }while(sommet=='Z');
            creerSommet(sommet,graphe);
            printf("\n Voici le graphe apres ajout du sommet: ");
            fflush(stdout);
            afficherGraphe(graphe); 
            
        }else if (choix=='L'){
            printf("\n******************************************");
            printf("\nChoix L : On creer une arete entre sommet1 et sommet2 (en char)");
            char sommet1,sommet2;
            do{
                printf("\n Quel est le nom du noeud 1 (en char)? ");
                fflush(stdout);
                scanf(" %c",&sommet1);
                fflush(stdin);
            }while(sommet1=='Z');

            do{
                printf("\n Quel est le nom du noeud 2 (en char)? ");
                fflush(stdout);
                scanf(" %c",&sommet2);
                fflush(stdin);
            }while(sommet2=='Z');

            lierDeuxSommets(sommet1,sommet2,graphe);
            printf("\n Voici le graphe apres ajout de l'arete [%c,%c]: ",sommet1, sommet2);
            fflush(stdout);
            afficherGraphe(graphe); 

        }else if (choix=='S'){
            printf("\n******************************************");
            printf("\nChoix S : On supprime un sommet du graphe.");
            char sommet;
            do{
                printf("\n Quel est le nom du noeud (en char)? ");
                fflush(stdout);
                scanf(" %c",&sommet);
                fflush(stdin);
            }while(sommet=='Z');

            supprimerSommet(sommet,graphe);
            printf("\n Voici l'arbre apres l'insertion' : ");
            fflush(stdout);
            afficherGraphe(graphe);     

        }else if (choix=='R'){
            printf("\n******************************************");
            printf("\nChoix S : On retire une arete du graphe.");
            char sommet1,sommet2;
            do{
                printf("\n Quel est le nom du noeud 1 (en char)? ");
                fflush(stdout);
                scanf(" %c",&sommet1);
                fflush(stdin);
            }while(sommet1=='Z');

            do{
                printf("\n Quel est le nom du noeud 2 (en char)? ");
                fflush(stdout);
                scanf(" %c",&sommet2);
                fflush(stdin);
            }while(sommet2=='Z');

            retirerArete(sommet1,sommet2,graphe);
            printf("\n Voici le graphe apres avoir retire l'arete [%c,%c]: ",sommet1, sommet2);
            fflush(stdout);
            afficherGraphe(graphe);          
        }
        else if (choix=='E'){
            Graphe* grapheE= (Graphe*) malloc(sizeof(Graphe));
	        initGraphe(grapheE);
	        printf("Ajout des sommets");
	        fflush(stdout);
	        creerSommet('A',grapheE);
	        creerSommet('B',grapheE);
	        creerSommet('C',grapheE);

	        lierDeuxSommets('A','B',grapheE);
	        lierDeuxSommets('B','C',grapheE);
	        lierDeuxSommets('D','A',grapheE);
	        lierDeuxSommets('A','A',grapheE);

	        printf("\n\nOn affiche le graphe sous forme de liste d'adjacence");
	        fflush(stdout);
	        afficherGraphe(grapheE);
	        free(grapheE);

        }else if (choix=='Q'){

        }else{
            printf("\n Erreur non listee");
            fflush(stdout);
            
        }

    }
    printf("\n---------------------------------------------------------------\n");
    printf("\nFin du programme 'monGraphe'.");
    fflush(stdout);

    
    printf("\n\nAffichage du graphe:");
    fflush(stdout);
	afficherGraphe(graphe);
	free(graphe);
}