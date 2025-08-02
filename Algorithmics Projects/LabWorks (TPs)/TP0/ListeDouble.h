#ifndef LISTEDOUBLE_H_
#define LISTEDOUBLE_H_

typedef struct noeud{
    int valeur;
    struct noeud* pred;
    struct noeud* suiv;
}noeud;

typedef struct DListe{
    int taille;
    noeud *debut;
    noeud *fin;
}DListe;


void initDliste(DListe *dliste);

void ajoutNoeudDebut(int val, DListe *dliste);

void ajoutNoeudFin(int val, DListe *dliste);

void inserNoeud(int val, int indice, DListe *dliste);

void retirerNoeud(int indice, DListe *dliste);

void effacerDliste(DListe *dliste);

void afficherDliste(DListe *dliste);

void UI();

#endif /* LISTEDOUBLE_H_ */