#ifndef _GLWIDGET_H_
#define _GLWIDGET_H_

#include <QtOpenGL/qgl.h>
#include <iostream>
#include <qstring.h>
#include <qfiledialog.h>
#include <qtimer.h>
#include <QKeyEvent>

#include "material_lib.h"
#include "point.h"
#include "scene.h"
#include "cameraIDI.h"
#include "cameraFirst.h"

class GLWidget : public QGLWidget
{
  Q_OBJECT

 public:
  GLWidget(QWidget * parent);

 public slots:

  // help - Ajuda per la terminal des de la que hem  engegat el programa.
  void help(void);
	
  //SLOTS
  // Afegiu aquí la declaració dels slots que necessiteu
  void resetCam();
  void switchCam();
  
  void loadModel();
  void mostrarcapsa(bool val) { dibuixa = val; }
  void mostrarllumdofi(bool val) { llumdofi = val; }
  void mostrarllumglobal(bool val) { llumglobal = val; }
  //SIGNALS
  // Afegiu aquí la declaració dels signals que necessiteu
signals:

 protected:
  // initializeGL() - Aqui incluim les inicialitzacions del contexte grafic.
  virtual void initializeGL();

  // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
  // Tot el que es dibuixa es dibuixa aqui.
  virtual void paintGL( void );
 
  // resizeGL() - Es cridat quan canvi la mida del widget
  virtual void resizeGL (int width, int height);

  // keyPressEvent() - Cridat quan es prem una tecla
  virtual void keyPressEvent(QKeyEvent *e);
  virtual void keyReleaseEvent(QKeyEvent *e);

  // mousePressEvent() i mouseReleaseEvent()
  virtual void mousePressEvent( QMouseEvent *e);
  virtual void mouseReleaseEvent( QMouseEvent *);
 
  // mouseMoveEvent() - Cridat quan s'arrosega el ratoli amb algun botó premut.
  virtual void mouseMoveEvent(QMouseEvent *e);
 
  void computeDefaultCamera(); 
 
 private:

  // paràmetres de la camera
  int use_cam_first;
  cameraIDI cam;
  cameraFirst camFirst;
  bool dibuixa;
  bool llumglobal;
  bool llumdofi;
  // interaccio
  typedef  enum {NONE, ROTATE, ZOOM} InteractiveAction;
  InteractiveAction DoingInteractive;
  bool puja;
  int   xClick, yClick, lastZoom;
  
  Scene scene;  // Escena a representar en el widget
  
  double radi;
  Point centreEscena;
  
  int id_dofi;
  bool carregat;

  QTimer timer;
};


#endif
