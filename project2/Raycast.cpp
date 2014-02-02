// Raycast.cpp

using namespace std;
#include "Raycast.h"

int main( int argc, char *argv[] ) {
  char viewmode = DEFAULT_VIEW_MODE;
  unsigned int pixwidth = DEFAULT_PIXEL_WIDTH;
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
  Pixel_t *pixmap = (Pixel_t *)malloc( sizeof(Pixel_t) * num_pixels ); 
  
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
      Pixel_t pixcolor = shoot( main_view->getViewPoint(),
                                target_vector,
                                obj_hit,
                                main_scene );
      // CONSOLIDATE INTO SHADE FUNCTION
      //pixmap[row][col]->r = pixcolor.r;
      //pixmap[row][col]->g = pixcolor.g;
      //pixmap[row][col]->b = pixcolor.b;
      
      free(obj_hit);
    }
  }
  
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

}

void handleKey( unsigned char key, int x, int y ) {

}

void drawImage() {

}

void writeImage() {

}

Pixel_t shoot(Vector3d origin, Vector3d target_vector, Object_hit_t* obj_hit, Scene* main_scene) {
  SceneObj* cur_target = main_scene->headPoly;
  while( cur_target != NULL ) {
    cur_target->hit( obj_hit );
    // if hit, compare obj_hit->distance
    // if closer, obj_hit = curPoly
      // set norm
      // set distance
      // set hit point
      // set obj hit
    cur_target = cur_target->next;
  }
}

