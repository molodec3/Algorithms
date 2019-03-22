#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>
#include <stack>
#include <queue>

class Graph {
public:
    Graph(int vertices);
    void AddEdge(int first, int second);
    bool IfPlanar();

private:
    void CycleDFS(int vertex, int parent, int& flag);
    void DFS(int vertex, int parent);
    bool FindCycle();
    bool GammaDivisionReversed(std::deque<int>& path);
    bool GammaDivision(std::deque<int>& path); //making path clear
    bool SegmentationReversed();
    bool Segmentation();
    void FillCycleEdges(std::deque<int>& vertices);
    void FindStart(int& start, int& end, int i);
    std::vector<std::vector<int>> graph_;
    std::vector<int> colour_;
    std::vector<int> visited_;
    std::stack<int> cycle_;
    std::vector<std::unordered_set<int>> gammas_;
    std::vector<std::deque<int>> ordered_gammas_; //gamma is face Г
    std::unordered_set<int> big_cycle_; //set of verticies included in new graph
    std::set<std::pair<int, int>> cycle_edges_;
    std::set<std::pair<int, int>> tree_edges_;
    std::set<std::pair<int, int>> back_edges_;
    std::queue<std::pair<int, int>> order_tree_edges_;
    std::queue<std::pair<int, int>> order_back_edges_;
};

Graph::Graph(int vertices)
        : graph_(vertices), colour_(vertices), visited_(vertices) {}

void Graph::AddEdge(int first, int second) {
    graph_[first].emplace_back(second);
    graph_[second].emplace_back(first);
}

void Graph::FillCycleEdges(std::deque<int>& vertices) {
    int first_vertex = vertices.front();
    int size = vertices.size();
    int first = vertices.front();
    vertices.pop_front();
    for (int i = 0; i < size - 1; ++i) {
        int second = vertices.front();
        vertices.pop_front();
        cycle_edges_.insert(std::make_pair(first, second));
        cycle_edges_.insert(std::make_pair(second, first));
        first = second;
    }
    cycle_edges_.insert(std::make_pair(first_vertex, first));
    cycle_edges_.insert(std::make_pair(first, first_vertex));
}

void Graph::CycleDFS(int vertex, int parent, int& flag) {
    visited_[vertex] = 1;
    cycle_.push(vertex);
    for (int child : graph_[vertex]) {
        if (visited_[child] == 0) {
            CycleDFS(child, vertex, flag);
            if (flag == 1) {
                return;
            }
        } else if (child != parent) {
            cycle_.push(child);
            flag = 1;
            return;
        }
    }
}

bool Graph::FindCycle() {
    int flag = 0;
    std::deque<int> current_gamma;
    std::unordered_set<int> unordered_gamma;
    CycleDFS(0, -1, flag);
    int last_vertex = 0;
    last_vertex = cycle_.top();
    cycle_.pop();
    while (!cycle_.empty()) {
        int current_vertex = 0;
        current_vertex = cycle_.top();
        cycle_.pop();
        big_cycle_.insert(current_vertex);
        current_gamma.push_front(current_vertex);
        unordered_gamma.insert(current_vertex);
        if (current_vertex == last_vertex) {
            gammas_.emplace_back(unordered_gamma);
            gammas_.emplace_back(unordered_gamma);
            ordered_gammas_.emplace_back(current_gamma);
            ordered_gammas_.emplace_back(current_gamma);
            FillCycleEdges(current_gamma);
            return true;
        }
    }
    return false;
}

void Graph::DFS(int vertex, int parent) {
    visited_[vertex] = 1;
    for (int child : graph_[vertex]) {
        if (big_cycle_.count(child) == 0) {
            if (visited_[child] == 0) {
                tree_edges_.insert(std::make_pair(vertex, child));
                order_tree_edges_.push(std::make_pair(vertex, child));
                DFS(child, vertex);
            } else if (child != parent &&
                       back_edges_.count(std::make_pair(child, vertex)) == 0) {
                back_edges_.insert(std::make_pair(vertex, child));
                order_back_edges_.push(std::make_pair(vertex, child));
            }
        } else if (child != parent &&
                   cycle_edges_.count(std::make_pair(vertex, child)) == 0 &&
                   cycle_edges_.count(std::make_pair(child, vertex)) == 0) {
            back_edges_.insert(std::make_pair(vertex, child));
            order_back_edges_.push(std::make_pair(vertex, child));
        } /*else if (child != parent) {
            if (visited_[child] == 0) {
                DFS(child, vertex);
            }
        }*/
    }
}

