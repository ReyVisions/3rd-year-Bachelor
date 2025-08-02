#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "WelshPowell.c"


int main() {
    Graph graph;
    printf("\n---------------------------------------------------------------");
    fflush(stdout);
    printf("\nVoici le programme pour tester le programme sur l'algoruthme de Welsh-Powell'.");
    fflush(stdout);
    printf("\nOn initialisera le graphe apres avoir defini N.");
    fflush(stdout);

    char choix;
    while (choix!='Q'){
        do{
            printf("\nFaites votre choix : \nE pour afficher l'exemple du programme, \nG pour generer soi meme un graphe pour effectuer l'algorithme de WelshPowell, \nQ pour quitter l'interface.");
            fflush(stdout);
            scanf(" %c",&choix);
        } while (choix !='G' && choix !='E' && choix!='Q');

        if (choix=='G'){
            printf("\n******************************************");
            printf("\nChoix G : On genere un graphe de taille N");
            fflush(stdout);
            printf("\n\nQuelle valeur (en int) de la taille N du graphe?");
            fflush(stdout);
            int nb;
            do{
                scanf("%d",&nb);
            }while(nb<1);
            if(nb>50000){
                printf("\nVous avez choisi une valeur tres grande, le programme peut ne pas fonctionner, veuillez patienter tout de meme pour verifier...");
                fflush(stdout);
            }
            else{
                printf("\nVeuillez patienter (cela peut prendre du temps si N est tres grand)\n");
                fflush(stdout);
            }
            initGraph(&graph,nb);
            addEdgeRandom(&graph);
            welshPowell(&graph);
            clearGraph(&graph);
        }
        else if (choix=='E'){
            initGraph(&graph,5);
            graph.vertices = 5;
            // Add edges
            addEdge(&graph, 0, 1);
            addEdge(&graph, 0, 2);
            addEdge(&graph, 1, 2);
            addEdge(&graph, 1, 3);
            addEdge(&graph, 2, 3);
            addEdge(&graph, 3, 4);
            welshPowell(&graph);
            afficherAdjacence(graph.vertices, graph.adjMatrix);
            clearGraph(&graph);

        }else if (choix=='Q'){
        }else{
            printf("\n Erreur non listee");
            fflush(stdout);
        }


    }
    printf("\n---------------------------------------------------------------\n");
    initGraph(&graph,50);
    addEdgeRandom(&graph);
    welshPowell(&graph);
    afficherAdjacence(graph.vertices, graph.adjMatrix);
    clearGraph(&graph);
    printf("\nFin d'exemple de matrice pour N=50");
    printf("\n---------------------------------------------------------------\n");
    printf("\nFin du programme 'monWelshPowell'.");
    fflush(stdout);
    return 0;

}