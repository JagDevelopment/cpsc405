// PointLight.cpp

#include "PointLight.h"
#include "Scene.h"

PointLight::PointLight(Vector3d point, Pixel_t *color) 
  : Light::Light() {
  this->point = point;
  this->color = *color;
}

Vector3d PointLight::getPoint() {
  return this->point;
}

Pixel_t PointLight::getColor() {
  return this->color;
}

void PointLight::doLighting(Object_hit_t *hit_obj, Scene *main_scene) {
  Pixel_t c;
  Object_hit_t *test_obj = new Object_hit_t();
  Vector3d light_ray = (hit_obj->hit_point - this->point).normalize();
            // Iterate through each light, shoot ray from light to hit_location
          // For each light ray, check for intersection with all objects
          // If no intersect, calculate and multiply intensities.
          // If intersect, do nothing.
  SceneObj* blocking_obj = main_scene->headPoly;
  while (blocking_obj != NULL) {
    if( blocking_obj != hit_obj->hit_object ) {
      blocking_obj->hit( this->point, light_ray, test_obj );
    }
    blocking_obj = blocking_obj->next;
  }
  
  if ( test_obj->hit_object == NULL ) {
    Vector3d origin = this->point;
    Vector3d target = hit_obj->hit_point;
    Vector3d ray = target-origin;
    Vector3d obj_diffuse = hit_obj->hit_object->getDiffuse();
    Vector3d obj_specular = hit_obj->hit_object->getSpecular();
    Pixel_t light_color = this->color;
    float i_t;
    float i_s;
    float i_d = -(ray * hit_obj->hit_normal);
    
    
    // I_d 
  }
  
  // do stuff
}
