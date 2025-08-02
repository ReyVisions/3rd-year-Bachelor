import cv2 as cv
import numpy as np
import os


import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as Image2
import cv2
import math
import os
from PIL import Image

def OpenImage(route):
    """
    Fonction pour obtenir une image a partir d'un path
    Retourne l'image
    route: chemin de l'image a acquisitionner
    """
    img = Image2.imread(route)
    return(img)

def PlotImage(img):
    """
    Fonction pour afficher une image a partir d'un path
    Retourne rien
    img: image a afficher
    """
    plt.imshow(img, cmap='gray')
    plt.show()

def GreyImage(img):
    """
    Fonction pour convertir de l'image en couleur en nuances de gris
    Retourne l'image grise
    img: image a afficher
    """
    print("Conversion de l'image en couleur en nuances de gris")

    height=img.shape[0]
    width=img.shape[1]
    gris=np.zeros((height,width),dtype=np.uint8)
    for i in range(height):
        for j in range(width):
            r, g, b = img[i][j]
            gris[i][j] = int(0.299 * r + 0.587 * g + 0.114 * b)
    return(gris)

def Convolution(img,filtre,avant_convolution):
    """
    Fonction pour effectuer la convolution en fonction du filtre, et du padding qu'on utilise. 
    Retourne l'image apres le produit de convolution
    img: image a utiliser pour la convolution
    filtre: filtre a utiliser parmis les suivants: moyenneur, median, gaussien.
    avant_convolution: image identique a img auxquelles on a rajoute le padding: (zero ou copy)
    """
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

    return(apres_convolution)

def filtre_gaussien(taille,sX,sY):
    """
    Fonction qui retourne le filtre gaussien de taille "taille".
    Retourne la matrice contenant le filtre gaussien
    taille:taille de la matrice caree du filtre gaussien
    sX:ecart type suivant l'axe X
    sY:ecart type suivant l'axe Y
    """
    print("Application du fltre gaussien")

    if taille % 2 != 1:
        print("La taille doit etre impair")
        assert taille % 2 == 1

    x0 = taille // 2
    y0 = taille // 2
    filtre = np.zeros((taille, taille))
    for x in range(taille):
        for y in range(taille):
            filtre[x][y] = (1 / (2 * math.pi * sX * sY)) * math.exp(-((x - x0)**2 / (2 * sX**2) + (y - y0)**2 / (2 * sY**2)))
    return filtre

def filtre_moyenneur(taille):
    """
    Fonction pour convertir de l'image en couleur en nuances de gris
    Retourne la matrice contenant le filtre moyenneur
    img: image a afficher
    """
    print("Application d'un filtre moyenneur")
    filtre=np.zeros((taille,taille))
    for i in range(taille):
        for j in range(taille):
            filtre[i][j]=1/9
    return(filtre)


def zero_padding(img,taille):
    """
    Fonction pour ajouteur le zero padding a l'image
    Retourne une matrice de taille adaptee pour pouvoir utiliser le filtre meme sur les coins.
    img: image a afficher
    taille: taille du filtre a utiliser.
    """
    cases_supp=taille//2
    height=img.shape[0]
    width=img.shape[1]
    
    avant_convolution=np.zeros((height+2*cases_supp,width+2*cases_supp),dtype=np.uint8)
    for i in range(cases_supp,height+cases_supp):
        for j in range(cases_supp,width+cases_supp):
            avant_convolution[i][j]=img[i-cases_supp][j-cases_supp]
    return(avant_convolution)

