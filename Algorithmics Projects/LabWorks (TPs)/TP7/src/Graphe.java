import java.util.*;

public class Graphe {
    private int nbSommet;
    private int nbArete;
    private Sommet[] graphe;
    private Arete[] listeArete;
    private final int INFINI = 10000;

    public Graphe(int sommetMax) {
        nbSommet=0;
        nbArete=0;
        graphe=new Sommet[sommetMax];
        listeArete=new Arete[sommetMax*(sommetMax)/2];
    }

    public void ajouterSommet(char nom) {
        if(sommetExiste(nom)==-1){
            graphe[nbSommet]=new Sommet(nom);
            nbSommet++;
        }
        else{
            System.out.println("Le sommet existe deja!");
        }
    }
    public void ajouterArete(char nomSommet1, char nomSommet2, int poids){
        int i=sommetExiste(nomSommet1);
        int j=sommetExiste(nomSommet2);
        Sommet sommet1=graphe[j];
        Sommet sommet2=graphe[i];
        if (i!=-1 && j!=-1 && areteExiste(sommet1, sommet2)==-1){      
            if (sommet1.getNbVoisins()==Sommet.nbMax){
                System.out.println("Le nombre de voisins pour le sommet1 est sature");
                return;
            }else if(sommet2.getNbVoisins()==Sommet.nbMax){
                System.out.println("Le nombre de voisins pour le sommet2 est sature");
                return;
            }
            sommet1.getTabVoisins()[sommet1.getNbVoisins()]=sommet2;
            sommet2.getTabVoisins()[sommet2.getNbVoisins()]=sommet1;
            sommet1.incrNbVoisins();
            sommet2.incrNbVoisins();
        }
        else if(i==-1){
            System.out.println("Le sommet en premier paremetre n'existe pas.");
        }
        else if(j==-1){
            System.out.println("Le sommet en deuxieme paremetre n'existe pas ");
        }
        listeArete[nbArete]=new Arete(sommet1, sommet2, poids);
    }
    public int sommetExiste(char nomSommet1){
        for (int i=0;i<nbSommet;i++){
            if(nomSommet1==graphe[i].getNomSommet()){
                return(i);
            }
        }
        return(-1);
    }
    public int sommetExiste(Sommet sommet){
        for (int i=0;i<nbSommet;i++){
            if(sommet==graphe[i]){
                return(i);
            }
        }
        return(-1);
    }
    public int areteExiste(Sommet sommet1, Sommet sommet2){
        for (int i=0;i<sommet1.getNbVoisins();i++){
            if (graphe[i].getNomSommet()==sommet2.getNomSommet()){
                return(i);
            }
        }
        for (int j=0;j<sommet2.getNbVoisins();j++){
            if (graphe[j].getNomSommet()==sommet1.getNomSommet()){
                return(j);
            }
        }
        return(-1);
    }
    public Sommet[] getGraphe(){
        return(graphe);
    }
    public Sommet getGraphe(int i){
        return(graphe[i]);
    }
    public int chercherPoids(Sommet sommet1, Sommet sommet2){
        for (int i=0;i<nbArete;i++){
            Arete arete=listeArete[i];
            if (arete.getSommet1()==sommet1){
                if (arete.getSommet2()==sommet2){
                    return(arete.getPoids());
                }
            }
            if (arete.getSommet1()==sommet2){
                if (arete.getSommet2()==sommet1){
                    return(arete.getPoids());
                }
            }
        }
        return(-1);
    }

