import os
import cv2
import json
import numpy as np
import matplotlib.pyplot as plt
from pprint import pprint

dossier_image_preprocessed = r"C:\Users\remyx\OneDrive\Bureau\Projet image\Contours 71-140"
dossier_json = r"C:\Users\remyx\OneDrive\Bureau\Projet image\json_files"
dossier_sortie = r"C:\Users\remyx\OneDrive\Bureau\Projet image\contours2"

pieces_trouvees_total = {}
verites_terrain_total = {}

if not os.path.exists(dossier_sortie): # création du dossier de sortie si nécessaire
    os.makedirs(dossier_sortie)

# Fonction pour compter les pièces trouvées
def count_coins(contours_dict, contours_found):
    coin_counts = {label: 0 for label in contours_dict.keys()}
    for contour in contours_found:
        (x, y), radius = cv2.minEnclosingCircle(contour)
        for label, (cx, cy, cr) in contours_dict.items():
            if abs(cx - x) < 65 and abs(cy - y) < 65 and abs(cr - radius) < 65:
                coin_counts[label] += 1
    return coin_counts

# Réorganisation des lables dans le dictionnaire si le label était mal étiqueté
label_mapping = {
    "1 euro": "1 euro",
    "1 euros": "1 euro",
    "1 eurs": "1 euro",
    "1e": "1 euro",
    
    "2 euros": "2 euros",
    "2e": "2 euros",
    
    "20 centimes": "20 centimes",
    "20ct": "20 centimes",
    
    "10 centimes": "10 centimes",
    "10ct": "10 centimes",
    
    "50 centimes": "50 centimes",
    "50ct": "50 centimes",
    
    "5 centimes": "5 centimes",
    "5ct": "5 centimes",
    "5 cenitmes": "5 centimes",
    
    "1 centime": "1 centime",
    "1 centimes": "1 centime",
    "1ct": "1 centime",
    
    "2 centimes": "2 centimes",
    "2ct": "2 centimes"
}

# Dictionnaire pour stocker le nombre total de chaque pièce trouvée
total_coin_counts = {v: 0 for v in label_mapping.values()}

# Fonction pour compter les vérités terrain à partir des fichiers JSON
def count_ground_truth(dossier_json, label_mapping):
    for fichier_json in os.listdir(dossier_json):
        if fichier_json.lower().endswith('.json'):
            chemin_json = os.path.join(dossier_json, fichier_json).replace("\\", "/")
            # Créer un dictionnaire vide pour chaque fichier JSON trouvé
            verites_terrain_total[fichier_json] = {}

            with open(chemin_json, 'r') as f:
                data = json.load(f)
                for shape in data['shapes']:
                    if shape['shape_type'] == 'circle':
                        label = shape['label']
                        unified_label = label_mapping.get(label, label)
                        # Vérifier et mettre à jour le compte dans le dictionnaire correspondant
                        if unified_label not in verites_terrain_total[fichier_json]:
                            verites_terrain_total[fichier_json][unified_label] = 0
                        verites_terrain_total[fichier_json][unified_label] += 1

    return verites_terrain_total

# Compter les vérités terrain
ground_truth_counts = count_ground_truth(dossier_json, label_mapping)

