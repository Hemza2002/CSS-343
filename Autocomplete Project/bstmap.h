// Yusuf Pisan pisan@uw.edu
// 15 Jan 2018

// Completed by Hemza Al Shamari hemzas@uw.edu
// 16 Apr 2023

// BST class
// Creates a BST to store values
// Uses Node which holds the data
// Uses templates to store any type of data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BSTMAP_H
#define BSTMAP_H

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class BSTMap {

  // display BST tree in a human-readable format
  // comment out printSideways or printVertical
  friend ostream &operator<<(ostream &out, const BSTMap &bst);

public:
  using key_type = string;
  using mapped_type = uint64_t;
  using value_type = pair<key_type, mapped_type>;

  // constructor, empty tree
  BSTMap() = default;

  // copy constructor
  BSTMap(const BSTMap &bst);

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (uses same helper as rebalance)
  explicit BSTMap(const vector<value_type> &v);

  // destructor
  virtual ~BSTMap();

  // move not allowed
  BSTMap(BSTMap &&other) = delete;

  // assignment not allowed
  BSTMap &operator=(const BSTMap &other) = delete;

  // move assignment not allowed
  BSTMap &operator=(BSTMap &&other) = delete;

  // true if no nodes in BST
  bool empty() const;

  // Number of nodes in BST
  int size() const;

  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int height() const;

  // delete all nodes in tree
  void clear();

  // true if item is in BST
  bool contains(const key_type &key) const;

  // same as contains, but returns 1 or 0
  // compatibility with std::map
  size_t count(const key_type &k) const;

  // If k matches the key returns a reference to its value
  // If k does not match any key, inserts a new element
  // with that key and returns a reference to its mapped value.
  mapped_type &operator[](const key_type &k);

  // inorder traversal: left-root-right
  // takes a function that takes a single parameter of type T
  void inorder(void visit(const value_type &item)) const;

  // preorder traversal: root-left-right
  void preorder(void visit(const value_type &item)) const;

  // postorder traversal: left-right-root
  void postorder(void visit(const value_type &item)) const;

  // balance the BST by saving all nodes to a vector inorder
  // and then recreating the BST from the vector
  void rebalance();

  // returns true if item successfully erased - BONUS
  bool erase(const key_type &k);

  vector<value_type> getAll(const key_type &k) const;

  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BSTMap &other) const;

  // not == to each other
  bool operator!=(const BSTMap &other) const;

  // sorter
  static bool sortByWeight(value_type &a, value_type &b);

private:
  // Node for BST
  struct Node {
    // key-value pair
    value_type data;
    // children
    struct Node *left;
    struct Node *right;
  };

  // refer to data type "struct Node" as Node
  using Node = struct Node;

  // print Node
  friend ostream &operator<<(ostream &out, const Node &n);

  // root of the tree
  Node *root{nullptr};

  // print tree sideways with root on left
  static ostream &printSideways(ostream &out, const Node *curr, int level = 0);

  // helper for printVertical
  static ostream &centeredPrint(ostream &out, int space, const string &str,
                                char fillChar = ' ');

  // print tree with the root at top
  static ostream &printTreeLevel(ostream &out, queue<const Node *> &q,
                                 int width, int depth, int maxDepth);

  // helper function for displaying tree sideways, works recursively
  static ostream &printVertical(ostream &out, Node *curr);

  // height of a Node, nullptr is 0, root is 1, static, no access to 'this'
  // helper function to height(), used by printVertical
  static int getHeight(const Node *n);

  // recursive helper function used in a tree data structure to perform an
  // operation on each node and its children
  void treeHelperFunction(Node *n);

  // helper function for creating a new tree data structure using the values in
  // the specified vector
  Node *createNewTreeHelperFunction(const vector<value_type> &v,
                                    const int &start, const int &end);

  //  creates a new node for a linked list with the specified value, and returns
  //  a pointer to the newly created node
  static Node *createNewNode(const value_type &item);

  // const member helper function that recursively calculates the total number
  // of nodes in a tree data structure, including the root node, and returns the
  // result as an integer
  int sizeHelperFunction(Node *root) const;

  // function for deleting all the nodes in a tree data structure starting from
  // the root node
  void deleteNodesInTree(Node *root);

  // helper function to recursively search the tree for a node with the
  // specified key value, starting from the root node.
  Node *searchKeyHelper(Node *root, const key_type &key) const;

  // helper function for a map data structure, and takes a value_type object as
  // its parameter inserts the key-value pair represented by the value_type
  // object into the map, if the key does not already exist
  mapped_type &insertFunctionHelper(const value_type &item);

  // helper function for a tree data structure, and takes a pointer to a Node
  // object and a key as its parameters recursively searches the tree for a node
  // with the specified key value, starting from the given node returns a
  // boolean indicating whether a node with the given key value was found in the
  // BST
  bool containsHelperFunction(Node *n, const key_type &key) const;

  // recursive helper function for a tree data structure, and takes a pointer to
  // a Node object and a value_type object as its parameters recursively inserts
  // a new node with the specified value into the tree, starting from the given
  // node
  Node *recursiveFunctionHelper(Node *curr, const value_type &item);

  // helper function that performs an inorder traversal of the tree, starting
  // from the given node, and calls the provided function on each visited node
  void inorderHelperFunction(Node *n, void visit(const value_type &item)) const;

  // helper function that performs a preorder traversal of the tree, starting
  // from the given node, and calls the provided function on each visited node
  void preorderHelperFunction(Node *n,
                              void visit(const value_type &item)) const;

  // helper function that performs a preorder traversal of the tree, starting
  // from the given node, and calls the provided function on each visited node
  void postorderHelperFunction(Node *n,
                               void visit(const value_type &item)) const;

  // function that performs an inorder traversal of the tree, starting from the
  // given node, and stores the values of each visited node in the provided
  // vector object
  void saveNode(Node *n, vector<value_type> &v);

  // helper function that recursively searches the tree for a node with the
  // specified key value, starting from the given node
  Node *eraseHelperFunction(Node *n, bool &flag, const key_type &k);

  // function that finds and returns a pointer to the node with the minimum key
  // value in the subtree rooted at the given node
  static Node *minimumKeyValue(Node *n);

  // helper function that recursively compares the key and value of each node in
  // the two trees rooted at the given nodes, to determine if they have the same
  // structure and content
  bool isSameStructureHelperFunction(Node *n, Node *nn) const;

  // helper function that performs an inorder traversal of the subtree rooted at
  // the given node, and stores the values of each visited node that has the
  // specified key value in the provided vector object
  static void getAllHelperFunction(vector<value_type> &v, Node *n,
                                   const key_type &k);
};

#endif // BSTMAP_H
