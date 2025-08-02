#ifndef ARBRE_H_
#define ARBRE_H_


typedef struct noeud{
    int valeur;
    struct noeud* filsG;
    struct noeud* filsD;
}noeud;

typedef struct Arbre{
    int taille;
    noeud *racine;
}Arbre;

void initArbre(Arbre *arbre);

void remplirArbre(int val,Arbre *arbre);

void remplirArbreParOrdre(int val,char *instructions, Arbre *arbre);

char* intEnArbo(int indiceA);

void freeNoeud(noeud *node);

void afficherArbre(noeud* noeud);

void effacerNoeud(char *instructions, Arbre *arbre);

int calculerNoeuds(noeud* node);

void UI();

void afficherPrefixe(noeud* noeud);

void afficherInfixe(noeud* noeud);

void afficherPostfixe(noeud* noeud);

#endif /* ARBRE_H_ */