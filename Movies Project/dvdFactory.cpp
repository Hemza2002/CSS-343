// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#include "dvdFactory.h"
#include <iostream>

using namespace std;

// Factory method to create a DVD object based on the provided type and
// parameters
Dvd *DvdFactory::create(const string &type, const string &stock,
                        const string &director, const string &title,
                        const string &unique) {
  if (type == "F") {
    // Create a Comedy DVD object
    return new Comedy(stoi(stock), director, title, stoi(unique));
  }

  if (type == "D") {
    // Create a Drama DVD object
    return new Drama(stoi(stock), director, title, stoi(unique));
  }

  if (type == "C") {
    // Create a Classic DVD object
    // Parse the unique parameter into tokens
    vector<string> tokens;
    stringstream check1(unique);
    string token;
    while (getline(check1, token, ' ')) {
      tokens.push_back(token);
    }
    string p1;
    string p3;
    p1 = tokens[1] + " " + tokens[0]; // Combine tokens to create actor
    p3 = tokens[2] + " " + tokens[3]; // Combine tokens to create release date
    return new Classic(stoi(stock), director, title, p1, p3);
  }

  // Invalid DVD type
  cout << "Error: DVD type \"" + type + "\" is not valid." << endl;
  return nullptr;
}
