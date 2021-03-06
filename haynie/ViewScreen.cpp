// Viewscreen.cpp

#include "ViewScreen.h"

ViewScreen::ViewScreen(char viewmode, int pixwidth) {
  // SET THIS DYNAMICALLY LATER
  viewpoint = Vector3d(0.0, 0.0, 0.5);
  view_pixel_width = pixwidth;
  view_pixel_height = (pixwidth * 4) / 5;
  view_meter_height = 0.4;
  view_meter_width = (view_meter_height * 5 ) / 4;
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

Vector3d ViewScreen::getViewPoint() {
  return viewpoint;
}

