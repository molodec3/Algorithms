#include <math.h>
#include <iostream>
#include <vector>

const double max_int = 1e9 + 9;

struct Edge {
  int first;
  int second;
  double weight;
};

class Graph {
 public:
  Graph(int vertices);
  void AddPaths(int from, std::vector<double>& connected_vertices);
  bool FindNegCycle(int vertex);

 private:
  std::vector<std::vector<double>> graph_;
  std::vector<double> distance_;
  std::vector<Edge> edges_;
};

Graph::Graph(int vertices) {
  graph_.resize(vertices);
  std::vector<double> dist(vertices, max_int);
  distance_ = dist;
  for (int i = 0; i < vertices; ++i) {
    graph_[i].resize(vertices);
  }
}

void Graph::AddPaths(int from, std::vector<double>& connected_vertices) {
  graph_[from] = connected_vertices;
  for (int to = 0; to < graph_.size(); ++to) {
    if (connected_vertices[to] != 0 && from != to) {
      Edge edge;
      edge.first = from;
      edge.second = to;
      edge.weight = connected_vertices[to];
      edges_.emplace_back(edge);
    }
  }
}

bool Graph::FindNegCycle(int vertex) {
  distance_[vertex] = 0;
  int n = 0;
  n = graph_.size();
  for (int i = 0; i < n - 1; ++i) {
    for (auto edge : edges_) {
      if (distance_[edge.second] > distance_[edge.first] + edge.weight) {
        distance_[edge.second] = distance_[edge.first] + edge.weight;
      }
    }
  }
  for (auto edge : edges_) {
    if (distance_[edge.second] > distance_[edge.first] + edge.weight) {
      return true;
    }
  }
  return false;
}

int main() {
  int vertices = 0;
  std::cin >> vertices;
  Graph* graph = new Graph(vertices);
  for (int i = 0; i < vertices; ++i) {
    std::vector<double> paths;
    for (int j = 0; j < vertices; ++j) {
      double weight = 0;
      if (i != j) {
        std::cin >> weight;
        weight > 0 ? paths.emplace_back(-log(weight)) : paths.emplace_back(0);
      } else {
        paths.emplace_back(0);
      }
    }
    graph->AddPaths(i, paths);
  }
  std::cout << (graph->FindNegCycle(0) ? "YES" : "NO") << std::endl;
  return 0;
}