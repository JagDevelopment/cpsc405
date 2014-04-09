// Scene.cpp

/*
Name: Kevin Haynie
Date: 3/3/2014
Project: 4 - Ooh, shiny!
Filename: Scene.cpp
*/

#include "Scene.h"
#include "SceneObj.h"
#include "Light.h"
#include "PointLight.h"
#include "ParallelLight.h"
#include "Sphere.h"
#include "Plane.h"
#include "Raycast.h"
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
  return;
}

void Scene::loadSphere( ifstream& infile ) {
  string camargs[8] = { "center", "color", "radius", "diffuse", "specular", "spec_exp" };
  int flag = -1;
  int param_count = 0;
  string buffer;
  
  Vector3d center;
  Pixel_t* color = new Pixel_t();
  float radius;
  float diffuse;
  float specular;
  int spec_exp;

  // Create SceneObjects
   
  while ( param_count < 6 && infile >> buffer ) {
    flag = -1;
    for( int i = 0; i < 6; i++ ) {
      if( camargs[i] == buffer ) {
        flag = i;
      }
    }
    switch( flag ) {
      case 0: // center
        param_count++;
        infile >> center[0];
        infile >> center[1];
        infile >> center[2];
        cout << "Loaded center: " << center << endl;
        break;
      case 1: // color
        param_count++;
        infile >> color->r;
        infile >> color->g;
        infile >> color->b;
        cout << "Loaded color: " << color->r << ", " << color->g << ", " << color->b << "." << endl;
        break;
      case 2: // radius
        param_count++;
        infile >> radius;
        cout << "Loaded radius: " << radius << endl;
        break;
      case 3: // diffuse
        param_count++;
        infile >> diffuse;
        cout << "Loaded diffuse: " << diffuse << endl;
        break;
      case 4: // specular
        param_count++;
        infile >> specular;
        cout << "Loaded specular: " << specular << endl;
        break;
      case 5: // spec_exp
        param_count++;
        infile >> spec_exp;
        cout << "Loaded specular exponent: " << spec_exp << endl;
        break;
      default:
        break;
    }
  }
  
  SceneObj *newSphere = new Sphere( center, color, radius, diffuse, specular, spec_exp );
  if ( headPoly == NULL ) {
    headPoly = newSphere;
    headPoly->next = NULL;
    headPoly->prev = NULL;
  } else {
    SceneObj* cursor = headPoly;
    while ( cursor->next != NULL ) {
      cursor = cursor->next;
    }
    cursor->next = newSphere;
    newSphere->prev = cursor;
  }
}

void loadTriangles( PolySurf scene ) {
  
}

void Scene::loadPlane( ifstream& infile ) {
  string camargs[8] = { "point", "color", "normal", "diffuse", "specular", "spec_exp" };
  int flag = -1;
  int param_count = 0;
  string buffer;
  
  Vector3d point;
  Vector3d normal;
  Pixel_t* color = new Pixel_t();
  float diffuse;
  float specular;
  int spec_exp;

  // Create SceneObjects
   
  while ( param_count < 6 && infile >> buffer ) {
    flag = -1;
    for( int i = 0; i < 6; i++ ) {
      if( camargs[i] == buffer ) {
        flag = i;
      }
    }
    switch( flag ) {
      case 0: // center
        param_count++;
        infile >> point[0];
        infile >> point[1];
        infile >> point[2];
        cout << "Loaded point: " << point << endl;
        break;
      case 1: // color
        param_count++;
        infile >> color->r;
        infile >> color->g;
        infile >> color->b;
        cout << "Loaded color: " << color->r << ", " << color->g << ", " << color->b << "." << endl;
        break;
      case 2: // normal
        param_count++;
        infile >> normal[0];
        infile >> normal[1];
        infile >> normal[2];
        cout << "Loaded plane normal: " << normal << endl;
        break;
      case 3: // diffuse
        param_count++;
        infile >> diffuse;
        cout << "Loaded diffuse: " << diffuse << endl;
        break;
      case 4: // specular
        param_count++;
        infile >> specular;
        cout << "Loaded specular: " << specular << endl;
        break;
      case 5: // spec_exp
        param_count++;
        infile >> spec_exp;
        cout << "Loaded specular exponent: " << spec_exp << endl;
        break;
      default:
        break;
    }
  }
  
  SceneObj *newPlane = new Plane( point, color, normal, diffuse, specular, spec_exp );
  if ( headPoly == NULL ) {
    headPoly = newPlane;
    headPoly->next = NULL;
    headPoly->prev = NULL;
  } else {
    SceneObj* cursor = headPoly;
    while ( cursor->next != NULL ) {
      cursor = cursor->next;
    }
    cursor->next = newPlane;
    newPlane->prev = cursor;
  }
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
