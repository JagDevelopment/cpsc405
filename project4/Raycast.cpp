// Raycast.cpp

/*
Name: Kevin Haynie
Date: 2/20/2014
Project: 3 - Looking a Bit Shady!
Filename: Raycast.cpp

This application is a simple raycaster with options for parallel or perspective viewing,
image write capabilities, and variable pixel width.

Syntax: ./shady [l/v] [pixwidth] [filename.ext]

Notes: Pixel width must be greater than/equal to 25 and a multiple of 5 for proper aspect ratio.
*/

using namespace std;
#include "Raycast.h"

image_t icontainer;

int main( int argc, char *argv[] ) {
  int viewmode = 1;
  int depth = 8;
  unsigned int pixwidth = DEFAULT_PIXEL_WIDTH;
  icontainer.fnameprovided = 0;
  
  // Parse command line arguments: raycast [l|v] [pixwidth] [filename.ext]
  if ( argc > 4 ) {
    cerr << "Invalid number of arguments provided. Syntax: raycast [l|v] [pixwidth] [filename.ext]" << endl;
    exit(0);
  }
  if ( argc == 4 ) {
    string temp( argv[3] );
    icontainer.fnameprovided = 1;
    icontainer.filename = temp;
  }
  if ( argc >= 3 ) {
    if ( (atoi(argv[2]) >= 25) && (( atoi(argv[2]) % 5 ) == 0) ) {
      pixwidth = atoi(argv[2]);
    } else {
      cerr << "Please enter a pixwidth greater than 25 and divisible by 5. Ex: 250" << endl;
      exit(0);
    }
  }
  if ( argc >= 2 ) {
    if ( argv[1][0] == 'l' ) {
      viewmode = 0;
    } else if ( argv[1][0] == 'v' ) {
      viewmode = 1;
    } else {
      cerr << "Invalid viewmode. Choices are 'l' for parallel and 'v' for perspective" << endl;
      exit(0);
    }
  }
  
  // List arguments
  for( int i = 1; i < argc; i++ ) {
      cout << "Argument " << i << " is " << argv[i] << ".\n";
  }
  
  Vector3d v_point = Vector3d(0.0, 0.0, 0.5);  // default viewpoint
  Vector3d v_dir = Vector3d(0.0, 0.0, -1.0);   // default view direction
  Vector3d v_up = Vector3d(0.0, 1.0, 0.0);     // default v_up
  float focal_length = 0.5;                    // Default focal length
  float aspect_ratio = 1.25;                   // Default aspect ratio
  float meter_width = 0.5;                     // Default meter width

  // Read in arguments from "camera.txt"
  string camargs[8] = { "viewpoint", "v_dir", "v_up", "focal_length", "aspect_ratio", "screen_width", "sphere", "pointlight" };
  ifstream infile ( "camera.txt" );
  int flag = -1;
  string buffer;

  // Create SceneObjects
  Scene *main_scene = new Scene();
    
  while ( infile >> buffer ) {
    flag = -1;
    for( int i = 0; i < 8; i++ ) {
      if( camargs[i] == buffer ) {
        flag = i;
      }
    }
    switch( flag ) {
      case 0: // viewpoint
        infile >> v_point[0];
        infile >> v_point[1];
        infile >> v_point[2];
        cout << "Loaded viewpoint: " << v_point << endl;
        break;
      case 1: // v_dir
        infile >> v_dir[0];
        infile >> v_dir[1];
        infile >> v_dir[2];
        cout << "Loaded view direction: " << v_dir << endl;
        break;
      case 2: // v_up
        infile >> v_up[0];
        infile >> v_up[1];
        infile >> v_up[2];
        cout << "Loaded v_up: " << v_up << endl;
        break;
      case 3: // focal_length
        infile >> focal_length;
        cout << "Loaded focal length: " << focal_length << endl;
        break;
      case 4: // aspect_ratio
        infile >> aspect_ratio;
        cout << "Loaded aspect ratio: " << aspect_ratio << endl;
        break;
      case 5: // meter_width
        infile >> meter_width;
        cout << "Loaded screen meter width: " << meter_width << endl;
        break;
      case 6: // sphere
        cout << "Loading circle..." << endl;
        main_scene->loadSphere( infile );
        break;
      case 7: // pointlight
        cout << "Loading point light..." << endl;
        main_scene->loadPointLight( infile );
        break;
      default:
        break;
    }
  }
  
  // Create Viewscreen
  ViewScreen *main_view = new ViewScreen(viewmode, pixwidth, v_point, v_dir,
                                         v_up, focal_length, aspect_ratio, meter_width);

  // Pull viewscreen pixel widths/heights and meter widths/heights
  int v_pix_w = main_view->getPixelWidth();
  int v_pix_h = main_view->getPixelHeight();
  float v_met_w = main_view->getMeterWidth();
  float v_met_h = main_view->getMeterHeight();
  
  // Create Pixmap
  int num_pixels = v_pix_w * v_pix_h;
  icontainer.pixmap = (Pixel_char_t *)malloc( sizeof(Pixel_char_t) * num_pixels );
  icontainer.w = v_pix_w;
  
  // Determine individual pixel height and width, in meters
  float pix_height = (float)v_met_h / (float)v_pix_h;
  float pix_width = (float)v_met_w / (float)v_pix_w;
  
  // Initialize values for pixel location
  icontainer.h = v_pix_h;
  float x_coord;
  float y_coord;
  
  // Find screen Center
  Vector3d c_0 = main_view->getViewPoint() + (main_view->getFocal() * main_view->getDir().normalize() );
  
  // Initialize vectors for coordinate system
  Vector3d u_x = (main_view->getDir().normalize() % main_view->getUp()).normalize();
  Vector3d u_y = ((-main_view->getDir().normalize()) % u_x).normalize();
  Vector3d u_z = (-main_view->getDir()).normalize();
  Vector3d p_center;
  
  // Calculate new viewscreen coordinates
  //cout << "u_x: " << u_x << endl << "u_y: " << u_y << endl << "u_z: " << u_z << endl;
  //cout << "c_0: " << c_0 << endl;
  
  // Iterate through all rows/columns and shoot ray from camera (origin) to pixel coordinates
  for (int row = 0; row < v_pix_h; row++) {
    y_coord = (-v_met_h / 2.0 ) + ( pix_height * ( row + 0.5 ) );
    for (int col = 0; col < v_pix_w; col++) {
      x_coord = (-v_met_w / 2.0 ) + ( pix_width * ( col + 0.5 ) );
      p_center = c_0 + ( x_coord * u_x ) + ( y_coord * u_y );
      
      Vector3d target_vector;
      
      if ( viewmode == 0 ) {
        // 'l' -- parallel - orthog
        target_vector = Vector3d( main_view->getDir() );
      } else {
        // 'v' -- perspective
        target_vector = Vector3d(p_center - main_view->getViewPoint()).normalize();
      }
      
      Object_hit_t* obj_hit = new Object_hit_t();
      Pixel_t *obj_illum = new Pixel_t();
      
      
      // **********************************************************************

      shoot( p_center, target_vector, obj_hit, main_scene, main_view, obj_illum, depth);
      
      // **********************************************************************      

      icontainer.pixmap[(row * v_pix_w) + col].r = floatToPixmap(obj_illum->r);
      icontainer.pixmap[(row * v_pix_w) + col].g = floatToPixmap(obj_illum->g);
      icontainer.pixmap[(row * v_pix_w) + col].b = floatToPixmap(obj_illum->b);
      free(obj_hit);
      free(obj_illum);
    }
  }
  
  // Image now exists, flag for Glut
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

// Convert float to RGB pixmap scaled value -- ceiling = 255, floor = 0
unsigned char floatToPixmap( float val ) {
  int temp = 0;
  temp = val * 255;
  if (temp > 255.0) temp = 255.0;
  if (temp <= 0.0) temp = 0.0;
  return temp;
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
    if ((w < icontainer.w ) || (h < icontainer.h)) {
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
case 'r': // 'r' or 'R' -- Prompt user for input image filename
case 'R':
readImage( "", 0 );
break;
*/
    case 'w': // 'w' or 'W' -- Prompt user for output image filename
    case 'W':
      writeImage();
      break;
      
    case 'q': // Program exit
    case 'Q':
    case 27: // esc
      exit( 0 );
      
    default: // invalid keypress, ignore
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
  
  if ( icontainer.fnameprovided ) {
    outfilename = icontainer.filename;
    cout << "User provided filename: " << outfilename << endl;
  } else {
  /* Prompt user for output filename and write image */
  cout << "Output image filename: ";
  cin >> outfilename;
  }
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

// Momentarily unused
void shoot(Vector3d origin, Vector3d target_vector, Object_hit_t* obj_hit, Scene* main_scene, ViewScreen* main_view, Pixel_t* obj_illum, int depth) {
  Pixel_t *ref_illum = new Pixel_t();
  Object_hit_t *ref_obj_hit = new Object_hit_t();

  if ( depth <= 0 ) {
    return;
  }
      /*
      if ( depth <= 0 ) {
        obj_illum->r = 0;
        obj_illum->g = 0;
        obj_illum->b = 0;        
        return;
      }*/

  // Start with first object in list
  SceneObj* cur_target = main_scene->headPoly;

  // While currently targetting a valid object, call hit function on object with correct viewmode
  while( cur_target != NULL ) {    
  // Move to next target
    cur_target->hit( origin, target_vector, obj_hit);
    cur_target = cur_target->next;
  } 
  
  // Create illumination value and scale by ambient

                               
  // If object hit, do reflection, lighting, and set pixel value to color values
  
  if ( obj_hit->hit_object != NULL ) {

    Vector3d new_origin = obj_hit->hit_point;
    Vector3d u_prime = target_vector - ( obj_hit->hit_normal * ( target_vector * obj_hit->hit_normal ) ) * 2;
    u_prime = u_prime.normalize();
    ref_obj_hit->prev_hit_object = obj_hit->hit_object;
    shoot( new_origin, u_prime, ref_obj_hit, main_scene, main_view, ref_illum, depth-1);

    obj_illum->r = 0.2 * obj_hit->hit_color.r;
    obj_illum->g = 0.2 * obj_hit->hit_color.g;                                   
    obj_illum->b = 0.2 * obj_hit->hit_color.b;        

    obj_illum->r = (obj_illum->r * 0.3) + ( ref_illum->r * 0.7 );
    obj_illum->g = (obj_illum->g * 0.3) + ( ref_illum->g * 0.7 );
    obj_illum->b = (obj_illum->b * 0.3) + ( ref_illum->b * 0.7 );
    
    Light *cur_light = main_scene->headLight;
    while( cur_light != NULL ) {
      cur_light->doLighting( obj_hit, main_scene, main_view, obj_illum );
      cur_light = cur_light -> next;
    }
  } else {
    obj_illum->r = 0.0;
    obj_illum->g = 0.0;
    obj_illum->b = 0.0;
  }
}
