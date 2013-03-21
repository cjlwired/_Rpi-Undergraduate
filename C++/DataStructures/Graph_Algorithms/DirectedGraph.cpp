// Carlos Lazo
// 10-31-05
// DSA Homework #6

/* implementation file for DirectedGraph class */

#include "DirectedGraph.h"

/* copy constructor */
DirectedGraph::DirectedGraph(const DirectedGraph& dg)
{
	int i,j,len;

	const vertex* pv;

	_size = dg._size;
	
	/* loop through and copy all vertex information */
	for (i=0; i<_size; ++i)
	{
		verts.push_back(vertex());

		pv = &(dg.verts[i]);
		len = pv->edges.size();

		/* loop through edges */
		for (j=0; j<len; ++j)
			verts[i].edges.push_back(edge(i, pv->edges[j].dest,
					pv->edges[j].weight));
	}
}

/* assignment operator */
DirectedGraph& DirectedGraph::operator=(const DirectedGraph& dg)
{
	int i,j,len;

	const vertex* pv;

	_size = dg._size;

	verts.clear();
	
	/* loop through and copy all vertex information */
	for (i=0; i<_size; ++i)
	{
		verts.push_back(vertex());

		pv = &(dg.verts[i]);
		len = pv->edges.size();

		verts[i].edges.clear();

		/* loop through edges */
		for (j=0; j<len; ++j)
			verts[i].edges.push_back(edge(i, pv->edges[j].dest,
					pv->edges[j].weight));
	}

	return (*this);
}

/* add vertex specified by index */
int DirectedGraph::addVertex()
{
	int old_size = _size;
	
	verts.push_back(vertex());
	_size = verts.size();
	return old_size;
}

/* see if vertex specified by index exists */
bool DirectedGraph::containsVertex(int index)
{
	if (index < _size && index >= 0)
		return true;

	return false;
}

/* add edge specified by source and dest */
void DirectedGraph::addEdge(int src, int dest, int weight)
{
	int i, len;
	vertex* pv;
	
	/* simple check of input validity */
	if (src >= _size || dest >= _size || src < 0 || dest < 0)
		return;

	pv = &verts[src];
	len = pv->edges.size();
	
	
	/* check through all edges */
	for (i=0; i<len; ++i)
	{
		/* if it already exists, just change the weight */
		if (pv->edges[i].dest == dest)
		{
			pv->edges[i].weight = weight;
			return;
		}
	}

	/* if it doesn't exist, add it */
	pv->edges.push_back(edge(src, dest, weight));
}

/* remove edge specified by source and dest */
void DirectedGraph::removeEdge(int src, int dest)
{
	int i, len;
	vertex* pv;
	edge* pe, *plast;

	/* simple check of input validity */
	if (src >= _size || dest >= _size || src < 0 || dest < 0)
		return;

	pv = &verts[src];
	len = pv->edges.size();
	

	/* scan through to find the edge */
	for (i=0; i<len; ++i)
	{
		/* found the one to remove, swap it with last and decrement */
		if (pv->edges[i].dest == dest)
		{
			pe = &(pv->edges[i]);
			plast = &(pv->edges.back());

			pe->dest = plast->dest;
			pe->weight = plast->weight;
			
			pv->edges.pop_back();
			return;
		}
	}
}

/* see if edge exists specified by source and dest */
bool DirectedGraph::containsEdge(int src, int dest)
{
	int i, len;
	vertex* pv;

	/* simple check of input validity */
	if (src >= _size || dest >= _size || src < 0 || dest < 0)
		return false;

	pv = &verts[src];
	len = pv->edges.size();
	

	/* scan through to find the edge */
	for (i=0; i<len; ++i)
		/* found edge, return */
		if (pv->edges[i].dest == dest)
			return true;

	return false;
}

/* return edge weight specified by source and dest */
int DirectedGraph::getEdgeWeight(int src, int dest)
{
	int i, len;
	vertex* pv;

	/* simple check of input validity */
	if (src >= _size || dest >= _size || src < 0 || dest < 0)
		return 0;

	pv = &verts[src];
	len = pv->edges.size();
	

	/* scan through to find the edge */
	for (i=0; i<len; ++i)
		/* found edge, return answer */
		if (pv->edges[i].dest == dest)
			return pv->edges[i].weight;

	return 0;
}

/* print a specific vertex, designated by the index */
void DirectedGraph::printVertex(int index)
{
	int i, len;
	vertex* pv;
	edge* pe;


	std::cout << "Vertex " << index << ":";

	pv = &verts[index];
	len = pv->edges.size();
	

	/* scan through and print edges */
	for (i=0; i<len; ++i)
	{
		pe = &(pv->edges[i]);
		std::cout << " " << pe->dest << " (" << pe->weight << "),";
	}
	
	std::cout << std::endl;
}

/* print the vertices in order */
void DirectedGraph::printAll()
{
	int i;

	for (i=0; i<_size; ++i)
		printVertex(i);
}

/* return size */
int DirectedGraph::size()
{
	return _size;
}
