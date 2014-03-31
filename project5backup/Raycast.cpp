// Raycast.cpp

/*
Name: Kevin Haynie
Date: 3/3/2014
Project: 4 - Ooh, shiny!
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
  OBJFile objfile;
  PolySurf *scene;	      // polygonal surface data structure
  Vector3d centroid, bboxmin, bboxmax; 
  icontainer.fnameprovided = 0;
  
  // Parse command line arguments: raycast [l|v] [pixwidth] [filename.ext]
  if ( argc < 3 || argc > 4 ) {
    cerr << "Invalid number of arguments provided. Syntax: objview objfile.obj [nrays]" << endl;
    exit(0);
  }
  
  
  /*
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
  */
  
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
  string camargs[11] = { "viewpoint", "v_dir", "v_up", "focal_length", "aspect_ratio", "screen_width", "sphere", "pointlight", "plane", "pixwidth", "viewmode"  };
  ifstream infile ( "camera.txt" );
  int flag = -1;
  string buffer;

  // Create SceneObjects
  Scene *main_scene = new Scene();
    
  while ( infile >> buffer ) {
    flag = -1;
    for( int i = 0; i < 11; i++ ) {
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
        cout << "Loading sphere..." << endl;
        main_scene->loadSphere( infile );
        break;
      case 7: // pointlight
        cout << "Loading point light..." << endl;
        main_scene->loadPointLight( infile );
        break;
      case 8: // plane
        cout << "Loading plane..." << endl;
        main_scene->loadPlane( infile );
        break;
      case 9: // pixwidth
        infile >> pixwidth;
        cout << "Loaded pixwidth: " << pixwidth << endl;
        break;
      case 10: // viewmode
        infile >> viewmode;
        cout << "Loaded view mode: " << viewmode << endl;
        break;
      default:
        break;
    }
  }
  
  get_commandline(argc, argv, objfile);

  // load scene and print the scene
  load_scene(&scene, objfile);
  cout << *scene << endl;
  
  // get and print the centroid and bounding box
  centroid = scene->Centroid();
  bboxmin = scene->MinBBox();
  bboxmax = scene->MaxBBox();
  cout << "Centroid = " << centroid << ", Bounding Box: (" << bboxmin << ", " << bboxmax << ")" << endl;
  
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
      
      Collision* obj_hit = new Collision();
      Pixel_t *obj_illum = new Pixel_t();
      
      
      // **********************************************************************

      shoot( p_center, target_vector, obj_hit, main_scene, scene, main_view, obj_illum, 0);
   
      // **********************************************************************      
      
      if ( obj_hit->hit_distance == INFINITY ) {
        icontainer.pixmap[(row * v_pix_w) + col].r = floatToPixmap(0);
        icontainer.pixmap[(row * v_pix_w) + col].g = floatToPixmap(0);
        icontainer.pixmap[(row * v_pix_w) + col].b = floatToPixmap(0);
      } else {
        //cout << "Writing color r: " << obj_illum->r << ", g: " << obj_illum->g << ", b: " << obj_illum->b << "." << endl;
        //icontainer.pixmap[(row * v_pix_w) + col].r = floatToPixmap(obj_illum->r);
        //icontainer.pixmap[(row * v_pix_w) + col].g = floatToPixmap(obj_illum->g);
        //icontainer.pixmap[(row * v_pix_w) + col].b = floatToPixmap(obj_illum->b);
        icontainer.pixmap[(row * v_pix_w) + col].r = floatToPixmap(255);
        icontainer.pixmap[(row * v_pix_w) + col].g = floatToPixmap(0);
        icontainer.pixmap[(row * v_pix_w) + col].b = floatToPixmap(0);
      }
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
      exit(0);
      
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

void shoot(Vector3d origin, Vector3d target_vector, Collision* obj_hit, Scene* main_scene, PolySurf* poly_scene, ViewScreen* main_view, Pixel_t* obj_illum, int depth) {
  Pixel_t *ref_illum = new Pixel_t();
  Collision *ref_obj_hit = new Collision();

  // Reached end of recursion
  if ( depth >= 8 ) {
    return;
  }

  // Start with first object in list
  int cur_index = 0;

  // While currently targetting a valid object, call hit function on object with correct viewmode
  while( cur_index < poly_scene->nfaces ) {    
  // Move to next target
    hitTriangle( origin, target_vector, obj_hit, poly_scene, cur_index );
    cur_index++;
  } 
  
//  void hitTriangle(Vector3d origin, Vector3d target_vector, Collision* obj_hit, PolySurf* scene, int index);
  
  // Create illumination value and scale by ambient

                               
  // If object hit, do reflection, lighting, and set pixel value to color values
  
  if ( obj_hit->hit_distance < INFINITY && obj_hit -> hit_distance > 0.001 ) {
    Vector3d new_origin = obj_hit->hit_point;
    Vector3d u_prime = target_vector - ( obj_hit->hit_normal * ( target_vector * obj_hit->hit_normal ) ) * 2;
    u_prime = u_prime.normalize();
    ref_obj_hit->prev_hit_index = obj_hit->hit_index;
    shoot( new_origin, u_prime, ref_obj_hit, main_scene, poly_scene, main_view, ref_illum, depth + 1);

    // TODO -- Ambient based on poly
    // Factor in ambient light at location
    Color obj_ambient = poly_scene->materials[poly_scene->faces[obj_hit->hit_index].material].a;
    int illum_model = poly_scene->materials[poly_scene->faces[obj_hit->hit_index].material].illum_model;
    
    obj_illum->r = obj_ambient[0] * obj_hit->hit_color.r;
    obj_illum->g = obj_ambient[1] * obj_hit->hit_color.g;                                   
    obj_illum->b = obj_ambient[2] * obj_hit->hit_color.b;        

    // TODO -- Sum based on Poly
    // Weight object illumination and reflection illumination, and sum
    if ( illum_model == 1 || illum_model == 2 ) {
      // TODO -- CHECK AND VERIFY ILLUMINATION MODEL PROPERTIES
      obj_illum->r = (obj_illum->r * 0.3) + ( ref_illum->r * 0.7 );
      obj_illum->g = (obj_illum->g * 0.3) + ( ref_illum->g * 0.7 );
      obj_illum->b = (obj_illum->b * 0.3) + ( ref_illum->b * 0.7 );
    }
    Vector3d view_loc;
    
    if ( depth == 0 ) {
      view_loc = main_view->getViewPoint();
    } else {
      view_loc = origin;
    }
    
    Light *cur_light = main_scene->headLight;
    while( cur_light != NULL ) {
      cur_light->doLighting( obj_hit, main_scene, poly_scene, main_view, obj_illum, view_loc );
      cur_light = cur_light -> next;
    }
    
  } else {
    obj_illum->r = 0.0;
    obj_illum->g = 0.0;
    obj_illum->b = 0.0;
  }
  
  delete ref_illum;
  delete ref_obj_hit;
}

