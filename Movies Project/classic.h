// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#ifndef CLASSIC_H
#define CLASSIC_H

#include "dvd.h"
#include <iostream>

using namespace std;

class Classic : public Dvd {
public:
  // Constructor for Classic class
  Classic(int stock, string director, string title, string actor,
          string release);

  // Override functions from the base class
  string getMovieSorting() override;
  string getMovieGenre() override;
  int getInventoryCount() override;
  void incrementInventory() override;
  void decrementInventory() override;
  string getMovieTitle() override;
  string getMovieDirector() override;
  string getMovieYear() override;

private:
  int count;     // Inventory count of the movie
  string direct; // Director of the movie
  string name;   // Title of the movie
  string act;    // Actor of the movie
  string rel;    // Release year of the movie
};

#endif
