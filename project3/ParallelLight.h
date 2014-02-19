// Sphere.h
// Name: Kevin Haynie
// Date: 2/4/2014
// Project: Project 2 -- Oh Shoot!

#ifndef PARALLELLIGHT_H
#define PARALLELLIGHT_H

#include "Raycast.h"
#include "SceneObj.h"
#include "Light.h"

class ParallelLight : public Light {
  private:

  public:
    ParallelLight();
    ~ParallelLight();
    Pixel_t getColor();
};

#endif
