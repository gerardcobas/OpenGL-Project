#ifndef _CAMERAIDI_H_
#define _CAMERAIDI_H_

class cameraIDI;

#include <cmath>
#include "point.h"
#include "scene.h"


class cameraIDI{

  float anglecam;
  double anterior, posterior; 
  Point VRP;
  double dist; 
  float angleX, angleY, angleZ;
  float zoom;


 public:  

  void iniciTGModelat();
  void identitat();
  void fiTGModelat();
  void trasllada(float tx, float ty, float tz);
  void escala(float sx, float sy, float sz);
  void rota(float graus, float rx, float ry, float rz);
  void resetCam();
  void computeDefaultCamera( double radi, const Point& centreEscena); 
  void setModelview();
  void setProjection(int width, int height);
  
  void userRotate(double anglex, double angley);
  void userZoom(double zoom);

 private:
  float rad2angle(float angle);
  double radi;

};



#endif
