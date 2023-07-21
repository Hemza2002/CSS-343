// Movie Project by Hemza Al Shamari and Ali Elgazzar
// CSS-343

#include "command.h"
#include <iostream>

using namespace std;

// Constructor for Command class
Command::Command(char type, int id, string invi, string genre, string param1,
                 string param2) {
  cmd = type;
  ID = id;
  inv = invi;
  dvd = genre;
  par1 = param1;
  par2 = param2;
}

// Get the type of the command
char Command::getType() const { return cmd; }

// Get the ID of the command
int Command::getID() const { return ID; }

// Get the inventory parameter of the command
string Command::getInv() { return inv; }

// Get the genre parameter of the command
string Command::getGenre() { return dvd; }

// Get the first additional parameter of the command
string Command::getParam1() { return par1; }

// Get the second additional parameter of the command
string Command::getParam2() { return par2; }
