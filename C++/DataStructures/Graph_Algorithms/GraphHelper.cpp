#include "MinPriorityQueue.h"
#include "GraphHelper.h"

#define INFINITY 99999999
#define NIL -1

using namespace std;

void GraphHelper::initializeSingleSource(int size, 
                                         vector<vertex_t> &dists, 
                                         int start)
{
  vertex_t v;
  v.dist = INFINITY;
  v.parent = NIL;
  
  for (int i = 0; i < size; i++) {
    v.id = i;
    dists.push_back(v);
  }
  dists[start].dist = 0;
}

void GraphHelper::relax(vector<vertex_t> &dists, int u, int v, int w)
{
  if (dists[v].dist > dists[u].dist + w) {
    dists[v].dist = dists[u].dist + w;
    dists[v].parent = u;
  }
}

DirectedGraph GraphHelper::buildTree(DirectedGraph g, vector<vertex_t> &dists)
{
  int u, v, w;
  DirectedGraph s;

  /* Add the necessary number of vertices */
  for (int i = 0; i < (int)dists.size(); i++) {
    s.addVertex();
  }

  /* Add the edges that exist in the shortest path tree */
  for (int i = 0; i < (int)dists.size(); i++) {
    u = dists[i].parent;
    if (u != NIL) {
      v = dists[i].id;
      w = g.getEdgeWeight(u, v);
      s.addEdge(u, v, w);
    }
  }
  return s;
}

UndirectedGraph GraphHelper::buildTree(UndirectedGraph g, vector<vertex_t> &dists)
{
  int u, v, w;
  UndirectedGraph s;

  /* Add the necessary number of vertices */
  for (int i = 0; i < (int)dists.size(); i++) {
    s.addVertex();
  }

  /* Add the edges that exist in the shortest path tree */
  for (int i = 0; i < (int)dists.size(); i++) {
    u = dists[i].parent;
    if (u != NIL) {
      v = dists[i].id;
      w = g.getEdgeWeight(u, v);
      s.addEdge(u, v, w);
    }
  }
  return s;
}

DirectedGraph GraphHelper::dijkstraSP(DirectedGraph g, int start)
{
  MinPriorityQueue q;
  vector<vertex_t> dists;
  vector<int> adj;
  vertex_t u;
 
  /* Initialize the shortest path estimates and priority queue */
  initializeSingleSource(g.size(), dists, start);
  for (int i = 0; i < g.size(); i++) {
    q.insert(dists[i]);
  }
  
  /* Find the shortest paths */ 
  while (q.size() != 0) {
    u = q.extract_min();
    adj = g.getAdjList(u.id);
    for (int i = 0; i < (int)adj.size(); i++) {
      relax(dists, u.id, adj[i], g.getEdgeWeight(u.id, adj[i]));
      q.decrease_key(dists[adj[i]]);
    }
  }

  /* Build a tree of shortest paths rooted at the starting node */
  return buildTree(g, dists);
}

UndirectedGraph GraphHelper::primMST(UndirectedGraph g, int start)
{
  MinPriorityQueue q;
  vector<vertex_t> keys;
  vector<int> adj;
  vertex u;
  int w;
  bool *set = new bool[g.size()];
  
  /* Initialize the set of keys and priority queue */
  initializeSingleSource(g.size(), keys, start);
  for (int i = 0; i < g.size(); i++) {
    q.insert(keys[i]);
    set[i] = true;
  }

  /* Compute the edges in a MST for g */
  while (q.size() != 0) {
    u = q.extract_min();
    set[u.id] = false;
    adj = g.getAdjList(u.id);
    for (int i = 0; i < (int)adj.size(); i++) {
      w = g.getEdgeWeight(u.id, adj[i]);
      if (set[adj[i]] && w < keys[adj[i]].dist) {
        keys[adj[i]].parent = u.id;
        keys[adj[i]].dist = w;
        q.decrease_key(keys[adj[i]]);
      }
    }
  }
  delete [] set;

  /* Return a graph representing the MST */
  return buildTree(g, keys);
}

