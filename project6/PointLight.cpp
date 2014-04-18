// PointLight.cpp

/*
Name: Kevin Haynie
Date: 3/3/2014
Project: 4 - Ooh, shiny!
Filename: PointLight.cpp
*/

#include "PointLight.h"
#include "Scene.h"

PointLight::PointLight(Vector3d point, Color color) 
  : Light::Light() {
  this->point = point;
  this->color = color;
}

Vector3d PointLight::getPoint() {
  return this->point;
}

Color PointLight::getColor() {
  return this->color;
}