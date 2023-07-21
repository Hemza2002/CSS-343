// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#include "customer.h"

Customer::Customer() {
  ID = 0;
  firstName = "";
  lastName = "";
}

Customer::~Customer() {}

Customer::Customer(int id, string firstName, string lastName) {
  // Check if the provided ID, first name, and last name are valid
  if (id != 0 && !firstName.empty() && !lastName.empty()) {
    this->ID = id;
    this->firstName = firstName;
    this->lastName = lastName;
  }
}

int Customer::getID() const {
  // Return the ID of the customer
  return ID;
}

string Customer::getFirstName() const {
  // Return the first name of the customer
  return firstName;
}

void Customer::setFirstName(string firstname) {
  // Set the first name of the customer
  this->firstName = firstname;
}

string Customer::getLastName() const {
  // Return the last name of the customer
  return lastName;
}

void Customer::setLastName(string lastName) {
  // Set the last name of the customer
  this->lastName = lastName;
}

void Customer::logBorrow(string title) {
  string transaction;
  // Log a new borrowing transaction
  transaction = title + " Borrowed";
  log.push_back(transaction);
}

void Customer::logReturn(string title) {
  string transaction;
  // Log a new borrowing transaction
  transaction = title + " Returned";
  log.push_back(transaction);
}

void Customer::showTransaction() {
  // Display the transaction log of the customer
  cout << "Transaction Log of " << getFirstName() << " " << getLastName()
       << endl;
  if (log.empty()) {
    cout << "No transactions found." << endl;
    return;
  }
  for (int i = 0; i < log.size(); i++) {
    cout << (i + 1) << ". " << log[i] << endl;
  }
}

int Customer::getNumberOfTransactions() {
  // Return the total number of transactions for the customer
  return log.size();
}