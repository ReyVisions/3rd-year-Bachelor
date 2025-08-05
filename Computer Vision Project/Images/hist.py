import cv2
import numpy as np
import matplotlib.pyplot as plt

# Charger l'image
image_path = 'C:/Users/triqu/Documents/Image/Projet_Image/Images/Test_JPEG.jpeg'
image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)

# Appliquer le seuillage
_, binary_image = cv2.threshold(image, 168, 255, cv2.THRESH_BINARY)

# Afficher l'image binarisée avec Matplotlib
plt.figure(figsize=(8, 6))
plt.imshow(binary_image, cmap='gray')
plt.title('Image binarisée')
plt.axis('on')  # Afficher les axes pour redimensionner correctement l'image
plt.show()
