// Sphere.h

/*
Name: Kevin Haynie
Date: 2/20/2014
Project: 3 - Looking a Bit Shady!
Filename: Sphere.h
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "Raycast.h"
#include "SceneObj.h"

class Sphere : public SceneObj {
  private:
    Vector3d center;
    double radius;
    Pixel_t color;
    float diffuse;
    float specular;
    int specularExponent;
  public:
    Sphere(Vector3d center, Pixel_t *color, double radius, float diffuse, float specular, int specularExponent);
    ~Sphere();
    void hit(Vector3d origin, Vector3d target_vector, Object_hit_t* obj_hit);
    Pixel_t getColor();
    float getDiffuse();
    float getSpecular();
    int getExponent();
};

#endif
