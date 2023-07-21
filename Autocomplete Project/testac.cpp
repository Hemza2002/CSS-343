// Completed by Hemza Al Shamari hemzas@uw.edu
// 16 Apr 2023

#include "autocomplete.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void testAC01() {
  cout << "Starting AC test01" << endl;
  cout << "* Testing basic autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("small.txt");
  auto v = ac.complete("hel");
  assert(v.size() == 2);
  assert(v[0].first == "help");
  assert(v[0].second == 20);
  assert(v[1].first == "hello");
  assert(v[1].second == 10);
  cout << "Ending tesAC01" << endl;
}

void testAC02() {
  cout << "Starting AC test02" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Sea");
  assert(v.size() == 47);
  assert(v[0].first == "Seattle, Washington, United States");
  assert(v[0].second == 608660);
  assert(v[46].first == "Seabeck, Washington, United States");
  assert(v[46].second == 1105);
  cout << "Ending tesAC02" << endl;
}

void testAC03() {
  cout << "Starting AC test03" << endl;
  cout << "* Testing wiktionary autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("wiktionary.txt");
  auto v = ac.complete("thro");
  assert(v.size() == 9);
  assert(v[0].first == "through");
  assert(v[0].second == 79292500);
  assert(v[8].first == "throws");
  assert(v[8].second == 951655);
  cout << "Ending tesAC03" << endl;
}

// // Calling all test functions
void testACAll() {
  testAC01();
  testAC02();
  testAC03();
}