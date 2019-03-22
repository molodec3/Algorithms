//
// Created by andrey on 2/15/19.
//

#include "headers/ArcGraph.h"

ArcGraph::ArcGraph(int vertices) :
    vertices_count_(vertices)
{}

ArcGraph::ArcGraph(IGraph* graph) {
    ArcGraph* arc_graph = dynamic_cast<ArcGraph*>(const_cast<IGraph*>(graph));
    if (arc_graph == nullptr) {
        *this = *arc_graph;
        return;
    }
    vertices_count_ = graph->GetVerticesCount();
    for (int vertex = 0; vertex < vertices_count_; ++vertex) {
        std::vector<int> children;
        graph->GetNextVertices(vertex, children);
        for (int count_children = 0; count_children < children.size(); ++count_children) {
            AddEdge(vertex, children[count_children]);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    connected_vertices_.emplace_back(std::make_pair(from, to));
}

int ArcGraph::GetVerticesCount() const {
    return vertices_count_;
}

void ArcGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
    for (int connections = 0; connections < connected_vertices_.size(); ++connections) {
        if (connected_vertices_[connections].first == vertex) {
            vertices.emplace_back(connected_vertices_[connections].second);
        }
    }
}

void ArcGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
    for (int connections = 0; connections < connected_vertices_.size(); ++connections) {
        if (connected_vertices_[connections].second == vertex) {
            vertices.emplace_back(connected_vertices_[connections].first);
        }
    }
}