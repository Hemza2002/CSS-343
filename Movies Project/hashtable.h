// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#ifndef HashTable_H
#define HashTable_H

#define HASHTABLESIZE 10

#include <iostream>
#include <vector>
using namespace std;

#include "customer.h"

class HashTable {
public:
  // Constructor
  HashTable();

  // Destructor
  ~HashTable();

  // Insert a customer into the hash table
  bool insert(Customer *customer);

  // Get a customer from the hash table based on ID
  Customer *get(int id);

  // Get the size of the hash table
  int size() const;

  // Remove a customer from the hash table based on ID
  bool remove(int id);

  // Print all customers in the hash table
  void printAll();

  // Get all customers from the hash table as a vector
  vector<Customer *> getAll();

private:
  struct Node {
    int id;
    Customer *customer;
    Node *next;
    Node(int id, Customer *cust) : id(id), customer(cust), next(nullptr) {}
  };

  Node **hashTableArray;
  static int hashFunction(int id);
};

#endif
