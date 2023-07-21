// Yusuf Pisan pisan@uw.edu
// 17 Jan 2021

// Completed by Hemza Al Shamari hemzas@uw.edu
// 16 Apr 2023

// BST class
// Creates a BST to store values
// Uses Node which holds the data

#include "bstmap.h"
#include <boost/algorithm/string.hpp>
#include <cassert>

using namespace std;

// copy constructor
BSTMap::BSTMap(const BSTMap &bst) { this->treeHelperFunction(bst.root); }

// given an array of length n
// create a tree to have all items in that array
// with the minimum height (uses same helper as rebalance)
BSTMap::BSTMap(const vector<value_type> &v) {
  vector<value_type> v2(v);
  int start = static_cast<int>(0);
  int end = static_cast<int>(v2.size() - 1);

  sort(v2.begin(), v2.end(), sortByWeight);
  root = createNewTreeHelperFunction(v2, start, end);
}

// sorter
bool BSTMap::sortByWeight(value_type &a, value_type &b) {
  return a.second < b.second;
}

// destructor
BSTMap::~BSTMap() { clear(); }

// delete all nodes in tree
void BSTMap::clear() {
  if (root == nullptr) {
    return;
  }
  deleteNodesInTree(root);
  root = nullptr;
}

// true if no nodes in BST
bool BSTMap::empty() const { return root == nullptr; }

// Number of nodes in BST
int BSTMap::size() const {
  sizeHelperFunction(this->root);
  return sizeHelperFunction(this->root);
}

// true if item is in BST
bool BSTMap::contains(const key_type &key) const {
  containsHelperFunction(root, key);
  return containsHelperFunction(root, key);
}

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {
  Node *node = searchKeyHelper(this->root, k);
  if (node != nullptr) {
    return node->data.second;
  }
  value_type item = value_type(k, mapped_type{});
  return insertFunctionHelper(item);
  assert(false && "operator[] has not been implemented");
}

vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> v;
  getAllHelperFunction(v, root, k);
  return v;
}

// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const {
  getHeight(root);
  return getHeight(root);
}

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
int BSTMap::getHeight(const Node *n) {
  if (n == nullptr) {
    return 0;
  }
  int height = 1;
  std::queue<const Node *> q;
  q.push(n);
  while (!q.empty()) {
    int levelSize = static_cast<int>(q.size());
    for (int i = 0; i < levelSize; i++) {
      const Node *curr = q.front();
      q.pop();
      if (curr->left != nullptr) {
        q.push(curr->left);
      }
      if (curr->right != nullptr) {
        q.push(curr->right);
      }
    }
    if (!q.empty()) {
      height++;
    }
  }
  return height;
}

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const string &k) const {
  return static_cast<size_t>(containsHelperFunction(root, k));
}

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const value_type &item)) const {
  inorderHelperFunction(root, visit);
}

// preorder traversal: root-left-right
// takes a function that takes a single parameter of type T
void BSTMap::preorder(void visit(const value_type &item)) const {
  preorderHelperFunction(root, visit);
}

// postorder traversal: left-right-root
// takes a function that takes a single parameter of type T
void BSTMap::postorder(void visit(const value_type &item)) const {
  postorderHelperFunction(root, visit);
}

// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance() {
  vector<value_type> v;
  saveNode(root, v);
  int start = 0;
  int end = static_cast<int>(v.size()) - 1;
  deleteNodesInTree(root);
  root = createNewTreeHelperFunction(v, start, end);
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const {
  return isSameStructureHelperFunction(root, other.root);
}

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const {
  return !isSameStructureHelperFunction(root, other.root);
}

// returns true if item successfully erased - BONUS
bool BSTMap::erase(const key_type &k) {
  bool erased = false;
  eraseHelperFunction(root, erased, k);
  return erased;
}

// this function performs a level-order traversal of the binary search tree and
// inserts each node's value into the BSTMap using this helper function
void BSTMap::treeHelperFunction(Node *n) {
  // create a queue to perform level-order traversal and enqueue the root node
  queue<Node *> nodeQueue;
  nodeQueue.push(n);
  // process all nodes in the queue
  while (!nodeQueue.empty()) {
    // dequeue the front node and assign it to currNode
    Node *currNode = nodeQueue.front();
    nodeQueue.pop();
    // insert the value of the current node in the BSTMap
    this->insertFunctionHelper(currNode->data);
    // enqueue the left and right children of currNode if they are not nullptr
    if (currNode->left != nullptr) {
      nodeQueue.push(currNode->left);
    }
    if (currNode->right != nullptr) {
      nodeQueue.push(currNode->right);
    }
  }
}

