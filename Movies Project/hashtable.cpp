// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#include "hashtable.h"

HashTable::HashTable() {
  // Constructor: Initializes the hashTableArray with nullptr
  hashTableArray = new Node *[HASHTABLESIZE];
  for (int i = 0; i < HASHTABLESIZE; i++) {
    hashTableArray[i] = nullptr;
  }
}

HashTable::~HashTable() {
  // Destructor: Deletes the dynamically allocated nodes in hashTableArray
  for (int i = 0; i < HASHTABLESIZE; i++) {
    Node *current = hashTableArray[i];
    while (current != nullptr) {
      Node *temp = current;
      current = current->next;
      delete temp;
    }
  }
  delete[] hashTableArray;
}

bool HashTable::insert(Customer *customer) {
  // Inserts a customer into the hash table based on its ID
  int id = customer->getID();
  int index = hashFunction(id);

  Node *newNode = new Node(id, customer);
  if (hashTableArray[index] == nullptr) {
    hashTableArray[index] = newNode;
  } else {
    Node *current = hashTableArray[index];
    while (current->next != nullptr) {
      if (current->id == id) {
        delete newNode;
        return false; // Customer with the same ID already exists
      }
      current = current->next;
    }
    if (current->id == id) {
      delete newNode;
      return false; // Customer with the same ID already exists
    }
    current->next = newNode;
  }
  return true;
}

Customer *HashTable::get(int id) {
  // Retrieves a customer from the hash table based on the provided ID
  int index = hashFunction(id);
  Node *current = hashTableArray[index];
  while (current != nullptr) {
    if (current->id == id) {
      return current->customer;
    }
    current = current->next;
  }
  return nullptr;
}

int HashTable::size() const {
  // Returns the total number of customers in the hash table
  int size = 0;
  for (int i = 0; i < HASHTABLESIZE; i++) {
    Node *current = hashTableArray[i];
    while (current != nullptr) {
      size++;
      current = current->next;
    }
  }
  return size;
}

bool HashTable::remove(int id) {
  // Removes a customer from the hash table based on the provided ID
  int index = hashFunction(id);
  Node *current = hashTableArray[index];
  Node *prev = nullptr;

  while (current != nullptr) {
    if (current->id == id) {
      if (prev == nullptr) {
        hashTableArray[index] = current->next;
      } else {
        prev->next = current->next;
      }
      delete current;
      return true;
    }
    prev = current;
    current = current->next;
  }
  return false;
}

void HashTable::printAll() {
  // Prints all the customers in the hash table
  for (int i = 0; i < HASHTABLESIZE; i++) {
    Node *current = hashTableArray[i];
    if (current != nullptr) {
      string prex = (i < 10) ? "0" : "";
      cout << "[" << prex << i << "] =>";
      while (current != nullptr) {
        string name = current->customer->getFirstName() + " " +
                      current->customer->getLastName();
        int space = 18 - name.length();
        string spacePrex = (space > 0) ? string(space / 2, ' ') : "";
        string spaceEnd = (space > 0 && space % 2 != 0) ? " " : "";
        cout << "[" << spacePrex << current->id << " " << name << spaceEnd
             << "] ";
        current = current->next;
      }
      cout << endl;
    }
  }
}

vector<Customer *> HashTable::getAll() {
  // Retrieves all customers from the hash table as a vector
  vector<Customer *> tmp;
  for (int i = 0; i < HASHTABLESIZE; i++) {
    Node *current = hashTableArray[i];
    while (current != nullptr) {
      tmp.push_back(current->customer);
      current = current->next;
    }
  }
  return tmp;
}

int HashTable::hashFunction(int id) {
  // Hash function to calculate the index for the provided ID
  return (id % HASHTABLESIZE);
}