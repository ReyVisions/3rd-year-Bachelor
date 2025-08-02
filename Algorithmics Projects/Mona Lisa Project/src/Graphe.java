import java.util.*;

public class Graphe {
    private int nbSommet;
    private int xMax;
    private int yMax;
    private int nbArete;
    private Sommet[][] graphe;
    private Arete[] listeArete;

    public Graphe(int xMax, int yMax) {
        this.xMax=xMax;
        this.yMax=yMax;
        nbSommet=0;
        nbArete=0;
        graphe=new Sommet[xMax][yMax];
        for (int i=0;i<xMax;i++){
            for (int j=0;j<yMax;j++){
                graphe[i][j]=null;
            }
        }
        //On approxime la taille de la liste d'arete a 8 fois le nombre total de sommet, car il y a au maximum 8 aretes par sommet.
        int nbSommetMax = xMax*yMax;
        listeArete=new Arete[8*nbSommetMax];
    }
        
    public Sommet[][] getGraphe(){
        return(graphe);
    }
    public Sommet getSommet(int x, int y){
        return(graphe[x][y]);
    }
    public int getX(){
        return(xMax);
    }
    public int getY(){
        return(yMax);
    }

    public void ajouterSommet(int x, int y, double l, double a, double b) {
        if (graphe[x][y]==null){
            graphe[x][y]=new Sommet();
            nbSommet++;
            graphe[x][y].setL(l);
            graphe[x][y].setA(a);
            graphe[x][y].setB(b);
        }
        else{
            System.out.println("Le sommet existe deja");
        }
        
    }
    /**
     * Methode permettant de ajouter une arete entre deux sommets s'il elle n'existe pas. Et calcule le poids de l'arete.
     * @param x1 numero de ligne su sommet 1
     * @param y1 numero de colonne su sommet 1
     * @param x2 numero de ligne su sommet 2
     * @param y2 numero de colonnesu sommet 1
     * Cree une arete entre les deux sommets et l'ajoute dans la liste d'aretes
     */
    public void ajouterArete(int x1, int y1, int x2, int y2){
        Sommet sommet1=getSommet(x1, y1);
        Sommet sommet2=getSommet(x2, y2);
        if (areteExiste(sommet1, sommet2)){
            //System.out.println("Une arete entre les deux sommets existe deja");
            return;
        }
        if (sommet1.getNbVoisins()==Sommet.nbMax){
            System.out.println("Le nombre de voisins pour le sommet1 est sature");
            return;
        }else if(sommet2.getNbVoisins()==Sommet.nbMax){
            System.out.println("Le nombre de voisins pour le sommet2 est sature");
            return;
        }
        if (x1<xMax && y1<yMax && x2<xMax && y2<yMax && x1>=0 && y1>=0 && x2>=0 && y2>=0){ 
            
            
            sommet1.getTabVoisins()[sommet1.getNbVoisins()]=sommet2;
            sommet2.getTabVoisins()[sommet2.getNbVoisins()]=sommet1;
            sommet1.incrNbVoisins();
            sommet2.incrNbVoisins();
        }
        else if(x1>=xMax || y1>=yMax){
            System.out.println("Le sommet en premier paremetre n'existe pas.");
            return;
        }
        else if(x2>=xMax || y2>=yMax){
            System.out.println("Le sommet en deuxieme paremetre n'existe pas ");
            return;
        }
        //Calcul du poids (distance euclidienne entre les valeurs L a b des deux sommets.)
        double poids = Math.abs(Math.pow(Math.pow(sommet2.getL()-sommet1.getL(), 2.0) + Math.pow(sommet2.getA()-sommet1.getA(), 2.0) + Math.pow(sommet2.getB()-sommet1.getB(), 2.0), 1.0/2.0));
        //System.out.println("Poids calculé pour l'arête entre " + sommet1.getNom() + " et " + sommet2.getNom() + ": " + poids);
        listeArete[nbArete]=new Arete(sommet1, sommet2, poids);
        nbArete++;
    }

