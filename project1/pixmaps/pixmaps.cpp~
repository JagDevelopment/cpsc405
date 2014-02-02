/*
 *  pixmaps.cpp
 *  
 *  Demonstration of two ways to build a pixmap
 *
 *  Created by Donald House on 8/25/08.
 *  Copyright 2008 Clemson University. All rights reserved.
 *
 */

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

//
// handy typedefs for RGBA pixels
// only one should be uncommented
//
//typedef unsigned char RGBApixel[4];
struct RGBApixel{
  unsigned char r, g, b, a;
};

// globals for 2 different kinds of pixmap
RGBApixel *pixmap1d;
RGBApixel **pixmap2d;

int Width, Height;

//
// drawing callback routine. Uncomment the line to draw the pixmap you want
//
void drawScreen(){
  glRasterPos2i(0, 0);
  
  //glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, pixmap1d);
  glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, pixmap2d[0]);
  
  glutSwapBuffers();
}

//
// Keyboard Callback Routine: 'q' or ESC quit
// This routine is called every time a key is pressed on the keyboard
//
void handleKey(unsigned char key, int x, int y){
  
  switch(key){
    case 'q':		// q - quit
    case 'Q':
    case 27:		// esc - quit
      exit(0);
      
    default:		// not a valid key -- just ignore it
      return;
  }
}

//
//  Open window and start up glut/OpenGL graphics
//
void startgraphics(int w, int h){
  
  // open window and establish coordinate system on it
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(w, h);
  glutCreateWindow("Pixmap Demo");
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
}

//
// Build different style pixmaps, and fill with red-black 8x8 checkerboard
//
void buildpixmaps(int w, int h){
  int row, col;	  // pixmap row and columen indices
  int dx, dy;	  // number of pixels wide and high for checkerboard squares
  
  // allocate an RGBA pixmap organized as a 1D array
  pixmap1d = new RGBApixel[w * h];
  
  // allocate an RGBA pixmap organized as a 2D array
  pixmap2d = new RGBApixel*[h];
  pixmap2d[0] = new RGBApixel[w * h];
  for(row = 1; row < h; row++)
    pixmap2d[row] = pixmap2d[row - 1] + w;
  
  // make checkerboards: black and red: 
  //   if board row + board col is odd, then black, else red
  dx = w / 8;	  // 8 columns on checkerboard
  dy = h / 8;	  // 8 rows on checkerboard
  for(row = 0; row < h; row++)
    for(col = 0; col < w; col++)
      if((row / dy + col / dx) % 2){
		pixmap1d[w * row + col].r = 0; pixmap1d[w * row + col].g = 0;
		pixmap1d[w * row + col].b = 0; pixmap1d[w * row + col].a = 255;
		pixmap2d[row][col].r = 0; pixmap2d[row][col].g = 0;
		pixmap2d[row][col].b = 0; pixmap2d[row][col].a = 255;
      }
      else{
		pixmap1d[w * row + col].r = 255; pixmap1d[w * row + col].g = 0;
		pixmap1d[w * row + col].b = 0; pixmap1d[w * row + col].a = 255;
		pixmap2d[row][col].r = 255; pixmap2d[row][col].g = 0;
		pixmap2d[row][col].b = 0; pixmap2d[row][col].a = 255;
      }  
}

int main(int argc, char *argv[]){
  // get image width and height from command line
  // or error if command line parameters missing
  if(argc != 3){
    cout << "usage: pixmaps w h" << endl;
    return(1);
  }
  Width = atoi(argv[1]);
  Height = atoi(argv[2]);
  
  // construct the checkerboard pixmaps
  buildpixmaps(Width, Height);
  
  // start up glut
  glutInit(&argc, argv);
  
  // open window and establish coordinate system on it
  startgraphics(Width, Height);
  
  // register glut callback routines
  glutDisplayFunc(drawScreen);	  // display callback
  glutKeyboardFunc(handleKey);	  // keyboard callback

  glutMainLoop();
  
  return 0;
}