    public void printGraphe(){
        if (nbSommet<1){
            System.out.print("\n[]");
        }
        else{
            System.out.print("\n[");
            for (int i=0;i<nbSommet-1;i++){
                Sommet sommet=graphe[i];  
                sommet.printNomSommet();
                System.out.print("[");
                if (sommet.getNbVoisins()>0){
                    for (int j=0;j<sommet.getNbVoisins()-1;j++){
                        sommet.getTabVoisins()[j].printNomSommet();
                        System.out.print(",");
                    }
                    sommet.getTabVoisins()[sommet.getNbVoisins()-1].printNomSommet();
                    System.out.print("],");  
                }
                else{
                    System.out.print("]");
                }
            }
            
            Sommet sommet = graphe[nbSommet-1];
            sommet.printNomSommet();
            System.out.print("[");
            if (sommet.getNbVoisins()>0){
                for (int j=0;j<sommet.getNbVoisins()-1;j++){
                    sommet.getTabVoisins()[j].printNomSommet();
                    System.out.print(",");
                }
                sommet.getTabVoisins()[sommet.getNbVoisins()-1].printNomSommet();
                System.out.print("]]");
            }
            else{
                System.out.print("]]");
            }
        }
    }
    /**
     * Algorithme qui reprend le pseudo code du cours.
     * @param depart sommet ou l'on commence l'algo
     * 
     * Variables locales a la foncion:
     * @param areteDepart Fausse arete qui represente seulement la racine de l'arbre.
     * @param distanceProvisoire Liste de sommet ayant pour indice i la distance du sommet a l'indice i du graphe (graphe[i]).
     * @param pere Liste qui de meme que distanceProvisoire a a l'indice i le pere du sommet a l'indice i du graphe (graphe[i]).
     * @return arbreCouvrantMini arbre couvrant minimum qui sera en sortie.
     */
    public Arbre dijkstra(Sommet depart){
        //Arete areteDepart;
        Arbre arbreCouvrantMini;
        int[] distProvisoire;
        Sommet[] pere;
        ArrayList<Sommet> tabSommetRestants;
        int[] distFinale;
        Sommet dernierAjout;

        //racine de l'arbre (fausse arete)
        //areteDepart= new Arete(depart,depart,0);
        //T = {u}
        arbreCouvrantMini= new Arbre(nbSommet);
        //arbreCouvrantMini.ajouterArete(areteDepart);

        distProvisoire = new int[nbSommet];
        distFinale = new int[nbSommet];
        pere = new Sommet[nbSommet];        
        tabSommetRestants = new ArrayList<>();
        copierGrapheDansArrayList(tabSommetRestants);

        for (int i=0;i<nbSommet;i++){
            distProvisoire[i]=INFINI;
            pere[i]=null;
            distFinale[i]=INFINI;
        }
        distFinale[sommetExiste(depart)] = 0;
        dernierAjout= depart;
        tabSommetRestants.remove(sommetExiste(dernierAjout));
        int x=1;
        while (!grapheEgalArbre(graphe, arbreCouvrantMini)){

            System.out.println(x);
            Sommet v;
            for (int i=0;i<dernierAjout.getNbVoisins();i++){      
                v=dernierAjout.getTabVoisins(i);
                int poids= chercherPoids(dernierAjout, v);
                if (distFinale[sommetExiste(dernierAjout)]+poids<distProvisoire[sommetExiste(v)]){
                    distProvisoire[sommetExiste(v)]=distFinale[sommetExiste(dernierAjout)]+poids;
                    pere[sommetExiste(v)]=dernierAjout;
                }
            }
            //Selectionner v pas dans l'arbre tel que dist_prov est minimum
            int min=distProvisoire[0];
            int indice=0;
            for (int i=0;i<nbSommet;i++){
                               
                if (!arbreCouvrantMini.contient(graphe[i]) && min>distProvisoire[i]){
                    min = distProvisoire[i];
                    indice=i;
                }
            }
            v=graphe[indice];
            arbreCouvrantMini.ajouterArete(new Arete(pere[indice],v,chercherPoids(pere[indice],v)));
            arbreCouvrantMini.printArbreCouvrant();
            distFinale[sommetExiste(dernierAjout)]=distProvisoire[indice];
            dernierAjout=v;
            int indexDernierAjout = sommetExiste(dernierAjout);
            if (indexDernierAjout != -1) {
                tabSommetRestants.remove(indexDernierAjout);
            } else {
                System.out.println("Le sommet n'existe pas dans la liste des sommets restants.");
            }
            x++;
        }
        return(arbreCouvrantMini);
        
    }

    public boolean grapheEgalArbre(Sommet[] graphe, Arbre arbre){
        if (nbSommet!=arbre.getTailleListeSommets()){
            return(false);
        }
        else{
            int occurence;
            for (int i=0;i<nbSommet;i++){
                occurence=0;
                for (int j=0;j<arbre.getTailleListeSommets();j++){
                    if (graphe[i]==arbre.getListeSommets(j)){
                        occurence++;
                    }
                }
                if (occurence!=1){
                    return(false);
                }
            }
        }
        return(true);
    }
    public void copierGrapheDansArrayList(ArrayList<Sommet> tabSommetRestants){
        for (int i=0;i<nbSommet;i++){
            tabSommetRestants.add(graphe[i]);
        }
    }
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");
    }
}
