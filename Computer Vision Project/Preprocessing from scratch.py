import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as Image
import cv2
import math

def OpenImage(route):
    img = Image.imread(route)
    return(img)

def PlotImage(img):
    plt.imshow(img, cmap='gray')
    plt.show()

def GreyImage(img):
    height=img.shape[0]
    width=img.shape[1]
    gris=np.zeros((height,width),dtype=np.uint8)
    for i in range(height):
        for j in range(width):
            r, g, b = img[i][j]
            gris[i][j] = int(0.299 * r + 0.587 * g + 0.114 * b)
    return(gris)

def Convolution(img,filtre,avant_convolution):

    hauteur_filtre=np.shape(filtre)[0]
    largeur_filtre=np.shape(filtre)[1]


    if (largeur_filtre!=hauteur_filtre):
        print("La hauteur et la largeur du filtre doivent etre identiques")
        assert(largeur_filtre==hauteur_filtre)    
        if (hauteur_filtre%2)!=1:
            print("La taille doit etre impair")
            assert(hauteur_filtre%2==1)
    
    cases_supp=largeur_filtre//2
    height=img.shape[0]
    width=img.shape[1]

    apres_convolution=np.zeros((height,width),dtype=np.uint8)
    
    for i in range(cases_supp,height+cases_supp):
        for j in range(cases_supp,width+cases_supp):
            somme_convolution=0
            for k in range(hauteur_filtre):
                for l in range(largeur_filtre):
                    somme_convolution+=avant_convolution[i-cases_supp+k][j-cases_supp+l]*filtre[hauteur_filtre-k-1][largeur_filtre-l-1]
            apres_convolution[i-cases_supp][j-cases_supp]=somme_convolution
    plt.imshow(apres_convolution,cmap="gray")
    plt.show()

    return(apres_convolution)

def filtre_gaussien(taille,sX,sY):
    """
    taille:taille de la matrice caree du filtre gaussien
    sX:ecart type suivant l'axe X
    sY:ecart type suivant l'axe Y
    """
    if (taille%2)!=1:
        print("La taille doit etre impair")
        assert(taille%2==1)
        
    x0=taille//2
    y0=taille//2
    filtre=np.zeros((taille,taille))
    for x in range(taille):
        for y in range(taille):
            filtre[x][y] = (1/(2*math.pi*sX*sY))*math.exp(-(x-x0)**2/2*sX**2)*math.exp(-(y-y0)**2/2*sY**2)
    return(filtre)


def filtre_moyenneur(taille):
    filtre=np.zeros((taille,taille))
    for i in range(taille):
        for j in range(taille):
            filtre[i][j]=1/9
    return(filtre)


def zero_padding(img,taille):
    
    cases_supp=taille//2
    height=img.shape[0]
    width=img.shape[1]
    
    avant_convolution=np.zeros((height+2*cases_supp,width+2*cases_supp),dtype=np.uint8)
    for i in range(cases_supp,height+cases_supp):
        for j in range(cases_supp,width+cases_supp):
            avant_convolution[i][j]=img[i-cases_supp][j-cases_supp]
    return(avant_convolution)


def Convolution_median(img,filtre,avant_convolution):

    hauteur_filtre=filtre
    largeur_filtre=filtre


    if (largeur_filtre!=hauteur_filtre):
        print("La hauteur et la largeur du filtre doivent etre identiques")
        assert(largeur_filtre==hauteur_filtre)    
        if (hauteur_filtre%2)!=1:
            print("La taille doit etre impair")
            assert(hauteur_filtre%2==1)
    
    cases_supp=largeur_filtre//2
    height=img.shape[0]
    width=img.shape[1]

    apres_convolution=np.zeros((height,width),dtype=np.uint8)
    
    for i in range(cases_supp,height+cases_supp):
        for j in range(cases_supp,width+cases_supp):
            matrice_tri=[]
            for k in range(hauteur_filtre):
                for l in range(largeur_filtre):
                    matrice_tri.append(avant_convolution[i-cases_supp+k][j-cases_supp+l])
            for m in range(hauteur_filtre*hauteur_filtre-1):
                for n in range(hauteur_filtre*hauteur_filtre-1-m):
                    if matrice_tri[n]>matrice_tri[n+1]:
                        temp=matrice_tri[n+1]
                        matrice_tri[n+1]=matrice_tri[n]
                        matrice_tri[n]=temp                   
            apres_convolution[i-cases_supp][j-cases_supp]=matrice_tri[(hauteur_filtre*hauteur_filtre)//2]

    plt.imshow(apres_convolution,cmap="gray")
    plt.show()

    return(apres_convolution)



def Appliquer_Filtre(nom_filtre,taille_filtre,avec_detection_erreurs):
    """
    :nom_filtre : En str, nom du filtre qu'on veut appliquer 
    :taille_filtre : En int, taille en largeur ou hauteur du masque qu'on veut appliquer
    :avec_detection_erreurs : En booleen, si on veut comparer en pourcentage la precision par rapport aux filtres utilises avec cv2.
    """

    image = OpenImage(r"C:\Users\remyx\OneDrive\Documents\Info L4\Image2024\TP6\TP6\shapes.jpg")
    print("Conversion de l'image en couleur en nuances de gris")
    grey = GreyImage(image)

    if nom_filtre=='moyenneur':
        image_filtree = Convolution(grey,filtre_moyenneur(taille_filtre),zero_padding(grey,taille_filtre))
        test = cv2.blur(grey, (3, 3))
    elif nom_filtre=='gaussien':
        print("Application d'un filtre 3x3 gaussien avec zero padding")
        image_filtree = Convolution(grey,filtre_gaussien(taille_filtre,1,1),zero_padding(grey,taille_filtre))
        test = cv2.GaussianBlur(grey, (taille_filtre, taille_filtre),1,1)
    elif nom_filtre=='median':
        print("Application d'un filtre 3x3 median avec zero padding")
        image_filtree = Convolution_median(grey,taille_filtre,zero_padding(grey,taille_filtre))
        test=cv2.medianBlur(grey,taille_filtre)

    if avec_detection_erreurs:
        erreurs=0
    for i in range (test.shape[0]):
        for j in range (test.shape[1]):
            if image_filtree[i][j]!=test[i][j]:
                erreurs+=1

    print("Pourcentage de pixels differents:")
    print(str(100*erreurs/(test.shape[0]*test.shape[1]))+"%")

    cv2.imshow('image exemple', test)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

def gradientX(avant_convolution):
    return()


#Appliquer_Filtre('median',3,True)