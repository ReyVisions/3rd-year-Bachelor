#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "Arbre.h"

#define PROFONDEUR 5

void initArbre(Arbre *arbre){
    arbre->taille=0;
    arbre->racine=(noeud*) malloc(sizeof(noeud));
    arbre->racine->filsG=NULL;
    arbre->racine->filsD=NULL;
    arbre->racine->valeur=-1000;
}


void remplirArbre(int val, Arbre *arbre){
    if (arbre==NULL){
        printf("L'arbre n'est pas initialisee");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    int taille=arbre->taille;
    int sortie;
    
    //Input de la valeur
    /*int erreur;
    do{
    printf("Veuillez saisir la valeur a mettre :\n");
    erreur=scanf("%d",&val);
    }while (erreur=1);*/

    if (taille==0){

        arbre->racine->valeur=val;
        printf("\nOn a rajoute la racine");
        fflush(stdout);
        return;
    }
    else{
        //Les instructions seront du type: '00001'(0 pour le fils gauche, et 1 pour le fils droit);
        //On suppose la bonne implementation de l'utilisateur.

        //Input du STR
        char instructions[PROFONDEUR-1];
        do{
            printf("\nOn veut rajouter un fils : ");
            printf("\nVeuillez saisir la valeur a mettre en sequences de 0 et 1 de taille %d maximum:\n",PROFONDEUR-1);
            fgets(instructions,PROFONDEUR-1,stdin);
        }while (strlen(instructions)>4);

        char chiffre;
        noeud* node= (noeud*) malloc(sizeof(noeud));
        node->filsG=NULL;
        node->filsD=NULL;

        noeud* temp= (noeud*) malloc(sizeof(noeud));  
        temp=arbre->racine;

        sortie=0; //variable qui stoppe le parcours des fils si il en possede pas a un certain point donne.
        printf("\nIl y a %d elements dans instructions",strlen(instructions));
        fflush(stdout);
        printf("\nVoici le str : %s",instructions);
        fflush(stdout);
        for (int i=0;i<strlen(instructions)-1;i++){
            chiffre= instructions[i];

            
            
            if (i<strlen(instructions)-2){
                if (chiffre=='0'){
                    if(temp->filsG!=NULL){
                        temp=temp->filsG;
                    }else{
                        sortie=1;
                        break;                   
                    }   
                }
                else if (chiffre=='1'){
                    if(temp->filsD!=NULL){
                    temp=temp->filsD;
                    }else{
                        sortie=1;
                        break;
                    }
                }
                
            }else if(i==strlen(instructions)-2){
                if(instructions[i]=='0'){
                    temp->filsG=node;
                    temp->filsG->valeur=val;
                }
                else if(instructions[i]=='1'){
                    temp->filsD=node;
                    temp->filsD->valeur=val;
                }
            }
        }
    }
    if (sortie!=1||taille==0){
        arbre->taille+=1;
    }else{
        printf("On a pas ajoute de noeuds car pas de fils");
    }
    
}
void afficherArbre(noeud* noeud){
    if (noeud==NULL) return;
    printf("[");
    fflush(stdout);
    if (noeud->filsG) afficherArbre(noeud->filsG);
    printf("  %d  ",noeud->valeur);
    fflush(stdout);
    if (noeud->filsD) afficherArbre(noeud->filsD);
    printf("]");
    fflush(stdout); 
}

void remplirArbreParOrdre(int val,char *instructions, Arbre *arbre){
    if (arbre==NULL){
        printf("L'arbre n'est pas initialisee");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    int taille=arbre->taille;
    int sortie=0;
    
    //Input de la valeur
    /*int erreur;
    do{
    printf("Veuillez saisir la valeur a mettre :\n");
    erreur=scanf("%d",&val);
    }while (erreur=1);*/

    if (taille==0){

        arbre->racine->valeur=val;
        arbre->taille+=1;
        printf("\nOn a rajoute la racine %d : ",arbre->racine->valeur);
        fflush(stdout);
        return;
    }
    else{
        //Les instructions seront du type: '00001'(0 pour le fils gauche, et 1 pour le fils droit);
        //On suppose la bonne implementation de l'utilisateur.

        char chiffre;
        noeud* node= (noeud*) malloc(sizeof(noeud));
        node->filsG=NULL;
        node->filsD=NULL;

        noeud* temp= (noeud*) malloc(sizeof(noeud));  
        temp=arbre->racine;

        sortie=0; //variable qui stoppe le parcours des fils si il en possede pas a un certain point donne.
        /*printf("\nIl y a %d elements dans instructions",strlen(instructions));
        fflush(stdout);
        printf("\tVoici le str : %s",instructions);
        fflush(stdout);*/
        for (int i=0;i<strlen(instructions);i++){
            chiffre= instructions[i];      
            if (i<strlen(instructions)-1){
                if (chiffre=='0'){
                    if(temp->filsG!=NULL){
                        temp=temp->filsG;
                    }else{
                        sortie=1;
                        break;                   
                    }   
                }
                else if (chiffre=='1'){
                    if(temp->filsD!=NULL){
                    temp=temp->filsD;
                    }else{
                        sortie=1;
                        break;
                    }
                }
                
            }else if(i==strlen(instructions)-1){
                if(chiffre=='0'&& temp->filsG==NULL){
                    temp->filsG=node;
                    temp->filsG->valeur=val;
                }
                else if(chiffre=='1' && temp->filsD==NULL){
                    temp->filsD=node;
                    temp->filsD->valeur=val;
                }
                else{
                    printf("\nIl y a deja une valeur ici...");
                    fflush(stdout);
                    sortie=1;
                }
            }
        }if (sortie!=1){
            arbre->taille+=1;
            printf("\nOn a rajoute la valeur %d : ",val);
            fflush(stdout);
        }else{
            printf("\nOn a pas ajoute de noeuds car pas de fils");
            fflush(stdout);
        }
    }  
}

char* intEnArbo(int indiceA){
    if (indiceA==0){
        return(NULL);
    }
    //calcul de la taille du str en fonction de indiceA.
    int nbchar=0;
    int testindiceA=indiceA+1;
    while (testindiceA>0){
        testindiceA=testindiceA-pow(2,nbchar);
        nbchar++;
    } 
    nbchar=nbchar-1;
 
    char* str=malloc((nbchar+1)*sizeof(int));

    int reste=0;
    int i=0;
    //Etape 1:
    indiceA++;
    //Etape 2: On fait l'algorithme d'euclide indiceA avec 2 sur indice A. Les restes de chaque division euclidienne
    //donne la sequence inverse en binaire.
    while (nbchar-i>=1){  
        reste=indiceA%2;
        indiceA=indiceA/2;
        str[nbchar-i-1]=reste+'0';
        i++;
    }
    str[nbchar]='\0';
    //Etape 3 (deja effectuee dans 2): On n'affiche pas le dernier char(qui est le 1). Puis on inverse la sequence.
    /*printf("\nVOici la chaine de caractere: %s", str);
    fflush(stdout);*/
    return(str);
}

void freeNoeud(noeud *node) {
    if (node == NULL) {
        return;
    }
    
    freeNoeud(node->filsG); // Libérer les fils gauche de manière récursive.
    freeNoeud(node->filsD); // Libérer les fils droit de manière récursive.

    free(node); // Libérer le nœud actuel.
}

void effacerNoeud(char *instructions, Arbre *arbre) {
    if (arbre == NULL) {
        printf("L'arbre n'est pas initialisé\n");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    if (instructions == NULL) {
        // Si instructions est NULL, réinitialisez complètement l'arbre.
        freeNoeud(arbre->racine); // Appel à une nouvelle fonction pour libérer la mémoire.
        initArbre(arbre); // Réinitialisez l'arbre.
        return;
    } else {
        char chiffre;
        noeud* temp = arbre->racine;
        noeud* parent = NULL;

        int i;
        for (i = 0; i < strlen(instructions); i++) {
            chiffre = instructions[i];

            if (chiffre == '\0') {
                break; // Sortir de la boucle si on atteint la fin de la chaîne.
            }

            if (chiffre == '0') {
                parent = temp;
                temp = temp->filsG;
            } else if (chiffre == '1') {
                parent = temp;
                temp = temp->filsD;
            } else {
                printf("Instructions incorrectes\n");
                fflush(stdout);
                return;
            }

            if (temp == NULL) {
                printf("Noeud introuvable\n");
                fflush(stdout);
                return;
            }
        }

        // Ici, temp est le nœud à supprimer et parent est son parent.
        // Assurez-vous que le nœud temp est correctement libéré et que le parent ne pointe plus vers lui.
        if (parent != NULL) {
            if (parent->filsG == temp) {
                parent->filsG = NULL;
            } else {
                parent->filsD = NULL;
            }
            arbre->taille -= calculerNoeuds(temp) + 1; // 1 pour le nœud supprimé.
            freeNoeud(temp); // Libérer le nœud.
        } else {
            // Si parent est NULL, cela signifie que le nœud à supprimer est la racine de l'arbre.
            freeNoeud(arbre->racine); // Libérer la racine.
            initArbre(arbre); // Réinitialiser l'arbre.
        }
    }
}

int calculerNoeuds(noeud* node){
    if (node->filsG==NULL||node->filsD==NULL){
        return(0);
    }else{
        return(1+calculerNoeuds(node->filsG)+calculerNoeuds(node->filsD));
    }
}
void UI(){
    printf("\n---------------------------------------------------------------");
    fflush(stdout);
    printf("\nVoici le programme pour tester le programme sur les arbres binaires.");
    fflush(stdout);
    Arbre *arbre= (Arbre*) malloc(sizeof(Arbre));
    initArbre(arbre);
    printf("\nOn initialise l'arbre a chaque debut d'utilisation du programme.");
    fflush(stdout);

    char choix='A';
    char affichage;
    while (choix!='Q'){
        do{
            printf("\nChoisissez le mode d'affichage: \nA = Prefixe, \nB=Infixe, \nC=Postfixe");
            fflush(stdout);
            scanf(" %c",&affichage);
        } while (affichage!='A' && affichage !='B' && affichage !='C');
        do{
            printf("\nFaites votre choix : \nA pour rajouter un noeud, \nR pour retirer un noeud, \nE pour afficher un exemple, \nQ pour quitter l'interface.");
            fflush(stdout);
            scanf(" %c",&choix);
        } while (choix!='A' && choix !='R' && choix !='E' && choix!='Q');

        if (choix=='A'){
            printf("\n******************************************");
            printf("\nChoix A : On ajoute des valeurs");
            fflush(stdout);
            printf("\n\nAjout de combien (nb) de valeurs?");
            fflush(stdout);
            int nb;
            do{
                scanf("%d",&nb);
            }while(nb<1);

            for (int i=0;i<nb;i++){
                printf("\n Ajout n.%d : ",i);
                fflush(stdout);
                int sommet;
                do{
                    if (i==0){
                        printf("\n Quel est le nom de la racine (en int)? ");                   
                    }else{
                        printf("\n Quel est le nom du noeud (en int)? ");
                    }
                    fflush(stdout);
                    scanf("%d",&sommet);
                    fflush(stdin);
                }while(sommet<0);
                int place=0;
                do{
                    printf("\n Ou voulez vous le placer? ");
                    fflush(stdout);
                    scanf("%d",&place);
                    fflush(stdin);
                }while(place<0);
                remplirArbreParOrdre(sommet,intEnArbo(place),arbre);
                printf("\n Voici l'arbre apres les ajouts : ");
                fflush(stdout);
                afficherArbre(arbre->racine); 
            }
        }
        else if (choix=='E'){
            Arbre *arbreE= (Arbre*) malloc(sizeof(Arbre));
            initArbre(arbreE);
            remplirArbreParOrdre(0,intEnArbo(0),arbreE);
            remplirArbreParOrdre(1,intEnArbo(1),arbreE);
            remplirArbreParOrdre(2,intEnArbo(2),arbreE);
            remplirArbreParOrdre(3,intEnArbo(3),arbreE);
            remplirArbreParOrdre(4,intEnArbo(4),arbreE);
            remplirArbreParOrdre(5,intEnArbo(5),arbreE);
            remplirArbreParOrdre(6,intEnArbo(6),arbreE);
            printf("Cela donne normalement [[[ Noeud: 4  ] Noeud: 2  [ Noeud: 5  ]] Noeud: 1  [[ Noeud: 6  ] Noeud: 3  [ Noeud: 7  ]]]");
            fflush(stdout);
            afficherArbre(arbreE->racine); 
            printf("\nAffichage en parcours souhaite : ");
            if (affichage=='A'){
                afficherPrefixe(arbreE->racine);
            }else if (affichage=='B'){
                afficherInfixe(arbreE->racine);
            }
            else if (affichage=='C'){
                afficherPostfixe(arbreE->racine);
            }
            free(arbreE);
        }
        else if (choix=='R'){
            int place=-1;
            do{
                printf("\n Veuillez saisir l'ordre du noeud a effacer");
                fflush(stdout);
                scanf("%d",&place);
            }while(place<0);
            effacerNoeud(intEnArbo(place),arbre);
            printf("\n Voici l'arbre apres le retrait du noeud en ordre %d : ",place);
            fflush(stdout);
            afficherArbre(arbre->racine); 
        }else if (choix=='Q'){
            
        }else{
            printf("\n Erreur non listee");
            fflush(stdout);
            return;
        }


    }
    printf("\n---------------------------------------------------------------\n");
    printf("\nFin du programme 'monArbre(TP3)'.");
    fflush(stdout);

    
    printf("\n\nAffichage de l'arbre en mode souhaite:");
    fflush(stdout);
    if (affichage=='A'){
        afficherPrefixe(arbre->racine);
    }else if (affichage=='B'){
        afficherInfixe(arbre->racine);
    }
    else if (affichage=='C'){
        afficherPostfixe(arbre->racine);
    }
    free(arbre);
}

void afficherPrefixe(noeud* noeud){
    if (!noeud) return;
    
    printf("  %d  ",noeud->valeur);
    fflush(stdout);
    if (noeud->filsG) afficherPrefixe(noeud->filsG);  
    if (noeud->filsD) afficherPrefixe(noeud->filsD);
    fflush(stdout);
}
void afficherInfixe(noeud* noeud){
    if (!noeud) return;  
    if (noeud->filsG) afficherInfixe(noeud->filsG);  
    printf("  %d  ",noeud->valeur);
    fflush(stdout);
    if (noeud->filsD) afficherInfixe(noeud->filsD);
    fflush(stdout);
}

void afficherPostfixe(noeud* noeud){
    if (!noeud) return;  
    if (noeud->filsG) afficherPostfixe(noeud->filsG);  
    if (noeud->filsD) afficherPostfixe(noeud->filsD);
    printf("  %d  ",noeud->valeur);
    fflush(stdout);
}


