// Light.h

/*
Name: Kevin Haynie
Date: 2/20/2014
Project: 3 - Looking a Bit Shady!
Filename: Light.h
*/

#ifndef LIGHT_H
#define LIGHT_H

#include "Raycast.h"
#include "Scene.h"
#include "Collision.h"

struct Pixel_t;
class Scene;
class ViewScreen;
class PolySurf;

class Light {
  private:
  public:
    Light *next;
    Light *prev;
    Light();
    ~Light();
    virtual Pixel_t getColor() = 0;
    virtual Vector3d getPoint() = 0;
    virtual void doLighting(struct Collision *hit_obj, Scene *main_scene, PolySurf *poly_scene, ViewScreen *main_view, Pixel_t *obj_illum, Vector3d view_loc) = 0;
};

#endif
