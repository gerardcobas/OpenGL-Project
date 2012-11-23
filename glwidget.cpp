#include "glwidget.h"
#include <QFileDialog>

#include <stdlib.h>
#define _USE_MATH_DEFINES 1
#include <cmath>

// Constructora amb format per defecte
GLWidget::GLWidget(QWidget * parent)
: QGLWidget (parent)
{

  // Cal activar el timer per generar animacions a l'escena
  connect( &timer, SIGNAL(timeout()), this, SLOT(updateGL()) );
  timer.start(0);
  
  xClick = yClick = 45;
  lastZoom = 60; //default angle
  
  DoingInteractive = NONE;

  llumglobal=true;
  llumdofi=false;
  carregat=false;
  dibuixa=false;
  puja=false;
  use_cam_first = 0;
  id_dofi=-1;
  

}


// initializeGL() - Aqui incloem les inicialitzacions del context grafic.
void GLWidget::initializeGL()
{
  glClearColor(0.4f, 0.4f, 0.8f, 1.0f);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnable(GL_DEPTH_TEST);
  // inicialitzem també l'escena
  scene.Init();
  scene.computeTransformedBoxes();
  // dimensions escena i camera inicial
  
  scene.CalculaEsfera(radi, centreEscena);
  cam.computeDefaultCamera(radi, centreEscena);
}


// paintGL() - callback cridat cada cop que cal refrescar la finestra. 
void GLWidget::paintGL( void ) { 

	// Esborrem els buffers
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//cerr << "painting with cam " << use_cam_first << endl;
	if(use_cam_first) {
		camFirst.setProjection(width(), height());
	
		camFirst.setModelview();
		
	} else {
		cam.setProjection(width(), height());
	
		cam.setModelview();
	}
	// dibuixar eixos aplicacio
	glBegin(GL_LINES);
	glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(20,0,0); // X
	glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,20,0); // Y
	glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,20); // Z
	glEnd();

	// pintem l'escena: terra, objectes i el que calgui
    scene.Render(id_dofi,dibuixa, llumglobal, llumdofi);
}

// resizeGL() - Cridat quan es canvia el tamany del viewport.
void GLWidget::resizeGL (int width, int height) {
	glViewport (0, 0, width, height);

}

// help() - Surt per la terminal des de la que hem 
// engegat el programa. En la versio amn interficie 
// hauria de crear una nova finestra amb la informacio...
void GLWidget::help( void ){
  cout<<"Tecles definides: \n";
  cout<<"f         Pinta en filferros\n";
  cout<<"s         Pinta amb omplert de polígons\n";
  cout<<"h,H,?     Imprimir aquesta ajuda\n";
  // Completar amb altres tecles que definiu...
  //
}

/*--------------------
*
*  teclat()
*
*  callback per quan hom prem una tecla.
*
*/
void GLWidget::keyPressEvent(QKeyEvent *e)
{
    ObjectInstance* dofi;
    dofi = scene.getObjectInstance(id_dofi);
    switch( e->key() )
    {
      case Qt::Key_F: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        updateGL();
        break;
      case Qt::Key_S: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        updateGL();
        break;
      case Qt::Key_Z:
        if(carregat) {
		 cerr << "camera changed: Using  1st person view cam" << endl;
		 use_cam_first = 1;
		 camFirst.resetOrientation();
		 camFirst.setModelview();
         scene.getObjectInstance(id_dofi)->setVisible(false);
		 updateGL();
		}
		break;
	  case Qt::Key_X:
        if(carregat) {
	  	 cerr << "camera changed: Using default cam" << endl;
		 use_cam_first = 0;
		 cam.setModelview();
         scene.getObjectInstance(id_dofi)->setVisible(true);
         updateGL();
        }
		break;
      case Qt::Key_Left:
        if(carregat) {
			cerr << "Left!" << endl;
            dofi->Rotate(scene, 3);
			if(use_cam_first) camFirst.resetOrientation();
		}
		break;
      case Qt::Key_Right:
        if(carregat) {
			cerr << "Right!" << endl;
            dofi->Rotate(scene, -3);
			if(use_cam_first) camFirst.resetOrientation();
		}
		break;
      case Qt::Key_Up:
        if(carregat && !puja) {
			cerr << "Up!" << endl;
            dofi->MoveFront(scene);

		}
        else if(carregat && puja){
            cout << "Up+Puja!" << endl;
            dofi->Puja(scene);
            if(use_cam_first) camFirst.resetCam();
        }
		break;
      case Qt::Key_Down:
        if(carregat && !puja) {
			cerr << "Down!" << endl;
            dofi->MoveBack(scene);
		}
        else if(carregat && puja){
            cout << "Up+Baixa!" << endl;
            dofi->Baixa(scene);
            if(use_cam_first) camFirst.resetCam();
        }
		break;
      case Qt::Key_Control:
        puja=true;

        break;
      case  'h'  : case  'H'  : case  '?'  :  help();
        break;
      default: e->ignore(); // el propaguem cap al pare...
    }
    
    //if(use_cam_first) {
	//	camFirst.resetOrientation();
	//}
}