bool Graph::SegmentationReversed() {
    std::deque<int> path;
    while (!order_back_edges_.empty()) {
        std::pair<int, int> current_edge;
        std::pair<int, int> current_back_edge;
        if (path.empty()) {
            current_edge = order_back_edges_.front();
            while (big_cycle_.count(current_edge.first) != 0 &&
                   big_cycle_.count(current_edge.second) != 0 &&
                   !order_back_edges_.empty()) {
                path.push_back(current_edge.first);
                path.push_back(current_edge.second);
                if (!GammaDivisionReversed(path)) {
                    return false;
                }
                order_back_edges_.pop();
                current_edge = order_back_edges_.front();
            }
        }
        if (order_back_edges_.empty()) {
            break;
        }
        current_edge = order_tree_edges_.front();
        current_back_edge = order_back_edges_.front();
        while (current_edge.second != current_back_edge.first /*&& big_cycle_.count(current_back_edge.second) != 0*/) {
            path.push_back(current_edge.first);
            order_tree_edges_.pop();
            current_edge = order_tree_edges_.front();
        }
        order_tree_edges_.pop();
        if (current_edge.second == current_back_edge.first /*&& big_cycle_.count(current_back_edge.second) != 0*/) {
            path.push_back(current_edge.first);
            path.push_back(current_back_edge.first);
            path.push_back(current_back_edge.second);
            order_back_edges_.pop();
            if (!GammaDivisionReversed(path)) {
                return false;
            }
        }
    }
    return true;
}

bool Graph::Segmentation() {
    std::deque<int> path;
    while (!order_back_edges_.empty()) {
        std::pair<int, int> current_edge;
        std::pair<int, int> current_back_edge;
        if (path.empty()) {
            current_edge = order_back_edges_.front();
            while (big_cycle_.count(current_edge.first) != 0 &&
                   big_cycle_.count(current_edge.second) != 0 &&
                   !order_back_edges_.empty()) {
                path.push_back(current_edge.first);
                path.push_back(current_edge.second);
                if (!GammaDivision(path)) {
                    return false;
                }
                order_back_edges_.pop();
                current_edge = order_back_edges_.front();
            }
        }
        if (order_back_edges_.empty()) {
            break;
        }
        current_edge = order_tree_edges_.front();
        current_back_edge = order_back_edges_.front();
        while (current_edge.second != current_back_edge.first /*&& big_cycle_.count(current_back_edge.second) != 0*/) {
            path.push_back(current_edge.first);
            order_tree_edges_.pop();
            current_edge = order_tree_edges_.front();
        }
        order_tree_edges_.pop();
        if (current_edge.second == current_back_edge.first /*&& big_cycle_.count(current_back_edge.second) != 0*/) {
            path.push_back(current_edge.first);
            path.push_back(current_back_edge.first);
            path.push_back(current_back_edge.second);
            order_back_edges_.pop();
            if (!GammaDivision(path)) {
                return false;
            }
        }
    }
    return true;
}

void Graph::FindStart(int& start, int& end, int i) {
    int current_vertex = 0;
    std::deque<int> needed_gamma;
    needed_gamma = ordered_gammas_[i];
    current_vertex = needed_gamma.front();
    needed_gamma.pop_front();
    while (current_vertex != start && current_vertex != end) {
        current_vertex = needed_gamma.front();
        needed_gamma.pop_front();
    }
    if (current_vertex == end) {
        int tmp = 0;
        tmp = end;
        end = start;
        start = tmp;
    }
}