def copy_padding(img,taille):
    """
    Fonction pour ajouteur le copy padding a l'image
    Retourne une matrice de taille adaptee pour pouvoir utiliser le filtre meme sur les coins.
    img: image a afficher
    taille: taille du filtre a utiliser.
    """
    cases_supp=taille//2
    height=img.shape[0]
    width=img.shape[1]
    
    avant_convolution=np.zeros((height+2*cases_supp,width+2*cases_supp),dtype=np.uint8)
    for i in range(cases_supp,height+cases_supp):
        for j in range(cases_supp,width+cases_supp):
            avant_convolution[i][j]=img[i-cases_supp][j-cases_supp]

    for i in range(cases_supp):
        for j in range(cases_supp):
            avant_convolution[i][j]=avant_convolution[cases_supp][cases_supp]
            avant_convolution[height+cases_supp+i][j]=avant_convolution[height+cases_supp-1][cases_supp]
            avant_convolution[i][width+cases_supp+j]=avant_convolution[cases_supp][width+cases_supp-1]
            avant_convolution[height+cases_supp+i][width+cases_supp+j]=avant_convolution[height+cases_supp-1][width+cases_supp-1]

    for n in range(cases_supp):
        for i in range(cases_supp,height+cases_supp):
            avant_convolution[i][n]=avant_convolution[i][cases_supp]
            avant_convolution[i][width+cases_supp+n]=avant_convolution[i][width+cases_supp-1]
    for n in range(cases_supp):
        for j in range(cases_supp,width+cases_supp):
            avant_convolution[n][j]=avant_convolution[cases_supp][j]
            avant_convolution[height+cases_supp+n][j]=avant_convolution[height+cases_supp-1][j]
    return(avant_convolution)



def Convolution_median(img,taille_filtre,avant_convolution):
    """
    Fonction pour effectuer la convolution avec le filtre median, en fonction du padding qu'on utilise. 
    Retourne l'image apres le produit de convolutiona avec un filtre median
    img: image a utiliser pour la convolution
    taille_filtre: taille du filtre median
    avant_convolution: image identique a img auxquelles on a rajoute le padding: (zero ou copy)
    """
    hauteur_filtre=taille_filtre
    largeur_filtre=taille_filtre


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


    return(apres_convolution)



def Appliquer_Filtre(nom_filtre,taille_filtre,avec_detection_erreurs,padding):
    """
    Fonction (de test) permettant de tester tous les filtres s'il sont proches de ceux d'OpenCV
    Retourne un pourcentage d'erreur en fonction du filtre choisi.
    :nom_filtre : En str, nom du filtre qu'on veut appliquer: moyenneur, gaussien ou median
    :taille_filtre : En int, taille en largeur ou hauteur du masque qu'on veut appliquer
    :avec_detection_erreurs : En booleen, si on veut comparer en pourcentage la precision par rapport aux filtres utilises avec cv2.
    """

    image = OpenImage(r"C:\Users\remyx\OneDrive\Bureau\Projet image\Etiquetages 71-140")
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

def Sobel(img,avant_convolution):
    """
    Fonction appliquant le filtre de sobel a une image.
    Retourne la magnitude de l'image (on lui applique une puissance de 3/2 pour accentuer les valeurs)
    img: image sur laquelle on applique le filtre de sobel
    """

    print("Application de l'algorithme de Sobel")

    gradientVertical = Convolution(img,[[1,2,1],[0,0,0],[-1,-2,-1]],avant_convolution)
    gradientHorizontal = Convolution(img,[[-1,0,1],[-2,0,2],[-1,0,1]],avant_convolution)
    

    magnitude=(gradientHorizontal**2+gradientVertical**2)**(3/4)

    magnitude = np.clip(magnitude, 0, 255)
    magnitude = magnitude.astype(np.uint8)
    return(magnitude)

