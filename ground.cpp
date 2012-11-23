#include "ground.h"
#include <QtOpenGL/qgl.h>

Ground::Ground()
{
  midaX = 30;
  midaY = 0.5; 
  midaZ = 30;
}

void Ground::Init(double sx, double sz)
{
  midaX = sx; 
  midaZ = sz;
}

void Ground::Render()
{
  //glColor3f(0.1, 0.1, 0.4);

  GLfloat rgba[] = { 0.1, 0.1, 0.4, 0.0 };
  glMaterialfv(GL_FRONT,  GL_AMBIENT_AND_DIFFUSE,  rgba);
  glNormal3f(0, 1, 0);

  glBegin(GL_QUADS);
		
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, midaZ);
  glVertex3f(midaX, 0, midaZ);
  glVertex3f(midaX, 0, 0);
  
  glVertex3f(0, -midaY, 0);
  glVertex3f(0, -midaY, midaZ);
  glVertex3f(midaX, -midaY, midaZ);
  glVertex3f(midaX, -midaY, 0);
  
  glVertex3f(0, 0, 0);
  glVertex3f(0, -midaY, 0);
  glVertex3f(0, -midaY, midaZ);
  glVertex3f(0, 0, midaZ);
  
  glVertex3f(midaX, 0, 0);
  glVertex3f(midaX, -midaY, 0);
  glVertex3f(midaX, -midaY, midaZ);
  glVertex3f(midaX, 0, midaZ);
  
  glVertex3f(0, 0, 0);
  glVertex3f(midaX, 0, 0);
  glVertex3f(midaX, -midaY, 0);
  glVertex3f(0, -midaY, 0);

  glVertex3f(0, 0, midaZ);
  glVertex3f(midaX, 0, midaZ);
  glVertex3f(midaX, -midaY, midaZ);
  glVertex3f(0, -midaY, midaZ);
  
  glEnd();
}

double Ground::MidaX () { return midaX; }

double Ground::MidaY () { return midaY; }

double Ground::MidaZ () { return midaZ; }
