// Carlos Lazo
// 11-21-05
// DSA Homework #7

#include <iostream>
#include <string>
#include <vector>

#include "MinPriorityQueue.h"

using namespace std;

// Insert a Node into the MinPriorityQueue. Call heapify on it to ensure order is kept.

void MinPriorityQueue::insert(Node n)
{
	priority_queue.push_back(n);

	for(int i = priority_queue.size()/2; i>=0; i--) 
		heapify(i);

}

// Extract Node with highest priority from the MinPriorityQueue. Heapify to ensure preservation of order. 

Node MinPriorityQueue::extract_max()
{
	Node temp = priority_queue[0];
	priority_queue[0] = priority_queue[int(priority_queue.size()-1)]; 
	priority_queue.pop_back();
	heapify(0);

	return temp;

}

// Heapify function implementation with Nodes.

void MinPriorityQueue::heapify(int index)
{
	int left = 2*index+1;
	int right = 2*index+2;
	int largest;

	if(left < priority_queue.size() && priority_queue[left].frequency < priority_queue[index].frequency)
		largest = left;
	else
		largest = index;

	if(right < priority_queue.size() && priority_queue[right].frequency < priority_queue[largest].frequency)
		largest = right;

	if(largest != index)
	{

		Node temp = priority_queue[index];
		priority_queue[index] = priority_queue[largest];
		priority_queue[largest] = temp;
		heapify(largest);
	}
}