import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class GestionImage {

    private BufferedImage image;
    private int hauteur;
    private int largeur;
    private String chemin;
    private Pixel[][] tabPixels;
    /**
     * Constructeur
     * @param chemin chemin du fichier, de l'image surlaquelle on veut travailler
     */
    public GestionImage(String chemin){
        this.chemin = chemin;
        image = ouvrirImage(chemin);
        largeur = image.getWidth();
        hauteur = image.getHeight();
    }

    public static void main(String[] args) {
        /* */
        GestionImage gestionImage = new GestionImage("D:\\TELECHARGEMENTS\\Mona_LisaColor.png");
        gestionImage.afficherImage();
        
        gestionImage.construireTableauPixels();
        //gestionImage.afficherTableauPixels();

        Pixel pixel = new Pixel(255,255,255);

        
        double[] valeurXyz = gestionImage.rgbToXyz(pixel);
        gestionImage.afficherValeur("XYZ", valeurXyz);
        
        double[] valeurLab = gestionImage.rgbToLab(pixel);
        gestionImage.afficherValeur("Lab", valeurLab);
    }
    /**
     * Methode complementaire au main pour afficher les valeurs des tests de calculs
     */
    public void afficherValeur(String espace, double[] valeur) {
        System.out.println(espace + " :");
        for (double v : valeur) {
            System.out.print(v + " ");
        }
        System.out.println();
    }

    /**
     * Methodes concernant l'ouverture, l'affichage d'image
     * 
     */
    public BufferedImage getImage(){
        return(image);
    }

    public BufferedImage ouvrirImage(String chemin) {
        try {
            return ImageIO.read(new File(chemin));
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public void afficherImage() {
        JFrame frame = new JFrame("Afficher une image");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Charger l'image
        ImageIcon imageIcon = new ImageIcon(chemin);

        // Créer un JLabel pour afficher l'image
        JLabel label = new JLabel(imageIcon);

        // Ajouter le JLabel à la JFrame
        frame.getContentPane().add(label);

        // Ajuster la taille de la JFrame à la taille de l'image
        frame.pack();

        // Centrer la JFrame sur l'écran
        frame.setLocationRelativeTo(null);

        // Rendre la JFrame visible
        frame.setVisible(true);
    }

    /**
     * Methodes concernant la conversion rgb en Cie lab
     * 
     */
    public double[] rgbToXyz(Pixel pixel) {
        double R = pixel.getRed() / 255.0;
        double G = pixel.getGreen() / 255.0;
        double B = pixel.getBlue() / 255.0;
        
        R = (R > 0.04045) ? Math.pow((R + 0.055) / 1.055, 2.4) : R / 12.92;
        G = (G > 0.04045) ? Math.pow((G + 0.055) / 1.055, 2.4) : G / 12.92;
        B = (B > 0.04045) ? Math.pow((B + 0.055) / 1.055, 2.4) : B / 12.92;
        
        R*=100;
        G*=100;
        B*=100;

        double X=0.4124564*R + 0.3575761*G + 0.1804375*B;
        double Y=0.2126729*R + 0.7151522*G + 0.0721750*B;
        double Z=0.0193339*R + 0.1191920*G + 0.9503041*B;
        return new double[]{X, Y, Z};
    }
    
    public double[] rgbToLab(Pixel pixel) {
        double[] valeurXyz = rgbToXyz(pixel);
    
        double X = valeurXyz[0];
        double Y = valeurXyz[1];
        double Z = valeurXyz[2];
    
        double[] valeurWhite = rgbToXyz(new Pixel(255, 255, 255));
        double Xn = valeurWhite[0];
        double Yn = valeurWhite[1];
        double Zn = valeurWhite[2];
    
        double L = 116.0 * f(Y / Yn) - 16.0;
        double a = 500.0 * (f(X / Xn) - f(Y / Yn));
        double b = 200.0 * (f(Y / Yn) - f(Z / Zn));

        return new double[]{L, a, b};
    }
    

    public double f(double t) {
        if (t > Math.pow(6.0 / 29.0, 3.0)) {
            return Math.pow(t, 1.0 / 3.0);
        } else {
            return t * (1.0 / 3.0) * Math.pow(29.0 / 6.0, 2) + 4.0 / 29.0;
        }
    }

    /**
     * Methodes servant a la creation du tableau de pixels
     */
    public void construireTableauPixels() {
        tabPixels = new Pixel[hauteur][largeur];
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < largeur; j++) {
                tabPixels[i][j] = new Pixel(image.getRGB(j, i));
            }
        }
    }
    public void afficherTableauPixels(){
        for (int i=0;i<hauteur;i++){
            for (int j=0;j<largeur;j++){
                tabPixels[i][j].printPixel();
            }
        }
    }
    public int getHauteur(){
        return(hauteur);
    }
    public int getLargeur(){
        return(largeur);
    }
    public Pixel getPixel(int i,int j){
        return(tabPixels[i][j]);
    }
}
