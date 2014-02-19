// Scene.h
// Name: Kevin Haynie
// Date: 2/4/2014
// Project: Project 2 -- Oh Shoot!

#ifndef SCENE_H
#define SCENE_H

#include "SceneObj.h"
#include "Light.h"

class SceneObj;

class Scene {
  private:

  public:
    SceneObj *headPoly;
    SceneObj *tailPoly;
    Light *headLight;
    Light *tailLight;
    Scene();
    ~Scene();
    void loadScene();
};

#endif
