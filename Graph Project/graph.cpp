// Completed by Hemza Al Shamari
// 04/30/23
// hemzas@uw.edu

#include "graph.h"
#include <algorithm>
#include <climits>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

// constructor, empty graph
// directionalEdges defaults to true
Graph::Graph(bool directionalEdges) {
  graph = {};
  directional = directionalEdges;
}

// destructor
Graph::~Graph() {
  for (auto &entry : graph) {
    delete entry.second;
  }
  graph.clear();
}

// @return total number of vertices
std::map<std::string, Vertex *>::size_type Graph::verticesSize() const {
  return graph.size();
}

// @return total number of edges
int Graph::edgesSize() const {
  int res = 0;
  for (const auto &itr : graph) {
    res += static_cast<int>(itr.second->edges.size());
  }
  return res;
}

// @return number of edges from given vertex, -1 if vertex not found
int Graph::vertexDegree(const string &label) const {
  if (graph.find(label) != graph.end()) {
    return static_cast<int>(graph.find(label)->second->edges.size());
  }
  return -1;
}

// @return true if vertex added, false if it already is in the graph
bool Graph::add(const string &label) {
  if (this->contains(label)) {
    return false;
  }
  graph.emplace(label, new Vertex(label));
  return true;
}

/** return true if vertex already in graph */
bool Graph::contains(const string &label) const {
  return graph.find(label) != graph.end();
}

// @return string representing edges and weights, "" if vertex not found
// A-3->B, A-5->C should return B(3),C(5)
string Graph::getEdgesAsString(const string &vertexLabel) const {
  string res;
  if (graph.find(vertexLabel) != graph.end()) {
    map<string, int> edgeMap = edgeHelperFunction(vertexLabel);
    int count = 0;
    for (auto it : edgeMap) {
      res += it.first;
      res += "(";
      res += to_string(it.second);
      res += ")";
      count++;
      if (count < edgeMap.size()) {
        res += ",";
      }
    }
  }
  return res;
}

// @return true if successfully connected
bool Graph::connect(const string &from, const string &to, int weight) {
  if (from == to) {
    return false;
  }
  // Ensure that both vertices exist in the graph
  if (!contains(from)) {
    add(from);
  }
  if (!contains(to)) {
    add(to);
  }
  // directional graph
  if (directional) {
    Vertex *vFrom = graph.find(from)->second;
    Vertex *vTo = graph.find(to)->second;
    if (vFrom->findingEdge(vTo)) {
      return false;
    }
    auto *newEdge = new Edge(vFrom, vTo, weight);
    return vFrom->addingNewEdge(newEdge);
  }
  // non-directional
  Vertex *vFrom = graph.find(from)->second;
  Vertex *vTo = graph.find(to)->second;
  bool result = false;
  if (!vFrom->findingEdge(vTo)) {
    auto *newEdge = new Edge(vFrom, vTo, weight);
    result = vFrom->addingNewEdge(newEdge);
  }
  if (!vTo->findingEdge(vFrom)) {
    auto *newEdge = new Edge(vTo, vFrom, weight);
    result = vTo->addingNewEdge(newEdge) || result;
  }
  return result;
}

bool Graph::disconnect(const string &from, const string &to) {
  if (graph.find(from) == graph.end() || graph.find(to) == graph.end()) {
    return false;
  }
  Vertex *vFrom = graph.find(from)->second;
  Vertex *vTo = graph.find(to)->second;
  bool removed = false;
  for (auto it = vFrom->edges.begin(); it != vFrom->edges.end(); ++it) {
    if ((*it)->from->label == from && (*it)->to->label == to) {
      delete (*it);
      vFrom->edges.erase(it);
      removed = true;
      break;
    }
  }
  if (!directional) {
    for (auto it = vTo->edges.begin(); it != vTo->edges.end(); ++it) {
      if ((*it)->to->label == to && (*it)->from->label == from) {
        delete (*it);
        vTo->edges.erase(it);
        removed = true;
        break;
      }
    }
  }
  return removed;
}

// depth-first traversal starting from given startLabel
void Graph::dfs(const string &startLabel, void visit(const string &label)) {
  if (graph.find(startLabel) == graph.end()) {
    return;
  }
  stack<pair<string, Vertex *>> s;
  s.push(make_pair(startLabel, graph.find(startLabel)->second));
  set<string> visited;
  visited.insert(startLabel);
  while (!s.empty()) {
    auto current = s.top();
    s.pop();
    visit(current.first);
    for (auto it = current.second->edges.rbegin();
         it != current.second->edges.rend(); it++) {
      if (visited.find((*it)->to->label) == visited.end()) {
        s.push(make_pair((*it)->to->label, (*it)->to));
        visited.insert((*it)->to->label);
      }
    }
  }
}

