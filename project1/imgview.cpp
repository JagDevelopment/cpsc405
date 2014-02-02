//imgview.cpp

/*
Name: Kevin Haynie
Date: 1/18/2014
Project: 1
Filename: imgview.cpp

This application is a simple image viewer with image read and write capabilities. It
utilizes OpenGL for window control and drawing. Additionally, it uses ImageMagick's
Magick++ library for C++ to handle all image reading, writing, and the underlying
functionality for pixmap population.

Usage: See README
*/

#include "imgview.h"

/* Initialize container to be used to hold image pixmap, width, and height
   Global so that GLUT may access from within callbacks during mainloop */
image_t icontainer;

int main( int argc, char* argv[] ) {
  /* Initialize GLUT, set display mode to double buffered, RGBA color mode,
     set initial window size, and create the window with title provided */
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
  glutInitWindowSize( DEFWIDTH, DEFHEIGHT );
  glutCreateWindow( "Image View" );
  
  /* Define GLUT callback functions for mainloop */
  glutReshapeFunc( handleReshape );
  glutDisplayFunc( drawImage );
  glutKeyboardFunc( handleKey );
  
  /* Determine if image given at command line.  If so, proceed with reading image */
  if ( argc == 2 ) {
    readImage( argv[1], argc );
  }
  
  /* Enter GLUT's mainloop */
  glutMainLoop();
  return 0;
}

void handleReshape( int w, int h ) {
  // Initialize viewport x/y start positions and default scale factor
  int vx = 0;
  int vy = 0;
  float leastscalefactor = 1.0;  

  //Default viewport of 0, 0, window width, window height
  glViewport(vx, vy, w, h);

  /* Determine if window is now smaller than original image size and calculate
     the scalefactor of the most restricted dimension */
  if ( icontainer.exists ) {
    if ((w < icontainer.w ) || (h < icontainer.h))  {
      float scalefactorw = (float)w / (float)icontainer.w;
      float scalefactorh = (float)h / (float)icontainer.h;

      if ( scalefactorw < scalefactorh ) {
        leastscalefactor = scalefactorw; // Width is smallest relative dimension
      } else {
        leastscalefactor = scalefactorh; // Height is smallest relative dimension
      }
    }
    /* Determine if original or scaled image is now smaller than the window on any
       side, and "slide" the viewport to center the image */
    if( w > (leastscalefactor * icontainer.w) ) {
      vx = (w - (icontainer.w * leastscalefactor))/2; // Width is smaller
    }
    if( h > (leastscalefactor * icontainer.h) ) {
      vy = (h - (icontainer.h * leastscalefactor))/2; // Height is smaller
    }
    // Set the viewport to the adjusted coordinates, and scaled width/height of image
    glViewport(vx, vy, (icontainer.w * leastscalefactor), (icontainer.h * leastscalefactor));
  }
  
  // Scale w and h of the image by the smallest scale factor
  glPixelZoom(leastscalefactor, leastscalefactor);
  
  /* Swap to projection matrix for Ortho2D operation, load Identity Matrix, perform
     operation, and then switch back to modelview matrix */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);
  return;
}

void handleKey( unsigned char key, int x, int y ) {
  switch( key ){
    case 'r':   // 'r' or 'R' -- Prompt user for input image filename
    case 'R':
      readImage( "", 0 );
      break;
    
    case 'w':   // 'w' or 'W' -- Prompt user for output image filename
    case 'W':   
      writeImage();
      break;
      
    case 'q':   // Program exit
    case 'Q':
    case 27:    // esc
      exit( 0 );
      
    default:    // invalid keypress, ignore
      return;
  }
}

/* Image Draw callback routine for MainLoop... if image has been loaded, reset the
   raster position to the bottom left corner and draw pixels of w x h contained in
   the associated pixmap
*/
void drawImage() {
  
  if ( icontainer.exists ) {
    glRasterPos2i( 0, 0 );
    glDrawPixels( icontainer.w, icontainer.h, GL_RGBA, GL_UNSIGNED_BYTE, icontainer.pixmap );
  }
  
  glutSwapBuffers();
  return;
}

/*
Write image currently displayed in GLUT window to filename specified by user.
*/
void writeImage() {
  int w = glutGet( GLUT_WINDOW_WIDTH );
  int h = glutGet( GLUT_WINDOW_HEIGHT );
  unsigned char pixmap[4 * w * h];
  string outfilename;
  
  /* Read pixels on front frame buffer and store in associated pixmap of size 
     4 * window width * window height */
  glReadBuffer(GL_FRONT);
  glReadPixels( 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixmap );
  
  /* Load pixmap into a Magick image type and flip image to prepare for write */
  Magick::Image image( w, h, "RGBA", Magick::CharPixel, (void *)pixmap );
  image.flip();
  
  /* Prompt user for output filename and write image */
  cout << "Output image filename: ";
  cin >> outfilename;
  cout << "Attempting to save image to " << outfilename << "...\n";
  
  try {
    image.write( outfilename );
  }
  
  catch( exception &e ) {
    cout << "Error in write attempt: " << e.what() << endl;
    return;
  }

  cout << "Image saved to " << outfilename << " successfully." << endl;

  return;
}

/*
Read image file specified by user and prepare for draw
*/
void readImage( string infilename, int argc ) {
  string filename = infilename;
  Magick::Image image;
  
  /* If call is made from keypress, and not from command line input, prompt
     user for input */
  if ( argc == 0 ) {
    cout << "Image filename to read: ";
    cin >> filename;
  }
  
  cout << "Attempting to read " << filename << "...\n";
  
  try {
    image.read( filename );
  }
  
  catch ( exception &e ) {
    cout << "Error in read attempt: " << e.what() << endl;
    return;
  }  
  
  cout << "Loaded " << filename << " successfully." << endl;
  
  /* Flip image, set container flags and values to image associated values,
     create the image pixmap, and write the image data to the pixmap. */
  image.flip();
  icontainer.exists = true;
  icontainer.w = image.columns();
  icontainer.h = image.rows();
  icontainer.pixmap = new pixel_t[4 * icontainer.w * icontainer.h];
  image.write(0, 0, icontainer.w, icontainer.h, "RGBA", Magick::CharPixel, icontainer.pixmap);
  
  /* Resize window to the imagae dimensions */
  glutReshapeWindow(icontainer.w, icontainer.h);
    
  return;
}


