// raycast.h
// Name: Kevin Haynie
// Date: 2/4/2014
// Project: Project 2 -- Oh Shoot!

#ifndef RAYCAST_H
#define RAYCAST_H

#include "Vector.h"
#include "SceneObj.h"
#include "Scene.h"
#include "ViewScreen.h"

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
#define MAX_CHANNEL 255

// GEOMETRY CONSTANTS FOR READABILITY
#define SPHERE 1
#define PLANE 2

// CONTAINS INDIVIDUAL PIXEL DATA
typedef struct Pixel_t {
  unsigned char r; // Pixel Red Value
  unsigned char g; // Pixel Green Value
  unsigned char b; // Pixel Blue Value
  unsigned char a;
  
  // Default Constructor
  Pixel_t() {
    r = MAX_CHANNEL;
    g = MAX_CHANNEL;
    b = MAX_CHANNEL;
    a = 0;
  }
  Pixel_t(unsigned char r_val, unsigned char g_val, unsigned char b_val) {
    r = r_val;
    g = g_val;
    b = b_val;
    a = 0;
  }
  // Destructor
  ~Pixel_t() {}
} Pixel_t;

// GLOBALLY HOUSES IMAGE DATA FOR GLUT/OPENGL ACCESS
struct image_t {
  Pixel_t *pixmap;
  int w, h;
  bool exists;
  string filename;
  int fnameprovided;
};

// FORWARD DECLARATION OF SceneObj
class SceneObj;

// HOUSES ALL DATA FOR SUCCESSFUL OBJECT HITS FOR COMMUNICATION BETWEEN HIT FUNCTIONS
typedef struct Object_hit_t {
  double hit_distance;
  SceneObj* hit_object;
  Vector3d hit_point;
  Vector3d hit_normal;
  Object_hit_t() {
    hit_object = NULL;
    hit_distance = 9999;
  }
} Object_hit_t;

// FORWARD DECLARATION OF Scene
class Scene;

Pixel_t shoot(Vector3d origin, Vector3d target_vector, Object_hit_t* obj_hit,
              Scene* main_scene, int viewmode);
void handleReshape( int w, int h );
void handleKey( unsigned char key, int x, int y );
void drawImage();
void writeImage();

#endif
