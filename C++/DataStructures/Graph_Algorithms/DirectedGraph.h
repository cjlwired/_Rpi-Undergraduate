// Carlos Lazo
// 10-31-05
// DSA Homework #6

/* header file for DirectedGraph class */

#include <iostream>
#include <vector>
#include "Vertex.h"

class DirectedGraph
{

public:
	/* Constructor/Destructor */
	DirectedGraph() : _size(0) {}
	DirectedGraph(const DirectedGraph& dg);
	~DirectedGraph() {}

	DirectedGraph& operator=(const DirectedGraph& dg);

	/* Vertex functions */
	int addVertex();
	bool containsVertex(int index);

	/* Edge functions */
	void addEdge(int src, int dest, int weight);
	void removeEdge(int src, int dest);
	bool containsEdge(int src, int dest);
	int getEdgeWeight(int src, int dest);

	/* general functions */
	void printVertex(int index);
	void printAll();
	int size();

	/* Member variables */

	std::vector<vertex> verts;
	int _size;
};
