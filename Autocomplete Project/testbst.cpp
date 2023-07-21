// /**
//  * Testing BST - Binary Search Tree functions
//  *
//  * This file has series of tests for BST
//  * Each test is independent and uses assert statements
//  * Test functions are of the form
//  *
//  *      test_netidXX()
//  *
//  * where netid is UW netid and XX is the test number starting from 01
//  *
//  * Test functions can only use the public functions from BST
//  * testBSTAll() is called from main in main.cpp
//  * testBSTAll calls all other functions
//  * @author Multiple
//  * @date ongoing
//  */

// Completed by Hemza Al Shamari hemzas@uw.edu
// 16 Apr 2023

#include "bstmap.h"
#include <cassert>
#include <sstream>

using namespace std;

// global value for testing
// NOLINTNEXTLINE
stringstream globalSS;

// need to reset SS before calling this
void printer(const BSTMap::value_type &p) {
  globalSS << "[" << p.first << "=" << p.second << "]";
}

// // Testing == and []
void test01() {
  cout << "Starting test01" << endl;
  cout << "* Testing ==, !=, [] and copy constructor" << endl;
  BSTMap b1;
  auto val = b1["hello"];
  assert(val == 0);
  b1["hello"] = 5;
  val = b1["hello"];
  assert(val == 5);
  b1["world"] = 42;

  BSTMap b2;
  assert(b1 != b2);
  b2["hello"] = 5;
  b2["world"] = 42;
  assert(b1 == b2);

  BSTMap b3(b2);
  assert(b1 == b3);
  cout << "Ending tes01" << endl;
}

// Testing traversal
void test02() {
  cout << "Starting test02" << endl;
  cout << "* Testing traversal" << endl;
  BSTMap b;
  b["x"] = 10;
  b["f"] = 5;
  b["b"] = 3;
  b["e"] = 4;
  b["z"] = 50;
  cout << b;

  globalSS.str("");
  b.inorder(printer);
  string order = globalSS.str();
  assert(order == "[b=3][e=4][f=5][x=10][z=50]");

  globalSS.str("");
  b.preorder(printer);
  order = globalSS.str();
  assert(order == "[x=10][f=5][b=3][e=4][z=50]");

  globalSS.str("");
  b.postorder(printer);
  order = globalSS.str();
  assert(order == "[e=4][b=3][f=5][z=50][x=10]");
  cout << "Ending test02" << endl;
}

// Testing rebalance
void test03() {
  cout << "Starting test03" << endl;
  cout << "* Testing rebalance" << endl;
  BSTMap b;
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;
  b["6"] = 6;
  assert(b.height() == 6);
  cout << b << endl;
  b.rebalance();
  assert(b.height() == 3);
  cout << b << endl;
  b.clear();
  assert(b.height() == 0);
  cout << "Ending test03" << endl;
}

// Testing count, empty, clear, contains and size
void test04() {
  cout << "Starting test04" << endl;
  cout << "* Testing for count, empty, clear ,contains and size," << endl;
  BSTMap b;
  assert(b.empty());
  assert(b.contains("pineapple") == false);
  b["apple"] = 3;
  b["banana"] = 5;
  b["carrots"] = 7;
  b["dates"] = 9;
  b["eggs"] = 11;
  assert(b.size() == 5);
  cout << b << endl;
  b.clear();
  assert(b.empty());
  cout << "Ending test04" << endl;
}

// Testing getAll()
void test05() {
  cout << "Starting test05" << endl;
  cout << "* Testing for getAll()" << endl;
  BSTMap b;
  b["Seattle"] = 9;
  b["Seoul"] = 11;
  b["San Diego"] = 7;
  b["Sacremento"] = 5;
  b["San Juan"] = 8;
  b["Switzerland"] = 13;
  b["Dubai"] = 2;
  b["Turkey"] = 16;
  cout << b << endl;
  auto v = b.getAll("Sa");
  assert(v.size() == 3);
  b.rebalance();
  cout << "Testing for only cities that start with 'Sa'" << endl;
  BSTMap b1(v);
  cout << b1 << endl;
  cout << "Ending test05" << endl;
}
// Testing BSTMap(const vector<value_type> &v)
void test06() {
  cout << "Starting test06" << endl;
  cout << "* Testing BSTMap(const vector<value_type> &v)" << endl;
  BSTMap b;
  b["peacock"] = 10;
  b["penguin"] = 20;
  b["parrot"] = 3;
  b["panther"] = 15;
  b["parakeet"] = 1;
  assert(b.size() == 5);
  auto v = b.getAll("pa");
  assert(v.size() == 3);
  BSTMap d(v);
  cout << d << endl;
  assert(d.size() == 3);
  cout << "Ending test06" << endl;
}
// Testing erase function
void test07() {
  cout << "Starting test07" << endl;
  cout << "* Testing erase function" << endl;
  BSTMap b;
  b["0"] = 0;
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;

  assert(b.size() == 6);
  cout << b << endl;
  assert(b.erase("0") == true);
  cout << b << endl;
  assert(b.erase("0") == false);
  assert(b.size() == 5);
  assert(b.erase("1") == true);
  assert(b.erase("2") == true);
  assert(b.erase("3") == true);
  assert(b.erase("4") == true);
  cout << b << endl;
  assert(b.size() == 1);
  cout << "Ending test07" << endl;
}
// Testing copy constructor
void test08() {
  cout << "Starting test08" << endl;
  cout << "* Testing copy constructor function" << endl;

  BSTMap b;
  b["strawberry"] = 21;
  b["cherry"] = 7;
  b["apple"] = 3;

  BSTMap b2(b);
  cout << b2 << endl;
  assert(b == b2);

  BSTMap b3;
  b3["strawberry"] = 21;
  b3["cherry"] = 8;
  b3["apple"] = 2;
  assert(b2 != b3);
  cout << "Ending test08" << endl;
}
// Calling all test functions
void testBSTAll() {
  test01();
  test02();
  test03();
  test04();
  test05();
  test06();
  test07();
  test08();
}