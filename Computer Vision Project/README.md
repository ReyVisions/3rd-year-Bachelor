# Group Project Report: Coin Contour Detection


**Author**: Remy XU


**Project type**: Group Project of 4 students

## Summary

The project aims to study and implement image processing techniques for detecting the contours of coins in digital images. As part of our Image Processing course in the sixth semester at Université Paris Cité, each group submitted about twenty photos of coins, forming the study dataset for coin detection.

## Introduction

Detecting object contours in images is a crucial step in many computer vision applications, such as object recognition, image segmentation, and industrial image analysis. This task involves extracting the boundaries of objects present in an image, facilitating their identification and analysis. Various image processing techniques can be used for this detection, including convolution filters, edge detectors like Sobel and Canny, and morphological transformations.

In this context, algorithms can be developed manually or using libraries like OpenCV, which offer optimized and robust functions for contour detection and other image operations.

This project report will explain the principles used through these two methods (with and without OpenCV), the results obtained with error evaluation, and potential improvements.

## Table of Contents

1. [Image Labeling](#image-labeling)
2. [Image Preprocessing](#image-preprocessing)
3. [Contour Detection](#contour-detection)
4. [Associating Contours with Annotations](#associating-contours-with-annotations)
5. [Choosing the 60/20/20 Ratio for Training, Test, and Validation Sets](#choosing-the-602020-ratio-for-training-test-and-validation-sets)
6. [Converting Images to JSON](#converting-images-to-json)
7. [Results](#results)
8. [Problems Encountered](#problems-encountered)
9. [Improvement Strategies](#improvement-strategies)
10. [Conclusion](#conclusion)

## Image Labeling

All images were labeled using the Labelme software, with contours shaped as circles. Some coins positioned differently (on their side instead of heads or tails) or partially overlapping were labeled with polygons. Different types of Euro coins were distinguished: 1 cent, 10 cents, ..., up to 2 euros.

![Labeling Application](image_url)

Thanks to LabelMe, these labels were converted into .json files, which helped compare our model (input) with the ground truth (target).

## Image Preprocessing

Image preprocessing is a crucial step in preparing data for contour detection. We preprocessed a dataset of 140 images using various image processing techniques. These steps help reduce noise, enhance edge quality, and prepare images for contour detection.

All the following functions were implemented, but OpenCV was also used for performance and optimization reasons.

### Convolution Filters and Padding

Convolution filters are used to apply local transformations to the image. We implemented classic filters such as averaging, median, and Gaussian filters with adjustable parameters. During the project, we chose to use the Gaussian filter (Gaussian Blur) to reduce noise.

Padding is applied to prevent the edges of the image from being affected by these transformations. Zero padding, copy padding, or symmetric padding were implemented.

### Sobel Filters

Sobel filters are used to detect horizontal and vertical edges in an image using horizontal and vertical gradient filters. These filters detect color or brightness transitions, which are often the edges of objects in most of our images. We applied Sobel filters to each image to identify the edges of the coins.

### Canny Edge Detector

For performance reasons, we decided to abandon the Sobel filter and focus on the Canny filter. The Canny edge detector is a more sophisticated algorithm that detects edges by identifying rapid changes in pixel intensity.

The four steps were as follows:
a) Gaussian filter
b) Calculation of gradients and directions
c) Non-maximum suppression in 8-connectivity
d) Selection of nodes to keep based on min_value and max_value

This filter was applied to all images to obtain a binary map of detected edges, which was then used to identify the contours of the coins.

### Morphological Transformations

Morphological transformations, such as erosion and dilation, were used to refine the results of edge detection. Erosion reduces objects in an image, while dilation enlarges them. These operations were applied to improve contour detection and fill gaps in detected objects.

Although an opening (erosion, dilation) seems more logical for our problem, we chose a closing (dilation, erosion) using a cross-shaped structuring element (Matrix [[0,1,0],[1,1,1],[0,1,0]]). Due to time constraints, we measured the morphological transformation that gave the best experimental results.

![Preprocessing Applications](image_url)

Initially, we used our own functions for the Gaussian filter and the Canny algorithm. We noticed that the contours were mostly detected in this image, but variations in the image background were also detected. Using closing or opening did not visually yield notable results, but theoretically, it should work well.

In a second step, using the Canny algorithm with OpenCV allowed for a fine, precise contour without background noise. However, there were sometimes false positives for more complex images constituting a minority of the dataset (or exceptional cases).

## Contour Detection

Once the images were preprocessed, we used the cv2.findContours function from OpenCV to detect contours in the images. However, two versions of the code were developed for contour detection:

Initially, we considered methods like the Hough transform for circle detection and the convex hull method to extract contours. However, we later decided to focus on other functions.

The second version relies entirely on the cv2.findContours function from OpenCV, which is optimized for contour detection in images. This version offers faster performance and is more robust to image artifacts.

![Contour Detection Application](image_url)

Here is an example of applying findContours to the image preprocessed with our functions. We notice that the slightest round details are detected as coins. There are very frequent false positives (when non-existent coins are detected) and false negatives (when coins are not detected).

We notice that the function works much better on the image preprocessed with OpenCV methods. However, here we notice 3 false positives.

## Associating Contours with Annotations

Once the contours were detected, we compared the results with the annotations in JSON format to identify the coins in the image. The annotations contain the coordinates of the center and the radius of the coins. We used this information to associate each detected contour with an annotation.

## Choosing the 60/20/20 Ratio for Training, Test, and Validation Sets

To evaluate the performance of our algorithms, we chose to divide our image database into two subsets: a training set and a test set. We used a 60/20/20 ratio, meaning that 60% of the images were used for training our models, while 20% were reserved for performance evaluation. The remaining 20% were kept for model validation.

## Converting Images to JSON

To facilitate annotation and data management, we converted the information related to the detected coins (centers and radii) into JSON format using the LabelMe software. This allows for easy storage of metadata associated with each image, including information about the contours of annotated objects.

## Results

The results of the performance evaluation showed significant differences between the two versions of the code, both in terms of accuracy and performance.

### Error Evaluation

#### Without OpenCV (custom code):

a) Average MAE per image = 9.1
b) MAE over the entire dataset (22 images) = 206
c) Average MSE = 315.1
d) MSE over the entire dataset = 6302

The error evaluation shows that the method without OpenCV has a significant error over only 22 preprocessed images. This is likely due to the rudimentary implementation of the functions, poorer performance for the implementation of the Canny filter, or the use of closing instead of opening.

The average error per image is relatively high, suggesting that the preprocessing techniques used are less robust.

#### With OpenCV:

a) Average MAE per image = 2.9
b) MAE over the entire dataset (140) = 616
c) Average MSE = 20
d) MSE over the entire dataset = 5700

