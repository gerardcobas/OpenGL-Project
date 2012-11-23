#include "scene.h"
#include "XML.h"
#include <math.h>

int Scene::CASA1=0;
int Scene::CASA2=1;
int Scene::CASA3=2;
int Scene::OBELISC=3;

MaterialLib Scene::matlib;

Scene::Scene() {
	this->load=false;
}

void Scene::Init()
{
  XML xmlloader;
  xmlloader.LoadSceneDescription(this, "escena.xml");
  id_model_dofi=-1;
  lights.Init();
  
}

// Modifica un punt donat aplicant-li la transformació que es té guardada
// a la matriu MODELVIEW
void Scene::transformPoint(Point &p)
{
  GLfloat m[16];
  GLfloat p1[16];

  int i; 
  for (i=4; i<16; ++i) p1[i]=0.0f;

  p1[0] = p.x; 
  p1[1] = p.y; 
  p1[2] = p.z; 
  p1[3] = 1;

  glPushMatrix();
  glMultMatrixf(p1);
  glGetFloatv(GL_MODELVIEW_MATRIX, m);
  p.x = m[0];
  p.y = m[1];
  p.z = m[2];
  glPopMatrix();
}


// Mètode que pinta l'escena: el terra, els objectes i el que calgui
void Scene::Render(int id_dofi, bool dibuixa, bool llumglobal, bool llumdofi) {

	//pintem el terra
	ground.Render();


    if(id_dofi>=0) {

        lights.Render(true, this->lobjectsInstances[id_dofi].posCara, llumglobal, llumdofi, this->lobjectsInstances[id_dofi].orientation,
                       this->lobjectsInstances[id_dofi].orienX);
    } else lights.Render(false, Point(), llumglobal, llumdofi, 0.0, 0.0);

	// Cal pintar tots els objectes de l'escena que es troben al vector
	//recorrem tots els objects i fem per cada object un object.Render()
  	int i;
	for (i=0;i<(int)this->lobjectsInstances.size();i++) 
	  {
	    //if (i%3 == 0)
        this->lobjectsInstances[i].Render(lmodels, dibuixa, id_model_dofi);
		
	  }
}

//----------------------------------------------------------------------------------------


int Scene::AddModel(Model &o)
{
  lmodels.push_back(o);
  return lmodels.size() - 1;
}

int Scene::AddObject(ObjectInstance &oref)
{
  lobjectsInstances.push_back(oref);
  return lobjectsInstances.size() - 1;
}

int Scene::AddInstance(int modelid, int escala, Point& pos, float orien) {

  double modulGround = sqrt(ground.MidaX()*ground.MidaX() + ground.MidaZ()*ground.MidaZ()); //diagonal terra
  Model* mod;
  mod = this->getModel(modelid);
  Box b = mod->boundingBox();
  Point min = b.minb;
  Point max = b.maxb;
  double dx = (max.x-min.x);
  double dy = (max.y-min.y);
  double dz = (max.z-min.z);
  double modulModel = sqrt(dx*dx + dz*dz);
  double ratio = modulGround/escala;
  double moviment=modulGround/40;
  
  Vector v(dx*ratio/modulModel, dy*ratio/modulModel, dz*ratio/modulModel);
  pos.y=pos.y+2*ratio; //doble diagonal del dofi com es va demanar a classe
  ObjectInstance tmp(modelid, pos,v,0, orien, moviment);
  id_model_dofi=modelid;
  int iid = this->AddObject(tmp);
  return iid;
}

Model* Scene::getModel(int id) {
	if(id<lmodels.size())
		return &lmodels[id];
	else return 0;
}

ObjectInstance* Scene::getObjectInstance(int id) {
	if(id<lobjectsInstances.size())
		return &lobjectsInstances[id];
	else return 0;
}

// Calcula les caixes contenidores dels objectes de l'escena
// un cop s'han fet les transformacions de model
void Scene::computeTransformedBoxes()
{
  std::vector<ObjectInstance>::iterator ito;
  for (ito=lobjectsInstances.begin(); ito!=lobjectsInstances.end(); ito++)
  {
    (*ito).computeTransformedBox(lmodels[(*ito).getObjectId()]);
  }
}





