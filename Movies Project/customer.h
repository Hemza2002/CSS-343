// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Customer {
public:
  // Default constructor
  Customer();

  // Destructor
  ~Customer();

  // Parameterized constructor
  Customer(int id, string firstName, string lastName);

  // Get the ID of the customer
  int getID() const;

  // Get the first name of the customer
  string getFirstName() const;

  // Set the first name of the customer
  void setFirstName(string firstname);

  // Get the last name of the customer
  string getLastName() const;

  // Set the last name of the customer
  void setLastName(string lastname);

  // Log a transaction (borrow or return)
  void logBorrow(string title);

  void logReturn(string title);

  // Display the transaction log of the customer
  void showTransaction();

  // Get the total number of transactions for the customer
  int getNumberOfTransactions();

private:
  int ID;
  string firstName;
  string lastName;
  vector<string> log;  // Vector to store transaction log
};

#endif
