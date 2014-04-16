// Scene.cpp

/*
Name: Kevin Haynie
Date: 3/3/2014
Project: 4 - Ooh, shiny!
Filename: Scene.cpp
*/

#include "Scene.h"
#include "Light.h"
#include "PointLight.h"
#include "Raycast.h"
#include <cstddef>

Scene::Scene() {
  headLight = NULL;
  tailLight = NULL;
  loadScene();
}

Scene::~Scene() {
  return;
}

void Scene::loadScene() {
  return;
}

void Scene::loadPointLight( ifstream& infile ) {
  string camargs[8] = { "point", "color" };
  int flag = -1;
  int param_count = 0;
  string buffer;
  
  Vector3d point;
  Pixel_t* color = new Pixel_t();
    
  while ( param_count < 2 && infile >> buffer ) {
    flag = -1;
    for( int i = 0; i < 2; i++ ) {
      if( camargs[i] == buffer ) {
        flag = i;
      }
    }
    switch( flag ) {
      case 0: // point
        param_count++;
        infile >> point[0];
        infile >> point[1];
        infile >> point[2];
        cout << "Loaded point: " << point << endl;
        break;
      case 1: // color
        param_count++;
        infile >> (color->r);
        infile >> (color->g);
        infile >> (color->b);
        cout << "Loaded color: " << color->r << ", " << color->g << ", " << color->b << "." << endl;
        break;
      default:
        break;  
    }
  }
  
  Light *newLight = new PointLight( point, color );
  if ( headLight == NULL ) {
    headLight = newLight;
    headLight->next = NULL;
    headLight->prev = NULL;
  } else {
    Light* cursor = headLight;
    while ( cursor->next != NULL ) {
      cursor = cursor->next;
    }
    cursor->next = newLight;
    newLight->prev = cursor;
  }
}
