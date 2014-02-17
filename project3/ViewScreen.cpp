// Viewscreen.cpp

#include "ViewScreen.h"

ViewScreen::ViewScreen(char viewmode, int pixwidth, Vector3d v_point, Vector3d v_dir, Vector3d v_up, double focal_length, double aspect_ratio, double meter_width) {
  // SET THIS DYNAMICALLY LATER
  this->viewmode = viewmode;
  viewpoint = v_point;
  this->v_dir = v_dir;
  this->v_up = v_up;
  this->focal_length = focal_length;
  this->aspect_ratio = aspect_ratio;
  view_meter_width = meter_width;  
  view_pixel_width = pixwidth;
  view_pixel_height = (pixwidth * (1/aspect_ratio));
  view_meter_height = (view_meter_width * (1/aspect_ratio));

}

int ViewScreen::getPixelWidth() {
  return view_pixel_width;
}

int ViewScreen::getPixelHeight() {
  return view_pixel_height;
}

double ViewScreen::getMeterWidth() { 
  return view_meter_width;
}

double ViewScreen::getMeterHeight() {
  return view_meter_height;
}

double ViewScreen::getFocal() {
  return focal_length;
}

Vector3d ViewScreen::getViewPoint() {
  return viewpoint;
}

Vector3d ViewScreen::getUp() {
  return v_up;
}

Vector3d ViewScreen::getDir() {
  return v_dir;
}