//
// Load the scene and get the centroid and bounding box
//
void load_scene(PolySurf **scene, OBJFile &objfile){

  int err = objfile.read();
  *scene = objfile.getscene();

  if(err || scene == NULL){
    char *filename = objfile.getfilename();
    cerr << "OBJ file " << filename << " has errors" << endl;
    exit(2);
  }
}

void hitTriangle(Vector3d origin, Vector3d target_vector, Collision* obj_hit, PolySurf* poly_scene, int index) {
  float u, v, w;
  float a, au, av;
  float t, d;
  Vector3d p0, p1, p2;
  Vector3d n0, n1, n2;
  Vector3d e01, e12, e20;
  Vector3d tri_norm, vn, n;
  Vector3d x;
  Vector3d u_ray = target_vector.normalize();

  p0 = poly_scene->verts[poly_scene->faces[index].verts[0][0]];
  p1 = poly_scene->verts[poly_scene->faces[index].verts[1][0]];
  p2 = poly_scene->verts[poly_scene->faces[index].verts[2][0]];   
  
  n0 = poly_scene->verts[poly_scene->faces[index].verts[0][1]];
  n1 = poly_scene->verts[poly_scene->faces[index].verts[1][1]];
  n2 = poly_scene->verts[poly_scene->faces[index].verts[2][1]]; 
  
  e01 = p1 - p0;
  e12 = p2 - p1;
  e20 = p0 - p2; 
  
  Vector3d test01 = p1 - p0;
  Vector3d test02 = p2 - p0;

  u = v = w = 0.0;
  
  tri_norm = (test01 % test02).normalize(); // Normal of Triangle/Plane
  Vector3d test_tri_norm = (e01 % e20).normalize();

  // First, test to see if you hit the plane that the triangle is on

  n = (test01 % test02).normalize();          // normal of triangle
  if ( (n * u_ray) == 0 ) {
    // No hit... Parallel!
    return;
  }
  d = n * p0;                             // point on plane?
  t = (d - (n * origin)) / ( n * u_ray ); // Distance to hit point
  x = origin + (t * u_ray);
  
  double t1, t2, t3;
  t1 = ((p1 - p0) % ( x - p0)) * n;
  t2 = ((p2 - p1) % ( x - p1)) * n;
  t3 = ((p0 - p2) % ( x - p2)) * n;
  

  
  if ( t1 < 0.0 || t2 < 0.0 || t3 < 0.0 ) {
    // Outside of the triangle...
    return;
  }
  
  u = t2 / (((p1 - p0) % (p2 - p0)) * n );
  v = t3 / (((p1 - p0) % (p2 - p0)) * n );
  w = t1 / (((p1 - p0) % (p2 - p0)) * n );
  
  if ( t < obj_hit->hit_distance ) {
    obj_hit->hit_point = x;
    obj_hit->hit_index = index;
    obj_hit->hit_distance = t;
    obj_hit->hit_normal = n;
  }
  /* BEGIN FIRST TRY
  
  t = tri_norm * u_ray;

  //if ( obj_hit->prev_hit_index != index ) {
    if ( t != 0 ) { // hit 
      t = -1.0 * ( (tri_norm * ( origin - p0 )) / t );
      if ( t > 0) { // in front of viewscreen
        if ( t < obj_hit->hit_distance ) { // Closest object, now to test if its inside triangle
          
          x = origin + ( t * u_ray );
          vn = (p2 - p1) % (p1 - p0);
          a = vn.norm();
          n = vn/a;
          u = ((p2-p1) % (x-p1))*(n/a);
          v = ((p0-p2) % (x-p2))*(n/a);
          w = 1 - u - v;
          if( u >= 0.0 && v >= 0.0 && (u + v) <= 1.0 ) {
            //printf("Hit...\n");
            obj_hit->hit_index = index;
            obj_hit->hit_distance = t;
            obj_hit->hit_point = x;
            obj_hit->hit_normal = tri_norm;
            //obj_hit->hit_color = Color(255, 0, 0, 0);
          }
        }
      }
    }
  //} 
   END FIRST TRY */     
}

//
// Validate command line, and initialize viewport width, and output filename
//
void get_commandline(int argc, char *argv[], OBJFile &objfile){
  int suffix;
  
  if(argc < 2 || argc > 3)
    goto abort;
  
  suffix = strlen(argv[1]) - 4;
  if(strcmp(&(argv[1][suffix]), ".obj") != 0)
    goto abort;
  objfile.setfilename(argv[1]);
  return;

abort:
  cerr << "usage: objview filename.obj [nrays]" << endl;
  exit(1);
}

