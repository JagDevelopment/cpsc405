// Scene.cpp

#include "Scene.h"
#include "SceneObj.h"
#include "Light.h"
#include "PointLight.h"
#include "ParallelLight.h"
#include "Sphere.h"
#include "Plane.h"
#include <cstddef>

Scene::Scene() {
  headPoly = NULL;
  tailPoly = NULL;
  headLight = NULL;
  tailLight = NULL;
  loadScene();
}

Scene::~Scene() {
  return;
}

void Scene::loadScene() {
  // Clean this up later to read from file and load automatically
  // CREATE SCENE
  
  // Load Red Sphere -- Radius 0.050 -- Center (-0.3, 0.1, -0.5)
  SceneObj* redSphere = new Sphere(Vector3d(-0.3, 0.1, -0.5),    
                                   new Pixel_t(255.0, 0.0, 0.0),           
                                   0.050,
                                   Vector3d(1.0, 1.0, 1.0),
                                   Vector3d(0.0, 0.0, 0.0),
                                   0 );      

  headPoly = redSphere;
  redSphere->prev = NULL;
  
  // Load Green Sphere -- Radius 0.150 -- Center (0.0, -0.2, -0.8)
  SceneObj* greenSphere = new Sphere(Vector3d(0.0, -0.2, -0.8),  
                                     new Pixel_t(0.0, 255.0/255.0, 0.0),           
                                     0.150,
                                     Vector3d(0.1, 0.1, 0.1),
                                     Vector3d(1.0, 1.0, 1.0),
                                     100 );                     
  greenSphere->prev = redSphere;
  greenSphere->prev->next = greenSphere;
  
  // Load Blue Sphere -- Radius 0.300 -- Center (0.3, 0.3, -1.1)
  SceneObj* blueSphere = new Sphere(Vector3d(0.3, 0.3, -1.1),    
                                    new Pixel_t(0.0, 0.0, 255.0/255.0),           
                                    0.300,
                                    Vector3d(0.5, 0.5, 0.5),
                                    Vector3d(0.5, 0.5, 0.5),
                                    50 );                     
  blueSphere->prev = greenSphere;
  blueSphere->prev->next = blueSphere;
  
  // Load Orange Sphere -- Radius 0.300 -- Center (0.1, 0.2, -0.3)
  SceneObj* orangeSphere = new Sphere(Vector3d(0.1, 0.2, -0.3),  
                                      new Pixel_t(255.0/255.0, 165.0/255.0, 0.0),         
                                      0.075,
                                      Vector3d(0.5, 0.5, 0.5),
                                      Vector3d(0.5, 0.5, 0.5),
                                      50 );                          
  orangeSphere->prev = blueSphere;
  orangeSphere->prev->next = orangeSphere;
  
  // Load Purple Sphere -- Radius 0.225 -- Center (-0.2, -0.25, -0.4)
  SceneObj* purpleSphere = new Sphere(Vector3d(-0.2, -0.25, -0.4),
                                      new Pixel_t(.6275, 0.125, 0.955),        
                                      0.225,
                                      Vector3d(1.0, 1.0, 1.0),
                                      Vector3d(0.0, 0.0, 0.0),
                                      0 );   

  purpleSphere->prev = orangeSphere;
  purpleSphere->prev->next = purpleSphere;
                                        
  SceneObj* backPlane = new Plane(Vector3d(0.0, 0.0, -1.5),
                                  new Pixel_t(0.455, 0.455, 0.455),
                                  Vector3d(0.0, 0.0, 1.0),
                                  Vector3d(0.5, 0.5, 0.5),
                                  Vector3d(0.5, 0.5, 0.5),
                                  50 );
  backPlane->prev = purpleSphere;
  backPlane->prev->next = backPlane;   

  SceneObj* topPlane = new Plane(Vector3d(0.0, 0.70, -1.45),
                                  new Pixel_t(0.745, 0.745, 0.745),
                                  Vector3d(0.0, -0.25, 1.0),
                                  Vector3d(0.5, 0.5, 0.5),
                                  Vector3d(0.5, 0.5, 0.5),
                                  50 );
  topPlane->prev = backPlane;
  topPlane->prev->next = topPlane;                                  
                                  
  SceneObj* bottomPlane = new Plane(Vector3d(0.0, -0.45, -1.45),
                                  new Pixel_t(190.0/255.0, 190.0/255.0, 190.0/255.0),
                                  Vector3d(0.0, 0.25, 0.65), 
                                  Vector3d(0.5, 0.5, 0.5),
                                  Vector3d(0.5, 0.5, 0.5),
                                  50 );
                                  
  bottomPlane->prev = topPlane;
  bottomPlane->prev->next = bottomPlane;
                                  
  SceneObj* leftPlane = new Plane(Vector3d(-0.65, 0.0, -1.45),
                                  new Pixel_t(135.0/255.0, 135.0/255.0, 135.0/255.0),
                                  Vector3d(0.25, 0.0, 1.0),
                                  Vector3d(0.5, 0.5, 0.5),
                                  Vector3d(0.5, 0.5, 0.5),
                                  50 );
                                  
  leftPlane->prev = bottomPlane;
  leftPlane->prev->next = leftPlane;
                                  
  SceneObj* rightPlane = new Plane(Vector3d(0.65, 0.0, -1.45),
                                  new Pixel_t(135.0/255.0, 135.0/255.0, 135.0/255.0),
                                  Vector3d(-0.25, 0.0, 1.0),
                                  Vector3d(0.5, 0.5, 0.5),
                                  Vector3d(0.5, 0.5, 0.5),
                                  50 );
  rightPlane->prev = leftPlane;
  rightPlane->prev->next = rightPlane;
  rightPlane->next = NULL;
 
  tailPoly = rightPlane;
  
  // LOAD LIGHTS
  Light* pointLight = new PointLight( Vector3d( -1.0, 1.0, 0.25 ), new Pixel_t(0.4, 0.4, 0.8) );
  headLight = pointLight;
  tailLight = pointLight;
  pointLight->next = NULL;
  pointLight->prev = NULL;
  
}