// breadth-first traversal starting from startLabel
void Graph::bfs(const string &startLabel, void visit(const string &label)) {
  if (graph.find(startLabel) == graph.end()) {
    return;
  }
  queue<pair<string, Vertex *>> q;
  q.push(make_pair(startLabel, graph.find(startLabel)->second));
  set<string> visited;
  visited.insert(startLabel);
  while (!q.empty()) {
    auto current = q.front();
    q.pop();
    visit(current.first);
    for (auto &edge : current.second->edges) {
      if (visited.find(edge->to->label) == visited.end()) {
        q.push(make_pair(edge->to->label, edge->to));
        visited.insert(edge->to->label);
      }
    }
  }
}

// store the weights in a map
// store the previous label in a map
pair<map<string, int>, map<string, string>>
Graph::dijkstra(const string &startLabel) const {
  map<string, int> weights;
  map<string, string> previous;
  if (graph.find(startLabel) == graph.end()) {
    return make_pair(weights, previous);
  }
  Vertex *startVertex = graph.find(startLabel)->second;
  using VertexData = pair<int, Vertex *>;
  priority_queue<VertexData, vector<VertexData>, greater<VertexData>> pq;
  set<string> visited;
  pq.push({0, startVertex});
  weights[startLabel] = 0;
  for (auto &edge : startVertex->edges) {
    weights[edge->to->label] = INT_MAX;
    pq.push({INT_MAX, edge->to});
  }
  while (!pq.empty()) {
    VertexData curr = pq.top();
    pq.pop();
    Vertex *currVertex = curr.second;
    for (int i = 0; i < currVertex->edges.size(); i++) {
      Vertex *neighbour = currVertex->edges[i]->to;
      if (!neighbour->edges.empty()) {
        for (auto &edge : neighbour->edges) {
          if (weights.find(edge->to->label) == weights.end()) {
            weights[edge->to->label] = INT_MAX;
            pq.push({INT_MAX, edge->to});
          }
        }
      }
      int newWeight = weights.find(currVertex->label)->second +
                      currVertex->edges[i]->weight;
      int oldWeight = weights.find(neighbour->label)->second;
      if (newWeight < oldWeight) {
        weights[neighbour->label] = newWeight;
        previous[neighbour->label] = currVertex->label;
        pq.push({newWeight, neighbour});
      }
    }
  }
  weights.erase(startLabel);
  return make_pair(weights, previous);
}

// minimum spanning tree using Prim's algorithm
int Graph::mstPrim(const string &startLabel,
                   void visit(const string &from, const string &to,
                              int weight)) const {

  if (graph.find(startLabel) == graph.end()) {
    return -1;
  }
  int totalWeight = 0;
  set<string> visitedLabels;
  visitedLabels.insert(startLabel);

  using EdgeData = pair<int, Edge *>;
  priority_queue<EdgeData, vector<EdgeData>, greater<EdgeData>> pq;
  for (auto &e : graph.find(startLabel)->second->edges) {
    pq.push({e->weight, e});
  }
  while (!pq.empty()) {
    EdgeData curr = pq.top();
    pq.pop();
    int currWeight = curr.first;
    Edge *currEdge = curr.second;
    string currFromLabel = currEdge->from->label;
    string currToLabel = currEdge->to->label;
    if (visitedLabels.find(currToLabel) == visitedLabels.end()) {
      visitedLabels.insert(currToLabel);
      totalWeight += currWeight;
      visit(currFromLabel, currToLabel, currWeight);
      for (auto &e : graph.find(currToLabel)->second->edges) {
        if (visitedLabels.find(e->to->label) == visitedLabels.end()) {
          pq.push({e->weight, e});
        }
      }
    }
  }
  return totalWeight;
}

// // minimum spanning tree using Prim's algorithm
// int Graph::mstKruskal(const string &startLabel,
//                       void visit(const string &from, const string &to,
//                                  int weight)) const {}

// read a text file and create the graph
bool Graph::readFile(const string &filename) {
  ifstream file(filename);
  if (!file) {
    cerr << "Error: Cannot open file " << filename << endl;
    return false;
  }
  string line;
  string fromVertex;
  string toVertex;
  int weight;
  while (getline(file, line)) {
    istringstream iss(line);
    if (iss >> fromVertex >> toVertex >> weight) {
      connect(fromVertex, toVertex, weight);
    }
  }
  file.close();
  return true;
}

// Given a label for a vertex, this function returns a map containing
// the labels of all vertices that the vertex is connected to, along
// with the weight of the edge connecting them. If the label is not found
// in the graph, an empty map is returned and an error message is printed.
map<string, int> Graph::edgeHelperFunction(const string &label) const {
  // Find the vertex in the graph with the given label.
  auto it = graph.find(label);
  if (it == graph.end()) {
    cerr << "Vertex " << label << " not found in graph." << endl;
    return {};
  }
  const Vertex *vertex = it->second;
  // Create a map to store the results
  map<string, int> result;
  // For each edge connected to the vertex, add the label of the connected
  // vertex and the weight of the edge to the result map
  for (const auto &edge : vertex->edges) {
    result[edge->to->label] = edge->weight;
  }
  // Return the map containing the labels and weights of all edges connected
  // to the vertex with the given label
  return result;
}
