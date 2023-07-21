// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#include "classic.h"
#include "dvd.h"
#include <iostream>

using namespace std;

// Constructor for Classic class
Classic::Classic(int stock, string director, string title, string actor,
                 string release) {
  if (stock >= 1) {
    count = stock;
  }
  direct = director;
  name = title;
  act = actor;
  rel = release;
}

// Get the sorting value of the movie
string Classic::getMovieSorting() { return rel; }

// Get the genre of the movie (always returns "C" for Classic)
string Classic::getMovieGenre() { return "C"; }

// Get the inventory count of the movie
int Classic::getInventoryCount() { return count; }

// Increment the inventory count of the movie
void Classic::incrementInventory() { count++; }

// Decrement the inventory count of the movie
void Classic::decrementInventory() { count--; }

// Get the title of the movie
string Classic::getMovieTitle() { return name; }

// Get the director of the movie
string Classic::getMovieDirector() { return act; }

// Get the release year of the movie
string Classic::getMovieYear() { return rel; }
