// Scene.h

#ifndef SCENE_H
#define SCENE_H

#include "SceneObj.h"

class Scene {
  private:

  public:
    SceneObj *headPoly;
    SceneObj *tailPoly;
    Scene();
    ~Scene();
    void loadScene();
};

#endif
