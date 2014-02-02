// Viewscreen.h

#ifndef VIEWSCREEN_H
#define VIEWSCREEN_H

#include "Vector.h"

class ViewScreen {
  private:
    Vector3d viewpoint;
    int view_pixel_width;
    int view_pixel_height;
    double view_meter_width;
    double view_meter_height;
  public:
    ViewScreen(char viewmode, int pixwidth);
    ~ViewScreen();
    Vector3d getViewPoint();
    int getPixelWidth();
    int getPixelHeight();
    double getMeterWidth();
    double getMeterHeight();
};

#endif
