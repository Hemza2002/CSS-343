// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#include "comedy.h"
#include "dvd.h"
#include <iostream>

using namespace std;

// Constructor for Comedy class
Comedy::Comedy(int stock, string director, string title, int year) {
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
string Comedy::getMovieSorting() { return name + " " + to_string(y); }

// Get the genre of the movie
string Comedy::getMovieGenre() { return "F"; }

// Get the inventory count of the movie
int Comedy::getInventoryCount() { return count; }

// Increment the inventory count of the movie
void Comedy::incrementInventory() { count++; }

// Decrement the inventory count of the movie
void Comedy::decrementInventory() { count--; }

// Get the title of the movie
string Comedy::getMovieTitle() { return name; }

// Get the director of the movie
string Comedy::getMovieDirector() { return direct; }

// Get the release year of the movie
string Comedy::getMovieYear() { return to_string(y); }
