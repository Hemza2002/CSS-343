#include "triangle.h"
#include <fstream>
#include <iostream>

using namespace std;

// operator<< equivalent to write the object out
ostream &Triangle::write(ostream &out) const {
  out << "      <polygon points=\"" << x1 << "," << y1 << " " << x2 << "," << y2 << " " << x3 << "," << y3 << "\" fill=\"" << color << "\" />" << endl;
  return out;
}

// operator>> equivalent to read the object contents
istream &Triangle::read(istream &inn) {
  inn >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> color;
  return inn;
}
