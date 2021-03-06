// SceneObj.h
// Name: Kevin Haynie
// Date: 2/4/2014
// Project: Project 2 -- Oh Shoot!

#ifndef SCENEOBJ_H
#define SCENEOBJ_H

#include "Raycast.h"

struct Object_hit_t;
struct Pixel_t;

class SceneObj {
  private:
  protected:
    int type;
  public:
    SceneObj* next;
    SceneObj* prev;
    SceneObj(int type);
    ~SceneObj();
    virtual void hit(Vector3d origin, Vector3d target_vector, Object_hit_t* obj_hit) = 0;
    virtual Pixel_t getColor() = 0;
};

#endif
