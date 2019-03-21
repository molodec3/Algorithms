#include <iostream>
#include <map>
#include <queue>
#include <vector>

const int max_int = 1000000009;

class Graph {
 public:
  Graph(int vertices);
  void AddEdge(int from, int to, int weight);
  int CountAns(int from, int to);

 private:
  std::vector<std::vector<int>> graph_;
  void CountPaths(int vertex);
  bool CheckStraight(int first, int second);
  bool CheckReversed(int first, int second);
  void RelaxStraight(int first, int second);
  void RelaxReversed(int first, int second);
  std::map<std::pair<int, int>, int> edge_weight_;
  std::vector<int> distance_;
  std::vector<int> visited_;
};

Graph::Graph(int vertices)
    : graph_(vertices), distance_(vertices, max_int), visited_(vertices, 0) {}

void Graph::AddEdge(int from, int to, int weight) {
  graph_[from].emplace_back(to);
  graph_[to].emplace_back(from);
  if (edge_weight_.count(std::make_pair(from, to)) == 0 &&
      edge_weight_.count(std::make_pair(to, from)) == 0) {
    edge_weight_[std::make_pair(from, to)] = weight;
  } else if (edge_weight_.count(std::make_pair(from, to)) != 0) {
    if (weight < edge_weight_[std::make_pair(from, to)]) {
      edge_weight_[std::make_pair(from, to)] = weight;
    }
  } else {
    if (weight < edge_weight_[std::make_pair(to, from)]) {
      edge_weight_[std::make_pair(to, from)] = weight;
    }
  }
}

bool Graph::CheckStraight(int first, int second) {
  return distance_[first] >
         distance_[second] + edge_weight_[std::make_pair(first, second)];
}

bool Graph::CheckReversed(int first, int second) {
  return distance_[first] >
         distance_[second] + edge_weight_[std::make_pair(second, first)];
}

void Graph::RelaxStraight(int first, int second) {
  distance_[first] =
      distance_[second] + edge_weight_[std::make_pair(first, second)];
}

void Graph::RelaxReversed(int first, int second) {
  distance_[first] =
      distance_[second] + edge_weight_[std::make_pair(second, first)];
}

void Graph::CountPaths(int vertex) {
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      queue;
  queue.push(std::make_pair(0, vertex));
  distance_[vertex] = 0;
  while (!queue.empty()) {
    int current_vertex = queue.top().second;
    queue.pop();
    for (int child : graph_[current_vertex]) {
      if (edge_weight_.count(std::make_pair(current_vertex, child)) != 0) {
        if (CheckReversed(child, current_vertex)) {
          RelaxReversed(child, current_vertex);
          queue.push(std::make_pair(distance_[child], child));
        }
      } else {
        if (CheckStraight(child, current_vertex)) {
          RelaxStraight(child, current_vertex);
          queue.push(std::make_pair(distance_[child], child));
        }
      }
    }
  }
}

int Graph::CountAns(int from, int to) {
  CountPaths(from);
  return distance_[to];
}

int main() {
  int vertices = 0;
  int connections = 0;
  std::cin >> vertices >> connections;
  Graph* graph = new Graph(vertices);
  for (int i = 0; i < connections; ++i) {
    int first = 0;
    int second = 0;
    int weight = 0;
    std::cin >> first >> second >> weight;
    if (first != second) {
      graph->AddEdge(first, second, weight);
    }
  }
  int start = 0;
  int finish = 0;
  std::cin >> start >> finish;
  int ans = graph->CountAns(start, finish);
  std::cout << (ans == max_int ? -1 : ans) << std::endl;
  delete (graph);
  return 0;
}