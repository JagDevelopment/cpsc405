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
#include "SceneObj.h"

struct Pixel_t;
struct Object_hit_t;
class Scene;
class ViewScreen;

class Light {
  private:
  public:
    Light *next;
    Light *prev;
    Light();
    ~Light();
    virtual Pixel_t getColor() = 0;
    virtual void doLighting(Object_hit_t *hit_obj, Scene *main_scene, ViewScreen *main_view, Pixel_t *obj_illum, Vector3d view_loc) = 0;
};

#endif
