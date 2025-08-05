import cv2 as cv
import numpy as np
import os

# images files
img_dir = "C:/Users/triqu/Documents/Image/Image_Dataset/Projet_Image/Images"

# preprocessed images files
output_ppd_dir = "C:/Users/triqu/Documents/Image/Image_Dataset/Projet_Image/preprocessed_img"
output_contour_dir = "C:/Users/triqu/Documents/Image/Image_Dataset/Projet_Image/test_countours"

for img in os.listdir(img_dir):
      if img.endswith(".jpg") or img.endswith(".JPG") or img.endswith(".png") or img.endswith(".jpeg"):
    
        img_path = os.path.join(img_dir, img)
        image = cv.imread(img_path)
        
        # convert img in gray scale
        gray_img = cv.cvtColor(image, cv.COLOR_BGR2GRAY)

        gray_img = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
        
        #_, otsu_img = cv.threshold(gray_img, 0, 255, cv.THRESH_BINARY + cv.THRESH_OTSU)
        
            # Réduire le bruit avec un filtre gaussien
        blurred_img = cv.GaussianBlur(gray_img, (9, 9), 2)
        
        # Détection des bords avec Canny
        canny_img = cv.Canny(blurred_img, 100, 200)
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