# Image to ASCII art
---

## Introduction
This simple program was made via the formula supported in [Wikipedia](https://en.wikipedia.org/wiki/Grayscale#Converting_color_to_grayscale "grayscale page") and the grayscale in terms of characters based on the set of characters on [Paul Bourke's site](http://paulbourke.net/dataformats/asciiart/ "ascii grayscale").

## Methodoloy
Employing the use of the formula from Wikipedia, we first convert the various color values per pixel in an image file into grayscale. Then we proceed with the process of determining the character value based on the result of the formula used.

The process can be explained in these steps:

    1. Retrieve pixel value in RGB (program assumes max value of the scale of these color is 255).
    2. Convert these values into a scale of [0,1].
    3. Remove any gamma compression via linearization formula.
    4. Calculate the linear luminance of the colors.
    5. Gamma compress the linear luminance again.
    6. Retrieve the index of the grayscale array of characters based on the percentage of the gamma compressed linear luminance.
    7. Rinse and repeat till the last pixel.


## Installation
The application makes use of the [OpenCV Library](https://opencv.org/) for computer vision. It's free, and is required to run the program.
I used version **4.0.1** when I made the program.

## Afterword
This was made during my boredom and free-time, I first tested this out on javascript, then migrated it to C++; to hone and sharpen my rusty skills in C++. 
