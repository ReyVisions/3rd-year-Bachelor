public class Arete {
    private Sommet sommet1;
    private Sommet sommet2;
    private int poids;

    public Arete(Sommet sommet1,Sommet sommet2, int poids){
        this.sommet1=sommet1;
        this.sommet2=sommet2;
        this.poids=poids;
    }
    public void printArete(){
        System.out.println(sommet1.getNomSommet()+ ", " +sommet2.getNomSommet()+", "+poids);
    }
    public Sommet getSommet1(){
        return(sommet1);
    }
    public Sommet getSommet2(){
        return(sommet2);
    }
    public int getPoids(){
        return(poids);
    }
}
