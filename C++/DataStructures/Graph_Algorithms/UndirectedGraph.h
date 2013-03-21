/* header file for UndirectedGraph class */

#include <iostream>
#include <vector>

class UndirectedGraph
{
	class edge
	{
	public:
		edge() : src(0), dest(0), weight(0) {}
		edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
		int src;
		int dest;
		int weight;
	};

	class vertex
	{
	public:
		std::vector<edge> edges;
	};
public:
	/* Constructor/Destructor */
	UndirectedGraph() : _size(0) {}
	UndirectedGraph(const UndirectedGraph& dg);
	~UndirectedGraph() {}

	UndirectedGraph& operator=(const UndirectedGraph& dg);

	/* Vertex functions */
	int addVertex();
	bool containsVertex(int index);

	/* Edge functions */
	void addEdge(int src, int dest, int weight);
	void removeEdge(int src, int dest);
	bool containsEdge(int src, int dest);
	int getEdgeWeight(int src, int dest);
  int totalWeight();
  std::vector<int> getAdjList(int v);
 
	/* general functions */
	void printVertex(int index);
	void printAll();
	int size();

private:
	std::vector<vertex> verts;
	int _size;
};
