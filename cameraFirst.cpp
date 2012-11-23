#include "cameraFirst.h"
#include <QtOpenGL/qgl.h>
#include <GL/glu.h>


cameraFirst::cameraFirst() { }
cameraFirst::cameraFirst(ObjectInstance* viewer) : viewer(viewer) { }

void cameraFirst::computeDefaultCamera(double radi, const Point& centreEscena) 
{

  //VRP = Point(viewer->pos.x, 0, viewer->pos.z);
  //this->radi = radi;
  //dist = 2*radi;  
  
  //TODO: BEFORE THIS, HAVE TO LOOK AND CLEAN
  
  anterior = 2.;
  posterior = 2*radi+5;
  zoom=0;
  anglecam=90;

  Box b = viewer -> getTransformedBox();
  altura = (b.maxb.y);
  if(altura < 0) altura *= -1;

  angleY=0;
  angleX=0;
  
}

void cameraFirst::setModelview() 
{
  glMatrixMode(GL_MODELVIEW); //Modifiquem matriu ModelView (Camera)      
  glLoadIdentity(); //Coloquem camera a l'origent (punt per defecte)
  
        
  int n = 4;


  float orien = viewer->getOrientation();
  float orienX = viewer->getOrienX();

//VRP en la posicio mitja del dofi
  VRP.x=viewer->pos.x-n*(-sin(angle2rad(orien)))*(-cos(angle2rad(orienX+90)));
  VRP.y=viewer->pos.y-n*(-cos(angle2rad(orienX)));
  VRP.z=viewer->pos.z-n*(-cos(angle2rad(orien)))*(-cos(angle2rad(orienX+90)));

//lookat amb la direccio de visio del dofi
  double lookAtX = viewer->pos.x-(n+1)*sin(angle2rad(orien+angleX));
  double lookAtY = viewer->pos.y-(n+1)*cos(angle2rad(180+orienX+angleY));
  double lookAtZ = viewer->pos.z-(n+1)*cos(angle2rad(orien+angleX));

  gluLookAt(VRP.x, VRP.y, VRP.z,
            lookAtX, lookAtY, lookAtZ,
            0, 1, 0); // UP vector
}


void cameraFirst::setProjection(int width, int height) 
{
  float aspect=float(width)/float(height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(anglecam,aspect,anterior,posterior);

}


void cameraFirst::resetOrientation() {
    angleX=0;
}

void cameraFirst::resetCam() 
{
  angleY=viewer->orienX+90;
  this->resetOrientation();
  anglecam = 90;
}


void cameraFirst::userRotate(double anglex, double angley) {
	//distancia en x = rotacio sobre l'eix y, i a l'inreves
	angleY = angleY + angley;
	angleX = angleX + anglex;
	this->setModelview();
}

void cameraFirst::userZoom(double zoom) {
	anglecam = anglecam + zoom;
	if(anglecam<1) anglecam = 1;
    if(anglecam>100) anglecam = 100;
	this->setModelview();
}



void cameraFirst::iniciTGModelat()
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
}

void cameraFirst::identitat()
{
  glLoadIdentity();
}

void cameraFirst::fiTGModelat()
{
  glPopMatrix();
}

void cameraFirst::trasllada(float tx, float ty, float tz)
{
  glTranslatef(tx, ty, tz);
}

void cameraFirst::escala(float sx, float sy, float sz)
{
  glScalef(sx, sy, sz);
}

void cameraFirst::rota(float graus, float rx, float ry, float rz)
{
  glRotatef(graus, rx, ry, rz);
}


double cameraFirst::rad2angle(double rad) {
	return (rad * 180 / M_PI);
}

double cameraFirst::angle2rad(double angle) {
	return (angle * M_PI / 180);
}
