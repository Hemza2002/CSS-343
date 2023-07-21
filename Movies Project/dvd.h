// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#ifndef DVD_H
#define DVD_H

#include <iostream>

// Base class for DVD
class Dvd {
public:
  // Virtual destructor for polymorphic behavior
  virtual ~Dvd() = default;

  // Pure virtual functions to be implemented by derived classes
  virtual std::string getMovieSorting() = 0;
  virtual std::string getMovieGenre() = 0;
  virtual int getInventoryCount() = 0;
  virtual void incrementInventory() = 0;
  virtual void decrementInventory() = 0;
  virtual std::string getMovieTitle() = 0;
  virtual std::string getMovieDirector() = 0;
  virtual std::string getMovieYear() = 0;
};

#endif
