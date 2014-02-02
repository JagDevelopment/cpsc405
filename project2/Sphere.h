// Sphere.h

#ifndef SPHERE_H
#define SPHERE_H

#include "Raycast.h"
#include "SceneObj.h"

class Sphere : public SceneObj {
  private:
    Vector3d center;
    double radius;
    Pixel_t color;
  public:
    Sphere(Vector3d center, Pixel_t color, double radius);
    ~Sphere();
    void hit(Object_hit_t* obj_hit);
};

#endif
