// Sphere.cpp

#include "Sphere.h"

Sphere::Sphere(Vector3d center, Pixel_t color, double radius) 
  : SceneObj::SceneObj(SPHERE) {
  this->center = center;
  this->radius = radius;
  this->color = color;
}

void Sphere::hit(Object_hit_t* obj_hit) {

}
