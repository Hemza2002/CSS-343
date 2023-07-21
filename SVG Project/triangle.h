#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "svg.h"
#include <iostream>
#include <string>

using namespace std;

class Triangle : public SVG {

public:
  // operator<< equivalent to write the object out
  ostream &write(ostream &out) const override;

  // operator>> equivalent to read the object contents
  istream &read(istream &inn) override;

private:
  // coordinates for vertices of triangle
  int x1{0}, y1{0}, x2{0}, y2{0}, x3{0}, y3{0};

  // color of triangle
  string color{"black"};
};

#endif
