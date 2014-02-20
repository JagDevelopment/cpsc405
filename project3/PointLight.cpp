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

void PointLight::doLighting(Object_hit_t *hit_obj, Scene *main_scene, ViewScreen *main_view) {
  Pixel_t c;
  Object_hit_t *test_obj = new Object_hit_t();
  Vector3d light_ray = ( hit_obj->hit_point - this->point).normalize();
            // Iterate through each light, shoot ray from light to hit_location
          // For each light ray, check for intersection with all objects
          // If no intersect, calculate and multiply intensities.
          // If intersect, do nothing.
  /*
  SceneObj* blocking_obj = main_scene->headPoly;
  while (blocking_obj != NULL) {
    if( blocking_obj != hit_obj->hit_object ) {
      blocking_obj->hit( this->point, light_ray, test_obj);
    }
    blocking_obj = blocking_obj->next;  
  }
  */
  test_obj->hit_object = NULL;
  if ( test_obj->hit_object == NULL ) {
    
    // I = obj_Diffuse * i_d + obj_specular * i_s
    float obj_diffuse = hit_obj->hit_object->getDiffuse();
    float obj_specular = hit_obj->hit_object->getSpecular();
    int spec_exp = hit_obj->hit_object->getExponent();
    Pixel_t light_color = this->color;
    Pixel_t obj_color = hit_obj->hit_color;
    Vector3d u_prime = (light_ray - (2 * (light_ray * (-hit_obj->hit_normal))) * (-hit_obj->hit_normal)).normalize();
    Vector3d v_r = (main_view->getViewPoint() - hit_obj->hit_point).normalize();
    float i_d = -(light_ray * hit_obj->hit_normal);
    float i_s = pow((u_prime * v_r), spec_exp);
//    if( i_d > 0 ) printf("i_d: %f\n", i_d);
//    if( i_s > 0.00001 ) printf("i_s: %f\n", i_s);
//    cout << "Light Ray: " << light_ray << endl << "u_prime: " << u_prime << endl;
    
    obj_color.r = (light_color.r * i_d + light_color.r * i_s) * obj_color.r; 
    obj_color.g = (light_color.g * i_d + light_color.g * i_s) * obj_color.g;
    obj_color.b = (light_color.b * i_d + light_color.b * i_s) * obj_color.b;
    hit_obj->hit_color.r = obj_color.r;
    hit_obj->hit_color.g = obj_color.g;
    hit_obj->hit_color.b = obj_color.b;    
    
    // I_d 
  }
  
  // do stuff
}