// this functon is a helper function that creates a binary search tree from the
// vector
BSTMap::Node *BSTMap::createNewTreeHelperFunction(const vector<value_type> &v,
                                                  const int &start,
                                                  const int &end) {
  // base case: if start index is greater than end index, return nullptr to
  // indicate an empty subtree
  if (start > end) {
    return nullptr;
  }
  // calculate the middle index between start and end
  int middle = (start + end) / 2;
  // create a new Node with the middle value of the vector
  Node *temp = createNewNode(v[middle]);
  // recursively construct the left and right subtrees of the current Node
  // by calling this function with appropriate arguments
  temp->left = createNewTreeHelperFunction(v, start, middle - 1);
  temp->right = createNewTreeHelperFunction(v, middle + 1, end);
  return temp;
}

// this function creates a new node for the binary search tree and returns its
// pointer
BSTMap::Node *BSTMap::createNewNode(const value_type &item) {
  // dynamically allocate a new node object and initialize its fields
  auto *tempNode = new Node{item, nullptr, nullptr};
  return tempNode;
}

// helper function that keeps count of how many nodes are in the binary search
// tree
int BSTMap::sizeHelperFunction(Node *root) const {
  if (root == nullptr) {
    return 0;
  }
  // recursively count the size of the left and right subtrees and
  // return the total size
  return (sizeHelperFunction(root->left) + 1 + sizeHelperFunction(root->right));
}

// function that deletes all of the nodes in the tree
void BSTMap::deleteNodesInTree(Node *root) {
  if (root != nullptr) {
    deleteNodesInTree(root->left);
    deleteNodesInTree(root->right);
    delete root;
  }
}

// helper function that recursively searches the tree for a node that contains
// the key, and return a pointer to that node. If the key is not found, return
// nullptr
BSTMap::Node *BSTMap::searchKeyHelper(Node *root, const key_type &key) const {
  if (root == nullptr || root->data.first == key) {
    return root;
  }
  if (root->data.first < key) {
    return searchKeyHelper(root->right, key);
  }
  return searchKeyHelper(root->left, key);
}

// this function inserts a new key-value pair into the binary search tree
// if the key already exists, it updates the value with the new one
// it returns a reference to the value associated with the key
BSTMap::mapped_type &BSTMap::insertFunctionHelper(const value_type &item) {
  // if the BSTMap is empty, create a new node as root and return the value
  if (root == nullptr) {
    root = createNewNode(item);
    return root->data.second;
  }
  // otherwise, find the correct position for the new node
  Node *curr = recursiveFunctionHelper(root, item);
  // if the key already exists, update the value with the new one
  if (curr->data.first == item.first) {
    curr->data.second = item.second;
  }
  // otherwise, insert a new node with the given key-value pair
  else {
    Node *newNode = createNewNode(item);
    if (item.first < curr->data.first) {
      curr->left = newNode;
    } else {
      curr->right = newNode;
    }
    curr = newNode;
  }
  return curr->data.second;
}

// helper function that returns true if certain item is found in binary search
// tree
bool BSTMap::containsHelperFunction(Node *n, const key_type &key) const {
  if (n == nullptr) {
    return false;
  }
  // if the key matches the key of the current node, return true
  if (key == n->data.first) {
    return true;
  }
  // if the key is less than the key of the current node, recursively search the
  // left subtree
  if (key < n->data.first) {
    return containsHelperFunction(n->left, key);
  }
  // if the key is greater than the key of the current node, recursively search
  // the right subtree
  return containsHelperFunction(n->right, key);
}

// helper function used to recursively traverse the BST and find the correct
// position for inserting a new node takes the current node and the new
// key-value pair as input and returns the node where the new node should be
// inserted
BSTMap::Node *BSTMap::recursiveFunctionHelper(Node *curr,
                                              const value_type &item) {
  // if the new key is greater than the current node's key, go to the right
  // subtree
  if (curr->data < item) {
    // if the right subtree is null, create a new node with the given key-value
    // pair and insert it as the right child of the current node
    if (curr->right == nullptr) {
      Node *insertNode = createNewNode(item);
      curr->right = insertNode;
      curr = curr->right;
    }
    // otherwise, recursively call the function on the right subtree
    else {
      return recursiveFunctionHelper(curr->right, item);
    }
  }
  // if the new key is less than the current node's key, go to the left subtree
  else if (curr->data > item) {
    // if the left subtree is null, create a new node with the given key-value
    // pair and insert it as the left child of the current node
    if (curr->left == nullptr) {
      Node *insertNode = createNewNode(item);
      curr->left = insertNode;
      curr = curr->left;
    }
    // otherwise, recursively call the function on the left subtree
    else {
      return recursiveFunctionHelper(curr->left, item);
    }
  }
  // return the current node, which is the node where the new node should be
  // inserted
  return curr;
}