def Fermeture(img,kernel):
    """
    Fonction appliquant la fermeture sur une image en fonction du kernel.
    Retourne l'image apres fermeture.
    img: image sur laquelle on applique le filtre de sobel
    kernel: matrice representant le kernel qu'on utilise (on considere l'origine du kernel comme le centre de la matrice)
    """
    print("Application de la fermeture morphologique")
    height,width = img.shape            
    h_kernel=kernel.shape[0]
    l_kernel=kernel.shape[1]
    cases_supp=kernel.shape[0]//2
    img_new= np.copy(img)

    #Dilatation
    for i in range(cases_supp,height-cases_supp):
        for j in range(cases_supp,width-cases_supp): 
            max_value=0

            for k in range(h_kernel):
                for l in range(l_kernel):
                    if kernel[k][l]==1:

                        max_value=max(max_value,img[i-cases_supp+k][j-cases_supp+l])
            img_new[i][j]=max_value  

    #Erosion
    
    for i in range(cases_supp,height-cases_supp):
        for j in range(cases_supp,width-cases_supp): 
            min_value=255

            for k in range(h_kernel):
                for l in range(l_kernel):
                    if kernel[k][l]==1:
                        min_value=min(min_value,img[i-cases_supp+k][j-cases_supp+l])
            img_new[i][j]=min_value
    
    return(img_new)


def ContourSobel(path):
    """
    Fonction qui cherche les contours avec Sobel pour une image (premiere version de detection de contour)
    Retourne la magnitude de l'image
    path: chemin de l'image sur laquelle on veut chercher les contours avec Sobel
    """
    image = OpenImage(path)
    print("Pre traitement : \n")
    print("Conversion de l'image en couleur en nuances de gris")
    grey = GreyImage(image)
    print("Application du fltre gaussien")
    image_filtree=Convolution(grey,filtre_gaussien(5,1,1),zero_padding(grey,5))

    print("Application de l'algorithme de Sobel")
    image_Sobel=Sobel(image_filtree,zero_padding(image_filtree,5))
    """
    mean_intensity=np.mean(image_Sobel)
    threshold=mean_intensity * 1.5

    #seuillage rapide
    for i in range(image_Sobel.shape[0]):
       for j in range (image_Sobel.shape[1]):
           if image_Sobel[i][j] < threshold:
               image_Sobel[i][j]=0
           else:
                image_Sobel[i][j]=255
    """
    kernel = np.array([[0, 1, 0], [1, 1, 1], [0, 1, 0]], dtype=np.uint8)
    image_fermee=Fermeture(image_Sobel,kernel)
    print("Post traitement: Application d'un filtre moyenneur")
    image_median=Convolution(image_fermee,filtre_moyenneur(5),zero_padding(image_fermee,5))

    plt.imshow(image_median,cmap="gray")
    plt.show()
    return(image_median)

def MSE(X,Y):
    """
    X: Tableau de nombre de pieces identifiees pour chaque image
    Y: Tableau des verites terrains pour chaque image.
    return: Le MSE d'une banque d'image
    """
    if len(X)>len(Y):
        print("Il y a plus de resultats d'images que de verites terrains")
    elif len(X)<len(Y):
        print("Il y a plus de verites terrains que de resultats d'images")
    MSE=0
    for i in range(min(len(X),len(Y))):
        MSE+=(X[i]-Y[i])**2
    return(MSE/214)

def MAE(X,Y):
    """
    X: Tableau de nombre de pieces identifiees pour chaque image
    Y: Tableau des verites terrains pour chaque image.
    return: Le MAE d'une banque d'image
    """
    if len(X)>len(Y):
        print("Il y a plus de resultats d'images que de verites terrains")
    elif len(X)<len(Y):
        print("Il y a plus de verites terrains que de resultats d'images")

    MAE=0
    for i in range(min(len(X),len(Y))):
        MAE+=abs(X[i]-Y[i])
    return(MAE/214)

def Precision(TP,TN,FP,FN):
    """
    Fonction pour calculer la precision de la matrice de confusion (qu'on utilise pas car on considere qu'un seul objet qui est la piece)
    TP: True positive
    TN: True negative
    TP: False positive
    TP: False negative
    """
    return(TP/(TP+FP))

def Rappel(TP,TN,FP,FN):
    """
    Fonction pour calculer le rappel de la matrice de confusion (qu'on utilise pas car on considere qu'un seul objet qui est la piece)
    TP: True positive
    TN: True negative
    TP: False positive
    TP: False negative
    """
    return(TP/(TP+FN))

