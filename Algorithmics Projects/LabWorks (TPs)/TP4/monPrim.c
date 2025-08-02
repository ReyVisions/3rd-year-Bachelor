#include "Prim.c"


int main(){

    printf("\n\nQuelle valeur (en int) de la taille N du graphe?");
    fflush(stdout);
    int ordre;
    do{
        scanf("%d",&ordre);
    }while(ordre<1);
    float** adjacencePoids;
    adjacencePoids=matriceAdjPoids(ordre);
    /*
    // Exemple de remplissage:
    adjacencePoids[0][1] = 2.0;
    adjacencePoids[1][0] = 2.0;
    adjacencePoids[0][2] = 4.0;
    adjacencePoids[2][0] = 4.0;
    adjacencePoids[1][2] = 3.0;
    adjacencePoids[2][1] = 3.0;
    adjacencePoids[1][3] = 5.0;
    adjacencePoids[3][1] = 5.0;
    adjacencePoids[2][3] = 1.0;
    adjacencePoids[3][2] = 1.0;
    */
    afficherAdjacence(adjacencePoids,ordre);
    // Appel de la fonction "prim" pour trouver l'arbre de poids minimum
    DListe* arbreMin = prim(adjacencePoids, ordre);

    // Affichage de l'arbre de poids minimum
    printf("\nArbre de poids minimum :\n");
    afficherDliste(arbreMin);

    // Nettoyage de la mémoire
    for (int i = 0; i < ordre; i++) {
        free(adjacencePoids[i]);
    }
    free(adjacencePoids);
    free(arbreMin);

    return(0);
}