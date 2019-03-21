#include <iostream>
#include <set>
#include <vector>
#include <queue>

class Graph {
public:
    Graph(unsigned int vertices);
    void AddEdge(int first, int second);
    int BFS(int vertex, int destination);

private:
    std::vector<std::vector<int>> graph_;
    std::vector<int> count_paths_;
    std::vector<int> distance_;
};

Graph::Graph(unsigned int vertices) :
        count_paths_(vertices),
        graph_(vertices),
        distance_(vertices)
{}

void Graph::AddEdge(int first, int second) {
    graph_[first].emplace_back(second);
    graph_[second].emplace_back(first);
}

int Graph::BFS(int vertex, int destination) {
    count_paths_[vertex] = 1;
    std::queue<int> order;
    order.push(vertex);
    while (!order.empty()) {
        int current_vertex = order.front();
        order.pop();
        for (auto child : graph_[current_vertex]) {
            if (count_paths_[child] == 0) {
                order.push(child);
                count_paths_[child] = count_paths_[current_vertex];
                distance_[child] = distance_[current_vertex] + 1;
            }
            else if (distance_[child] == distance_[current_vertex] + 1) {
                count_paths_[child] += count_paths_[current_vertex];
            }
        }
    }
    return count_paths_[destination];
}

int main() {
    unsigned int vertices = 0, connections = 0;
    std::cin >> vertices >> connections;
    Graph* graph = new Graph(vertices);
    for (int i = 0; i < connections; ++i) {
        int first = 0, second = 0;
        std::cin >> first >> second;
        graph->AddEdge(first, second);
    }
    int from = 0, to = 0;
    std::cin >> from >> to;
    int result = graph->BFS(from, to);
    std::cout << result << std::endl;
    return 0;
}