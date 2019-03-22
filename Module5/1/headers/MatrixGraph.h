//
// Created by andrey on 2/13/19.
//

#ifndef INC_1_MATRIXGRAPH_H
#define INC_1_MATRIXGRAPH_H

#include "../IGraph.h"

class MatrixGraph : public IGraph {
public:
    MatrixGraph(int vertices);
    MatrixGraph(const IGraph* graph);
    virtual void AddEdge(int from, int to);
    virtual int GetVerticesCount() const;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const;

private:
    int vertices_count_;
    std::vector<std::vector<bool>> connected_vertices_;
};

#endif //INC_1_MATRIXGRAPH_H
