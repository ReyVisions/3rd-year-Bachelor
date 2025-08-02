int* marquerVoisins (int** adjacence, int ordre, int s) {
    // Variables locales
    int *marques ; // tableau dynamique indiquant si les sommets sont marqués ou non
    int x, y ; // numéros de sommets intermédiaires
    // Allouer le tableau marques de taille « ordre »

    marques = (int*)malloc(ordre*sizeof(int));
    // Initialiser les marquages à 0
    for (x=0 ; x<ordre ; x++)
        marques[x] = 0 ;
    // Marquer le sommet s à 1
    marques[s] = 1 ;
  
    //Traitement du cas ou aucun voisin est marque.
    int somme=0;

    for (x=0 ; x<ordre ; x++)
        somme+=marques[x];
    if (somme==0){
        printf("Les composantes sont toutes non connexes");
        fflush(stdout);
        return(marques);
    }
   //methode naive avec une complexite de n^3
   /*
    int marquages=1; //Variable pour verifier si    
    while (marquages>0){
        marquages=0;
        for (int i=0;i<ordre;i++){
            if (marques[i]){
                for (int j=0;j<ordre;j++){
                    if (adjacence[i][j] && !marques[j]){
                        marques[j] = 1;
                        marquages+=1;
                    }   
                }                
            }
        }
    }*/

    //Utilisation du parcours BFS avec la file (indices)
    int nbElementFile;
    int* indices = (int*)malloc(ordre*sizeof(int));
        for (x=0 ; x<ordre ; x++)
            indices[x] = -1 ;
    indices[0]=s;

    nbElementFile+=1;
    while(nbElementFile>0){
        int u=indices[0];
        for (int w=0;w<ordre;w++){
            if (adjacence[u][w] && !marques[w]){
                marques[w] = 1;
                //on ajoute w a indices
                indices[nbElementFile]=w;
                nbElementFile+=1;
            }
        }
        //Supprimer u de F
        indices[0]=0;
        for (int i=1;indices[i]!=-1;i++){
            indices[i-1]=indices[i];
        }
        indices[nbElementFile-1]=0;
    }

    return(marques);
    
}

//VERSION linearisee de la matrice d'adjacence.
int* marquerVoisins (int* adjacence, int ordre, int s) {
    // Variables locales
    int *marques ; // tableau dynamique indiquant si les sommets sont marqués ou non
    int x, y ; // numéros de sommets intermédiaires
    // Allouer le tableau marques de taille « ordre »

    marques = (int*)malloc(ordre*sizeof(int));
    // Initialiser les marquages à 0
    for (x=0 ; x<ordre ; x++)
        marques[x] = 0 ;
    // Marquer le sommet s à 1
    marques[s] = 1 ;
    
    //Traitement du cas ou aucun voisin est marque.
    int somme=0;

    for (x=0 ; x<ordre ; x++)
        somme+=marques[x];
    if (somme==0){
        printf("Les composantes sont toutes non connexes");
        fflush(stdout);
        return(marques);
    }
   //methode naive avec une complexite de n^3
   /*
    int marquages=1; //Variable pour verifier si    
    while (marquages>0){
        marquages=0;
        for (int i=0;i<ordre;i++){
            if (marques[i]){
                for (int j=0;j<ordre;j++){
                    if (adjacence[ordre*i+j] && !marques[j]){
                        marques[j] = 1;
                        marquages+=1;
                    }   
                }                
            }
        }
    }*/

    //Utilisation du parcours BFS avec la file (indices)

    //Creation de la file
    int nbElementFile;
    int* indices = (int*)malloc(ordre*sizeof(int));
        for (x=0 ; x<ordre ; x++)
            indices[x] = -1 ;
    indices[0]=s;

    nbElementFile+=1;
    while(nbElementFile>0){
        int u=indices[0];
        for (int w=0;w<ordre;w++){
            if (adjacence[ordre*u+w]  && !marques[w]){
                marques[w] = 1;
                //on ajoute w a indices
                indices[nbElementFile]=w;
                nbElementFile+=1;
            }
        }
        //Supprimer u de F
        indices[0]=0;
        for (int i=1;indices[i]!=-1;i++){
            indices[i-1]=indices[i];
        }
        indices[nbElementFile-1]=0;
        nbElementFile-=1;
    }
    return(marques);  
}

//Pour verifier l'affichage
void afficherVoisinsMarque(int* marques,int ordre){
    for (int i=0;i<ordre,i++){
        if (marques[i]==1){
            printf("\nLe sommet %d est marque.",i);
        }
    }
}