# Parcourir les images prétraitées et les fichiers JSON correspondants
for fichier_preprocessed in os.listdir(dossier_image_preprocessed):
    if fichier_preprocessed.lower().endswith((".jpg", ".jpeg", ".png")):
        nom_img = os.path.splitext(fichier_preprocessed)[0]
        chemin_image_preprocessed = os.path.join(dossier_image_preprocessed, fichier_preprocessed).replace("\\", "/")
        chemin_json = os.path.join(dossier_json, nom_img + '.json').replace("\\", "/")
        
        print(f"Traitement de l'image : {chemin_image_preprocessed}")
        print(f"Chemin prevu pour le JSON : {chemin_json}\n")
        
        if os.path.exists(chemin_json): # on charge chaque image si le chemin d'accès existe
            with open(chemin_json, 'r') as f:
                data = json.load(f)
                
            # on crée un dictionnaire pour stocker les contours
            contours_dict = {}
            for shape in data['shapes']:
                if shape['shape_type'] == 'circle':
                    label = shape['label']
                    x, y = shape['points'][0]
                    r = ((x - shape['points'][1][0]) ** 2 + (y - shape['points'][1][1]) ** 2) ** 0.5
                    contours_dict[label] = (x, y, r)
                
            otsu_img = cv2.imread(chemin_image_preprocessed, cv2.IMREAD_GRAYSCALE) # on charge l'image preprocessed en niveaux de gris
            
            contours_found, _ = cv2.findContours(otsu_img, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE) # on trouve les contours avec findcontours
            # qui utilise l'algorithme de suzuki pour la détection des contours
            
            contour_img = cv2.cvtColor(otsu_img, cv2.COLOR_GRAY2RGB) # on la met en rgb pour dessiner les contours
            cv2.drawContours(contour_img, contours_found, -1, (0, 255, 0), 2)
            
            coin_counts = count_coins(contours_dict, contours_found) # on compte les pièces trouvées
            
            pieces_trouvees_total[nom_img] = {}

            for label, count in coin_counts.items(): # on compte les pièces trouvées
                unified_label = label_mapping.get(label, label)
                if unified_label not in pieces_trouvees_total[nom_img]:
                    pieces_trouvees_total[nom_img][unified_label] = 0
                pieces_trouvees_total[nom_img][unified_label] += count
            
            for contour in contours_found: # on retrouve les contours des pièces à partir du centre du cercle
                (x, y), radius = cv2.minEnclosingCircle(contour) # pour chaquer contour on recupere centre et rayon
                cv2.circle(contour_img, (int(x), int(y)), int(radius), (0, 255, 0), 2)
                for label, (cx, cy, cr) in contours_dict.items():
                    if abs(cx - x) < 50 and abs(cy - y) < 50 and abs(cr - radius) < 50: # on compare les contours avec le json pour détecter le type de pièce
                        unified_label = label_mapping.get(label, label) 
                        print(f"Contour correspondant a {unified_label}\n")
                    
            output_contour_path = os.path.join(dossier_sortie, fichier_preprocessed).replace("\\", "/") # on download les images avec contours
            cv2.imwrite(output_contour_path, contour_img)
            
            print(f"{fichier_preprocessed} pretraite et contours detectes.")
        else:
            print(f"Aucun fichier JSON trouve pour l'image {fichier_preprocessed}")

# Afficher les résultats finaux

resultats = []
verites_terrain = []


"""print("Nombre total de pieces trouvees :\n")
for label, count in total_coin_counts.items():
    print(f"{label}: {count}\n")
    resultats.append(count) # on ajoute le nombre de pièces trouvées d'un certain label à la liste des pièces trouvées

print("Verite terrain :\n")
for label, count in ground_truth_counts.items():
    print(f"{label}: {count}\n")
    verites_terrain.append(count) # idem pour les vérités terrains"""

print("Calcul termine.")

def recup_souslistes(dict):
    total = []
    for sous_dict in dict.values():
        l = []
        for i in sous_dict.values():
            l.append(i)
        total.append(l)
    return total

pieces_trouvees = recup_souslistes(pieces_trouvees_total)
verites_total = recup_souslistes(ground_truth_counts)

print(pieces_trouvees)

print(verites_total)

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
    return(MSE)

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
    return(MAE)

MSE_TOTAL = 0
MAE_TOTAL = 0

if len(pieces_trouvees) == len(verites_total):
    for i in range(len(pieces_trouvees)):
        mae = MAE(pieces_trouvees[i], verites_total[i])
        mse = MSE(pieces_trouvees[i], verites_total[i])
        MAE_TOTAL += mae
        MSE_TOTAL += mse
else:
    print("Les listes n'ont pas la même taille.")

print(len(verites_total))
print("MAE total : "+ str(MAE_TOTAL))
print("MSE total : "+ str(MSE_TOTAL))

