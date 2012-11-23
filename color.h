#ifndef _COLOR_H_
#define _COLOR_H_

#include <iostream>
using namespace std;

class Color
{
 public:
  Color(float red=0., float green=0., float blue=0., float alfa=1.);

  // atributs
  float r,g,b,a ;	// components RGB del color
};

ostream& operator<< (ostream &os, const Color &c);

#endif
