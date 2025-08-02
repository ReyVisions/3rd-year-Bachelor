#ifndef GRAPHE2_H_
#define GRAPHE2_H_

typedef struct noeud{
    char nom;
    int nbVoisins;
    struct noeud* voisins[];
}noeud;

typedef struct Graphe{
    int taille;
    noeud* sommets[];
}Graphe;

void initGraphe(Graphe *graphe);

int SommetExiste(char name, Graphe* graphe);

void creerSommet(char name, Graphe* graphe);

void lierDeuxSommets(char nomNode1, char nomNode2, Graphe* graphe);

void afficherGraphe(Graphe* graphe);

Graphe* chargeGraphe();


#endif /* GRAPHE2_H_ */