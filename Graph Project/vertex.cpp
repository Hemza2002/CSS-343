// Completed by Hemza Al Shamari
// 04/30/23
// hemzas@uw.edu

#include "vertex.h"
#include <string>
#include <vector>

using namespace std;

// Default constructor: initializes label to an empty string and edges to an
// empty vector
Vertex::Vertex() = default;

// Copy constructor: copies the label and edges vector from another Vertex
// object
Vertex::Vertex(const Vertex &vertex) {
  this->label = vertex.label;
  for (const auto &edge : vertex.edges) {
    this->edges.push_back(new Edge(edge->from, edge->to, edge->weight));
  }
}

// Constructor that takes a label and initializes the label member variable
Vertex::Vertex(const string &label) { this->label = label; }

// Destructor: frees memory used by the Vertex object and its associated edges
Vertex::~Vertex() {
  for (auto &edge : edges) {
    delete edge;
  }
  edges.clear();
}

// Returns true if an edge exists between this vertex and the specified vertex
// vTo, false otherwise
bool Vertex::findingEdge(Vertex *vTo) {
  auto *e = new Edge(this, vTo, 0);
  for (auto &edge : edges) {
    if (edge->from == e->from && edge->to == e->to) {
      delete e;
      return true;
    }
  }
  delete e;
  return false;
}

// Adds a new edge to the edges vector in sorted order by the label of the "to"
// vertex Returns true if the edge was successfully added, false otherwise
bool Vertex::addingNewEdge(Edge *newEdge) {
  if (edges.empty()) {
    edges.push_back(newEdge);
    return true;
  }
  for (int i = 0; i < edges.size(); i++) {
    if (newEdge->to->label < edges.at(i)->to->label) {
      edges.insert(edges.begin() + i, newEdge);
      return true;
    }
  }
  edges.push_back(newEdge);
  return true;
}
