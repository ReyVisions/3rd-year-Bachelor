import cv2
import numpy as np
import matplotlib.pyplot as plt
import json

with open('evaluation_set/251.json', 'r') as f:
    data = json.load(f)

contours_dict = {}
for shape in data['shapes']:
    if shape['shape_type'] == 'circle':
        label = shape['label']
        x, y = shape['points'][0]
        r = ((x - shape['points'][1][0]) ** 2 + (y - shape['points'][1][1]) ** 2) ** 0.5
        contours_dict[label] = (x, y, r)

otsu_img = cv2.imread('preprocessed_img/251.jpg', cv2.IMREAD_GRAYSCALE)

contours_found, _ = cv2.findContours(otsu_img, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

contour_img_green = cv2.cvtColor(otsu_img, cv2.COLOR_GRAY2RGB)

for contour in contours_found:
    (x, y), radius = cv2.minEnclosingCircle(contour)
    cv2.circle(contour_img_green, (int(x), int(y)), int(radius), (0, 255, 0), 10)
    for label, (cx, cy, cr) in contours_dict.items():
        if abs(cx - x) < 50 and abs(cy - y) < 50 and abs(cr - radius) < 50:
            
            print(f"Contour correspondant a {label}")

plt.imshow(contour_img_green)
plt.show()
