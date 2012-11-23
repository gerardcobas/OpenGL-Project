#include "box.h"
#include <QtOpenGL/qgl.h>


Box::Box(const Point& minimum, const Point& maximum)
: minb(minimum), maxb(maximum)
{}


void Box::update(const Point& p)
{
  if (p.x < minb.x) minb.x=p.x;
  if (p.y < minb.y) minb.y=p.y;
  if (p.z < minb.z) minb.z=p.z;
  if (p.x > maxb.x) maxb.x=p.x;
  if (p.y > maxb.y) maxb.y=p.y;
  if (p.z > maxb.z) maxb.z=p.z;
}

void Box::init(const Point& p)
{
  minb = p;
  maxb = p;
  radi = (maxb-minb).length()/2.f;
  quadObj = gluNewQuadric();
}

void Box::minToCenter()
{
  float dx=(maxb.x-minb.x)/2;
  float dy=(maxb.y-minb.y)/2;
  float dz=(maxb.z-minb.z)/2;
  
  minb.x+=dx;
  maxb.x+=dx;
  
  minb.y+=dy;
  maxb.y+=dy;
  
  minb.z+=dz;
  maxb.z+=dz;
}

// per a poder fer comprovacions si es vol
void Box::Render()
{
  glLineWidth(1.0);
  Render(1.0, 1.0, 1.0);
}

void Box::RenderEsfera(){
            radi = (maxb-minb).length()/2.f;
            Point p=this->getCenter();
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glTranslatef(p.x,p.y,p.z);
            if(!quadObj) quadObj = gluNewQuadric();
            gluQuadricDrawStyle(quadObj, GLU_LINE);
            gluQuadricNormals(quadObj, GLU_SMOOTH);
            gluSphere(quadObj, radi, 15, 15);
           glPopMatrix();

}

void Box::Render(double r, double g, double b)
{
  glColor3f(r, g, b);
  glBegin(GL_LINES);
  glVertex3f(minb.x, minb.y, minb.z);
  glVertex3f(maxb.x, minb.y, minb.z);
  
  glVertex3f(maxb.x, minb.y, minb.z);
  glVertex3f(maxb.x, maxb.y, minb.z);
  
  glVertex3f(maxb.x, maxb.y, minb.z);
  glVertex3f(minb.x, maxb.y, minb.z);
  
  glVertex3f(minb.x, maxb.y, minb.z);
  glVertex3f(minb.x, minb.y, minb.z);
  
  glVertex3f(minb.x, minb.y, maxb.z);
  glVertex3f(maxb.x, minb.y, maxb.z);
  
  glVertex3f(maxb.x, minb.y, maxb.z);
  glVertex3f(maxb.x, maxb.y, maxb.z);
  
  glVertex3f(maxb.x, maxb.y, maxb.z);
  glVertex3f(minb.x, maxb.y, maxb.z);
  
  glVertex3f(minb.x, maxb.y, maxb.z);
  glVertex3f(minb.x, minb.y, maxb.z);
  
  glVertex3f(minb.x, maxb.y, minb.z);
  glVertex3f(minb.x, maxb.y, maxb.z);
  
  glVertex3f(maxb.x, maxb.y, minb.z);
  glVertex3f(maxb.x, maxb.y, maxb.z);
  
  glVertex3f(minb.x, minb.y, minb.z);
  glVertex3f(minb.x, minb.y, maxb.z);
  
  glVertex3f(maxb.x, minb.y, minb.z);
  glVertex3f(maxb.x, minb.y, maxb.z);


glEnd();
}

Point Box::getCenter() {
  float dx=(maxb.x-minb.x)/2;
  float dy=(maxb.y-minb.y)/2;
  float dz=(maxb.z-minb.z)/2;
  
  Point p(minb.x+dx, minb.y+dy, minb.z+dz);
  return p;
}

double Box:: getHorizRadius() {
	float dx=(maxb.x-minb.x)/2;
    float dy=(maxb.y-minb.y)/2;
	float dz=(maxb.z-minb.z)/2;
    return sqrt(dx*dx + dz*dz + dy*dy);
}

bool Box::hasCollisions(Box& b) {

	double ra = this->getHorizRadius();
	double rb = b.getHorizRadius();
	
	Point pa = this->getCenter();
	Point pb = b.getCenter();
	
	float dx=(pa.x-pb.x);
    float dy=(pa.y-pb.y);
	float dz=(pa.z-pb.z);
    double d = sqrt(dx*dx + dz*dz+ dy*dy);
	
	if(d < (ra+rb)) return true;
	else return false;

}