def Erreur(TP,TN,FP,FN):
    """
    Fonction pour calculer l'erreur de la matrice de confusion (qu'on utilise pas car on considere qu'un seul objet qui est la piece)
    TP: True positive
    TN: True negative
    TP: False positive
    TP: False negative
    """
    return(FP+FN/(TP+TN+FP+FN))

def F1(TP,TN,FP,FN):
    """
    Fonction pour calculer le score F1 de la matrice de confusion (qu'on utilise pas car on considere qu'un seul objet qui est la piece)
    TP: True positive
    TN: True negative
    TP: False positive
    TP: False negative
    """
    P=Precision(TP,TN,FP,FN)
    R=Rappel(TP,TN,FP,FN)
    return(2*P*R/(P+R))

def Gradient(img, avant_convolution):
    """
    Fonction pour calculer les gradient dans l'algorithme de Canny
    Retourne la magnitude et la direction de la magnitude.
    img:image sur laquelle on calcule
    avant_convolution: Choix du padding (zero ou copy)
    """
    gradientVertical = Convolution(img, np.array([[0, 1, 0], [0, 0, 0], [0, -1, 0]]), avant_convolution)
    gradientHorizontal = Convolution(img, np.array([[0, 0, 0], [-1, 0, 1], [0, 0, 0]]), avant_convolution)
    magnitude = np.sqrt(gradientHorizontal**2 + gradientVertical**2)
    magnitude = np.clip(magnitude, 0, 255).astype(np.uint8)
    direction=np.arctan2(gradientVertical,gradientHorizontal)
    return magnitude, direction


def CannyTest(path):
    """
    Fonction pour detecter les contours avec le filtre de Canny.
    1) Filtre gaussien, 2) Calcul des gradients et des directions 3)Suppression des non maximums en 8-connexite
    4) Selection des noeuds que l'on decide de garder en fonction de min_value et max_value
    Retourne l'image avec les contours trouves avec Canny
    path: chemin de l'image que l'on veut appliquer la detection de contours.
    """
    image = OpenImage(path)
    grey = GreyImage(image)
    image_filtree = Convolution(grey, filtre_gaussien(5, 1, 1), zero_padding(grey, 5))

    magnitude,direction = Gradient(image_filtree, zero_padding(image_filtree, 5))
    print("Suppression des non maximas")
    height,width=magnitude.shape
    new_image=np.zeros((height,width), dtype=np.float32)
    angle=direction*180.0/np.pi
    angle[angle<0]+=180

    for i in range(1,magnitude.shape[0]-1):
        for j in range(1,magnitude.shape[1]-1):
            a=255
            b=255
            theta=angle[i][j]
            if (0<=theta<=22.5)&(157.5<=theta<=180):
                a=magnitude[i][j+1]
                b=magnitude[i][j-1]
            elif (22.5<=theta<=67.5):
                a=magnitude[i-1][j+1]
                b=magnitude[i+1][j-1]
            elif (67.5<=theta<=112.5):
                a=magnitude[i+1][j]
                b=magnitude[i-1][j]
            elif (112.5<=theta<=157.5):
                a=magnitude[i+1][j+1]
                b=magnitude[i-1][j-1]
            if magnitude[i][j]>=a & magnitude[i][j]>=b:
                new_image[i][j]=magnitude[i][j]
            else:
                new_image[i][j]=0
    print("Hysteresis Thresholding")
    hysteresis_thresholding(new_image,100,200)

    image_finale = Convolution(new_image, filtre_gaussien(5, 1, 1), zero_padding(new_image, 5)) 
    kernel = np.array([[0, 1, 0], [1, 1, 1], [0, 1, 0]], dtype=np.uint8)
    image_finale=Fermeture(image_finale,kernel)
    #plt.imshow(image_finale,cmap="gray")
    #plt.show()
    image_finale = (image_finale * 255).astype(np.uint8)  # Ensure the image values are in 0-255 range
    return(image_finale)

