//
// Created by andrey on 2/12/19.
//

#ifndef INC_1_IGRAPH_H
#define INC_1_IGRAPH_H

#include <vector>

class IGraph {
public:
    virtual ~IGraph() {}
    virtual void AddEdge(int from, int to) = 0;
    virtual int GetVerticesCount() const = 0;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
};

#endif //INC_1_IGRAPH_H
