Liste des erreurs et ameliorations:

1) IL ne s'agit pas tout a fait de l'algorithme de Welsh Powell

Lorsque le sommet n a un de ses voisins colorie, il change de couleur mais pour les arretes suivantes 
il ne revient pas sur la couleur precedente qu'il pourrait potentiellement colorier.
Il colorie certes toutes les aretes, mais il pourrait colorier le graphe avec moins de couleurs. 

Par exemple: Le sommet 0 a une couleur 0, le sommet 1
est un voisin du premier sommet. Comme ils sont voisins, le sommet 1 aura une couleur attribuee de 1. Cependant d'autres sommets
peuvent avoir eventuellement la couleur 0.

2) Erreur de definition de la structure:

on definit struct Graph sans lui donner de nom
Ensuite on ecrit struct Graph* en parametre ce qui essaie de creer une autre structure dans les parametres ce qu'on ne veut pas 
et qui est en plus synthaxiquement incorrect.
(warning: 'struct Graph' declared inside parameter list will not be visible outside of this definition or declaration)

3) Le tableau color est mal initialise. Il faut mettre tous les elements du graphe a -1

4) POur des raisons de performances et d'efficacite, on prefere l'utilisation de pointeurs pour afficher les matrices