#include "face.h"
#include <cmath>

Face::Face() 
{}

Face::Face(int i1, int i2, int i3, int i4)
{
	vertices.push_back(i1);
	vertices.push_back(i2);
	vertices.push_back(i3);
	if (i4!=-1) vertices.push_back(i4);
	

}

void Face::computeNormal(vector<Vertex> &v)
{
  int j;
  normal.x=0.0;
  normal.y=0.0;
  normal.z=0.0;
  int n = vertices.size();
  for (int i=0; i<n; i++)
  {
    j = (i+1)%n;
    normal.x += ((v[vertices[i]].coord.z+v[vertices[j]].coord.z)*
                 (v[vertices[i]].coord.y-v[vertices[j]].coord.y));
    normal.y += ((v[vertices[i]].coord.x+v[vertices[j]].coord.x)*
                 (v[vertices[i]].coord.z-v[vertices[j]].coord.z));
    normal.z += ((v[vertices[i]].coord.y+v[vertices[j]].coord.y)*
                 (v[vertices[i]].coord.x-v[vertices[j]].coord.x));
  }
  normal.x *= 0.5;
  normal.y *= 0.5;
  normal.z *= 0.5;
  //normal.normalize();
}



