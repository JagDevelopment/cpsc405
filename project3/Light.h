// Sphere.h
// Name: Kevin Haynie
// Date: 2/4/2014
// Project: Project 3 -- Shady

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
    virtual void doLighting(Object_hit_t *hit_obj, Scene *main_scene, ViewScreen *main_view) = 0;
};

#endif