    public boolean areteExiste(Sommet sommet1, Sommet sommet2){
        for (int i=0;i<sommet1.getNbVoisins();i++){
            if (sommet1.getTabVoisins()[i]==sommet2){
                return(true);
            }
        }
        for (int j=0;j<sommet2.getNbVoisins();j++){
            if (sommet2.getTabVoisins()[j]==sommet1){
                return(true);
            }
        }
        return(false);
    }
    /**
     * Methode pour creer des aretes selon la 8 connexite du sommet.
     */
    public void aretes8connexite(){
        for (int i=0;i<xMax;i++){
            for (int j=0;j<yMax;j++){
                if (indicesExistent(i+1, j-1)){
                    ajouterArete(i,j,i+1,j-1);
                }
                if (indicesExistent(i+1, j)){
                    ajouterArete(i,j,i+1,j);
                }
                if (indicesExistent(i+1, j+1)){
                    ajouterArete(i,j,i+1,j+1);
                }
                if (indicesExistent(i, j-1)){
                    ajouterArete(i,j,i,j-1);
                }
                if (indicesExistent(i, j+1)){
                    ajouterArete(i,j,i,j+1);
                }
                if (indicesExistent(i-1, j-1)){
                    ajouterArete(i,j,i-1,j-1);
                }
                if (indicesExistent(i-1, j)){
                    ajouterArete(i,j,i-1,j);
                }
                if (indicesExistent(i-1, j+1)){
                    ajouterArete(i,j,i-1,j+1);
                }
            }
        }
    }
    /**
     * Methode pour creer des aretes selon la 8 connexite du sommet.
     * @return true si l'indice est dans le tableau, false s'il ne l'est pas
     */
    public boolean indicesExistent(int i, int j){
        if(i<0 || j<0 || xMax-1<i || yMax-1<j){
            return(false);
        }
        else{
            return(true);
        }
    }
    /**
     * Methode pour chercher le poids de l'arete entre sommet1 et sommet2 s'il existe.
     * @return le poids de l'arete
     */
    public double chercherPoids(Sommet sommet1, Sommet sommet2) {
        for (int i = 0; i < nbArete; i++) {
            Arete arete = listeArete[i];
            if ((arete.getSommet1() == sommet1 && arete.getSommet2() == sommet2) || (arete.getSommet1() == sommet2 && arete.getSommet2() == sommet1)) {
                return arete.getPoids();
            }
        }
        return -1.0;
    }
    /**
     * Algorithme affichant le graphe en liste d'adjacence.
     */
    public void printListeAdjacence(){
        if (nbSommet<1){
            System.out.print("\n[]");
        }
        else{
            System.out.print("\n[");
            for (int i=0; i<xMax; i++){
                for (int j=0; j<yMax; j++){
                    Sommet sommet=graphe[i][j];  
                    sommet.printNom();
                    System.out.print("[");
                    if (sommet.getNbVoisins()>0){
                        for (int k=0;k<sommet.getNbVoisins()-1;k++){
                            sommet.getTabVoisins()[k].printNom();
                            System.out.print(",");
                        }
                        sommet.getTabVoisins()[sommet.getNbVoisins()-1].printNom();
                        if (i==xMax-1 && j==yMax-1){
                            System.out.println("]]");
                        }else{
                            System.out.println("],"); 
                        }
                        
                    }
                    else{
                        if (i==xMax-1 && j==yMax-1){
                            System.out.println("]]");
                        }else{
                            System.out.print("],");  
                        }
                    }
                }
            }
        }
        
    }
    /**
     * Algorithme affichant les valeurs L A B des sommets.
     */
    public void printValeurs(){
        if (nbSommet<1){
            System.out.print("\n[]");
        }
        else{
            System.out.print("\n[");
            for (int i=0; i<xMax; i++){
                for (int j=0; j<yMax; j++){
                    Sommet sommet=graphe[i][j];
                    System.out.print("[");  
                    sommet.printValeurSommet();
                       
                    if (i==xMax-1 && j==yMax-1){
                        System.out.print("]]");
                    }else{
                        System.out.println("],");  
                    }        
                }
            }
        }       
    }
    public void printListeArete(){
        if (nbArete<1){
            System.out.print("\n[]");
        }
        else{
            System.out.print("\n[");
            for (int i=0; i<nbArete; i++){
                Arete arete=listeArete[i];
                System.out.print("[");  
                arete.printArete();   
                if (i==xMax-1){
                    System.out.print("]]");
                }else{
                    System.out.println("],");  
                }        
            }
        }       
    }
    
