// Triangle.h

/*
Name: Kevin Haynie
Date: 2/20/2014
Project: 3 - Looking a Bit Shady!
Filename: Triangle.h
*/

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Raycast.h"
#include "SceneObj.h"
class PolySurf;

class Triangle : public SceneObj {
  private:
    Vector3d v0;
    Vector3d v1;
    Vector3d v2;
    Pixel_t color;
    float diffuse;
    float specular;
    int specularExponent;
  public:
    Triangle();
    ~Triangle();
    void hitTriangle(Vector3d origin, Vector3d target_vector, Collision* obj_hit, PolySurf* scene, int index);
};

#endif
