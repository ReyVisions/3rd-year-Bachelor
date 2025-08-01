from PIL import Image
from math import*

def OuvrirImage():
    image = Image.open(r"D:\TELECHARGEMENTS\Mona_LisaColor.png")
    return(image)

def AfficherImage(image):
    image.show()


def AffichePixels(image):
    largeur, hauteur = image.size

    for y in range(hauteur):
        for x in range(largeur):
            couleur = image.getpixel((x, y))
            print(f"Pixel ({x}, {y}): {couleur}")

def RgbToXyz(pixel):
    R=pixel[0]/255
    G=pixel[1]/255
    B=pixel[2]/255
    X=0.4124564*R + 0.3575761*G + 0.1804375*B
    Y=0.2126729*R + 0.7151522*G + 0.0721750*B
    Z=0.0193339*R + 0.1191920*G + 0.9503041*B
    return(X,Y,Z)

def f(t):
    if t>(6/29)**3:
        return(t**(1/3))
    else:
        return(t*(1/3)*(29/6)**2 + 4/29)

def XyzToLab(X,Y,Z):
    white = RgbToXyz([255,255,255])
    Xn=white[0]
    Yn=white[1]
    Zn=white[2]
    L= 116*f(Y/Yn)-16
    a=500*(f(X/Xn)-f(Y/Yn))
    b=200*(f(Y/Yn)-f(Z/Zn))
    return(L,a,b)
    
def RgbToLab(pixel):
    valeurEnXyz = RgbToXyz(pixel)
    X=valeurEnXyz[0]
    Y=valeurEnXyz[1]
    Z=valeurEnXyz[2]
    return(XyzToLab(X,Y,Z))
    
    

#def DistanceColorimetrie(pixel1,pixel2):
#    sqrt((pixel2[0]-pixel1[0])**2+(pixel2[1]-pixel1[1])**2+(pixel2[2]-pixel1[2])**2)

image = OuvrirImage()
AfficherImage(image)
pixel = [255,255,255]
valeur = RgbToXyz(pixel)
print(valeur)

valeur = RgbToLab(pixel)
print(valeur)
