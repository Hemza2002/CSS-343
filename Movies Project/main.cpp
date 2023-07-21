/**
 * Driver for starting movie store tests
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

#include "classic.h"
#include "comedy.h"
#include "command.h"
#include "customer.h"
#include "drama.h"
#include "dvd.h"
#include "dvdFactory.h"
#include "hashtable.h"


using namespace std;

std::set<Dvd *> dvdInventory;
HashTable customerTable; // Global hash table for customers

//sort dvds based on sorting parameter
void sortstring(vector<string> &v) {
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v.size() - 1; j++) {
      if (v[j] > v[j + 1]) {
        auto temp = v[j];
        v[j] = v[j + 1];
        v[j + 1] = temp;
      }
    }
  }
}

// special sort for classic dvds
void sortc(vector<pair<string, string>> &v) {
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v.size() - 1; j++) {
      if (v[j].first > v[j + 1].first) {
        auto temp = v[j];
        v[j] = v[j + 1];
        v[j + 1] = temp;
      }
    }
  }
}

// Function to read customer data from a file and insert them into the hash
// table
void readCustomers() {
  ifstream ifs("data4customers.txt");
  string line;
  while (getline(ifs, line)) {
    // Process customer data and insert into the hash table
    // (Assuming the format is ID, FirstName, LastName)
    int id;
    string firstName;
    string lastName;
    stringstream ss(line);
    if (ss >> id >> firstName >> lastName) {
      Customer *customer = new Customer(id, firstName, lastName);
      customerTable.insert(customer);
    }
  }
  ifs.close();
}

// forward declaration, implementation in store_test.cpp
// Iterate through the dvd inventory, sort, and print
void inventory() {
  vector<Dvd *> f;
  vector<string> fs;
  vector<Dvd *> c;
  vector<pair<string, string>> cs;
  vector<Dvd *> d;
  vector<string> ds;
  for (auto *x : dvdInventory) {
    if (x->getMovieGenre() == "F") {
      f.push_back(x);
    } else if (x->getMovieGenre() == "C") {
      c.push_back(x);
    } else if (x->getMovieGenre() == "D") {
      d.push_back(x);
    }
  }
  for (auto *y : f) {
    string add = y->getMovieGenre() + ": " + y->getMovieTitle() + " (" +
                 y->getMovieYear() + "). Directed by " + y->getMovieDirector() +
                 ". " + to_string(y->getInventoryCount()) + " left in stock";
    fs.push_back(add);
  }
  for (auto s : fs) {
    cout << s << endl;
  }
  sortstring(fs);
  for (auto *y : d) {
    string add = y->getMovieGenre() + ": " + y->getMovieDirector() + " (" +
                 y->getMovieTitle() + "). Released " + y->getMovieYear() +
                 ". " + to_string(y->getInventoryCount()) + " left in stock";
    ds.push_back(add);
  }
  sortstring(ds);
  for (auto s : ds) {
    cout << s << endl;
  }
  for (auto *y : c) {
    // cout << y->getMovieYear() << endl;
    string add = y->getMovieGenre() + ": (Acted by " + y->getMovieDirector() +
                 "). " + y->getMovieTitle() + ". " +
                 to_string(y->getInventoryCount()) +
                 " left in stock. Released: " + y->getMovieSorting();
    cs.push_back(make_pair(y->getMovieSorting(), add));
  }
  sortc(cs);
  for (auto s : cs) {
    cout << s.second << endl;
  }
}

// Print the customer transaction history
void history(Command *cmd) {
  customerTable.get(cmd->getID())->showTransaction();
}

// Add a dvd to a customer's account
void borrow(Command *cmd) {
  Customer *them;
  Dvd *cur = nullptr;
  if (cmd->getGenre() == "F" || cmd->getGenre() == "B" ||
      cmd->getGenre() == "C") {
    for (auto *d : dvdInventory) {
      if (d->getMovieTitle() == cmd->getParam1()) {
        cur = d;
        break;
      }
    }
    if (cur == nullptr) {
      return;
    }
    if (cur->getInventoryCount() <= 0) {
      cout << "Error: Insuficient inventory to borrow." << endl;
      return;
    }
    them = customerTable.get(cmd->getID());
    them->logBorrow(cur->getMovieTitle());
    cur->decrementInventory();
  }
}

// Remove a dvd from a customer's account
void remove(Command *cmd) {
  Customer *them;
  Dvd *cur = nullptr;
  if (cmd->getGenre() == "F" || cmd->getGenre() == "B" ||
      cmd->getGenre() == "C") {
    for (auto *d : dvdInventory) {
      if (d->getMovieTitle() == cmd->getParam1()) {
        cur = d;
        break;
      }
    }
    if (cur == nullptr) {
      return;
    }
    them = customerTable.get(cmd->getID());
    them->logReturn(cur->getMovieTitle());
    cur->incrementInventory();
  }
}

// Verifies whether the new dvd already exists
bool verify(Dvd *toAdd) {
  for (auto *exist : dvdInventory) {
    if (exist->getMovieTitle() == toAdd->getMovieTitle()) {
      return false;
    }
    if (exist->getMovieDirector() == toAdd->getMovieDirector()) {
      return false;
    }
  }
  return true;
}

// Reads each line of "data4movies.txt", saves into a queue, then creates and
// excecutes each dvd one by one from the queue.
void makeMovies() {
  ifstream ifs("data4movies.txt");
  string line;
  queue<vector<string>> movieQ;
  do {
    getline(ifs, line);
    vector<string> tokens;
    stringstream check1(line);
    string token;
    while (getline(check1, token, ',')) {
      tokens.push_back(token);
    }
    movieQ.push(tokens);
  } while (!line.empty());
  ifs.close();
  while (!movieQ.empty()) {
    vector<string> add = movieQ.front();
    movieQ.pop();
    if (add.size() == 5) {
      Dvd *toAdd =
          DvdFactory::create(add[0], add[1].substr(1, add[1].size() - 1),
                             add[2].substr(1, add[2].size() - 1),
                             add[3].substr(1, add[3].size() - 1),
                             add[4].substr(1, add[4].size() - 1));
      if (toAdd == nullptr) {
        continue;
      }
      if (verify(toAdd)) {
        dvdInventory.insert(toAdd);
      }
    }
  }
}

// creates the command instance based on a given string
Command *createCommand(string line) {
  Command *created = nullptr;
  if (line[0] == 'I') {
    created = new Command('I', -1, "", "", "", "");
  } else if (line[0] == 'H') {
    int id = stoi(line.substr(2));
    created = new Command('H', id, "", "", "", "");
  } else if (line[0] == 'B' || line[0] == 'R') {
    string type;
    string id;
    string dvd;
    string genre;
    stringstream ss(line);
    ss >> type >> id >> dvd >> genre;
    if (dvd != "D") {
      return nullptr;
    }
    int pos = line.find(genre);
    string rest = line.substr(pos + 2);
    vector<string> tokens;
    stringstream check1(rest);
    string token;
    if (genre == "C") {
      while (getline(check1, token, ' ')) {
        tokens.push_back(token);
      }
      string p1;
      string p3;
      p1 += tokens[1] + " " + tokens[0];
      p3 += tokens[2] + " " + tokens[3];
      created = new Command(line[0], stoi(id), dvd, genre, p1, p3);
    } else if (genre == "F") {
      while (getline(check1, token, ',')) {
        tokens.push_back(token);
      }
      string p1 = tokens[0];
      string p3 = tokens[1].substr(1);
      created = new Command(line[0], stoi(id), dvd, genre, p1, p3);
    } else if (genre == "D") {
      while (getline(check1, token, ',')) {
        tokens.push_back(token);
      }
      string p1 = tokens[0].substr(2);
      string p3 = tokens[1].substr(1);
      created = new Command(line[0], stoi(id), dvd, genre, p1, p3);
    }
  } else {
    cout << "Error: Command is not valid \n";
  }
  return created;
}

// Reads each line of "data4commands.txt", saves into a queue, then creates and
// excecutes each command one by one from the queue.
void doCommands() {
  ifstream ifs("data4commands.txt");
  queue<Command *> commandQ;
  string line;
  Command *put;
  while (getline(ifs, line)) {
    put = createCommand(line);
    if (put != nullptr) {
      commandQ.push(put);
    }
  }
  ifs.close();
  while (!commandQ.empty()) {
    auto *cmd = commandQ.front();
    commandQ.pop();
    // cout << cmd->getType() << " " << cmd->getID() << " " << cmd->getInv() <<
    // " " << cmd->getGenre() << " " << cmd->getParam1() << " " <<
    // cmd->getParam2() << endl;
    if (cmd->getType() == 'I') {
      inventory();
    } else if (cmd->getType() == 'H') {
      history(cmd);
    } else if (cmd->getType() == 'B') {
      borrow(cmd);
    } else if (cmd->getType() == 'R') {
      remove(cmd);
    } else {
      cout << "Error: Command is not valid." << endl;
    }
    delete cmd;
  }
}

void testAll() {
  makeMovies();
  // for (auto a : dvdInventory) cout << a->getMovieTitle() << endl;
  readCustomers();
  // customerTable.printAll();
  doCommands();
  dvdInventory.~set();
  // customerTable.~HashTable();
}

int main() {
  testAll();
  cout << "Done." << endl;
  return 0;
}
