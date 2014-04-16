// Scene.h

/*
Name: Kevin Haynie
Date: 2/20/2014
Project: 3 - Looking a Bit Shady!
Filename: Scene.h
*/

#ifndef SCENE_H
#define SCENE_H

#include "Light.h"

class SceneObj;

class Scene {
  private:

  public:
    Light *headLight;
    Light *tailLight;
    Scene();
    ~Scene();
    void loadScene();
    void loadSphere( ifstream& infile );
    void loadPlane( ifstream& infile );
    void loadPointLight( ifstream& infile );
};

#endif
