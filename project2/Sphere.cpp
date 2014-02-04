// Sphere.cpp

#include "Sphere.h"

Sphere::Sphere(Vector3d center, Pixel_t color, double radius) 
  : SceneObj::SceneObj(SPHERE) {
  this->center = center;
  this->radius = radius;
  this->color = color;
}

void Sphere::hit(Vector3d origin, Vector3d target_vector, Object_hit_t* obj_hit) {
  Vector3d ray = origin - target_vector;
  double dx = ray[0];
  double dy = ray[1];
  double dz = ray[2];
  
  double a = ( dx * dx ) + ( dy * dy ) + ( dz * dz );
  double b = ( 2 * dx * ( origin[0] - center[0] ) ) +
             ( 2 * dy * ( origin[1] - center[1] ) ) +
             ( 2 * dz * ( origin[2] - center[2] ) );
  double c = ( center[0] * center[0] ) + ( center[1] * center[1] ) + ( center[2] * center[2] ) +
             ( origin[0] * origin[0] ) + ( origin[1] * origin[1] ) + ( origin[2] * origin[2] ) -
             ( 2 * ( center[0] * origin[0] + center[1] * origin[1] + center[2] * origin[2] ) ) -
             ( radius * radius );
  double discriminant = pow(b,2) - ( 4 * a * c );
  double t = ((0-b)-sqrt(discriminant)) / ( 2*a );
  
  if ( discriminant > 0 ) {
    // POINT INTERSECTS
    if ( t < 0 ) {
      // IS BEYOND VIEWPOINT
      if ( t > obj_hit->hit_distance ) {
        //cout << " t : " << t << " hit_distance: " << obj_hit->hit_distance << endl;
        obj_hit->hit_object = this;
        obj_hit->hit_distance = t;
        obj_hit->hit_point = ( origin + ( t * Vector3d(dx, dy, dz) ) );
        obj_hit->hit_normal = Vector3d( ((obj_hit->hit_point[0] - center[0]) / radius),
                                        ((obj_hit->hit_point[1] - center[1]) / radius),
                                        ((obj_hit->hit_point[2] - center[2]) / radius));
      }
    }
  }
}

Pixel_t Sphere::getColor() {
  return color;
}
