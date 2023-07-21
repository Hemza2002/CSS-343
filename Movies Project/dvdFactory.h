// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#ifndef DVDFACTORY_H
#define DVDFACTORY_H

#include "classic.h"
#include "comedy.h"
#include "drama.h"
#include "dvd.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class DvdFactory {
public:
  // Factory method to create a DVD object
  static Dvd *create(const string &type, const string &stock,
                     const string &director, const string &title,
                     const string &unique);
};

#endif
