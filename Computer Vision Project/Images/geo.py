import cv2
import matplotlib.pyplot as plt

# Charger l'image en niveaux de gris
image_path = 'C:/Users/triqu/Documents/Image/Projet_Image/Images/.jpg'
image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)

# Vérifier si l'image est chargée correctement
if image is None:
    print("Impossible de charger l'image. Assurez-vous que le chemin du fichier est correct.")
    exit()

# Seuillage de l'image
_, binary_image = cv2.threshold(image, 90, 255, cv2.THRESH_BINARY)

# Afficher l'image seuillée
plt.imshow(binary_image, cmap='gray')
plt.title('Image seuillée (Seuil: 150)')
plt.axis('off')
plt.show()