def Canny(grey,min_value,max_value):
    """
    Fonction pour detecter les contours avec le filtre de Canny.
    1) Filtre gaussien, 2) Calcul des gradients et des directions 3)Suppression des non maximums en 8-connexite
    4) Selection des noeuds que l'on decide de garder en fonction de min_value et max_value
    Ensuite, on applique un filtre gaussien, puis une fermeture, puis un filtre moyenneur.
    Retourne l'image avec les contours trouves avec Canny
    path: chemin de l'image que l'on veut appliquer la detection de contours.
    """
    
    image_filtree = Convolution(grey, filtre_gaussien(5, 1, 1), zero_padding(grey, 5))

    magnitude,direction = Gradient(image_filtree, zero_padding(image_filtree, 5))
    print("Suppression des non maximas")
    height,width=magnitude.shape
    new_image=np.zeros((height,width), dtype=np.float32)
    angle=direction*180.0/np.pi
    angle[angle<0]+=180

    for i in range(1,magnitude.shape[0]-1):
        for j in range(1,magnitude.shape[1]-1):
            a=255
            b=255
            theta=angle[i][j]
            if (0<=theta<=22.5)&(157.5<=theta<=180):
                a=magnitude[i][j+1]
                b=magnitude[i][j-1]
            elif (22.5<=theta<=67.5):
                a=magnitude[i-1][j+1]
                b=magnitude[i+1][j-1]
            elif (67.5<=theta<=112.5):
                a=magnitude[i+1][j]
                b=magnitude[i-1][j]
            elif (112.5<=theta<=157.5):
                a=magnitude[i+1][j+1]
                b=magnitude[i-1][j-1]
            if magnitude[i][j]>=a & magnitude[i][j]>=b:
                new_image[i][j]=magnitude[i][j]
            else:
                new_image[i][j]=0
    print("Hysteresis Thresholding")
    hysteresis_thresholding(new_image,75,125)

    image_finale = Convolution(new_image, filtre_gaussien(5, 1, 1), zero_padding(new_image, 5)) 
    kernel = np.array([[0, 1, 0], [1, 1, 1], [0, 1, 0]], dtype=np.uint8)
    image_finale=Fermeture(image_finale,kernel)
    #plt.imshow(image_finale,cmap="gray")
    #plt.show()
    image_finale = (image_finale * 255).astype(np.uint8)  # Ensure the image values are in 0-255 range
    return(image_finale)

def hysteresis_thresholding(image, low_threshold, high_threshold):
    """
    Fonction qui implemente l'hysteresis_thresholding qui est la selection des noeuds 
    que l'on decide de garder en fonction de min_value et max_value.
    Retourne l'image suite apres application de l'algorithme
    image:image sur laquelle on veut appliquer l'algorithme
    low_threshold:min value, seuil ou en dessus on supprime la valeur
    high_threshold: Seuil qui permet de valider les valeurs si elles y sont superieures
    si la valeur est entre les deux seuils, la valeur est gardee si le pixel est voisin
    en 8 connexite a un pixel au dessus de high_threshold.
    
    """
    rows, cols = image.shape
    result = np.zeros((rows, cols), dtype=np.uint8)

    strong = 255
    weak = 75

    strong_i, strong_j = np.where(image >= high_threshold)
    weak_i, weak_j = np.where((image <= high_threshold) & (image >= low_threshold))

    result[strong_i, strong_j] = strong
    result[weak_i, weak_j] = weak

    # Propagation des contours forts aux contours faibles connectés
    for i in range(1, rows-1):
        for j in range(1, cols-1):
            if result[i, j] == weak:
                if ((result[i+1, j-1] == strong) or (result[i+1, j] == strong) or (result[i+1, j+1] == strong)
                        or (result[i, j-1] == strong) or (result[i, j+1] == strong)
                        or (result[i-1, j-1] == strong) or (result[i-1, j] == strong) or (result[i-1, j+1] == strong)):
                    result[i, j] = strong
                else:
                    result[i, j] = 0

    return result

