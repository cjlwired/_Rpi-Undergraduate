#ifndef GRAPHHELPER_H
#define GRAPHHELPER_H

#include <vector>
#include "vertex.h"
#include "DirectedGraph.h"
#include "UndirectedGraph.h"


class GraphHelper
{
  private:
    void initializeSingleSource(int size, std::vector<vertex_t> &dists, int start);

    void relax(std::vector<vertex_t> &dists, int u, int v, int w);

    DirectedGraph buildTree(DirectedGraph g, std::vector<vertex_t> &dists);

    UndirectedGraph buildTree(UndirectedGraph g, std::vector<vertex_t> &dists);

  public:
    /* Default Constructor (do nothing) */
    GraphHelper() {}

    /* Calculate shortest paths (Dijkstra's Algorithm) */
    DirectedGraph dijkstraSP(DirectedGraph g, int start);

    /* Calculate a minimum spanning tree (Prim's Algorithm) */
    UndirectedGraph primMST(UndirectedGraph g, int start);
};

#endif

