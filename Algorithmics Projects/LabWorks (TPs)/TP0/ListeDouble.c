#include <stdio.h>
#include <stdlib.h>
#include "ListeDouble.h"

void initDliste(DListe *dliste){
    dliste->taille=0;
    dliste->debut=(noeud*) malloc(sizeof(noeud));
    dliste->fin=(noeud*) malloc(sizeof(noeud));
    dliste->debut=NULL;
    dliste->fin=NULL;
}

void ajoutNoeudDebut(int val, DListe *dliste){
    //Verification si la liste est bien initialisee
    

    if (!dliste){
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

void ajoutNoeudFin(int val, DListe *dliste){
    //Verification si la liste est bien initialisee
    if (!dliste){
        printf("La liste doublement chainee n'a pas ete initialisee");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    noeud *node;
    node = (noeud*) malloc(sizeof(noeud));

    node->valeur=val;
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

void inserNoeud(int val, int indice, DListe *dliste){
    //Verification si la liste est bien initialisee
    if (!dliste){
        printf("La liste doublement chainee n'a pas ete initialisee");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    //cas ou l'on insere le noeud en premier element ou en dernier element.
    int taille=dliste->taille;

    if (indice==0||taille==0){
        ajoutNoeudDebut(val, dliste);
    }
    else if (indice==taille){
        ajoutNoeudFin(val, dliste);
    }
    else{
        noeud *node;
        node = (noeud*) malloc(sizeof(noeud));
        
        node->suiv=NULL;
        node->pred=NULL;
        int taille=dliste->taille;
        node->valeur=val;
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

void UI(){
    printf("\n---------------------------------------------------------------");
    fflush(stdout);
    printf("\nVoici le programme pour tester le programme sur les listes doublement chainee.");
    fflush(stdout);
    DListe *dliste= (DListe*) malloc(sizeof(dliste));
    initDliste(dliste);
    printf("\nOn initialise la liste a chaque debut d'utilisation du programme.");
    fflush(stdout);

    char choix='E';
    while (choix!='Q'){
        do{
            printf("\n\nFaites votre choix : \nD pour rajouter un noeud au debut, \nF pour ajouter un noeud a la fin, \nI pour inserer un noeud, \nR pour retirer un noeud, \nE pour afficher un exemple, \nQ pour quitter l'interface.");
            fflush(stdout);
            scanf("%c",&choix);
        } while ( choix!='D' && choix!='F' && choix!='I'&& choix !='R' && choix !='E' && choix!='Q');

        if (choix=='D'){
            printf("\n******************************************");
            printf("\nChoix D : On ajoute une valeur au debut de la double liste");
            int sommet;
            sommet=0;
            do{
                printf("\n Quel est le nom du noeud (en int)? ");
                fflush(stdout);
                scanf("%d",&sommet);
                fflush(stdin);
            }while(sommet<0);
            ajoutNoeudDebut(sommet,dliste);
            printf("\n Voici l'arbre apres ajout au debut de la dliste : ");
            fflush(stdout);
            afficherDliste(dliste); 
            
        }else if (choix=='F'){
            printf("\n******************************************");
            printf("\nChoix F : On ajoute une valeur a la fin de la double liste");
            int sommet;
            sommet=0;
            do{
                printf("\n Quel est le nom du noeud (en int)? ");
                fflush(stdout);
                scanf("%d",&sommet);
                fflush(stdin);
            }while(sommet<0);

            ajoutNoeudFin(sommet,dliste);
            printf("\n Voici l'arbre apres ajout a la fin de la dliste : ");
            fflush(stdout);
            afficherDliste(dliste);            
        }else if (choix=='I'){
            printf("\n******************************************");
            printf("\nChoix I : On insere une valeur en un indice.");
            int sommet;
            sommet=0;
            do{
                printf("\n Quel est le nom du noeud (en int)? ");
                fflush(stdout);
                scanf("%d",&sommet);
                fflush(stdin);
            }while(sommet<0);

            int indice;
            indice=0;
            do{
                printf("\n Quel est l'indice ou il faut inserer le noeud?");
                fflush(stdout);
                scanf("%d",&indice);
                fflush(stdin);
            }while(indice<0);

            inserNoeud(sommet,indice,dliste);
            printf("\n Voici l'arbre apres l'insertion' : ");
            fflush(stdout);
            afficherDliste(dliste);            
        }
        else if (choix=='E'){
            DListe* dlisteE=NULL;
            dlisteE = (DListe*) malloc(sizeof(dlisteE));
    
            printf("On cree une liste vide : ");
            fflush(stdout);
            initDliste(dlisteE);
            afficherDliste(dlisteE);

            printf("On rajoute 0 au debut : ");
            fflush(stdout);
            ajoutNoeudDebut(0,dlisteE);
            afficherDliste(dlisteE);

            printf("On rajoute 3 a la fin : ");
            fflush(stdout);
            ajoutNoeudFin(3,dlisteE);
            afficherDliste(dlisteE);

            printf("On insere 1 au milieu : ");
            fflush(stdout);
            inserNoeud(1,1,dlisteE);
            afficherDliste(dlisteE);

            printf("On insere 2 au milieu : ");
            fflush(stdout);
            inserNoeud(2,2,dlisteE);
            afficherDliste(dlisteE);

            printf("On retire le noeud a l'indice 2 : ");
            fflush(stdout);
            retirerNoeud(2,dlisteE);
            afficherDliste(dlisteE);

            free(dlisteE);
            printf("la liste exemple a ete effacee");
            fflush(stdout);
        }
        else if (choix=='R'){
            int place=-1;
            do{
                printf("\n Veuillez saisir l'ordre du noeud a effacer");
                fflush(stdout);
                scanf("%d",&place);
            }while(place<0);
            retirerNoeud(place,dliste);
            printf("\n Voici l'arbre apres le retrait du noeud en ordre %d : ",place);
            fflush(stdout);
            afficherDliste(dliste);
        }else if (choix=='Q'){
            
        }else{
            printf("\n Erreur non listee");
            fflush(stdout);
            
        }

    }
    printf("\n---------------------------------------------------------------\n");
    printf("\nFin du programme 'maListeDouble'.");
    fflush(stdout);

    
    printf("\n\nAffichage de la dliste:");
    fflush(stdout);
    afficherDliste(dliste);
    free(dliste);
}
