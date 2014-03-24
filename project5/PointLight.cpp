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
  /*
  Pixel_t light_color = this->color;
  Pixel_t *temp_pixel = new Pixel(0.0, 0.0, 0.0);
  Face *obj_face = &poly_scene->faces[hit_obj->hit_index];
  Material *obj_material = &poly_scene->materials[obj_face->material];

  double spec_exp = obj_material->exp;  
  double text_alpha = obj_material->alpha;
  int illum_model = obj_material->illum_model;
  int tempindex, istextured = 0;
  int uvtest = 0;
  
  Color obj_ambient = obj_material->a;
  Color obj_diffuse = obj_material->d;
  Color obj_specular = obj_material->s;
  Color ambient = Color(0.3, 0.3, 0.3, 1.0);
     
  Pixmap *obj_amap = obj_material->amap;
  Pixmap *obj_dmap = obj_material->dmap;
  Pixmap *obj_smap = obj_material->smap;

  Vector3d hit_uvw = hit_obj->hit_uvw;
  Vector3d light_ray = ( this->point - hit_obj->hit_point ).normalize();
  Vector3d hit_normal = hit_obj->hit_normal;
  Vector3d view_ray = (hit_obj->hit_point - view_loc).normalize();  
  Vector3d obj_uvw = Vector3d(hit_obj->u, hit_obj->v, hit_obj->w);
  
  Vector2d uv0;
  Vector2d uv1;
  Vector2d uv2;
  
  double ux;
  double vx;
  
  if ( tempindex = poly_scene->faces[index].verts[0][2] != -1 ) {
    n0 = poly_scene->uvs[tempindex];
    uvtest++;
  }
  if ( tempindex = poly_scene->faces[index].verts[1][2] != -1 ) {
    n1 = poly_scene->uvs[tempindex];
    uvtest++;
  }
  if ( tempindex = poly_scene->faces[index].verts[2][2] != -1 ) {
    n2 = poly_scene->uvs[tempindex];
    uvtest++;
  }
  
  if( uvtest == 3 ) {
    ux = (hit_obj->u * uv0[0]) + (hit_obj->v * uv1[0]) + (hit_obj->w * uv2[0]);
    vx = (hit_obj->u * uv0[1]) + (hit_obj->v * uv1[1]) + (hit_obj->w * uv2[1]);   
    istextured = 1;
  }
  
  // Check for shadow blocking light_color
  //SceneObj* cur_obj = main_scene->headPoly;

  Collision* test_obj = new Collision();
  int cur_index = 0;
  
  while ( cur_index < poly_scene->nfaces ) {
    // TODO -- MODIFIED - MONITOR
    if( cur_index != hit_obj->hit_index ) {
      hitTriangle( this->point, (hit_obj->hit_point - this->point).normalize(), test_obj, poly_scene, cur_index );  
    }
    cur_index++;
  } 
 
  if ( test_obj->hit_distance > (hit_obj->hit_point - this->point).norm() ) {
    
    // TODO -- MODIFIED - MONITOR
    
    // DEPRECATED -- REFERENCE ONLY
    //float obj_diffuse = hit_obj->hit_object->getDiffuse();
    //float obj_specular = hit_obj->hit_object->getSpecular();
    float dotprod = light_ray * hit_obj->hit_normal;
    if ( illum_model == 0 ) {
      temp_pixel->r = obj_diffuse[0];
      temp_pixel->g = obj_diffuse[1];
      temp_pixel->b = obj_diffuse[2];
      if ( is_textured )
      delete temp_pixel;
      return;
    } else if ( illum_model == 1 ) {
      // diffuse shading
      if ( dotprod > 0 ) {
        // TODO -- MODIFIED -- MONITOR
        obj_illum->r += obj_diffuse[0] * ( dotprod * obj_color[0] ) * light_color.r;
        obj_illum->g += obj_diffuse[1] * ( dotprod * obj_color[1] ) * light_color.g;
        obj_illum->b += obj_diffuse[2] * ( dotprod * obj_color[2] ) * light_color.b;
      }
      
      Vector3d u_prime = light_ray - ( hit_normal * ( light_ray * hit_normal ) ) * 2;
      u_prime = u_prime.normalize();
      
      dotprod = u_prime * view_ray;
      
      // specular shading
      if ( dotprod > 0 ) {
        // TODO
        obj_illum->r += obj_specular[0] * pow(dotprod, spec_exp) * light_color.r;
        obj_illum->g += obj_specular[1] * pow(dotprod, spec_exp) * light_color.g;
        obj_illum->b += obj_specular[2] * pow(dotprod, spec_exp) * light_color.b;
      } 
    }
  }
  delete temp_pixel;
  */
}
