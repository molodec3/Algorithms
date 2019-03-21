#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

class Graph {
public:
    Graph(int vertices);
    void AddEdge(int first, int second);
    int FindMinCycle();

private:
    int BFS(int vertex);
    int vertices_count_;
    std::vector<std::unordered_set<int>> graph_;
    std::vector<int> if_visited_;
    std::vector<int> distance_;
    std::vector<int> parents_;
};

Graph::Graph(int vertices) :
    vertices_count_(vertices),
    graph_(vertices),
    parents_(vertices)
{}

void Graph::AddEdge(int first, int second) {
    graph_[first].insert(second);
    graph_[second].insert(first);
}

int Graph::BFS(int vertex) {
    int visited = 1;
    std::queue<int> order;
    order.push(vertex);
    parents_[vertex] = -1;
    while (!order.empty()) {
        int current_vertex = order.front();
        order.pop();
        if (parents_[current_vertex] != -1) {
            distance_[current_vertex] = (distance_[parents_[current_vertex]] + 1);
        }
        if_visited_[current_vertex] = visited;
        for (auto child : graph_[current_vertex]) {
            parents_[child] = current_vertex;
            if (child != parents_[current_vertex] && !if_visited_[child]) {
                order.push(child);
            }
            else if (child != parents_[current_vertex] && if_visited_[child]) {
                return distance_[current_vertex] + distance_[child] + 1;
            }
        }
    }
    return -1;
}

int Graph::FindMinCycle() {
    int result = 1000000009;
    for (int vertex = 0; vertex < vertices_count_; ++ vertex) {
        if_visited_.clear();
        if_visited_.resize(vertices_count_);
        distance_.clear();
        distance_.resize(vertices_count_);
        parents_.clear();
        parents_.resize(vertices_count_);
        int current_cycle = 0;
        current_cycle = BFS(vertex);
        if (result > current_cycle && current_cycle > 3) {
            result = current_cycle;
        }
        else if (current_cycle == 3) {
            return 3;
        }
    }
    return (result == 1000000009 ? -1 : result);
}

int main() {
    int vertices = 0, connections = 0, result = 0;
    std::cin >> vertices >> connections;
    Graph* graph = new Graph(vertices);
    for (int i = 0; i < connections; ++i) {
        int first = 0, second = 0;
        std::cin >> first >> second;
        graph->AddEdge(first, second);
    }
    result = graph->FindMinCycle();
    std::cout << result << std::endl;
    delete(graph);
    return 0;
}