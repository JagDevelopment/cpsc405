// SceneObj.h

#ifndef SCENEOBJ_H
#define SCENEOBJ_H

#include "Raycast.h"

class SceneObj {
  private:
  protected:
    int type;
  public:
    SceneObj* next;
    SceneObj* prev;
    SceneObj(int type);
    ~SceneObj();
    virtual void hit(Object_hit_t* obj_hit) = 0;
};

#endif