def otsu_threshold(image):
    """
    Fonction qui implemente l'algorithme d'otsu
    Retourne un seuil calcule idealement
    image:image sur laquelle on veut appliquer l'algorithme
    """
    print("calcul de l'algorithme d'otsu")
    hist, bins = np.histogram(image.ravel(), bins=256, range=(0, 1))
    hist_norm = hist / float(np.sum(hist))
    variance_values = []

    for t in range(1, 256):

        w0 = np.sum(hist_norm[:t])
        w1 = np.sum(hist_norm[t:])

        mu0 = np.sum(np.arange(t) * hist_norm[:t]) / (w0 + 1e-6)
        mu1 = np.sum(np.arange(t, 256) * hist_norm[t:]) / (w1 + 1e-6)

        interclass_variance = w0 * w1 * (mu0 - mu1) ** 2

        variance_values.append(interclass_variance)


    optimal_threshold = np.argmax(variance_values)

    return optimal_threshold

def seuillage_inverse(seuil,img):
    """
    Fonction qui fait le seuillage inverse de l'image
    Retourne un seuil calcule idealement
    seuil: seuil theta
    img:image sur laquelle on veut appliquer le seuillage
    """
    height=img.shape[0]
    width=img.shape[1]
    binaire=np.zeros((height,width),dtype=np.uint8)
    for i in range(height):
        for j in range(width):
            if img[i][j]>seuil:
                binaire[i][j]=255
            elif img[i][j]<=seuil:
                binaire[i][j]=0
    return(binaire)

def seuillage(seuil,img):
    """
    Fonction qui fait le seuillage de l'image
    Retourne un seuil calcule idealement
    seuil: seuil theta
    img:image sur laquelle on veut appliquer le seuillage
    """
    height=img.shape[0]
    width=img.shape[1]
    binaire=np.zeros((height,width),dtype=np.uint8)
    for i in range(height):
        for j in range(width):
            if img[i][j]<seuil:
                binaire[i][j]=0
            elif img[i][j]>=seuil:
                binaire[i][j]=255
    return(binaire)


def open_images_from_folder(folder_path):
    """
    Fonction permettant de recuperer un dossier et de le stocker dans une variable
    Retourne la variable stockant le dossier contenant des images (.jpg,.jpeg,.png,.JPEG)
    folder_path: Chemin du dossier qu'on veut recuperer dans la variable
    """
    supported_formats = ('.jpg', '.jpeg', '.png')
    images = []

    for filename in os.listdir(folder_path):
        if filename.lower().endswith(supported_formats):
            img_path = os.path.join(folder_path, filename)
            try:
                img = Image.open(img_path)
                images.append((filename, img))
            except IOError:
                print(f"Cannot open {filename}")

    return images

def try_folder(folder_path):
    """
    Fonction qui est complementaire a open_images_from_folder, qui permet d'appliquer Canny 
    a l'ensemble des images du dossier qu'on a extrait avant.
    Sauvegarde les images apres avoir applique Canny dans un dossier (on pourra modifier le chemin en fonction.)
    folder_path: Chemin du dossier qu'on veut recuperer dans la variable
    """
    images = open_images_from_folder(folder_path)
    i = 0
    for filename, img in images:
        print(filename)
        i+=1
        if i<=7:
            continue
        image_canny = Canny(os.path.join(folder_path, filename))
        nom_fichier = f"image_{i}.png"
        cv2.imwrite(os.path.join(r"C:\Users\remyx\OneDrive\Bureau\Projet image\Contours 71-140", nom_fichier), image_canny)

def equal(img_name):
    """
    Fonction qui permet de realiser l'egalisation d'histogramme.
    img_name: chemin de l'image a ouvrir et ou on applique l'algorithme
    """
    # Chargement et conversion de l'image en niveaux de gris
    img = np.array(Image.open(img_name).convert('L'), dtype=np.uint8)

    # Calcul de l'histogramme
    hist, bins = np.histogram(img.flatten(), bins=256, range=[0,256])

    # Calcul de l'histogramme cumulé
    hist_cumu = hist.cumsum()

    # Normalisation de l'histogramme cumulé
    hist_cumu_norm = hist_cumu * 255 / hist_cumu[-1]

    # Application de la transformation
    img_eq = hist_cumu_norm[img]

    # Conversion de l'image égalisée en type uint8
    img_eq = np.asarray(img_eq, dtype=np.uint8)

    return img_eq

