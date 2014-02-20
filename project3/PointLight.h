// Sphere.h
// Name: Kevin Haynie
// Date: 2/4/2014
// Project: Project 2 -- Oh Shoot!

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Raycast.h"
#include "SceneObj.h"
#include "Light.h"

struct Object_hit_t;

class PointLight : public Light {
  private:
    Vector3d point;
    Pixel_t color;
  public:
    PointLight(Vector3d point, Pixel_t *color);
    ~PointLight();
    Vector3d getPoint();
    Pixel_t getColor();
    void doLighting(Object_hit_t *hit_obj, Scene *main_scene, ViewScreen *main_view);
};

#endif
