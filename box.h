#ifndef _BOX_H_
#define _BOX_H_

#include "point.h"
#include "math.h"
#include <GL/glu.h>


#ifdef min 
#undef min
#endif

#ifdef max 
#undef max
#endif

// Box - permet representar una capsa aliniada amb els eixos
// (ex. capsa englobant)
class Box
{
 private:
  void Render(double r, double g, double b);
 public:

  GLUquadricObj *quadObj;
  double radi;


  Box(const Point& minimum=Point(), const Point& maximum=Point());

  // update - expandeix la capsa per que inclogui el punt donat
  void update(const Point& p);
  // init - inicialitza la capsa amb el punt donat
  void init(const Point& p);
	
  // atributs
  Point minb, maxb;	// extrems mínim i m� xim de la capsa

  void Render();
  void RenderEsfera();
  void minToCenter();   // posa el mínim de la caixa on era el centre
  
  bool hasCollisions(Box& b);
  
  Point getCenter();
  double getHorizRadius();

};



#endif