void GLWidget::keyReleaseEvent(QKeyEvent *e){
    switch( e->key() )
    {
    case Qt::Key_Control:
      puja=false;

      break;
    }
}

/*--------------------
* mousePressEvent()
*/
void GLWidget::mousePressEvent( QMouseEvent *e){
  xClick = e->x();
  yClick = e->y();

  if (e->button()&Qt::LeftButton &&
      ! (e->modifiers()&(Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
  else if (e->button()&Qt::LeftButton &&  e->modifiers() &Qt::ShiftModifier)
  {
    DoingInteractive = ZOOM;
  }
}

/*--------------------
*
* mouseReleaseEvent()
*
* Callback Qt cridat quan es deixa anar el botó del
* ratolí.
*
*/
void GLWidget::mouseReleaseEvent( QMouseEvent *) {
  	DoingInteractive = NONE;
}

/*--------------------
*
* mouseMoveEvent()
*
* Callback Qt cridat quan s'arrosega el ratoli amb
* algun boto premut.
*
*/
void GLWidget::mouseMoveEvent(QMouseEvent *e) {
    // Aquí cal que es calculi i s'apliqui la rotació o el zoom
 	// com s'escaigui...
	
	if (DoingInteractive==ROTATE) {
	  // Rotar la camera

	  if(!use_cam_first) {
		 cam.userRotate((xClick - e->x()), (yClick - e->y()));
      } else if(carregat) {
		  camFirst.userRotate((xClick - e->x()), (yClick - e->y()));
	  }
	  xClick = e->x();
	  yClick = e->y();
	}


	if (DoingInteractive==ZOOM) {
	  // Fer zoom
	  cerr << "zoom! " << e->y() << endl;
	  if(!use_cam_first) {
		 cam.userZoom(lastZoom - e->y());
      } else if(carregat) {
		  camFirst.userZoom(lastZoom - e->y());
	  }
	  lastZoom = e->y();
	}
      	updateGL();

}



void GLWidget::resetCam() {	
  if(!use_cam_first) {
	cam.resetCam();
  } else if(carregat) {
	camFirst.resetCam();  
  }
	
  updateGL();
}

void GLWidget::switchCam() {	
    if(carregat){
        if(!use_cam_first) {
                 cerr << "camera changed: Using  1st person view cam" << endl;
                 use_cam_first = 1;
                 camFirst.resetOrientation();
                 camFirst.setModelview();
                 scene.getObjectInstance(id_dofi)->setVisible(false);
        } else {
                 use_cam_first = 0;
                 cam.setModelview();
                 scene.getObjectInstance(id_dofi)->setVisible(true);
        }
        updateGL();
    }
}

void GLWidget::loadModel() {	

  QString path = QFileDialog::getOpenFileName(this, "Choose a model to load", ".", "Obj (*.obj)");
  cerr << "path = " << path.toAscii().data() << endl;
  if(path==QString::null or  path.toAscii().data()=="") {
	cerr << "invalid path!" << endl;
	return;  
  }
  if(path.toAscii().contains("dolphin")){
      Model mod("dofi");
      mod.readObj(path.toAscii().data(), Scene::matlib);
      mod.updateBoundingBox();
      int id = scene.AddModel(mod);


      cout << "Added model with id " << id << endl;
/*
      Point p(centreEscena.x, 0, centreEscena.z);
      p.y+=2.5; //para que no atraviese suelo
      */

      Point p(centreEscena.x, centreEscena.y, centreEscena.z);
      id_dofi = scene.AddInstance(id, 20, p, -90);
      cameraFirst c(scene.getObjectInstance(id_dofi));
      camFirst=c;
      camFirst.computeDefaultCamera(radi, centreEscena);
      carregat=true;
      scene.computeTransformedBoxes();
  }
  else{
      Model mod("altre");
      mod.readObj(path.toAscii().data(), Scene::matlib);
      mod.updateBoundingBox();
      int id = scene.AddModel(mod);
      cerr << "Added model with id " << id << endl;

      Point p(centreEscena.x, centreEscena.y, centreEscena.z);
      cerr<<"punt inici " << p << endl;


      id_dofi = scene.AddInstance(id, 20, p, 0);
      cameraFirst c(scene.getObjectInstance(id_dofi));
      camFirst=c;
      camFirst.computeDefaultCamera(radi, centreEscena);
      carregat=true;
      cerr << "punt dofi:" << p << endl;
    }


}


