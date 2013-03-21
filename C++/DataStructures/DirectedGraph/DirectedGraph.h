// Carlos Lazo
// DSA Assignment #5

#include <iostream>
#include <list>
#include <vector>

#ifndef DirectedGraph_H
#define DirectedGraph_H

using namespace std;

struct Node
{
	int vertex;
	int weight;
};

class DirectedGraph
{
	private:	
		vector<list<Node> > adj_list;

	public:	
		DirectedGraph();
		~DirectedGraph();

		int addVertex();
		bool containsVertex(int index);
		void addEdge(int source, int destination, int weight);
		void removeEdge(int source, int destination);
		bool containsEdge(int source, int destination);
		int getEdgeWeight(int source, int destination);
		void printVertex(int index);
		void printAll();
		int size();
};

#endif

