# Image Filtering in Cpp
A group project developed in the course of Computer Programming with C++, regarding adjustable filters on images in P6 PPM format. This format is one of the simplest ways of image representation, and is a combination of ASCII and binary format. More about PPM format can be found [here](http://paulbourke.net/dataformats/ppm/).

## Static Library
Images are required to have certain format as the program works only on 24bit PPM images. 
**ppm** is a static library that offers two functionalities, the function to read a PPM image and store its data in order to alter them, and the function to convert the altered data back to a PPM image form.  
*it is assumed that the headers of the images do not contain comments.

## Filters
There are three filters implemented, adjusted by user's arguments when the program is run. Each filter changes every pixel of the image based on a matherical type. 

### LinearFilter
This filter requires two arguments, **a** and **c**, which are 3-digit vectors. The algorithm this filter follows is the one below :
> p'(x,y) = a * p(x,y) + c  

| Original         | -f linear 2 2 2 0 0 0     |
|:--------------:|:-----------:|
| ![original](https://github.com/themelinaKz/UniWork/blob/master/Image%20Filtering%20in%20Cpp/images/original.png) | ![linera](https://github.com/themelinaKz/UniWork/blob/master/Image%20Filtering%20in%20Cpp/images/linear_only.png) |


### GammaFilter
This filter requires one argument, **g** , which is a float number between 0.5 and 2. The algorithm this filter follows is the one below :
> p'(x,y) = p(x,y)<sup>g</sup>

| Original         | -f gamma 2.0 -f linear -1 -1 -1 1 1 1     |
|:--------------:|:-----------:|
| ![original](https://github.com/themelinaKz/UniWork/blob/master/Image%20Filtering%20in%20Cpp/images/original.png) | ![linera](https://github.com/themelinaKz/UniWork/blob/master/Image%20Filtering%20in%20Cpp/images/linear_gamma.png) |

### BlurFilter
This filter requires one argument, **g** , which is a float number between 0.5 and 2. The concept of this filter is FilterBlur

The way this filter works is that it reads an NxN pixel space with (x,y) pixel being the center of this space, and sets (x,y) pixel's color to be the sum of all colors of the NxN area with a weight of 1/N<sup>2</sup>.  
Each pixel p'(x,y) is equal to:   
>      N/2     N/2
>       Σ    {  Σ   { p(x+M,y+n) * f(m+N/2, n+N/2)) } }
>      m=-N/2  n=-N/2

## Group
I did this project with [Marilena Kokkini](https://github.com/marilenakokkini)

*Winter 2018-2019*