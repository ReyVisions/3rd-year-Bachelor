#ifndef FILE_H_
#define FILE_H_

typedef struct noeud{
    int valeur;
    struct noeud* pred;
    struct noeud* suiv;
}noeud;

typedef struct t_file{
    int taille;
    noeud *debut;
    noeud *fin;
}t_file;


void initDliste(t_file *dliste);

void enfiler(int val, t_file *dliste);

int defiler(t_file *dliste);

void afficherDliste(t_file *dliste);

void plusCourtChemin (int**adjacence, int ordre, int s, int *l, int *pred);

#endif /* FILE_H_ */