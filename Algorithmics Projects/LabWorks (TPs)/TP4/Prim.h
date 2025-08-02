#ifndef PRIM_H_
#define PRIM_H_

typedef struct noeud{
    int x;
    int ymin;
    int poids;
    struct noeud* pred;
    struct noeud* suiv;
}noeud;

typedef struct DListe{
    int taille;
    noeud *debut;
    noeud *fin;
}DListe;



DListe * prim (float **adjacencePoids, int ordre) ;

float** matriceAdjPoids(int ordre);

void afficherAdjacence(float** matrice,int nbsommets);

void initDliste(DListe *dliste);

void ajoutNoeudDebut(int val1, int val2, int poids, DListe *dliste);

void ajoutNoeudFin(int val1, int val2, int poids, DListe *dliste);

void inserNoeud(int val1,int val2, int poids, int indice, DListe *dliste);

void retirerNoeud(int indice, DListe *dliste);

void remplirDListe(int x, int ymin, int poids, DListe* arbre);

#endif /* PRIM_H_ */