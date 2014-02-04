// Raycast.cpp

using namespace std;
#include "Raycast.h"

image_t icontainer;

int main( int argc, char *argv[] ) {
  char viewmode = 'c';
  //unsigned int pixwidth = DEFAULT_PIXEL_WIDTH;
  unsigned int pixwidth = 750;
  string filename;
  
  for( int i = 1; i < argc; i++ ) {
      cout << "Argument " << i << " is " << argv[i] << ".\n";
  }
  
  // Create Viewscreen
  ViewScreen *main_view = new ViewScreen(viewmode, pixwidth);
 
  // Create SceneObjects
  Scene *main_scene = new Scene();
  
  int v_pix_w = main_view->getPixelWidth();
  int v_pix_h = main_view->getPixelHeight();
  double v_met_w = main_view->getMeterWidth();
  double v_met_h = main_view->getMeterHeight();
  
  // Create Pixmap
  int num_pixels = v_pix_w * v_pix_h;
  icontainer.pixmap = (Pixel_t *)malloc( sizeof(Pixel_t) * num_pixels );
  icontainer.w = v_pix_w;
  icontainer.h = v_pix_h; 
  
  // Draw rays, pixel by pixel, and check collision with all scene objs
  double pix_height = (double)v_met_h / (double)v_pix_h;
  double pix_width = (double)v_met_w / (double)v_pix_w;

  double x_coord;
  double y_coord;  
  double z_coord = 0.0;

  for (int row = 0; row < v_pix_h; row++) {
    y_coord = 0.0 - ( v_met_h / 2.0 ) + ( pix_height * ( row + 0.5 ));
    for (int col = 0; col < v_pix_w; col++) {
      x_coord = 0.0 - ( v_met_w / 2.0 ) + ( pix_width * ( col + 0.5 ));
      Object_hit_t* obj_hit = new Object_hit_t();
      Vector3d target_vector = Vector3d(x_coord, y_coord, z_coord);
      Pixel_t pixcolor = shoot( Vector3d(target_vector[0], target_vector[1], 0.5),
                                target_vector,
                                obj_hit,
                                main_scene,
                                viewmode );
      if ( obj_hit->hit_object != NULL ) {
        icontainer.pixmap[(row * v_pix_w) + col].r = obj_hit->hit_object->getColor().r;
        icontainer.pixmap[(row * v_pix_w) + col].g = obj_hit->hit_object->getColor().g;
        icontainer.pixmap[(row * v_pix_w) + col].b = obj_hit->hit_object->getColor().b;
      }
      free(obj_hit);
    }
  }
  
  icontainer.exists = TRUE;
  
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
  glutInitWindowSize( v_pix_w, v_pix_h );
  glutCreateWindow( "Raycaster" );
    
  glutReshapeFunc( handleReshape );
  glutDisplayFunc( drawImage );
  glutKeyboardFunc( handleKey );
  
  glutMainLoop();
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
  /*
    case 'r':   // 'r' or 'R' -- Prompt user for input image filename
    case 'R':
      readImage( "", 0 );
      break;
  */  
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

void drawImage() { 
  if ( icontainer.exists ) {
    glRasterPos2i( 0, 0 );
    glDrawPixels( icontainer.w, icontainer.h, GL_RGBA, GL_UNSIGNED_BYTE, icontainer.pixmap );
  }
  
  glutSwapBuffers();
  return;
}

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

Pixel_t shoot(Vector3d origin, Vector3d target_vector, Object_hit_t* obj_hit, Scene* main_scene, char viewmode) {
  SceneObj* cur_target = main_scene->headPoly;
  while( cur_target != NULL ) {
    if ( viewmode == DEFAULT_VIEW_MODE ) {
      cur_target->hit( origin, target_vector, obj_hit );
    } else {
      cur_target->hit( Vector3d(target_vector[0], target_vector[1], 0.5), target_vector, obj_hit );
    }
    // if hit, compare obj_hit->distance
    // if closer, obj_hit = curPoly
      // set norm
      // set distance
      // set hit point
      // set obj hit
    cur_target = cur_target->next;
  }
}

