// Sphere.h
// Name: Kevin Haynie
// Date: 2/4/2014
// Project: Project 2 -- Oh Shoot!

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
    void hit(Vector3d origin, Vector3d target_vector, Object_hit_t* obj_hit);
    Pixel_t getColor();
};

#endif
