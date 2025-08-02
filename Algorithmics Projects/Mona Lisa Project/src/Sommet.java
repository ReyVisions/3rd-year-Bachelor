public class Sommet{
    //Variables de colorimetries necessaire pour calculer le poids entre deux aretes.
    private double L;
    private double A;
    private double B;
    //Le nom est un int. Il suit l'ordre de parcours de ligne par ligne et incremente. (nom=0 puis 1 puis 2 etc.. )
    private int nom;
    private static int nbSommet=0;
    //tableau des voisins
    private Sommet[] tabVoisins;
    private int nbVoisins;
    //En 8 connexite, on a au maximum 8 voisins.
    final static int nbMax=8;

    public Sommet(){
        nom=nbSommet;
        nbSommet++;
        L=0.0;
        A=0.0;
        B=0.0;
        tabVoisins=new Sommet[nbMax];
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
    public void setL(double l){
        L=l;
    }
    public void setA(double a) {
        A = a;
    }
    public void setB(double b) {
        B = b;
    }

    public double getA() {
        return A;
    }
    public double getB() {
        return B;
    }
    public double getL() {
        return L;
    }

    public void printNom(){
        System.out.print(nom);
    }
    public int getNom(){
        return(nom);
    }
    public void printValeurSommet(){
        System.out.print(L+" "+A+" "+B);
    }
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");
    }
}