Using OpenCV significantly reduced the error, particularly the MAE per image (about 3 coins incorrectly detected per image). We notice an MSE and MAE of the same order of magnitude, even though we applied our model to 140 images instead of 22. The performance remains quite mediocre using OpenCV functions, but given the complexity of the images, these are much more satisfactory statistics than our first method.

## Problems Encountered

During our coin contour detection project, several problems arose, each affecting different stages of the work. Here is a summary of the main challenges encountered:

1. **Labeling of Labels**: A major problem was related to the labeling of labels in JSON files. The annotations were sometimes imprecise, and the shapes were poorly defined or incomplete, making it difficult to correctly associate the detected contours with the actual coins in the image. Although this was a human error on our part, standardization among each member was difficult, so we had to revisit this part several times to adapt to our code.

2. **Recoding OpenCV Functions**: We also tried to recreate some OpenCV functions to better understand their operation. However, reproducing functions like cv2.findContours was not easy. Managing contours and their precision was not always successful, which forced us to revert to using OpenCV functions, which are more effective and reliable for this type of task.

3. **Images with Complex Backgrounds**: Errors were mainly due to image backgrounds that could disrupt image detection. For example, there were images with a mattress background with round patterns (which could be detected as coins), or images with a striped table that, with the Canny filter, were detected as positive for contours.

4. **Preprocessing Time with Our Methods**: Another difficulty came from the computation time. Our own functions were much slower than those of OpenCV. Preprocessing took a lot of time, especially for complex images, making the analysis of a large number of images (like our dataset of 140 images) slower and less efficient.

5. **Detection without JSON Labels**: Using targets was fundamental to help us detect the presence of coins. But without the JSON files, it was difficult for us to design an unsupervised model. This independence can be an axis for improvement.

## Improvement Strategies

1. **Parameter Optimization**: The choice of Canny and Sobel parameters can be optimized for specific images, particularly by adjusting the edge detection thresholds.
2. **Advanced Methods**: Using machine learning techniques could improve the accuracy of detection in complex images, for example, by using convolutional neural networks (CNNs).

## Conclusion

The project showed that detecting the contours of coins can be effectively achieved using classical image processing techniques, such as Sobel filters, Canny, and morphological transformations. Although both versions of the code (custom and OpenCV) showed similar results, the OpenCV version is faster and more robust, making it ideal for large-scale applications.

The project could be improved by using machine learning techniques to refine the detection and analysis of contours in more complex images.
