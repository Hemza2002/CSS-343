// Completed by Hemza Al Shamari
// 04/30/23
// hemzas@uw.edu

#ifndef VERTEX_H
#define VERTEX_H

#include "edge.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

class Edge;

class Vertex {
  friend class Edge;
  friend class Graph;

public:
  // Default constructor: initializes an empty vertex
  Vertex();

  // Copy constructor: copies the label and edges vector from another Vertex
  // object
  Vertex(const Vertex &vertex);

  // Constructor that takes a label and initializes the label member variable
  explicit Vertex(const string &label);

  // Destructor: frees memory used by the Vertex object and its associated edges
  ~Vertex();

  // Move constructor not allowed
  Vertex(Vertex &&other) = delete;

  // Assignment operator not allowed
  Vertex &operator=(const Vertex &other) = delete;

  // Move assignment operator not allowed
  Vertex &operator=(Vertex &&other) = delete;

  // Returns true if an edge exists between this vertex and the specified vertex
  // vTo, false otherwise
  bool findingEdge(Vertex *vTo);

  // Adds a new edge to the edges vector in sorted order by the label of the
  // "to" vertex Returns true if the edge was successfully added, false
  // otherwise
  bool addingNewEdge(Edge *newEdge);

private:
  // A vector that stores pointers to all the outgoing edges from this vertex
  vector<Edge *> edges;
  // A label that identifies this vertex in the graph
  string label;
};

#endif
