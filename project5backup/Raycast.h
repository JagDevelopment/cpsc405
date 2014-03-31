// Raycast.h

/*
Name: Kevin Haynie
Date: 2/20/2014
Project: 3 - Looking a Bit Shady!
Filename: Raycast.h
*/

#ifndef RAYCAST_H
#define RAYCAST_H

#include "Vector.h"
#include "SceneObj.h"
#include "Scene.h"
#include "ViewScreen.h"
#include "Light.h"
#include "Color.h"
#include "Face.h"
#include "File.h"
#include "Group.h"
#include "ImageFile.h"
#include "MakeSpace.h"
#include "Material.h"
#include "OBJFile.h"
#include "Pixmap.h"
#include "PolySurf.h"
#include "Utility.h"
#include "Vector.h"
#include "MTLFile.h"
#include "Line.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <Magick++.h>
#include <GL/glut.h>

// DEFAULT COMMAND LINE OPTIONS
#define DEFAULT_VIEW_MODE 'v'
#define DEFAULT_PIXEL_WIDTH 250

// DEFAULT COLOR OPTIONS
#define MAX_CHANNEL_FLOAT 1.0
#define MAX_CHANNEL_INT 255

// GEOMETRY CONSTANTS FOR READABILITY
#define SPHERE 1
#define PLANE 2

// CONTAINS INDIVIDUAL PIXEL DATA
typedef struct Pixel_t {
  float r; // Pixel Red Value
  float g; // Pixel Green Value
  float b; // Pixel Blue Value
  float a;
  
  // Default Constructor
  Pixel_t() {
    r = MAX_CHANNEL_FLOAT;
    g = MAX_CHANNEL_FLOAT;
    b = MAX_CHANNEL_FLOAT;
    a = 0.0;
  }
  Pixel_t(float r_val, float g_val, float b_val) {
    r = r_val;
    g = g_val;
    b = b_val;
    a = 0.0;
  }
  // Destructor
  ~Pixel_t() {}
} Pixel_t;

typedef struct Pixel_char_t {
  unsigned char r; // Pixel Red Value
  unsigned char g; // Pixel Green Value
  unsigned char b; // Pixel Blue Value
  unsigned char a;
} Pixel_char_t;

// GLOBALLY HOUSES IMAGE DATA FOR GLUT/OPENGL ACCESS
struct image_t {
  Pixel_char_t *pixmap;
  int w, h;
  bool exists;
  string filename;
  int fnameprovided;
};

// FORWARD DECLARATION OF SceneObj
class SceneObj;

// HOUSES ALL DATA FOR SUCCESSFUL OBJECT HITS FOR COMMUNICATION BETWEEN HIT FUNCTIONS
typedef struct Object_hit_t {
  float hit_distance;
  SceneObj* hit_object;
  SceneObj* prev_hit_object;
  Vector3d hit_point;
  Vector3d hit_normal;
  Pixel_t hit_color;
  Object_hit_t() {
    hit_object = NULL;
    prev_hit_object = NULL;
    hit_distance = INFINITY;
  }
} Object_hit_t;

typedef struct Collision {
  float hit_distance;
  int hit_index;
  int prev_hit_index;
  Vector3d hit_point;
  Vector3d hit_normal;
  Vector3d hit_uvw;
  Color hit_color;
  Collision() {
    hit_distance = INFINITY;
  }
} Collision;

// FORWARD DECLARATION OF Scene
class Scene;
class PolySurf;

// FUNCTION PROTOTYPES
void shoot(Vector3d origin, Vector3d target_vector, Collision* obj_hit, Scene* main_scene, PolySurf* poly_scene, ViewScreen* main_view, Pixel_t *obj_illum, int depth);
void hitTriangle(Vector3d origin, Vector3d target_vector, Collision* obj_hit, PolySurf* poly_scene, int index);
void handleReshape( int w, int h );
void handleKey( unsigned char key, int x, int y );
void drawImage();
void writeImage();
unsigned char floatToPixmap( float val );
void get_commandline(int argc, char *argv[], OBJFile &objfile);
void load_scene(PolySurf **scene, OBJFile &objfile);

#endif
