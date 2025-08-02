/**
 * Classe arbre qui est le type de retour de l'algorithme de Dijkstra.
 */

public class Arbre{
    private int tailleArbre;
    private Arete[] arbreCouvrant;
    private int tailleListeSommets;
    private Sommet[] listeSommets;
    
    public Arbre(int tailleGraphe){
        arbreCouvrant= new Arete[tailleGraphe];
        listeSommets = new Sommet[tailleGraphe];
        tailleArbre=0;
        tailleListeSommets=0;
    }
    public void ajouterArete(Arete branche){
        if (tailleArbre<arbreCouvrant.length){
            arbreCouvrant[tailleArbre]=branche;
            tailleArbre++;
            int occurence1=0;
            int occurence2=0;
            for (int i=0;i<tailleListeSommets;i++){
                Sommet elemListe= listeSommets[i];
                if (elemListe==branche.getSommet1()){
                    occurence1++;
                }else if (elemListe==branche.getSommet2()){
                    occurence2++;
                }
            }
            if (occurence1==0){
                listeSommets[tailleListeSommets]=branche.getSommet1();
                tailleListeSommets++;
            }
            if (occurence2==0){
                listeSommets[tailleListeSommets]=branche.getSommet2();
                tailleListeSommets++;
            }
        }
    }
    public Sommet getListeSommets(int i){
        return(listeSommets[i]);
    }
    public int getTailleListeSommets(){
        return(tailleListeSommets);
    }
    public void printArbreCouvrant(){
        for (int i=0;i<tailleArbre;i++){
            arbreCouvrant[i].printArete();
        }
    }
    public boolean contient(Sommet sommet){
        for (int i=0;i<tailleListeSommets;i++){
            if (sommet==listeSommets[i]){
                return(true);
            }
        }
        return(false);
    }
}