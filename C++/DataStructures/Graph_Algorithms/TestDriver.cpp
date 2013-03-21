#include <iostream>
#include <fstream>

#include "GraphHelper.h"

using namespace std;

/* Load an UndirectedGraph object from the specified data file */
int loadUndirectedGraph(char *data, UndirectedGraph *g)
{
  int n, s, u, v, w;
  
  /* Open the datafile for reading */
  ifstream in(data);
  if (!in.is_open()) {
    return -1;
  }
  
  /* Initialize the graph's vertices */
  in >> n;
  for (int i = 0; i < n; i++) {
    g->addVertex();
  }

  /* Load the starting vertex */
  in >> s;

  /* Load all the edges and weights */
  while (in >> u >> v >> w) {
    g->addEdge(u, v, w);
  }
  return s;
}

/* Load a DirectedGraph object from the specified data file */
int loadDirectedGraph(char *data, DirectedGraph *g)
{
  int n, s, u, v, w;
  
  /* Open the datafile for reading */
  ifstream in(data);
  if (!in.is_open()) {
    return -1;
  }
  
  /* Initialize the graph's vertices */
  in >> n;
  for (int i = 0; i < n; i++) {
    g->addVertex();
  }

  /* Load the starting vertex */
  in >> s;
  
  /* Load all the edges and weights */
  while (in >> u >> v >> w) {
    g->addEdge(u, v, w);
  }
  return s;
}

int main(int argc, char *argv[])
{
  GraphHelper helper;
  DirectedGraph digraph, sp;
  UndirectedGraph ugraph, mst;
  int start;
  
  /* Get the name of the graph file from the command line */
  if (argc != 2) {
    cout << "usage: " << argv[0] << " <graphfile>" << endl;
    return -1;
  }

  /* Load the directed graph */
  if ((start = loadDirectedGraph(argv[1], &digraph)) < 0) {
    cout << "Error loading directed graph from " << argv[1] << endl;
    return -1;
  }
  cout << "** Loaded Directed Graph **" << endl;
  digraph.printAll();
  cout << endl;
  
  /* Compute shortest paths (Dijkstra's algorithm) */
  sp = helper.dijkstraSP(digraph, start);
  cout << "** Shortest Paths From Vertex " << start << endl;
  sp.printAll();
  cout << endl;
  
  /* Load the undirected graph */
  if ((start = loadUndirectedGraph(argv[1], &ugraph)) < 0) {
    cout << "Error loading undirected graph from " << argv[1] << endl;
    return -1;
  }
  cout << "** Loaded Undirected Graph **" << endl;
  ugraph.printAll();
  cout << endl;
  
  /* Compute the minimum spanning tree (Prim's algorithm) */
  mst = helper.primMST(ugraph, start);
  cout << "** Minimum Spanning Tree **" << endl;
  mst.printAll();
  cout << "MST Weight = " << mst.totalWeight() << endl;

  return 0;
}
