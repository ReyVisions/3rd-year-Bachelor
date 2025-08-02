# Project: Algorithmics and image processing on Mona Lisa

**Author**: Remy XU
**Project type**: College individual project

## Description

This project was developed in Java and consists of six `.java` files. It aims to manipulate color images using advanced image processing and graph techniques. Detailed explanations are provided mainly in the form of Javadoc comments in the code.

## Features

- **Image Opening and Transformation**: Open an image and transform it into an array of RGB pixels.
- **Color Conversion**: Convert the image from the RGB color space to CIE L\*a\*b\*.
- **Graph Structure**: Create a graph structure including edges, vertices, and vertex neighbors.
- **Connectivity**: Create edges in 8-connectivity or less depending on the vertex situation.
- **Edge Weights**: Create weights between the Lab values of pixels (graph vertices).
- **Dijkstra's Algorithm**: Implementation of Dijkstra's algorithm between two coordinates. It works correctly for a distance of x and y of about 100 pixels. Beyond that, the program may not work correctly or may take too long.

## RGB to CIE L\*a\*b\* Conversion

In this project, RGB values are taken between 0 and 255, where (0, 0, 0) represents black and (255, 255, 255) represents white. Although the standard norm uses values between 0 and 1, this approach was chosen for readability reasons.

The sRGB (or RGB) standard is not representative of colorimetry relative to the human eye. Therefore, this project uses the CIE L\*a\*b\* color space to describe colors, whose Euclidean distance is applicable. RGB values are first converted to CIE XYZ, then to CIE L\*a\*b\*.

- [RGB to CIE XYZ Conversion](http://www.brucelindbloom.com/index.html?Eqn_RGB_to_XYZ.html)
- [CIE XYZ to CIE L\*a\*b\* Conversion](https://en.wikipedia.org/wiki/Lab_color_space)

## Remarks on Testing

Running examples on large images can take time. For example, Dijkstra's algorithm between coordinates (0, 0) and (300, 100) took approximately 11 minutes to execute. This also includes displaying provisional distance values if they are updated and displaying the edge on which the program is working.

To speed up execution time, you can remove the following lines in `Graphe.java`:

```java
System.out.println("Voici : " + system() + " Poids 10 " + poids);
System.out.println("Mise à jour de la distance pour le sommet " + .getNom());
