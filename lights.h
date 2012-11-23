#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include <QtOpenGL/qgl.h>
#include "point.h"



class Lights
{

 public:
 
  Lights();
  void Init();
  void Render(bool carregat, Point pos, bool llumglobal = false, bool llumdofi= false, float orien=0.0, float orienX=0.0);
};

#endif
