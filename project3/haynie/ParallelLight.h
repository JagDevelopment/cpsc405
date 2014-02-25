// ParallelLight.h

/*
Name: Kevin Haynie
Date: 2/20/2014
Project: 3 - Looking a Bit Shady!
Filename: ParallelLight.h
*/

#ifndef PARALLELLIGHT_H
#define PARALLELLIGHT_H

#include "Raycast.h"
#include "SceneObj.h"
#include "Light.h"

struct Object_hit_t;
struct Pixel_t;

class ParallelLight : public Light {
  private:
    Vector3d direction;
    Pixel_t color; 
  public:
    ParallelLight(Vector3d direction, Pixel_t *color);
    ~ParallelLight();
    Vector3d getDirection();
    Pixel_t getColor();
    void doLighting(Object_hit_t *hit_obj, Scene *main_scene, ViewScreen *main_view, Pixel_t *obj_illum);
};

#endif
