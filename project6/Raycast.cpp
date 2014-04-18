// Raycast.cpp

/*
Name: Kevin Haynie
Date: 3/3/2014
Project: 4 - Ooh, shiny!
Filename: Raycast.cpp

*/

using namespace std;
#include "Raycast.h"

image_t icontainer;

/************************************************************************
 ************************************************************************
                              RAYTRACE
 ************************************************************************
 ************************************************************************/

void raytrace( ViewScreen *main_view, Scene* main_scene, int num_rays, int viewmode, PolySurf *scene ) {
  // Pull viewscreen pixel widths/heights and meter widths/heights
  int v_pix_w = main_view->getPixelWidth();
  int v_pix_h = main_view->getPixelHeight();
  float v_met_w = main_view->getMeterWidth();
  float v_met_h = main_view->getMeterHeight();

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
  Vector3d target_vector;

  Ray target_ray;
  Color shade_color;
  Collision obj_hit;

  double rand_val = 0;    
  
  // Iterate through all rows/columns and shoot ray from camera (origin) to pixel coordinates
  for (int row = 0; row < v_pix_h; row++) {
    for (int col = 0; col < v_pix_w; col++) {
      shade_color = Color(0.0, 0.0, 0.0, 0.0); // Reset shade color
      for( int k = 0; k < num_rays; k++ ) {
        // Generate random value and offset pixel by that amount
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
          // 'l' -- parallel - orthogonal
          target_vector = Vector3d( main_view->getDir() );
          target_ray.Set(main_view->getViewPoint(), main_view->getDir());
        } else {
          // 'v' -- perspective
          target_vector = Vector3d(p_center - main_view->getViewPoint()).normalize();
          target_ray.Set(main_view->getViewPoint(), target_vector);
        }
        
        // Collide ray with objects in scene
        obj_hit = scene->RayCollide(target_ray);

        // If an object was hit, shade appropriately, otherwise shade black
        if ( obj_hit.t < INFINITY ) {
          shade_color = shade(obj_hit, target_ray, *main_scene) + shade_color;
        } else {
          shade_color = Color(0.0, 0.0, 0.0, 1.0) + shade_color;
        }
      } // for k (antialiasing k = num_rays)
      
      // Set Pixmap value to the final shaded color result
      icontainer.pixmap[(row * v_pix_w) + col].r = (floatToPixmap(shade_color[0]/num_rays));
      icontainer.pixmap[(row * v_pix_w) + col].g = (floatToPixmap(shade_color[1]/num_rays));
      icontainer.pixmap[(row * v_pix_w) + col].b = (floatToPixmap(shade_color[2]/num_rays));
      icontainer.pixmap[(row * v_pix_w) + col].a = (floatToPixmap(shade_color[3]/num_rays));      
    } // for col
  } // for row
}

/************************************************************************
 ************************************************************************
                               SHADE
 ************************************************************************
 ************************************************************************/

