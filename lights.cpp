#include "lights.h"
#include <cmath>

Lights::Lights()
{

}

void Lights::Init()
{
  glEnable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);

}

double angle2rado(double rad) {
    return (rad * M_PI / 180);
}


void Lights::Render(bool carregat, Point pos, bool llumglobal, bool llumdofi, float orien, float orienX)
{

    if(llumglobal){

      Point minb= Point(24,49,24);
      Point maxb= Point(26,51,26);

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

    glEnable(GL_LIGHT0);
    GLfloat light_ambient[] = { 1, 1, 1, 1.0 };
    GLfloat light_position[] = { 25.0, 50.0, 25.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    }
    else{
        glDisable(GL_LIGHT0);
    }

  if(carregat && llumdofi) {

      float diffuse[] = {0.9, 0.9, 0, 1.0};
      float specular[] = {0.9, 0.9, 0, 1.0};

      glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
      glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

      GLfloat light_position1[] = { pos.x-6*(-sin(angle2rado(orien)))*(-cos(angle2rado(orienX+90))), pos.y-6*(-cos(angle2rado(orienX))), pos.z-6*(-cos(angle2rado(orien)))*(-cos(angle2rado(orienX+90))), 1.0 };
      GLfloat light_direction1[] = {-sin(angle2rado(orien)), -cos(angle2rado(180+orienX)), -cos(angle2rado(orien)) };

      glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
      glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f);
      glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0f);

      glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_direction1);

      glEnable(GL_LIGHT1);

/* Couts de comprovació de llums:
      cout << "posdofi "<< pos;
      cout << "llumdofi "<< light_position1[0]<< " " <<  light_position1[1] << " " <<  light_position1[2]<< endl;
      cout << "direcciollumdofi "<< light_direction1[0]<< " " <<  light_direction1[1] << " " <<  light_direction1[2]<< endl;
      cout << endl;
*/

    }
  else{
      glDisable(GL_LIGHT1);
  }
}
