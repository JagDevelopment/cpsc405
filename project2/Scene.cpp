// Scene.cpp

#include "Scene.h"
#include "SceneObj.h"
#include "Sphere.h"
#include <cstddef>

Scene::Scene() {
  headPoly = NULL;
  tailPoly = NULL;
  loadScene();
}

Scene::~Scene() {
  return;
}

void Scene::loadScene() {
  // Clean this up later to read from file and load automatically
  
  // Load Red Sphere -- Radius 0.050 -- Center (-0.3, 0.1, -0.5)
  SceneObj* redSphere = new Sphere(Vector3d(-0.3, 0.1, -0.5),    
                                   Pixel_t(255, 0, 0),           
                                   0.050 );                      
  headPoly = redSphere;
  redSphere->prev = NULL;
  
  // Load Green Sphere -- Radius 0.150 -- Center (0.0, -0.2, -0.8)
  SceneObj* greenSphere = new Sphere(Vector3d(0.0, -0.2, -0.8),  
                                     Pixel_t(0, 255, 0),           
                                     0.150 );                      
  greenSphere->prev = redSphere;
  greenSphere->prev->next = greenSphere;
  
  // Load Blue Sphere -- Radius 0.300 -- Center (0.3, 0.3, -1.1)
  SceneObj* blueSphere = new Sphere(Vector3d(0.3, 0.3, -1.1),    
                                    Pixel_t(0, 0, 255),           
                                    0.300 );                      
  blueSphere->prev = greenSphere;
  blueSphere->prev->next = blueSphere;
  
  // Load Orange Sphere -- Radius 0.300 -- Center (0.1, 0.2, -0.3)
  SceneObj* orangeSphere = new Sphere(Vector3d(0.1, 0.2, -0.3),  
                                      Pixel_t(255, 165, 0),         
                                      0.075 );                       
  orangeSphere->prev = blueSphere;
  orangeSphere->prev->next = orangeSphere;
  
  // Load Purple Sphere -- Radius 0.225 -- Center (-0.2, -0.25, -0.4)
  SceneObj* purpleSphere = new Sphere(Vector3d(-0.2, -0.25, -0.4),
                                      Pixel_t(160, 32, 240),        
                                      0.225 );                      
  purpleSphere->prev = orangeSphere;
  purpleSphere->prev->next = purpleSphere;
  purpleSphere->next = NULL;
  tailPoly = purpleSphere;
}