bool Graph::GammaDivisionReversed(std::deque<int>& path) {
    std::deque<int> ordered_gamma_1;
    std::deque<int> ordered_gamma_2;
    std::unordered_set<int> gamma_1;
    std::unordered_set<int> gamma_2;
    std::deque<int> second_path = path;
    int start = 0;
    int end = 0;
    start = path.front();
    end = path.back();
    for (int i = gammas_.size() - 1; i >= 0; --i) {
        if (gammas_[i].count(start) != 0 && gammas_[i].count(end) != 0) {
            FindStart(start, end, i);
            while (ordered_gammas_[i].front() != start) {
                ordered_gamma_1.push_back(ordered_gammas_[i].front());
                gamma_1.insert(ordered_gammas_[i].front());
                big_cycle_.insert(ordered_gammas_[i].front());
                ordered_gammas_[i].pop_front();
            }
            for (int j = 0; j < second_path.size() - 1; ++j) {
                ordered_gamma_1.push_back(path.front());
                gamma_1.insert(path.front());
                big_cycle_.insert(path.front());
                path.pop_front();
            }
            while (ordered_gammas_[i].front() != end) {
                ordered_gamma_2.push_back(ordered_gammas_[i].front());
                gamma_2.insert(ordered_gammas_[i].front());
                ordered_gammas_[i].pop_front();
            }
            path = second_path;
            for (int j = 0; j < second_path.size() - 1; ++j) {
                ordered_gamma_2.push_back(path.back());
                gamma_2.insert(path.back());
                path.pop_back();
            }
            while (!ordered_gammas_[i].empty()) {
                ordered_gamma_1.push_back(ordered_gammas_[i].front());
                gamma_1.insert(ordered_gammas_[i].front());
                big_cycle_.insert(ordered_gammas_[i].front());
                ordered_gammas_[i].pop_front();
            }
            gammas_[i] = gamma_1;
            gammas_.emplace_back(gamma_2);
            ordered_gammas_[i] = ordered_gamma_1;
            ordered_gammas_.emplace_back(ordered_gamma_2);
            path.clear();
            return true;
        }
    }
    return false;
}

bool Graph::GammaDivision(std::deque<int>& path) {
    std::deque<int> ordered_gamma_1;
    std::deque<int> ordered_gamma_2;
    std::unordered_set<int> gamma_1;
    std::unordered_set<int> gamma_2;
    std::deque<int> second_path = path;
    int start = 0;
    int end = 0;
    start = path.front();
    end = path.back();
    for (int i = 0; i < gammas_.size(); ++i) {
        if (gammas_[i].count(start) != 0 && gammas_[i].count(end) != 0) {
            FindStart(start, end, i);
            while (ordered_gammas_[i].front() != start) {
                ordered_gamma_1.push_back(ordered_gammas_[i].front());
                gamma_1.insert(ordered_gammas_[i].front());
                big_cycle_.insert(ordered_gammas_[i].front());
                ordered_gammas_[i].pop_front();
            }
            for (int j = 0; j < second_path.size() - 1; ++j) {
                ordered_gamma_1.push_back(path.front());
                gamma_1.insert(path.front());
                big_cycle_.insert(path.front());
                path.pop_front();
            }
            while (ordered_gammas_[i].front() != end) {
                ordered_gamma_2.push_back(ordered_gammas_[i].front());
                gamma_2.insert(ordered_gammas_[i].front());
                ordered_gammas_[i].pop_front();
            }
            path = second_path;
            for (int j = 0; j < second_path.size() - 1; ++j) {
                ordered_gamma_2.push_back(path.back());
                gamma_2.insert(path.back());
                path.pop_back();
            }
            while (!ordered_gammas_[i].empty()) {
                ordered_gamma_1.push_back(ordered_gammas_[i].front());
                gamma_1.insert(ordered_gammas_[i].front());
                big_cycle_.insert(ordered_gammas_[i].front());
                ordered_gammas_[i].pop_front();
            }
            gammas_[i] = gamma_1;
            gammas_.emplace_back(gamma_2);
            ordered_gammas_[i] = ordered_gamma_1;
            ordered_gammas_.emplace_back(ordered_gamma_2);
            path.clear();
            return true;
        }
    }
    return false;
}

bool Graph::IfPlanar() {
    if (FindCycle()) {
        visited_.clear();
        visited_.resize(graph_.size());
        /*for (int vertex : big_cycle_) {
            DFS(vertex, -1);
        }*/
        DFS(*big_cycle_.begin(), -1);
        return (Segmentation() || SegmentationReversed());
    } else {
        return true;
    }
}

int main() {
    int vertices = 0;
    int connections = 0;
    std::cin >> vertices >> connections;
    if (connections > 3 * vertices - 6) {
        std::cout << "NO" << std::endl;
    } else {
        Graph *graph = new Graph(vertices);
        for (int connection = 0; connection < connections; ++connection) {
            int first = 0;
            int second = 0;
            std::cin >> first >> second;
            graph->AddEdge(first, second);
        }
        std::cout << (graph->IfPlanar() ? "YES" : "NO") << std::endl;
    }
    return 0;
}