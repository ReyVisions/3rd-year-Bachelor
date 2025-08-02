public class Exercice {
    public static void main(String[] args) throws Exception {
        
        long debutTemps = System.currentTimeMillis();
        GestionImage gestionImage = new GestionImage("Mona_Lisa.jpg");
        gestionImage.afficherImage();
        
        /**
         * Conversion des valeurs du JFrame de int en 3 entiers RGB
         */
        gestionImage.construireTableauPixels();

        /**
         * Verification de la conversion RGB.
         */
        //gestionImage.afficherTableauPixels();

        /**
         * Creation d'un graphe de meme taille que le tableau de gestionImage
         */
        int hauteur = gestionImage.getHauteur();
        int largeur = gestionImage.getLargeur();
        Graphe grapheHolder = new Graphe(hauteur,largeur);

        /**Construction du graphe
         * On convertit rgb en CIelab puis on le copie dans le graphe de l'instance grapheHolder
         */
        for (int i=0;i<hauteur;i++){
            for (int j=0;j<largeur;j++){
                Pixel pixel = gestionImage.getPixel(i,j);
                double[] valeurLab = gestionImage.rgbToLab(pixel);
                grapheHolder.ajouterSommet(i,j,valeurLab[0],valeurLab[1],valeurLab[2]);
            }
        }

        //grapheHolder.printValeurs();

        /**
         * Verification visuelle de si le nom du dernier sommet vaut bien largeur*hauteur-1
         */
        //grapheHolder.printListeAdjacence();
        //System.out.println(largeur*hauteur);

        /**
         * Creation des aretes en 8 connexite.
         */
        //System.out.println(hauteur);
        //System.out.println(largeur);
        grapheHolder.aretes8connexite();
        //grapheHolder.printListeAdjacence();
        //grapheHolder.printValeurs();
        //grapheHolder.printListeArete();

        grapheHolder.printChemin(grapheHolder.dijkstra(0,0,0,255));
        long finTemps = System.currentTimeMillis();

        System.out.println("Temps d'execution du programme:"+ (finTemps-debutTemps)/1000);

    }
}
