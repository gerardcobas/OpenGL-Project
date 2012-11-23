#include "objectInstance.h"
#include "box.h"

#include <QtOpenGL/qgl.h>

ObjectInstance::ObjectInstance(int ob, Point p, Vector sz, float ori, float orien, double movi):
    object(ob), pos(p), size(sz), orientation(ori), orienX(orien), visible(true), posCara(pos), mov(movi)
{
    if(this->orientation>=0) this->orientation = ((int)this->orientation)%360;
    _transBox.init(pos);
}

ObjectInstance::ObjectInstance() {}

ObjectInstance::~ObjectInstance(void)
{}

double angle2rad(double rad) {
	return (rad * M_PI / 180);
}


void ObjectInstance::Render(std::vector<Model> &lmodels, bool dibuixa, int id_dofi)
{
  	// Cal aplicar les transformacions de model necessàries i pintar l'objecte
    if (!visible) return; //evita que es vegi el dofi en la camara d eprimera persona
    Model &o=lmodels[object];
    Box box=o.boundingBox();
    //if(this->object==4) cerr << "Rendering instance from object " << this->object << " with orientation " << this->orientation << endl;
    //CENTRE DE LA CAIXA CONTENIDORA (BOUNDING BOX)
    Point centreBB;
    centreBB.x = (box.maxb.x+box.minb.x)/2;
    centreBB.y = (box.maxb.y+box.minb.y)/2;
    centreBB.z = (box.maxb.z+box.minb.z)/2;

    //MIDA EN COORDENADES DE LA CAIXA CONTENIDORA
    float midaX=box.maxb.x-box.minb.x;
    float midaY=box.maxb.y-box.minb.y;
    float midaZ=box.maxb.z-box.minb.z;


    if(object==id_dofi){
        posCara.x=pos.x;
        posCara.y=pos.y;
        posCara.z=pos.z;
    }
        else{

    }


    cameraIDI camAux;

    camAux.iniciTGModelat();
    camAux.trasllada(pos.x, pos.y, pos.z);
    camAux.rota(orientation, 0.0, 1.0, 0.0);
    camAux.rota(orienX, 1.0, 0.0, 0.0);

    camAux.escala(size.x/midaX, size.y/midaY, size.z/midaZ);
    camAux.trasllada(-centreBB.x, -box.minb.y, -centreBB.z);
    //Pintem l'objecte
    o.Render();

    camAux.fiTGModelat();

        if(dibuixa){
            //_transBox.Render();  // descomentar si es vol pintar la capsa englobant
            _transBox.RenderEsfera();
        }
}


int ObjectInstance::getObjectId()
{
  return object;
}

// Calculem la caixa transformada a partir de la caixa original
// de l'objecte
void ObjectInstance::computeTransformedBox(Model &obj)
{
  Box b = obj.boundingBox();
  float sa, sb, sc;
  sa=b.maxb.x-b.minb.x;	
  sb=b.maxb.y-b.minb.y;	
  sc = b.maxb.z - b.minb.z;	

  cameraIDI camAux;
  camAux.iniciTGModelat();
  camAux.identitat();

  camAux.trasllada(pos.x, pos.y, pos.z);
  camAux.rota(orientation, 0, 1, 0);
 camAux.rota(orienX, 1.0, 0.0, 0.0);
  camAux.escala(size.x/sa, size.y/sb, size.z/sc);
  camAux.trasllada(-0.5*(b.maxb.x + b.minb.x), -b.minb.y, -0.5*(b.maxb.z + b.minb.z));

  vector<Vertex> &verts = obj.vertices;
  Point punt(verts[0].coord.x, verts[0].coord.y, verts[0].coord.z);
  Scene::transformPoint(punt);
  _transBox.init(punt);

  for (unsigned int i=1; i<verts.size(); ++i)
  {
    Point punt(verts[i].coord.x, verts[i].coord.y, verts[i].coord.z);
    Scene::transformPoint(punt);
    _transBox.update(punt);
  }
  camAux.fiTGModelat();
}

Box & ObjectInstance::getTransformedBox ()
{
  return _transBox;
}

void ObjectInstance::Rotate(Scene& sc, double angle) {
	this->orientation += angle;
	if(this->orientation>=0) this->orientation = ((int)this->orientation)%360;
	else this->orientation = (360 + this->orientation);


    if(sc.detectCollisions(*this)){
        this->orientation -= angle;
    }

	sc.updateTransformedBox(*this);
}

void ObjectInstance::MoveFront(Scene& sc) {


	Point old_pos(pos.x, pos.y, pos.z);
    pos.x = pos.x - mov*sin(angle2rad(this->orientation));
    pos.y = pos.y + mov*cos(angle2rad(this->orienX));
    pos.z = pos.z - mov*cos(angle2rad(this->orientation));
	
	if(sc.detectCollisions(*this))
		pos = old_pos;
    int test=sc.detectCollisionsLimits(*this);
    if(test!=0){
         pos = old_pos;
    }

	sc.updateTransformedBox(*this);
}

void ObjectInstance::MoveBack(Scene& sc) {


	Point old_pos(pos.x, pos.y, pos.z);
    pos.x = pos.x + mov*sin(angle2rad(this->orientation));
    pos.y = pos.y - mov*cos(angle2rad(this->orienX));
    pos.z = pos.z + mov*cos(angle2rad(this->orientation));
	
	if(sc.detectCollisions(*this))
		pos = old_pos;
    int test=sc.detectCollisionsLimits(*this);
    if(test!=0){
         pos = old_pos;
    }
	sc.updateTransformedBox(*this);
}

void ObjectInstance::Puja(Scene& sc) {

    Point old_pos(pos.x, pos.y, pos.z);
    float oldOrienX = this->orienX;
    if(this->orienX<0 && this->orienX>=-180) {
        this->orienX += 3;
    }

    pos.x = pos.x - mov*sin(angle2rad(this->orientation));
    pos.y = pos.y + mov*cos(angle2rad(this->orienX));
    pos.z = pos.z - mov*cos(angle2rad(this->orientation));

    if(sc.detectCollisions(*this)){
        pos = old_pos;
        if(sc.detectCollisions(*this)){
             this->orienX=oldOrienX;
        }
    }
    int test=sc.detectCollisionsLimits(*this);
    if(test==1){
         pos = old_pos;
         this->orienX =oldOrienX;
    }
    else if(test==2){
        pos = old_pos;
    }
    else if(test==3){
        pos = old_pos;
    }

    sc.updateTransformedBox(*this);
}

void ObjectInstance::Baixa(Scene& sc) {
    Point old_pos(pos.x, pos.y, pos.z);
    float oldOrienX = this->orienX;
    if(this->orienX<=0 && this->orienX>-180){
        this->orienX -= 3;
    }
    pos.x = pos.x - mov*sin(angle2rad(this->orientation));
    pos.y = pos.y + mov*cos(angle2rad(this->orienX));
    pos.z = pos.z - mov*cos(angle2rad(this->orientation));

    if(sc.detectCollisions(*this)){
        pos = old_pos;
        if(sc.detectCollisions(*this)){
             this->orienX=oldOrienX;
        }
    }
    int test=sc.detectCollisionsLimits(*this);
    if(test==1){
         pos = old_pos;
    }
    else if(test==2){
        pos = old_pos;
        this->orienX =oldOrienX;
    }
    else if(test==3){
        pos = old_pos;
    }
    sc.updateTransformedBox(*this);
}

float ObjectInstance::getOrientation() {
	return this->orientation;
}

float ObjectInstance::getOrienX() {
    return this->orienX;
}
