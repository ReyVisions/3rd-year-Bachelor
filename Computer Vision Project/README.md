# Projet_Image

PREREQUIS:

A la base nous voulions implementer un code permettant de detecter differents types de pieces (1 centime, deux centimes, 5,...), mais notre algorithme permet seulement de detecter des pieces toutes confondues. (Meme si l'affichage affiche les differents types de pieces).

FONCTIONNEMENT:

Le code possede deux versions de l'algorithme permettant de detecter des pieces:

A) Une version optimisee: On utilise OpenCV pour notre algorithme. On pretraite les images dans preprocessing_img.
Le temps est tout a fait raisonnable et le main peut etre lance dans un temps raisonnable

B) Une version code par nous memes: N'utilise pas de fonctions OpenCV pour les algorithmes utilises dans le cadre de notre UE. Le pretraiement est dans preprocessing_img_non_optimized.
Il est possible de tester les fonctions importantes avec testfonctions().
Le temps peut parfois prendre du temps: On garde un filtre de Gauss de taille 5, pour garder un temps raisonnable. Certaines images (8Mo) peuvent prendre presque 10 minutes a appliquer Canny et tracer les contours.


REMARQUES SUPPLEMENTAIRES:

Avant de pouvoir utiliser nos algorithmes, on prendra bien soin de changer le chemin des dossiers pour les fichiers suivants:

Dans main.py:
dossier_image_preprocessed , dossier_json , dossier_sortie

Dans preprocessing_img et preprocessing_img_non_optimized:
img_dir, output_ppd_dir ,output_contour_dir

Dans preprocessing_img_non_optimized:
la fonction main: try_folder("mettre le chemin avec toutes les images")
la fonction try_folder: cv2.imwrite(os.path.join(r"mettre le chemin d'un dossier dans lequel on applique le filtre de Canny", nom_fichier), image_canny)
