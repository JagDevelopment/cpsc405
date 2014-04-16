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
  icontainer.fnameprovided = 0;
  
  // Parse command line arguments: raycast [l|v] [pixwidth] [filename.ext]
  if ( argc < 3 || argc > 4 ) {
    cerr << "Invalid number of arguments provided. Syntax: objview objfile.obj [nrays]" << endl;
    exit(0);
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
        break;
      case 7: // pointlight
        cout << "Loading point light..." << endl;
        main_scene->loadPointLight( infile );
        break;
      case 8: // plane
        cout << "Loading plane..." << endl;
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
  double x_coord;
  double y_coord;
  
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

  int num_rays = atoi(argv[2]);  
  double rand_val = 0;    
  // Iterate through all rows/columns and shoot ray from camera (origin) to pixel coordinates
  for (int row = 0; row < v_pix_h; row++) {
    for (int col = 0; col < v_pix_w; col++) {
    
      Vector3d target_vector;
      
      Pixel_t *total_color = new Pixel_t();
      total_color->r = 0;
      total_color->g = 0;
      total_color->b = 0;

      for( int k = 0; k < num_rays; k++ ) {
        rand_val = 0;  
        if ( num_rays > 1 )
          rand_val = (drand48()) - 0.5;
        x_coord = (-v_met_w / 2.0 ) + ( pix_width * ( ((double)col + rand_val) + 0.5 ) );   
        rand_val = 0;
        if ( num_rays > 1 )
          rand_val = (drand48()) - 0.5;
        y_coord = (-v_met_h / 2.0 ) + ( pix_height * ( ((double)row + rand_val) + 0.5 ) );

        p_center = c_0 + ( x_coord * u_x ) + ( y_coord * u_y );
    
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
        
        if ( obj_hit->t == INFINITY ) {
          total_color->r += floatToPixmap(0);
          total_color->g += floatToPixmap(0);
          total_color->b += floatToPixmap(0);
        } else {
          //cout << "Writing color r: " << obj_illum->r << ", g: " << obj_illum->g << ", b: " << obj_illum->b << "." << endl;
          total_color->r += obj_illum->r;
          total_color->g += obj_illum->g;
          total_color->b += obj_illum->b;
          //icontainer.pixmap[(row * v_pix_w) + col].r = floatToPixmap(255);
          //icontainer.pixmap[(row * v_pix_w) + col].g = floatToPixmap(0);
          //icontainer.pixmap[(row * v_pix_w) + col].b = floatToPixmap(0);
        }
        free(obj_hit);
        free(obj_illum);

      } // for

      icontainer.pixmap[(row * v_pix_w) + col].r = (floatToPixmap(total_color->r/num_rays));
      icontainer.pixmap[(row * v_pix_w) + col].g = (floatToPixmap(total_color->g/num_rays));
      icontainer.pixmap[(row * v_pix_w) + col].b = (floatToPixmap(total_color->b/num_rays));
      
      free(total_color);
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
  Pixel_t shaded_color;

  // Reached end of recursion
  if ( depth >= 8 ) {
    return;
  }

  // Start with first object in list
  int cur_index = 0;

  // While currently targetting a valid object, call hit function on object with correct viewmode
  while( cur_index < poly_scene->NFaces() ) {    
    // Move to next target
    // TODO -- DO THE TRIANGLE HIT FUNCTION HERE
    cur_index++;
  } 
                           
  // If object hit, do reflection, lighting, and set pixel value to color values
  
  if ( obj_hit->t < INFINITY && obj_hit->t > 0.001 ) {

    Vector3d u_prime = target_vector - ( obj_hit->n * ( target_vector * obj_hit->n ) ) * 2;
    u_prime = u_prime.normalize();

    Vector3d view_loc = origin;
    
    shaded_color = shade( obj_hit, main_scene, poly_scene, main_view, obj_illum, view_loc );

    obj_illum->r = shaded_color.r;
    obj_illum->g = shaded_color.g;
    obj_illum->b = shaded_color.b;
  } else {
    obj_illum->r = 0.0; /* REMOVE THIS */
    obj_illum->g = 0.0;
    obj_illum->b = 0.0;
  }
  
  delete ref_illum;
}

/*
########################################################################
########################################################################
########################################################################
########################################################################
 */

Pixel_t shade(Collision *obj_hit, Scene *main_scene, PolySurf *poly_scene, ViewScreen *main_view, Pixel_t *obj_illum, Vector3d view_loc) {
  
  Pixel_t total_diffuse = Pixel_t(0.0, 0.0, 0.0);
  Pixel_t total_specular = Pixel_t(0.0, 0.0, 0.0);
  Pixel_t total_ambient = Pixel_t(0.0, 0.0, 0.0);
  Pixel_t shaded;

  Face *obj_face = &poly_scene->Faces()[obj_hit->objectid];
  Material *obj_material = obj_hit->m;

  double spec_exp = obj_material->exp;  
  double texture_alpha = obj_material->alpha;
  double ux = obj_hit->uv[0];
  double vx = obj_hit->uv[1];
  
  int illum_model = obj_material->illum_model;
  int istextured = 0; // TODO
  int uvtest = 0;
  int maprow;
  int mapcol;
  int p_alpha;

  Color obj_ambient = obj_material->a;
  Color obj_diffuse = obj_material->d;
  Color obj_specular = obj_material->s;

  Vector3d hit_normal = obj_hit->n.normalize();
  
  Vector3d view_ray = (view_loc - obj_hit->x ).normalize();              
 
  Pixmap *obj_amap = obj_material->amap;
  Pixmap *obj_dmap = obj_material->dmap;
  Pixmap *obj_smap = obj_material->smap;

  Light *cur_light = main_scene->headLight;
  while( cur_light != NULL ) {
    Pixel_t light_color = cur_light->getColor();

    Vector3d light_point = cur_light->getPoint();
    Vector3d light_ray = ( obj_hit->x - light_point ).normalize();
 
    Collision* test_obj = new Collision();
    int cur_index = 0;
    

  
    if ( 1 ) {
      
      float dotprod = -(light_ray * hit_normal);
      
      // diffuse shading
      
      if ( dotprod > 0 && ( illum_model == 1 || illum_model == 2)) {
        total_diffuse.r += dotprod * light_color.r;
        total_diffuse.g += dotprod * light_color.g;
        total_diffuse.b += dotprod * light_color.b;
      }
        
      //Vector3d u_prime = light_ray + 2 * ( hit_normal * ( light_ray * hit_normal ) );
      Vector3d u_prime = ( light_ray * hit_normal ) * hit_normal;

      u_prime = ( light_ray - u_prime ) - u_prime; 
      dotprod = (u_prime * view_ray);      

      // specular shading
      if ( dotprod > 0 && illum_model == 2) {
        total_specular.r += pow(dotprod, spec_exp) * light_color.r;
        total_specular.g += pow(dotprod, spec_exp) * light_color.g;
        total_specular.b += pow(dotprod, spec_exp) * light_color.b;

      } 
    }
    cur_light = cur_light -> next;
  }

  if ( istextured ) {
    maprow = (int)(vx * obj_dmap->NRows());
    mapcol = (int)(ux * obj_dmap->NCols());    
  }
  
  if ( illum_model == 0 ) {
    if ( istextured ) {
      p_alpha = obj_dmap[0][maprow][mapcol][3]/255.0;
      total_diffuse.r = (( 1 - p_alpha) * obj_diffuse[0] + ( p_alpha * ((float)obj_dmap[0][maprow][mapcol][0]/255.0) ));
      total_diffuse.g = (( 1 - p_alpha) * obj_diffuse[1] + ( p_alpha * ((float)obj_dmap[0][maprow][mapcol][1]/255.0) ));
      total_diffuse.b = (( 1 - p_alpha) * obj_diffuse[2] + ( p_alpha * ((float)obj_dmap[0][maprow][mapcol][2]/255.0) ));       
    } else {
      total_diffuse.r = obj_diffuse[0];
      total_diffuse.g = obj_diffuse[1];
      total_diffuse.b = obj_diffuse[2];    
    }
  }
  
  if ( illum_model >= 1 ) {
    if ( istextured ) {
      p_alpha = obj_dmap[0][maprow][mapcol][3]/255.0;
      total_diffuse.r = (( 1 - p_alpha) * obj_diffuse[0] + ( p_alpha * ((float)obj_dmap[0][maprow][mapcol][0]/255.0) )) * total_diffuse.r;
      total_diffuse.g = (( 1 - p_alpha) * obj_diffuse[1] + ( p_alpha * ((float)obj_dmap[0][maprow][mapcol][1]/255.0) )) * total_diffuse.g;
      total_diffuse.b = (( 1 - p_alpha) * obj_diffuse[2] + ( p_alpha * ((float)obj_dmap[0][maprow][mapcol][2]/255.0) )) * total_diffuse.b;    
      
      /* PURE MODEL */
      p_alpha = obj_amap[0][maprow][mapcol][3]/255.0;
      total_ambient.r = (( 1 - p_alpha) * obj_ambient[0] + ( p_alpha * ((float)obj_amap[0][maprow][mapcol][0]/255.0) ));
      total_ambient.g = (( 1 - p_alpha) * obj_ambient[1] + ( p_alpha * ((float)obj_amap[0][maprow][mapcol][1]/255.0) ));
      total_ambient.b = (( 1 - p_alpha) * obj_ambient[2] + ( p_alpha * ((float)obj_amap[0][maprow][mapcol][2]/255.0) ));          
      
      /* SCALED MODEL
      p_alpha = obj_amap[0][maprow][mapcol][3]/255.0;
      total_ambient.r = ((( 1 - p_alpha) * obj_ambient[0] + ( p_alpha * ((float)obj_amap[0][maprow][mapcol][0]/255.0) )) * obj_ambient[0]);
      total_ambient.g = ((( 1 - p_alpha) * obj_ambient[1] + ( p_alpha * ((float)obj_amap[0][maprow][mapcol][1]/255.0) )) * obj_ambient[1]);
      total_ambient.b = ((( 1 - p_alpha) * obj_ambient[2] + ( p_alpha * ((float)obj_amap[0][maprow][mapcol][2]/255.0) )) * obj_ambient[2]);
      */
    } else {
      total_ambient.r = obj_ambient[0];
      total_ambient.g = obj_ambient[1];
      total_ambient.b = obj_ambient[2];
    
      total_diffuse.r = obj_diffuse[0] * total_diffuse.r;
      total_diffuse.g = obj_diffuse[1] * total_diffuse.g;
      total_diffuse.b = obj_diffuse[2] * total_diffuse.b;
    }
  }
  
  if ( illum_model >= 2 ) {
    if ( istextured ) {
      
      p_alpha = obj_smap[0][maprow][mapcol][3]/255.0;
      total_specular.r = (( 1 - p_alpha) * obj_specular[0] + ( p_alpha * ((float)obj_smap[0][maprow][mapcol][0]/255.0) )) * total_specular.r;
      total_specular.g = (( 1 - p_alpha) * obj_specular[1] + ( p_alpha * ((float)obj_smap[0][maprow][mapcol][1]/255.0) )) * total_specular.g;
      total_specular.b = (( 1 - p_alpha) * obj_specular[2] + ( p_alpha * ((float)obj_smap[0][maprow][mapcol][2]/255.0) )) * total_specular.b;
      
    } else {
      total_specular.r = obj_specular[0] * total_specular.r;
      total_specular.g = obj_specular[1] * total_specular.g;
      total_specular.b = obj_specular[2] * total_specular.b;    
    }  
  }
  /*
  shaded.r = total_ambient.r + total_diffuse.r + total_specular.r;
  shaded.g = total_ambient.g + total_diffuse.g + total_specular.g;
  shaded.b = total_ambient.b + total_diffuse.b + total_specular.b;
  */
  
  shaded.r = total_ambient.r + total_diffuse.r;
  shaded.g = total_ambient.g + total_diffuse.g;
  shaded.b = total_ambient.b + total_diffuse.b;
  
  /*
  shaded.r = total_ambient.r;
  shaded.g = total_ambient.g;
  shaded.b = total_ambient.b;
  */    
  /*
  shaded.r = total_specular.r;
  shaded.g = total_specular.g;
  shaded.b = total_specular.b;

  /*
  shaded.r = total_diffuse.r;
  shaded.g = total_diffuse.g;
  shaded.b = total_diffuse.b;
  /*
  */
  
    
  
  return shaded;    
} // shade

/*
########################################################################
########################################################################
########################################################################
########################################################################
 */

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

