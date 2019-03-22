//
// Created by andrey on 2/15/19.
//

#ifndef INC_1_ARCGRAPH_H
#define INC_1_ARCGRAPH_H

#include "../IGraph.h"
#include <vector>

class ArcGraph : public IGraph {
public:
    ArcGraph(int vertices);
    ArcGraph(IGraph* graph);
    virtual void AddEdge(int from, int to);
    virtual int GetVerticesCount() const;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const;

private:
    int vertices_count_;
    std::vector<std::pair<int, int>> connected_vertices_;
};

#endif //INC_1_ARCGRAPH_H
