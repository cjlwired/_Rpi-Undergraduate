// Carlos Lazo
// 10-24-05
// DSA Homework #5

#include <iostream>
#include <list>
#include <vector>

#include "DirectedGraph.h"

using namespace std;

// Default Constructor

DirectedGraph::DirectedGraph()	{}

// Destructor

DirectedGraph::~DirectedGraph() {}

/*
	Function used to sort the individual adjacency lists.
															*/
	
bool sort_Node(Node n1, Node n2)
{
	return n1.vertex < n2.vertex;
}

// Add a new vertex to the graph.

int DirectedGraph::addVertex()
{
	adj_list.resize(adj_list.size() + 1);

	return adj_list.size() - 1;
}

// Check to see if the vertex exists in the graph.

bool DirectedGraph::containsVertex(int index)
{
	return (index < adj_list.size());
}

// Add an edge to the graph.

void DirectedGraph::addEdge(int source, int destination, int weight)
{

	// First check to see if the edge is already in the graph.

	Node insert;

	insert.vertex = destination;
	insert.weight = weight;

	bool check = true;

	list<Node>::iterator p;		// Beginning of list.
	list<Node>::iterator q;		// Used to store variable if Node is already there.

	for (p = adj_list[source].begin(); p != adj_list[source].end(); p++)
	{
		// If the edge is found, set flag to false.
		// This implies that the edge is already there.

		if (p->vertex == destination)
		{
			check = false;
			q = p;
		}
	}

	if (check)	// If the edge isn't already in the graph, add it.
		adj_list[source].push_back(insert);

	else		// If the edge was already in, simply change it's value.
		q->weight = weight;

}

// Remove an edge from the graph.

void DirectedGraph::removeEdge(int source, int destination)
{
	list<Node>::iterator p;		// Beginning of list.
	list<Node>::iterator q;		// Used to keep track of edge to be removed.

	for (p = adj_list[source].begin(); p != adj_list[source].end(); p++)
	{
		// If the edge is found, set the q pointer to that Node.

		if (p->vertex == destination)
			q = p;
	}

	// Remove edge from the adjacency list.

	adj_list[source].erase(q);
}

// Return true if the edge exists in the graph, false is non-existant.

bool DirectedGraph::containsEdge(int source, int destination)
{

	list<Node>::iterator p;

	// If the edge is found, then return true. If not, return false.

	for (p = adj_list[source].begin(); p != adj_list[source].end(); p++)
		if (p->vertex == destination)
			return true;

	return false;
}

// Return the weight of the edge.

int DirectedGraph::getEdgeWeight(int source, int destination)
{

	list<Node>::iterator p;

	// If the edge is found, return its weight. If not, return 0.

	for (p = adj_list[source].begin(); p != adj_list[source].end(); p++)
		if (p->vertex == destination)
			return p->weight;

	return 0;
	
}

// Print out the request vertex along with accompanying edges and weights.

void DirectedGraph::printVertex(int index)
{

	list<Node>::iterator p;

	cout << "Vertex "<< index << ": ";

	// Sort list.

	adj_list[index].sort(sort_Node);

	// Print out the edges pertaining to the vertex.

	for (p = adj_list[index].begin(); p != adj_list[index].end(); p++)
		cout << p->vertex << " (" << p->weight << "), ";

}

// Print out the entire graph.

void DirectedGraph::printAll()
{
	list<Node>::iterator p;

	for (int index = 0; index < adj_list.size(); index++)
	{

		// Sort list.

		adj_list[index].sort(sort_Node);

		cout << "Vertex " << index << ": ";


		for (p = adj_list[index].begin(); p != adj_list[index].end(); p++)
			cout << p->vertex << " (" << p->weight << "), ";

		cout << endl;
	}

}

// Return the size of the graph (vertices in graph).

int DirectedGraph::size()
{
	return adj_list.size();
}