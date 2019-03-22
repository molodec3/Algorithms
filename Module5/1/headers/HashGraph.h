//
// Created by andrey on 2/15/19.
//

#ifndef INC_1_SETGRAPH_H
#define INC_1_SETGRAPH_H

#include "../IGraph.h"
#include <unordered_set>
#include <vector>

class HashGraph : public IGraph {
public:
    HashGraph(int vertices);
    HashGraph(IGraph* graph);
    virtual void AddEdge(int from, int to);
    virtual int GetVerticesCount() const;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const;

private:
    int vertices_count_;
    std::vector<std::unordered_set<int>> next_vertices_;
    std::vector<std::unordered_set<int>> prev_vertices_;
};

#endif //INC_1_SETGRAPH_H
