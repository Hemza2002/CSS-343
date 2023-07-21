// Completed by Hemza Al Shamari hemzas@uw.edu
// 16 Apr 2023

#include "autocomplete.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void testBSTAll();

void Autocomplete::readFile(const string &fileName) {
  // open the input file stream
  ifstream ifs(fileName);
  if (!ifs) {
    throw runtime_error("Failed to open file " + fileName);
  }
  // read the number of lines in the file
  string readingValue;
  int lines;
  getline(ifs, readingValue);
  istringstream parseLine(readingValue);
  parseLine >> lines;
  // read each line and add it to the phrases BSTMap
  for (auto i = 0; i < lines; ++i) {
    // read the value (integer) from the file
    getline(ifs, readingValue, '\t');
    istringstream parseValue(readingValue);
    int value;
    parseValue >> value;
    string keys;
    getline(ifs, keys, '\n');
    // add the key-value pair to the phrases BSTMap
    phrases[move(keys)] = value;
  }

  // close the input file stream and rebalance the phrases BSTMap
  ifs.close();
  phrases.rebalance();
  // cout << phrases << endl;
}

// a sorting function for sorting phrases by their weight (values)
bool Autocomplete::sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b) {
  return a.second > b.second;
}

// get all phrases in the BSTMap that start with the given prefix
vector<BSTMap::value_type>
Autocomplete::complete(const BSTMap::key_type &prefix) const {
  // get all phrases that start with the given prefix
  vector<BSTMap::value_type> v = phrases.getAll(prefix);
  // sort the phrases by weight (values)
  sort(v.begin(), v.end(), sortByWeight);
  return v;
}
