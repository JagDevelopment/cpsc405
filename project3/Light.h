// Sphere.h
// Name: Kevin Haynie
// Date: 2/4/2014
// Project: Project 3 -- Shady

#ifndef LIGHT_H
#define LIGHT_H

#include "Raycast.h"
#include "SceneObj.h"

class Light : public SceneObj {
  private:
    Pixel_t color;
  public:
    Light(Pixel_t color);
    ~Light();
    Pixel_t getColor();
};

#endif
