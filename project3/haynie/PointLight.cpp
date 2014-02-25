// PointLight.cpp

/*
Name: Kevin Haynie
Date: 2/20/2014
Project: 3 - Looking a Bit Shady!
Filename: PointLight.cpp
*/

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

void PointLight::doLighting(Object_hit_t *hit_obj, Scene *main_scene, ViewScreen *main_view, Pixel_t *obj_illum) {
  Pixel_t light_color = this->color;
  Pixel_t obj_color = hit_obj->hit_color;
  
  int spec_exp = hit_obj->hit_object->getExponent();

  Vector3d light_ray = ( this->point - hit_obj->hit_point ).normalize();
  Vector3d hit_normal = hit_obj->hit_normal;
  Vector3d view_ray = (hit_obj->hit_point - main_view->getViewPoint()).normalize();  

  float obj_diffuse = hit_obj->hit_object->getDiffuse();
  float obj_specular = hit_obj->hit_object->getSpecular();
  float dotprod = light_ray * hit_obj->hit_normal;
   
  if ( dotprod > 0 ) {
    obj_illum->r += obj_diffuse * ( dotprod * obj_color.r ) * light_color.r;
    obj_illum->g += obj_diffuse * ( dotprod * obj_color.g ) * light_color.g;
    obj_illum->b += obj_diffuse * ( dotprod * obj_color.b ) * light_color.b;
  }
  
  Vector3d u_prime = light_ray - ( hit_normal * ( light_ray * hit_normal ) ) * 2;
  u_prime = u_prime.normalize();
  
  dotprod = u_prime * view_ray;
  
  if ( dotprod > 0 ) {
    obj_illum->r += obj_specular * pow(dotprod, spec_exp) * light_color.r;
    obj_illum->g += obj_specular * pow(dotprod, spec_exp) * light_color.g;
    obj_illum->b += obj_specular * pow(dotprod, spec_exp) * light_color.b;
  } 
}
