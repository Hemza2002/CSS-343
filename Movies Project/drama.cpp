// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#include "drama.h"
#include "dvd.h"
#include <iostream>

using namespace std;

// Constructor for Drama class
Drama::Drama(int stock, string director, string title, int year) {
  if (stock >= 1) {
    count = stock;
  }
  direct = director;
  name = title;
  if (year >= 1) {
    y = year;
  }
}

// Get the sorting value of the movie
string Drama::getMovieSorting() { return direct + " " + name; }

// Get the genre of the movie (always returns "D" for Drama)
string Drama::getMovieGenre() { return "D"; }

// Get the inventory count of the movie
int Drama::getInventoryCount() { return count; }

// Increment the inventory count of the movie
void Drama::incrementInventory() { count++; }

// Decrement the inventory count of the movie
void Drama::decrementInventory() { count--; }

// Get the title of the movie
string Drama::getMovieTitle() { return name; }

// Get the director of the movie
string Drama::getMovieDirector() { return direct; }

// Get the release year of the movie
string Drama::getMovieYear() { return to_string(y); }