Color shade(Collision obj_hit, Ray target_ray, Scene lights){
  Vector3d hit_normal = obj_hit.n.normalize();
  Vector3d view_ray = (target_ray.p - obj_hit.x ).normalize(); 
  Vector3d light_point;
  Vector3d light_ray;
  Vector3d u_prime;

  Color t_ambi;
  Color t_diff;
  Color t_spec;
  Color shaded;

  Material *obj_material = obj_hit.m;

  double spec_exp = obj_material->exp;  
  double texture_alpha = obj_material->alpha;
  //cout << "Texture Alpha: " << texture_alpha << endl;
  double ux = obj_hit.uv[0];
  double vx = obj_hit.uv[1];
  
  float alpha;
  float dotprod;
  
  int illum_model = obj_material->illum_model;
  int maprow;
  int mapcol;
  
  Light *cur_light;

  Color obj_ambient = obj_material->a;
  Color obj_diffuse = obj_material->d;
  Color obj_specular = obj_material->s;

  Color total_diffuse = Color(0.0, 0.0, 0.0, 0.0);
  Color total_specular = Color(0.0, 0.0, 0.0, 0.0);
  Color total_ambient = Color(0.0, 0.0, 0.0, 0.0);

  Color mappix;
  Color light_color;

  Pixmap *amap = obj_material->amap;
  Pixmap *dmap = obj_material->dmap;
  Pixmap *smap = obj_material->smap;

  if ( amap != NULL ) {
    maprow = (int)(vx * amap->NRows());
    mapcol = (int)(ux * amap->NCols());

    alpha = ((float)amap[0][maprow][mapcol][3])/255.0;

    mappix = Color ( ((float)amap[0][maprow][mapcol][0])/255.0,
                     ((float)amap[0][maprow][mapcol][1])/255.0,
                     ((float)amap[0][maprow][mapcol][2])/255.0, 
                     1.0 );

    obj_ambient = (( 1 - alpha ) * obj_ambient + ( alpha * mappix ));
  }

  if ( dmap != NULL ) {
    maprow = (int)(vx * dmap->NRows());
    mapcol = (int)(ux * dmap->NCols());

    alpha = ((float)dmap[0][maprow][mapcol][3])/255.0;

    mappix = Color ( ((float)dmap[0][maprow][mapcol][0])/255.0,
                     ((float)dmap[0][maprow][mapcol][1])/255.0,
                     ((float)dmap[0][maprow][mapcol][2])/255.0, 
                     1.0 );

    obj_diffuse = (( 1 - alpha ) * obj_diffuse + ( alpha * mappix ));
  }

  if ( smap != NULL ) {
    maprow = (int)(vx * smap->NRows());
    mapcol = (int)(ux * smap->NCols());

    alpha = ((float)smap[0][maprow][mapcol][3])/255.0;

    mappix = Color ( ((float)smap[0][maprow][mapcol][0])/255.0,
                     ((float)smap[0][maprow][mapcol][1])/255.0,
                     ((float)smap[0][maprow][mapcol][2])/255.0, 
                     1.0 );

    obj_specular = (( 1 - alpha ) * obj_specular + ( alpha * mappix ));
  }

  if( illum_model == 0 ) 
    return obj_diffuse;

  cur_light = lights.headLight;
  while( cur_light != NULL ) {
    light_color = cur_light->getColor();
    light_point = cur_light->getPoint();
    light_ray = ( obj_hit.x - light_point ).normalize();

    dotprod = -(light_ray * hit_normal);
    
    // diffuse shading    
    if ( dotprod > 0 )
      total_diffuse = total_diffuse + ( dotprod * light_color ) * obj_diffuse;

    u_prime = ( light_ray * hit_normal ) * hit_normal;
    u_prime = ( light_ray - u_prime ) - u_prime; 
    dotprod = (u_prime * view_ray);      

    // specular shading
    if ( dotprod > 0 ) 
      total_specular = total_specular + ( pow(dotprod, spec_exp) * light_color * obj_specular );
    cur_light = cur_light->next;
  }

  total_ambient = obj_ambient * 0.2;

  if( illum_model >= 1 ) 
    shaded = shaded + total_diffuse + total_ambient;
  
  if( illum_model >= 2 ) 
    shaded = shaded + total_specular;
  
  return shaded;
} // shade

/************************************************************************
 ************************************************************************
                              HELPERS
 ************************************************************************
 ************************************************************************/

// Convert float to RGB pixmap scaled value -- ceiling = 255, floor = 0
unsigned char floatToPixmap( float val ) {
  int temp = 0;
  temp = val * 255;
  if (temp > 255.0) temp = 255.0;
  if (temp <= 0.0) temp = 0.0;
  return temp;
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


/************************************************************************
 ************************************************************************
                          OPENGL FUNCTIONS
 ************************************************************************
 ************************************************************************/


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

/************************************************************************
 ************************************************************************
                              HANDLERS
 ************************************************************************
 ************************************************************************/

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
      exit(1);
      
    default: // invalid keypress, ignore
      return;
  }
}

/************************************************************************
 ************************************************************************
                                MAIN
 ************************************************************************
 ************************************************************************/

int main( int argc, char *argv[] ) {
  int viewmode = 1;
  int depth = 8;
  unsigned int pixwidth = DEFAULT_PIXEL_WIDTH;
  OBJFile objfile;
  PolySurf *scene;        // polygonal surface data structure
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
  scene->BuildBIHTree();
  /*
  for( int k = 0; k < scene->NFaces(); k++ ) {
    scene->setFaceNormal(k);
  }
  */
  // Create Viewscreen
  ViewScreen *main_view = new ViewScreen(viewmode, pixwidth, v_point, v_dir,
                                         v_up, focal_length, aspect_ratio, meter_width);

  int v_pix_w = main_view->getPixelWidth();
  int v_pix_h = main_view->getPixelHeight();
  float v_met_w = main_view->getMeterWidth();
  float v_met_h = main_view->getMeterHeight();

  int num_rays = atoi(argv[2]);  

  // Create Pixmap
  int num_pixels = v_pix_w * v_pix_h;
  icontainer.pixmap = (Pixel_char_t *)malloc( sizeof(Pixel_char_t) * num_pixels );
  icontainer.w = v_pix_w;

  // DO THE RAYTRACING!
  raytrace( main_view, main_scene, num_rays, viewmode, scene );

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