Explication de intEnArbo():
 

    //On decide de parcourir les n noeuds en BFS.  
    //On remarque que l'arborescence lorsque l'on stocke un chiffre dans l'arbre est tres proche du binaire,
    /*Exemple: l'arborescence (comme decrit dans mon TP0) de chaque noeud parcouru est: 
    (racine) 0 1 00 01 10 11 000 001 010 etc..
    En rajoutant un 1 devant chaque sequence, on a:
    (racine) 10 11 100 101 110 111 1000 1001 1010 etc..
    ce qui fait en base 10:
    (racine) 2 3 4 5 6 7 8 9 10 etc...
    alors que l'on souhaite 
    (0) 1 2 3 4 5 6 7 8 9 10. donc on decale tout les entiers de +1 pour passer
    de cette ligne a la ligne du dessus.*/

    //Pour transformer notre ordre n en arborescence, on fait donc le chemin inverse.