    /**
     * Algorithme de Dijsktra
     * @param x1,y1 coordonnees du sommet ou l'on commence l'algo
     * @param x2,y2 coordonnees du sommet ou l'on veut arriver
     * 
     * Variables locales a la foncion:
     * @param areteDepart Fausse arete qui represente seulement la racine de l'arbre.
     * @param distanceProvisoire Liste de sommet ayant pour indice i la distance du sommet a l'indice i du graphe (graphe[i]).
     * @param pere Liste qui de meme que distanceProvisoire a a l'indice i le pere du sommet a l'indice i du graphe (graphe[i]).
     * @return Une liste d'arete montrant le chemin parcouru le moins couteux.
     */
    
    public List<Arete> dijkstra(int x1, int y1, int x2, int y2) {
        Sommet sommetDepart = getSommet(x1, y1);
        Sommet sommetArrivee = getSommet(x2, y2);
    
        if (sommetDepart == null || sommetArrivee == null) {
            System.out.println("Les sommets n'existent pas dans le graphe");
            return null;
        }
    
        Map<Sommet, Double> distProvisoire = new HashMap<>();
        Map<Sommet, Sommet> pere = new HashMap<>();
        PriorityQueue<Sommet> filePrioritaire = new PriorityQueue<>(Comparator.comparingDouble(distProvisoire::get));
    
        for (int i = 0; i < xMax; i++) {
            for (int j = 0; j < yMax; j++) {
                distProvisoire.put(graphe[i][j], Double.MAX_VALUE);
            }
        }
    
        distProvisoire.put(sommetDepart, 0.0);
        filePrioritaire.add(sommetDepart);
        int x=0;
        while (!filePrioritaire.isEmpty()) {
            System.out.println(x);
            Sommet dernierAjout = filePrioritaire.poll();
            Sommet v=null;
            for (int i = 0; i < dernierAjout.getNbVoisins(); i++) {
                v = dernierAjout.getTabVoisins(i);
                double poids = chercherPoids(dernierAjout, v);

                System.out.println("Voisin : " + v.getNom() + ", Poids : " + poids);

                if (distProvisoire.get(dernierAjout) + poids < distProvisoire.get(v)) {
                    distProvisoire.put(v, distProvisoire.get(dernierAjout) + poids);
                    pere.put(v, dernierAjout);
                    filePrioritaire.add(v);
                    System.out.println("Mise à jour de la distance pour le sommet " + v.getNom());
                }   
            }
            // Sortir de la boucle si on atteint le sommet d'arrivée
            if (dernierAjout.equals(sommetArrivee)) {
                break;
            }
            filePrioritaire.remove(dernierAjout);
            dernierAjout=v;
            x++;
        }
    
        // Construction du chemin
        List<Arete> chemin = new ArrayList<>();
        Sommet sommetActuel = sommetArrivee;
        while (pere.containsKey(sommetActuel)) {
            Sommet sommetPere = pere.get(sommetActuel);
            double poids = chercherPoids(sommetPere, sommetActuel);
            chemin.add(new Arete(sommetPere, sommetActuel, poids));
            sommetActuel = sommetPere;
        }
        Collections.reverse(chemin);
    
        return chemin;
    }

    public void printChemin(List<Arete> chemin){
        for (int i=0;i<chemin.size();i++){
            chemin.get(i).printArete();
        }
    }
    
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");
    }
}
