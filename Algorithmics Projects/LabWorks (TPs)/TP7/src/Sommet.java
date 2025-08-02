public class Sommet{
    private char nomSommet;
    private Sommet[] tabVoisins;
    private int nbVoisins;
    final static int nbMax=8;

    public Sommet(char nS){
        nomSommet=nS;
        tabVoisins=new Sommet[nbMax];
    }
    public Sommet(){
        tabVoisins=new Sommet[nbMax];
    }
    public void setNomSommet(char nom){
        nomSommet=nom;
    }
    public void printNomSommet(){
        System.out.print(nomSommet);
    }
    public char getNomSommet(){
        return(nomSommet);
    }
    public Sommet[] getTabVoisins(){
        return(tabVoisins);
    }
    public Sommet getTabVoisins(int i){
        return(tabVoisins[i]);
    }
    public int getNbVoisins(){
        return(nbVoisins);
    }
    public void incrNbVoisins(){
        nbVoisins++;
    }
    
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");
    }
}
