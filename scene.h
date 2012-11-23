#ifndef _Scene_H_
#define _Scene_H_
class Scene;

#include <QtOpenGL/qgl.h>
#include "model.h"
#include "ground.h"
#include "cameraIDI.h"
#include "objectInstance.h"
#include "lights.h"


class Scene
{
	friend class XML;
 private:

	// Això és per a millorar la cerca dels objectes dins del vector.
	static int LEAVES;
	static int STEM;
	static int CASA1;
	static int CASA2;
	static int CASA3;
	static int OBELISC;
	static int FAROLA;
	
	bool load;
	
	// Tindrem un vector amb els models geomètrics dels objectes urbans
	// bàsics (o primitius) i un altre amb instàncies seves (instàncies o 
	// referències a objectes).

	void computeTransformedBox(ObjectInstance &oref);
	void transformPoint(ObjectInstance &oref, GLfloat p[4]);

 public:
	static MaterialLib matlib;	  // col·lecció de materials 
	Ground ground;
	std::vector<Model> lmodels;
	std::vector<ObjectInstance> lobjectsInstances;
	Lights lights;
    int id_model_dofi;
	Scene();

	void Init();
    void Render(int id_dofi, bool dibuixa, bool llumglobal, bool llumdofi);
	int AddModel(Model &);
	int AddObject(ObjectInstance &);
    int AddInstance(int modelid, int escala, Point& pos, float orien);
	ObjectInstance* getObjectInstance(int id);
	Model* getModel(int id);
	void computeTransformedBoxes();
	void CalculaEsfera (double &radi, Point &centreEscena);
	void updateTransformedBox(ObjectInstance& io);
	bool objectIsInGround(ObjectInstance& io);
    bool detectCollisions(ObjectInstance& oi);
    int detectCollisionsLimits(ObjectInstance& oi);
	void InitGround(double sx, double sz);

	static void transformPoint(Point &p);
};

#endif

