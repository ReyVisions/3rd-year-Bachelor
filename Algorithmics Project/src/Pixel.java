public class Pixel {
    private int R;
    private int G;
    private int B;
    /**
     * Le constructeur prend uniquement la composante utile pour la couleur (R,B ou B).
     * @param pixelValue Valeur des trois pixels en binaire en un int
     */

    public Pixel(int pixelValue){
        R = (pixelValue >>> 16) & 0xFF;
        G = (pixelValue >>> 8) & 0xFF;
        B = pixelValue & 0xFF;
    }

    public Pixel(int R, int G ,int B){
        this.R =R;
        this.G =G;
        this.B =B;
    }
    public int getRed() {
        return R;
    }

    public int getGreen() {
        return G;
    }

    public int getBlue() {
        return B;
    }

    public int[] getRGB() {
        return new int[]{R, G, B};
    }


    public void setR(int red) {
        R = red & 0xFF;
    }

    public void setG(int green) {
        G = green & 0xFF;
    }

    public void setB(int blue) {
        B = blue & 0xFF;
    }

    public void printPixel(){
        System.out.println("["+R+","+G+","+B+"]");
    }


}
