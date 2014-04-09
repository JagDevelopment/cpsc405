// PointLight.h

/*
Name: Kevin Haynie
Date: 2/20/2014
Project: 3 - Looking a Bit Shady!
Filename: PointLight.h
*/

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
    void doLighting(Collision *hit_obj, Scene *main_scene, PolySurf *poly_scene, ViewScreen *main_view, Pixel_t *obj_illum, Vector3d view_loc);
};

#endif
