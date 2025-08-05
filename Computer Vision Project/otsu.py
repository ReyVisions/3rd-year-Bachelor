
import numpy as np
import matplotlib.pyplot as plt
import cv2 as cv

def otsu_threshold(image):
    # Calcul de l'histogramme de l'image
    hist, bins = np.histogram(image.ravel(), bins=256, range=(0, 1))

    # Normalisation de l'histogramme
    hist_norm = hist / float(np.sum(hist))

    # Variables pour stocker les valeurs intermédiaires
    variance_values = []

    # Pour chaque seuil possible, calculer la variance interclasse
    for t in range(1, 256):
        # Fraction de pixels en-dessous et au-dessus du seuil
        w0 = np.sum(hist_norm[:t])
        w1 = np.sum(hist_norm[t:])

        # Somme des valeurs en-dessous et au-dessus du seuil
        mu0 = np.sum(np.arange(t) * hist_norm[:t]) / (w0 + 1e-6)  # Eviter la division par zéro
        mu1 = np.sum(np.arange(t, 256) * hist_norm[t:]) / (w1 + 1e-6)  # Eviter la division par zéro

        # Calcul de la variance interclasse
        interclass_variance = w0 * w1 * (mu0 - mu1) ** 2

        # Ajouter la variance interclasse à la liste des valeurs
        variance_values.append(interclass_variance)

    # Trouver le seuil optimal qui maximise la variance interclasse
    optimal_threshold = np.argmax(variance_values)

    return optimal_threshold / 255.0  # Normaliser le seuil dans la plage [0, 1]


image = cv.imread("C:/Users/triqu/Documents/Image/Projet_Image/Images/0.jpg")
gray_image = cv.cvtColor(image, cv.COLOR_RGB2GRAY) 

# Appliquer la méthode d'Otsu pour obtenir un seuil automatique
threshold = otsu_threshold(gray_image)

# Appliquer un seuillage pour binariser l'image
binary_image = gray_image > threshold

# Affichage des résultats
fig, axes = plt.subplots(1, 2, figsize=(8, 4), sharex=True, sharey=True)
ax = axes.ravel()

ax[0].imshow(image, cmap=plt.cm.gray)
ax[0].set_title('Image originale')

ax[1].imshow(binary_image, cmap=plt.cm.gray)
ax[1].set_title('Image binarisée')

plt.show()
