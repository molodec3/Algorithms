//
// Created by andrey on 2/12/19.
//

#ifndef INC_1_LISTGRAPH_H
#define INC_1_LISTGRAPH_H

#include "../IGraph.h"

class ListGraph : public IGraph {
public:
    ListGraph(int vertices);
    ListGraph(const IGraph* graph);
    virtual void AddEdge(int from, int to);
    virtual int GetVerticesCount() const;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const;

private:
    int vertices_count_;
    std::vector<std::vector<int>> next_vertices_;
    std::vector<std::vector<int>> prev_vertices_;
};

#endif //INC_1_LISTGRAPH_H
