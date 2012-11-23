#ifndef _CAMERAFIRST_H_
#define _CAMERAFIRST_H_

class cameraFirst;

#include <cmath>
#include "point.h"
#include "scene.h"
#include "objectInstance.h"

class cameraFirst{

  float anglecam;
  double anterior, posterior; 
  Point VRP;
  double dist; 
  float angleX, angleY, angleZ;
  float zoom;

  double altura;

 public:  
  cameraFirst();
  cameraFirst(ObjectInstance* viewer);
  void iniciTGModelat();
  void identitat();
  void fiTGModelat();
  void trasllada(float tx, float ty, float tz);
  void escala(float sx, float sy, float sz);
  void rota(float graus, float rx, float ry, float rz);
  void resetCam();
  void resetOrientation();
  void computeDefaultCamera( double radi, const Point& centreEscena); 
  void setModelview();
  void setProjection(int width, int height);
  
  void userRotate(double anglex, double angley);
  void userZoom(double zoom);

 private:
  double rad2angle(double rad);
  double angle2rad(double angle);
  double radi;
  ObjectInstance* viewer;

};



#endif
