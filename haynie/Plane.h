// Plane.h
// Name: Kevin Haynie
// Date: 2/4/2014
// Project: Project 2 -- Oh Shoot!

#ifndef PLANE_H
#define PLANE_H

#include "Raycast.h"
#include "SceneObj.h"

class Plane : public SceneObj {
  private:
    Vector3d point;
    Vector3d normal;
    Pixel_t color;
  public:
    Plane(Vector3d point, Pixel_t color, Vector3d normal);
    ~Plane();
    void hit(Vector3d origin, Vector3d target_vector, Object_hit_t* obj_hit);
    Pixel_t getColor();
};

#endif
