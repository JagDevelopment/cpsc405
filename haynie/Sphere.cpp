// Sphere.cpp

#include "Sphere.h"

Sphere::Sphere(Vector3d center, Pixel_t color, double radius) 
  : SceneObj::SceneObj(SPHERE) {
  this->center = center;
  this->radius = radius;
  this->color = color;
}

// Determine if ray hits a sphere
void Sphere::hit(Vector3d origin, Vector3d target_vector, Object_hit_t* obj_hit) {
  Vector3d u_ray = (target_vector - origin).normalize();
  double t_close = u_ray * ( this->center - origin);
  Vector3d x_close = origin + t_close * u_ray;
  double d = (x_close - this->center).norm();
  double a;
  double t;
  
  if (d < this->radius ) {
    // hit x2 --- find closest and set obj_hit to values
    a = sqrt(pow(this->radius, 2) - pow(d,2));
    t = t_close - a;
    Vector3d x_hit = origin + (t * u_ray);
    obj_hit->hit_distance = t;
    obj_hit->hit_point = x_hit;
    obj_hit->hit_object = this;
    obj_hit->hit_normal = Vector3d(0.0, 0.0, 0.0);
  } else if (d == this->radius) {
    // hit x1
    obj_hit->hit_distance = t_close;
    obj_hit->hit_point = x_close;
    obj_hit->hit_object = this;
    obj_hit->hit_normal = Vector3d(0.0, 0.0, 0.0);// DO THIS
  }  // no hit
}

Pixel_t Sphere::getColor() {
  return color;
}
