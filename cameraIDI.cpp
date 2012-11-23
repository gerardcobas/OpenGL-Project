#include "cameraIDI.h"
#include <QtOpenGL/qgl.h>
#include <GL/glu.h>

void cameraIDI::computeDefaultCamera(double radi, const Point& centreEscena) 
{

  VRP = Point(centreEscena.x, centreEscena.y, centreEscena.z);
  this->radi = radi;
  dist = 2*radi;

  anterior = 3.;
  posterior = 150.;
  //2*... perque agafem les 2 bandes
  anglecam =  2* rad2angle(asin(this->radi/dist));

  // inicialitzem els angles per a veure-ho des d'un cert punt de vista   
  angleX = 45;
  angleY = 45;
  angleZ = 0;

  zoom=0;
}


void cameraIDI::setModelview() 
{
  glMatrixMode(GL_MODELVIEW); //Modifiquem matriu ModelView (Camera)      
  glLoadIdentity(); //Coloquem camera a l'origent (punt per defecte)      

  //gluLookAt(2*radi, 2*radi, 2*radi, centreEscena.x, centreEscena.y, centreEscena.z, 0, 1, 0);
  trasllada(0.,0.,-dist);
  rota (angleZ,0.,0.,1.);
  rota (angleX, 1.,0.,0.);
  rota (-angleY,0.,1.,0.);
  trasllada (-VRP.x, -VRP.y, -VRP.z);
}


void cameraIDI::setProjection(int width, int height) 
{
  float aspect=float(width)/float(height); //relació d'aspecte = amplada / alçada   

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(anglecam,aspect,anterior,posterior);

}


void cameraIDI::resetCam() 
{
  angleX = 45;
  angleY = 45;
  angleZ = 0;
  anglecam = 2 * rad2angle(asin(this->radi/dist));
}


void cameraIDI::userRotate(double anglex, double angley) {
	//distancia en x = rotacio sobre l'eix y, i a l'inreves
	angleX = angleX + angley;
	angleY = angleY + anglex;
	this->setModelview();
}

void cameraIDI::userZoom(double zoom) {
	anglecam = anglecam + zoom;
	if(anglecam<1) anglecam = 1;
    if(anglecam>100) anglecam = 100;
	this->setModelview();
}



void cameraIDI::iniciTGModelat()
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
}

void cameraIDI::identitat()
{
  glLoadIdentity();
}

void cameraIDI::fiTGModelat()
{
  glPopMatrix();
}

void cameraIDI::trasllada(float tx, float ty, float tz)
{
  glTranslatef(tx, ty, tz);
}

void cameraIDI::escala(float sx, float sy, float sz)
{
  glScalef(sx, sy, sz);
}

void cameraIDI::rota(float graus, float rx, float ry, float rz)
{
  glRotatef(graus, rx, ry, rz);
}


float cameraIDI::rad2angle(float angle) {
	return (angle * 180 / M_PI);
}
