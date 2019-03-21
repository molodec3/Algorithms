//
// Created by andrey on 2/15/19.
//

#include "headers/MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertices) :
    vertices_count_(vertices),
    connected_vertices_(vertices)
{}

MatrixGraph::MatrixGraph(const IGraph* graph) {
    MatrixGraph* matrix_graph = dynamic_cast<MatrixGraph*>(const_cast<IGraph*>(graph));
    if (matrix_graph == nullptr) {
        *this = *matrix_graph;
        return;
    }
    vertices_count_ = graph->GetVerticesCount();
    connected_vertices_.resize(vertices_count_);
    for (int vertex = 0; vertex < vertices_count_; ++vertex) {
        std::vector<int> children;
        graph->GetNextVertices(vertex, children);
        for (int count_children = 0; count_children < children.size(); ++count_children) {
            AddEdge(vertex, children[count_children]);
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    connected_vertices_[from][to] = true;
}

int MatrixGraph::GetVerticesCount() const {
    return vertices_count_;
}

void MatrixGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    for (int child = 0; child < vertices_count_; ++child) {
        if (connected_vertices_[vertex][child]) {
            vertices.emplace_back(child);
        }
    }
}

void MatrixGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    for (int parent = 0; parent < vertices_count_; ++parent) {
        if (connected_vertices_[parent][vertex]) {
            vertices.emplace_back(parent);
        }
    }
}
