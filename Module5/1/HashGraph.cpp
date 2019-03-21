//
// Created by andrey on 2/15/19.
//

#include "headers/HashGraph.h"

HashGraph::HashGraph(int vertices) :
    vertices_count_(vertices),
    next_vertices_(vertices),
    prev_vertices_(vertices)
{}

HashGraph::HashGraph(IGraph* graph) {
    HashGraph* hash_graph = dynamic_cast<HashGraph*>(const_cast<IGraph*>(graph));
    if (hash_graph == nullptr) {
        *this = *hash_graph;
        return;
    }
    vertices_count_ = graph->GetVerticesCount();
    next_vertices_.resize(vertices_count_);
    prev_vertices_.resize(vertices_count_);
    for (int vertex = 0; vertex < vertices_count_; ++vertex) {
        std::vector<int> children;
        graph->GetNextVertices(vertex, children);
        for (int count_children = 0; count_children < children.size(); ++count_children) {
            AddEdge(vertex, children[count_children]);
        }
    }
}

void HashGraph::AddEdge(int from, int to) {
    next_vertices_[from].insert(to);
    prev_vertices_[to].insert(from);
}

int HashGraph::GetVerticesCount() const {
    return vertices_count_;
}

void HashGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    for (auto child : next_vertices_[vertex]) {
        vertices.emplace_back(child);
    }
}

void HashGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    for (auto parent : prev_vertices_[vertex]) {
        vertices.emplace_back(parent);
    }
}