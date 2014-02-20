// Plane.cpp

#include "Plane.h"

Plane::Plane(Vector3d point, Pixel_t *color, Vector3d normal, float diffuse, float specular, int specularExponent) 
  : SceneObj::SceneObj(PLANE) {
  // Initialize point on plane, color, and unit vector normal to plane.
  this->point = point;
  this->normal = normal.normalize();
  this->color = *color;
  this->diffuse = diffuse;
  this->specular = specular;
  this->specularExponent = specularExponent;
}

void Plane::hit(Vector3d origin, Vector3d target_vector, Object_hit_t* obj_hit) {
  // Create ray from origin to target ViewScreen location
  Vector3d u_ray = target_vector;
  double t = this->normal * u_ray;

  if ( t != 0 ) { // hit 

    t = -1.0 * ( (this->normal * ( origin - this->point )) / t );

    if ( t > 0) { // in front of viewscreen
      if ( t < obj_hit->hit_distance ) {

        obj_hit->hit_object = this;
        obj_hit->hit_distance = t;
        obj_hit->hit_point = origin + ( t * u_ray );
        obj_hit->hit_color = this->color;
        
        // CHANGE THIS WHEN LIGHTING/DIFFUSE IS ADDED -- CALCULATE HIT NORM FOR RECURSIVE TRACING
        obj_hit->hit_normal = this->normal;
      }
    }
  }
}

Pixel_t Plane::getColor() {
  return color;
}

float Plane::getDiffuse() {
  return diffuse;
}

float Plane::getSpecular() {
  return specular;
}

int Plane::getExponent() {
  return specularExponent;
}
