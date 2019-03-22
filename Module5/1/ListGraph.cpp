//
// Created by andrey on 2/12/19.
//

#include "headers/ListGraph.h"

ListGraph::ListGraph(int vertices) :
    vertices_count_(vertices),
    next_vertices_(vertices),
    prev_vertices_(vertices)
{}

ListGraph::ListGraph(const IGraph* graph) {
    ListGraph* list_graph = dynamic_cast<ListGraph*>(const_cast<IGraph*>(graph));
    if (list_graph == nullptr) {
        *this = *list_graph;
        return;
    }
    vertices_count_ = graph->GetVerticesCount();
    next_vertices_.resize(vertices_count_);//graph->GetVerticesCount());
    prev_vertices_.resize(vertices_count_);//graph->GetVerticesCount());
    for (int vertex = 0; vertex < GetVerticesCount(); ++vertex) {
        graph->GetNextVertices(vertex, next_vertices_[vertex]);
        graph->GetPrevVertices(vertex, prev_vertices_[vertex]);
    }
}

void ListGraph::AddEdge(int from, int to) {
    next_vertices_[from].emplace_back(to);
    prev_vertices_[to].emplace_back(from);
}

int ListGraph::GetVerticesCount() const {
    return vertices_count_;
}

void ListGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    vertices = next_vertices_[vertex];
}

void ListGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    vertices = prev_vertices_[vertex];
}