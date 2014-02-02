// raycast.h

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

typedef struct Pixel_t {
  unsigned char r; // Pixel Red Value
  unsigned char g; // Pixel Green Value
  unsigned char b; // Pixel Blue Value
  
  // Default Constructor
  Pixel_t() {
    r = MAX_CHANNEL;
    g = MAX_CHANNEL;
    b = MAX_CHANNEL;
  }
  Pixel_t(unsigned char r_val, unsigned char g_val, unsigned char b_val) {
    r = r_val;
    g = g_val;
    b = b_val;
  }
  // Destructor
  ~Pixel_t() {}
} Pixel_t;

typedef struct Object_hit_t {
  double hit_distance;
  SceneObj* hit_object;
  Vector3d hit_point;
  Vector3d hit_normal;
  Object_hit_t() {
    hit_object = NULL;
    hit_distance = -1;
  }
} Object_hit_t;

Pixel_t shoot(Vector3d origin, Vector3d target_vector, Object_hit_t* obj_hit, Scene* main_scene);
void handleReshape( int w, int h );
void handleKey( unsigned char key, int x, int y );
void drawImage();
void writeImage();

#endif