// helper function that traverses tree inorder
void BSTMap::inorderHelperFunction(Node *n,
                                   void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  // recursively traverse the left subtree
  inorderHelperFunction(n->left, visit);
  // perform the visit function on the current node
  visit(n->data);
  // recursively traverse the right subtree
  inorderHelperFunction(n->right, visit);
}

// helper function that traverses tree in preorder
void BSTMap::preorderHelperFunction(Node *n,
                                    void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  // perform the visit function on the current node
  visit(n->data);
  // recursively traverse the left subtree
  preorderHelperFunction(n->left, visit);
  // recursively traverse the right subtree
  preorderHelperFunction(n->right, visit);
}

// helper function that traverses tree in postorder
void BSTMap::postorderHelperFunction(Node *n,
                                     void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  // recursively traverse the left subtree
  postorderHelperFunction(n->left, visit);
  // recursively traverse the right subtree
  postorderHelperFunction(n->right, visit);
  // perform the visit function on the current node
  visit(n->data);
}

// function to save all nodes into vector
void BSTMap::saveNode(Node *n, vector<value_type> &v) {
  if (n == nullptr) {
    return;
  }
  // recursively traverse the left subtree
  saveNode(n->left, v);
  // add the current node's data to the vector
  v.push_back(n->data);
  // recursively traverse the right subtree
  saveNode(n->right, v);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
// helper function that deletes key
BSTMap::Node *BSTMap::eraseHelperFunction(Node *n, bool &flag,
                                          const key_type &k) {
  Node *parent = nullptr;
  Node *curr = root;
  // find the node to delete and its parent
  while (curr != nullptr && curr->data.first != k) {
    parent = curr;
    if (k < curr->data.first) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  // if the key was not found, return the original root
  if (curr == nullptr) {
    return root;
  }
  // if the node has only one child or no children
  if (curr->left == nullptr || curr->right == nullptr) {
    Node *child;
    if (curr->left != nullptr) {
      child = curr->left;
    } else {
      child = curr->right;
    }
    if (parent == nullptr) {
      root = child;
    } else if (curr == parent->left) {
      parent->left = child;
    } else {
      parent->right = child;
    }
    delete curr;
    flag = true;
  }
  // if the node has two children
  else {
    Node *successor = curr->right;
    parent = curr;
    while (successor->left != nullptr) {
      parent = successor;
      successor = successor->left;
    }
    curr->data = successor->data;
    if (parent == curr) {
      parent->right = successor->right;
    } else {
      parent->left = successor->right;
    }
    delete successor;
    flag = true;
  }
  return root;
}
#pragma GCC diagnostic pop

// function that returns the node with minimum key value
BSTMap::Node *BSTMap::minimumKeyValue(Node *n) {
  Node *current = n;
  // traverse down the left side of the tree from the starting node until we
  // reach the minimum value
  while (current->left != nullptr) {
    current = current->left;
  }
  // return the node with the minimum value
  return current;
}

// helper function that returns true if trees are equal
bool BSTMap::isSameStructureHelperFunction(Node *n, Node *nn) const {
  if (n == nullptr && nn == nullptr) {
    return true;
  }
  // check if one of the nodes is null and the other isn't, indicating that the
  // subtrees rooted at these nodes have different structures
  if (n == nullptr || nn == nullptr) {
    return false;
  }
  // check if the data stored in the two nodes is different, indicating that the
  // subtrees rooted at these nodes have different structures
  if (n->data != nn->data) {
    return false;
  }
  // recursively check if the left and right subtrees rooted at these nodes have
  // the same structure
  return isSameStructureHelperFunction(n->left, nn->left) &&
         isSameStructureHelperFunction(n->right, nn->right);
}

// helper function that finds object which match to the key
void BSTMap::getAllHelperFunction(vector<value_type> &v, Node *n,
                                  const key_type &k) {
  // initialize a stack to keep track of the nodes to be processed
  vector<Node *> stack;
  stack.push_back(n);
  while (!stack.empty()) {
    // pop the top node from the stack and check if its key starts with the
    // given prefix
    Node *current = stack.back();
    stack.pop_back();
    if (boost::algorithm::starts_with(current->data.first, k)) {
      v.push_back(current->data);
    }
    // add the right and left subtrees of the current node to the stack in
    // reverse order
    if (current->right != nullptr) {
      stack.push_back(current->right);
    }
    if (current->left != nullptr) {
      stack.push_back(current->left);
    }
  }
}
