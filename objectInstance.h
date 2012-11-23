#ifndef _objectInstance_H_
#define _objectInstance_H_

class ObjectInstance;

#include <vector>
#include "point.h"
#include "model.h"
#include "box.h"
#include "cameraIDI.h"
#include "scene.h"

using namespace std;

class ObjectInstance
{
 private:
  int object;   // identificador de l'objecte
  Vector size;	   // mida en unitats
  Box _transBox;      // caixa contenidora de l'objecte transformat.
  bool visible;
  double mov;

 public:
  Point pos;    // posicio sobre el terra
  Point posCara;
  float orientation; //orientació respecte Y
  float orienX;
  ObjectInstance(int idob, Point p, Vector sz, float ori, float orien, double movi);
  ObjectInstance(void);
  ~ObjectInstance(void);

  void Render(std::vector<Model> &, bool dibuixa = false, int id_dofi=-2);
  void setVisible(bool val) { visible = val; }
  int getObjectId();
  void computeTransformedBox(Model &obj);

  Box & getTransformedBox ();
  
  
  void Rotate(Scene& sc, double angle);
  void MoveFront(Scene& sc);
  void MoveBack(Scene& sc);
  void Puja(Scene& sc);
  void Baixa(Scene& sc);
  float getOrientation();
  float getOrienX();
};

#endif
