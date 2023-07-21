#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "svg.h"
#include <iostream>
#include <string>

using namespace std;

class Rectangle : public SVG {

public:
  // operator<< equivalent to write the object out
  ostream &write(ostream &out) const override;

  // operator>> equivalent to read the object contents
  istream &read(istream &inn) override;

private:
  // coordinates for top-left corner of rectangle
  int x{0}, y{0};

  // width and height of rectangle
  int width{0}, height{0};

  // color of rectangle
  string color{"black"};
};

#endif
