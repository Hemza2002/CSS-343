#include "autocomplete.h"
#include "bstmap.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

void testBSTAll();
void testACAll();
//void testReadCities();

void testMain() {
  testBSTAll();
  testACAll();
  //testReadCities();
}

// void testReadCities() {
//   ifstream ifs("cities.txt");
//   int entries;
//   ifs >> entries;
//   while (entries > 0) {
//     int population;
//     string cityName;
//     ifs >> population;
//     getline(ifs, cityName);
//     --entries;
//     cout << cityName << " " << population << endl;
//   }
//   ifs.close();
// }

int main(int argc, char *argv[]) {
  if (argc == 3) {
    Autocomplete ac;
    string filename = argv[1];
    string prefix = argv[2];
    ac.readFile(filename);
    auto results = ac.complete(prefix);
    for (auto &p : results) {
      cout << p.first << "\t" << p.second << endl;
    }
  } else {
    testMain();
    //testReadCities();
  }
  return EXIT_SUCCESS;
}