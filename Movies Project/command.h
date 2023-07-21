// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>

using namespace std;

class Command {
public:
  // Destructor for Command class (default)
  ~Command() = default;

  // Constructor for Command class
  Command(char type, int id, string invi, string genre, string param1,
          string param2);

  // Get the type of the command
  char getType() const;

  // Get the ID of the command
  int getID() const;

  // Get the inventory parameter of the command
  string getInv();

  // Get the genre parameter of the command
  string getGenre();

  // Get the first additional parameter of the command
  string getParam1();

  // Get the second additional parameter of the command
  string getParam2();

private:
  char cmd;    // Type of the command
  int ID;      // ID of the command
  string inv;  // Inventory parameter of the command
  string dvd;  // Genre parameter of the command
  string par1; // First additional parameter of the command
  string par2; // Second additional parameter of the command
};

#endif
