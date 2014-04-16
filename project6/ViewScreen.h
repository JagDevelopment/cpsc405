// ViewScreen.h

/*
Name: Kevin Haynie
Date: 2/20/2014
Project: 3 - Looking a Bit Shady!
Filename: ViewScreen.h
*/

#ifndef VIEWSCREEN_H
#define VIEWSCREEN_H

#include "Vector.h"

class ViewScreen {
  private:
    Vector3d viewpoint;
    Vector3d v_up;
    Vector3d v_dir;
    double focal_length;
    double aspect_ratio;
    int view_pixel_width;
    int view_pixel_height;
    double view_meter_width;
    double view_meter_height;
    char viewmode;
  public:
    ViewScreen(char viewmode, int pixwidth, Vector3d v_point, Vector3d v_dir, Vector3d v_up, double focal_length, double aspect_ratio, double meter_widths);
    ~ViewScreen();
    Vector3d getViewPoint();
    Vector3d getUp();
    Vector3d getDir();
    double getFocal();
    int getPixelWidth();
    int getPixelHeight();
    double getMeterWidth();
    double getMeterHeight();
};

#endif