void Scene::CalculaEsfera (double &radi, Point &centreEscena)
{
  // creem la capsa inicialment amb els vèrtexs mínim i màxim del terra
  Box capsaEscena (Point (0.0, -ground.MidaY(), 0.0),
		   Point (ground.MidaX(), 0.0, ground.MidaZ()));

  // actualitzem la capsa amb tots els objectes de l'escena
  std::vector<ObjectInstance>::iterator ito;
  for (ito=lobjectsInstances.begin(); ito!=lobjectsInstances.end(); ito++)
  {
    Point punts[8];
    punts[0] = (*ito).getTransformedBox().minb;
    punts[7] = (*ito).getTransformedBox().maxb;

    punts[1].x = punts[7].x;
    punts[1].y = punts[0].y;
    punts[1].z = punts[0].z;
    
    punts[2].x = punts[0].x;
    punts[2].y = punts[7].y;
    punts[2].z = punts[0].z;
    
    punts[3].x = punts[0].x;
    punts[3].y = punts[0].y;
    punts[3].z = punts[7].z;
    
    punts[4].x = punts[7].x;
    punts[4].y = punts[7].y;
    punts[4].z = punts[0].z;

    punts[5].x = punts[0].x;
    punts[5].y = punts[7].y;
    punts[5].z = punts[7].z;
    
    punts[6].x = punts[7].x;
    punts[6].y = punts[0].y;
    punts[6].z = punts[7].z;

    for (int i=0; i<8; ++i)
      capsaEscena.update(punts[i]);
  }
  
  centreEscena =  (capsaEscena.minb + capsaEscena.maxb)/2;
  radi = (capsaEscena.maxb-capsaEscena.minb).length()/2.f;
}


bool Scene::objectIsInGround(ObjectInstance& io) {
	Box b = io.getTransformedBox();
	double r = b.getHorizRadius();
	if(io.pos.x<0 or (io.pos.x+r)>this->ground.MidaX()) return false;
	if(io.pos.z<0 or (io.pos.z+r)>this->ground.MidaZ()) return false;
	return true;
}


void Scene::updateTransformedBox(ObjectInstance& io) {
	 int ioid = io.getObjectId();
	 io.computeTransformedBox(lmodels[ioid]);
}

bool Scene::detectCollisions(ObjectInstance& io) {
	 this->updateTransformedBox(io);
	 Box iob = io.getTransformedBox();

	 for(int i=0; i<lobjectsInstances.size(); ++i) {
		 if(&(lobjectsInstances[i]) == &(io)) continue;
		 
		 int id = lobjectsInstances[i].getObjectId();
		 lobjectsInstances[i].computeTransformedBox(lmodels[id]);
		 Box b = lobjectsInstances[i].getTransformedBox();
		 
		 if(iob.hasCollisions(b)) {
             cerr << "colisio amb " << i << endl;
			 return true;
		}
	 }
	 return false;
	
}
int Scene::detectCollisionsLimits(ObjectInstance& io){
    this->updateTransformedBox(io);
    Box iob = io.getTransformedBox();
    double d=2.5; // marge de error degut al tamany del dofi
    if(iob.getCenter().y<d){
        cerr << "colision plano minimo"<< endl;
        return 2;
    }
    if(iob.getCenter().y>30-d) {
        cerr << "colision plano maximo"<< endl;
        return 1;
    }
    if(iob.getCenter().x<d) {
        cerr << "colision groundX minimo"<< endl;
        return 3;
    }
    if(iob.getCenter().x>ground.MidaX()-d) {
        cerr << "colision groundX maximo"<< endl;
        return 3;
    }
    if(iob.getCenter().z<d) {
        cerr << "colision groundZ minimo"<< endl;
        return 3;
    }
    if(iob.getCenter().z>ground.MidaZ()-d) {
        cerr << "colision groundZ maximo"<< endl;
        return 3;
    }
    return 0;
}

//--------------------------------------------------------------------------------------------


void Scene::InitGround(double sx, double sz)
{
	ground.Init(sx,sz);
}




