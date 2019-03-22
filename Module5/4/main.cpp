#include <iostream>
#include <set>
#include <vector>
#include <queue>

class Graph {
 public:
  Graph(unsigned int vertices);
  void AddEdge(int first, int second);
  bool IfBipartite(int vertex);

 private:
  std::vector<std::vector<int>> graph_;
  std::vector<int> visited_;
  std::vector<int> colour_;
};

Graph::Graph(unsigned int vertices) :
        colour_(vertices),
        graph_(vertices),
        visited_(vertices)
{}

void Graph::AddEdge(int first, int second) {
  graph_[first].emplace_back(second);
  graph_[second].emplace_back(first);
}

bool Graph::IfBipartite(int vertex) {
  visited_[vertex] = 1;
  for (int child : graph_[vertex]) {
    if (!visited_[child]) {
      colour_[child] = !colour_[vertex];
      if (!IfBipartite(child)) {
        return false;
      }
    }
    else if (colour_[child] == colour_[vertex]) {
      return false;
    }
  }
  return true;
}

int main() {
  int vertices = 0, connections = 0;
  std::cin >> vertices >> connections;
  Graph* graph = new Graph(vertices);
  for (int i = 0; i < connections; ++i) {
    int from = 0, to = 0;
    std::cin >> from >> to;
    graph->AddEdge(from, to);
  }
  std::cout << (graph->IfBipartite(0) ? "YES" : "NO") << std::endl;
  delete(graph);
  return 0;
}