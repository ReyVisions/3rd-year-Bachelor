public class Arete {
    private int nomSommet1;
    private int nomSommet2;
    private Sommet sommet1;
    private Sommet sommet2;
    private double poids;

    public Arete(Sommet sommet1, Sommet sommet2, double poids){
        this.sommet1=sommet1;
        this.sommet2=sommet2;
        this.nomSommet1=sommet1.getNom();
        this.nomSommet2=sommet2.getNom();
        this.poids=poids;
    }
    public void printArete(){
        System.out.print(nomSommet1+ ", " +nomSommet2+", "+poids);
    }
    public int getNomSommet1(){
        return(nomSommet1);
    }
    public int getNomSommet2(){
        return(nomSommet1);
    }
    public Sommet getSommet1(){
        return(sommet1);
    }
    public Sommet getSommet2(){
        return(sommet2);
    }
    public double getPoids(){
        return(poids);
    }
}