def testfonctions(path):
    print("Ouverture de l'image")
    image = OpenImage(path)

    print("Conversion de l'image en gris")
    grey = GreyImage(image)

    print("Filtre gaussien de taille 19")
    print(filtre_gaussien(19,2,2))

    print("image grey apres avoir ajoute le zero padding")
    print(zero_padding(grey,7))

    print("image grey apres avoir ajoute le copy padding")
    print(copy_padding(grey,7))
    #Attention le 1er parametre des filtres et le deuxieme du padding sont identiques.
    print("Application de la convolution avec un filtre moyenneur de taille 5 et le zero padding")

    image_filtree = Convolution(grey, filtre_moyenneur(5), zero_padding(grey, 5))
    print(image_filtree)
    plt.imshow(image_filtree,cmap="gray")
    plt.show()
    
    print("Application de la convolution avec un filtre median de taille 7 et le zero padding")
    median = Convolution_median(grey,7,zero_padding(grey,7))
    print(median)
    plt.imshow(median,cmap="gray")
    plt.show()
    
    print("Calcul des contours avec Sobel")
    sobel = ContourSobel(path)
    print(sobel)
    plt.imshow(sobel,cmap="gray")
    plt.show()

    print("calcul de la fermeture apres avoir utilise Sobel")
    fermeture=Fermeture(ContourSobel(path))
    print(fermeture)
    plt.imshow(fermeture,cmap="gray")
    plt.show()
    
    print("Calcul des contours avec Canny")
    canny = Canny(path)
    print(canny)
    plt.imshow(canny,cmap="gray")
    plt.show()


def main():
    #testfonctions(r"C:\Users\remyx\OneDrive\Bureau\Projet image\Etiquetages 71-140\74.jpg")
    # images files
    img_dir = r"C:\Users\remyx\OneDrive\Bureau\Projet image\Etiquetages 71-140"

    # preprocessed images files
    output_ppd_dir = r"C:\Users\remyx\OneDrive\Bureau\Projet image\Contours 71-140"

    for img in os.listdir(img_dir):
        if img.endswith(".jpg") or img.endswith(".JPG") or img.endswith(".png") or img.endswith(".jpeg"):
    
            img_path = os.path.join(img_dir, img)
            image = cv.imread(img_path)
        
            # convert img in gray scale

            gray_img = GreyImage(image)
        
            #_, otsu_img = cv.threshold(gray_img, 0, 255, cv.THRESH_BINARY + cv.THRESH_OTSU)
        
            # Réduire le bruit avec un filtre gaussien
            blurred_img = Convolution(gray_img,filtre_gaussien(9,1,1),zero_padding(gray_img,9))
        
            # Détection des bords avec Canny
            canny_img = Canny(blurred_img,75,125)
            # otsu threshold
            
        

            #countours, _ = cv.findContours(canny_img, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)
        
            #contour_img = image.copy()
            #cv.drawContours(contour_img, countours, -1, (0, 255, 0), 2)
        
            #for contour in countours:
            #    (x, y), radius = cv.minEnclosingCircle(contour)
            #    cv.circle(otsu_img, (int(x), int(y)), int(radius), (255, 0, 0), 2)

            
            output_ppd_path = os.path.join(output_ppd_dir, img)
            #output_contour_path = os.path.join(output_contour_dir,img)
        
            cv.imwrite(output_ppd_path, canny_img)
            #cv.imwrite(output_contour_path, )
            print(img + " preprocessed...")

    print("\n Preprocessing done.")

if __name__ == "__main__":
    main()




