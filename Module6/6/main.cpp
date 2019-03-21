#include <iostream>
#include <vector>

class Graph {
 public:
  Graph(int vertices);
  void AddPaths(int from, std::vector<int>& connected_vertices);
  void PrintAns();

 private:
  std::vector<std::vector<int>> graph_;
  void CountMinPaths();
  std::vector<std::vector<int>> distance_;
};

Graph::Graph(int vertices) {
  graph_.resize(vertices);
  distance_.resize(vertices);
  for (int i = 0; i < vertices; ++i) {
    graph_[i].resize(vertices);
    distance_.resize(vertices);
  }
}

void Graph::AddPaths(int from, std::vector<int>& connected_vertices) {
  graph_[from] = connected_vertices;
}

void Graph::CountMinPaths() {
  int n = 0;
  n = graph_.size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        graph_[j][k] = std::min(graph_[j][k], graph_[j][i] + graph_[i][k]);
      }
    }
  }
}

void Graph::PrintAns() {
  CountMinPaths();
  int n = 0;
  n = graph_.size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << graph_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  int vertices = 0;
  std::cin >> vertices;
  Graph* graph = new Graph(vertices);
  for (int i = 0; i < vertices; ++i) {
    std::vector<int> connected_vertices;
    for (int j = 0; j < vertices; ++j) {
      int weight = 0;
      std::cin >> weight;
      connected_vertices.emplace_back(weight);
    }
    graph->AddPaths(i, connected_vertices);
  }
  graph->PrintAns();
  delete (graph);
  return 0;
}