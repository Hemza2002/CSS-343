// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#ifndef DRAMA_H
#define DRAMA_H

#include "dvd.h"
#include <iostream>

using namespace std;

class Drama : public Dvd {
public:
  // Constructor for Drama class
  Drama(int stock, string director, string title, int year);

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
  int y;         // Release year of the movie
};

#endif
