// PointLight.h

/*
Name: Kevin Haynie
Date: 2/20/2014
Project: 3 - Looking a Bit Shady!
Filename: PointLight.h
*/

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Raycast.h"
#include "Light.h"

class PointLight : public Light {
  private:
    Vector3d point;
    Color color;
  public:
    PointLight(Vector3d point, Color color);
    ~PointLight();
    Vector3d getPoint();
    Color getColor();
};

#endif
