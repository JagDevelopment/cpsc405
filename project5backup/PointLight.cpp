// PointLight.cpp

/*
Name: Kevin Haynie
Date: 3/3/2014
Project: 4 - Ooh, shiny!
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

void PointLight::doLighting(Collision *hit_obj, Scene *main_scene, PolySurf *poly_scene, ViewScreen *main_view, Pixel_t *obj_illum, Vector3d view_loc) {
  Pixel_t light_color = this->color;
  Color obj_color = hit_obj->hit_color;
  
  /*
  obj_illum->r = 0.2 * hit_obj->hit_color.r;
  obj_illum->g = 0.2 * hit_obj->hit_color.g;                                   
  obj_illum->b = 0.2 * hit_obj->hit_color.b;
  */
  
  // TODO -- MODIFIED -- MONITOR
  int spec_exp = poly_scene->materials[poly_scene->faces[hit_obj->hit_index].material].exp;
  int illum_model = poly_scene->materials[poly_scene->faces[hit_obj->hit_index].material].illum_model;
    
  Vector3d light_ray = ( this->point - hit_obj->hit_point ).normalize();
  Vector3d hit_normal = hit_obj->hit_normal;
  Vector3d view_ray = (hit_obj->hit_point - view_loc).normalize();  

  // Check for shadow blocking light_color
  int cur_index;
  SceneObj* cur_obj = main_scene->headPoly;
  Collision* test_obj = new Collision();
  
  while ( cur_index < poly_scene->nfaces ) {
    // TODO -- MODIFIED - MONITOR
    if( cur_index != hit_obj->hit_index ) {
      hitTriangle( this->point, (hit_obj->hit_point - this->point).normalize(), test_obj, poly_scene, cur_index );  
    }
    cur_obj = cur_obj->next;
  }
  
  if ( test_obj->hit_distance > (hit_obj->hit_point - this->point).norm() ) {
    
    // TODO -- MODIFIED - MONITOR
    Color obj_diffuse = poly_scene->materials[poly_scene->faces[hit_obj->hit_index].material].d;
    Color obj_specular = poly_scene->materials[poly_scene->faces[hit_obj->hit_index].material].s;
    
    // DEPRECATED -- REFERENCE ONLY
    //float obj_diffuse = hit_obj->hit_object->getDiffuse();
    //float obj_specular = hit_obj->hit_object->getSpecular();
    float dotprod = light_ray * hit_obj->hit_normal;
     
    if ( dotprod > 0 ) {
      // TODO -- MODIFIED -- MONITOR
      obj_illum->r += obj_diffuse[0] * ( dotprod * obj_color[0] ) * light_color.r;
      obj_illum->g += obj_diffuse[1] * ( dotprod * obj_color[1] ) * light_color.g;
      obj_illum->b += obj_diffuse[2] * ( dotprod * obj_color[2] ) * light_color.b;
    }
    
    Vector3d u_prime = light_ray - ( hit_normal * ( light_ray * hit_normal ) ) * 2;
    u_prime = u_prime.normalize();
    
    dotprod = u_prime * view_ray;
    
    if ( dotprod > 0 && illum_model == 2 ) {
      // TODO
      obj_illum->r += obj_specular[0] * pow(dotprod, spec_exp) * light_color.r;
      obj_illum->g += obj_specular[1] * pow(dotprod, spec_exp) * light_color.g;
      obj_illum->b += obj_specular[2] * pow(dotprod, spec_exp) * light_color.b;
    } 
  }
}
