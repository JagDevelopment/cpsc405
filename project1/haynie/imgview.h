//imgview.h

/*
Name: Kevin Haynie
Date: 1/18/2014
Project: 1
Filename: imgview.h
*/

#include <Magick++.h>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

using namespace std;

/* Default Width / Height Values for no command line input */

#define DEFWIDTH  	300
#define DEFHEIGHT 	300

/* Struct for containing pixel data for RGBA unsigned bytes */
struct pixel_t {
  unsigned char r, g, b, a;
};

/* Struct for image data, includes pixmap of pixel data, width/height
   of image, and a boolean to indicate whether image is currently loaded
   into memory */
struct image_t {
  pixel_t *pixmap;
  int w, h;
  bool exists;
};

/* Function prototypes */
void handleReshape(int w, int h);
void handleKey(unsigned char key, int x, int y);
void writeImage();
void readImage(string infilename, int argc);
void drawImage();
