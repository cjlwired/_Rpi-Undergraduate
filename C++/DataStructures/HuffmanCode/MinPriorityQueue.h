// Carlos Lazo
// 11-21-05
// DSA Homework #7

#ifndef MinPriorityQueue_H
#define MinPriorityQueue_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Create a Node class that stores:
//		symbol of Node, frequency of Node, poiner to left child, pointer to right child

struct Node
{
	Node() : frequency(0), left(0), right(0) {}
	Node(string s, int f) : symbol(s), frequency(f), left(0), right(0) {}

	string symbol;
	int frequency;

	Node* left;
	Node* right;

};

class MinPriorityQueue
{

	public:

		vector <Node> priority_queue;	// Queue that will be used to store Nodes.

		MinPriorityQueue()  {}	// Default Constructor

		~MinPriorityQueue() { priority_queue.clear(); }	// Destructor

		void insert(Node n);	// Insert a Node into the queue and maintain order

		Node extract_max();		// Remove Node with the highest priority from the queue

		int size() {return priority_queue.size(); }	// Return the total number of Nodes in the queue

		/* *******************
		   * Heap Operations *
		   ******************* */

		void heapify (int index);	// Used to set elements of the heap in correct order

};

#endif
