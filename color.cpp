#include "color.h"

Color::Color(float red, float green, float blue, float alfa) 
: r(red), g(green), b(blue), a(alfa) 
{}

ostream& operator<< (ostream &os, const Color &c) 
{
  os << c.r << ", " << c.g << ", " << c.b << ", " << c.a << endl;
  return os;
}

