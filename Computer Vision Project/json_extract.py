import cv2
import json
import numpy as np

# Charger le fichier JSON d'annotation
with open('evaluation_set/2.json', 'r') as f:
    data = json.load(f)

# Charger l'image
image_path = data['imagePath']
image = cv2.imread(image_path)

# Redimensionner l'image pour l'afficher plus petit
scale_percent = 15  # Redimensionner à 25% de la taille originale
width = int(image.shape[1] * scale_percent / 100)
height = int(image.shape[0] * scale_percent / 100)
resized_image = cv2.resize(image, (width, height))

# Pour chaque pièce d'euro annotée
for shape in data['shapes']:
    # Récupérer les points de la forme
    points = np.array(shape['points'], np.int32)
    points = points.reshape((-1, 1, 2))

    # Extraire les coordonnées du rectangle englobant
    x, y, w, h = cv2.boundingRect(points)

    # Dessiner le rectangle englobant en rouge sur l'image originale
    cv2.rectangle(resized_image, (x, y), (x + w, y + h), (0, 0, 255), 2)

# Afficher l'image avec les rectangles englobants en rouge
cv2.imshow('Image avec rectangles rouges', resized_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
