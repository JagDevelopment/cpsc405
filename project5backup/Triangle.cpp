// Triangle.cpp

/*
Name: Kevin Haynie
Date: 3/3/2014
Project: 4 - Ooh, shiny!
Filename: Triangle.cpp
*/

#include "Triangle.h"

Triangle::Triangle() 
  : SceneObj::SceneObj(3) {
}

void Triangle::hitTriangle(Vector3d origin, Vector3d target_vector, Collision* obj_hit, PolySurf* scene, int index) {
  /*
  Vector3d u_ray = target_vector;
  double t = this->normal * u_ray;

  if ( obj_hit->prev_hit_object != this ) {
    if ( t != 0 ) { // hit 
      t = -1.0 * ( (this->normal * ( origin - this->point )) / t );
      if ( t > 0) { // in front of viewscreen
        if ( t < obj_hit->hit_distance ) {

          obj_hit->hit_object = this;
          obj_hit->hit_distance = t;
          obj_hit->hit_point = origin + ( t * u_ray );
          obj_hit->hit_color = this->color;
          
          obj_hit->hit_normal = this->normal;
        }
      }
    }
  } 
  */ 
}

