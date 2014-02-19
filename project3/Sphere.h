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
    Vector3d diffuse;
    Vector3d specular;
    int specularExponent;
  public:
    Sphere(Vector3d center, Pixel_t *color, double radius, Vector3d diffuse, Vector3d specular, int specularExponent);
    ~Sphere();
    void hit(Vector3d origin, Vector3d target_vector, Object_hit_t* obj_hit);
    Pixel_t getColor();
    Vector3d getDiffuse();
    Vector3d getSpecular();
    int getExponent();
};

#endif
