// Carlos Lazo
// 10-11-05
// DSA Homework #3

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "MaxPriorityQueue.h"

using namespace std;

// Default Constructor

MaxPriorityQueue::MaxPriorityQueue()
{}

//Destructor

MaxPriorityQueue::~MaxPriorityQueue()
{}

/* *******************
   * Heap Operations *
   ******************* */

void MaxPriorityQueue::heapify(int index)
{

	// Recursive function to determine which of the elements, the current node or its two children 
	// are the largest.

	int l_index = (index * 2) + 1;
	int r_index = (index * 2) + 2;

	int largest;

	// Make sure to account for the vector indexing starting at 0 and not 1.

	if ((l_index < heap.size()) && (heap[l_index].Job_Priority > heap[index].Job_Priority))
		largest = l_index;
	else
		largest = index;

	if ((r_index < heap.size()) && (heap[r_index].Job_Priority > heap[largest].Job_Priority))
		largest = r_index;

	if (largest != index)
	{
		Job temp = heap[index];
		heap[index] = heap[largest];
		heap[largest] = temp;

		heapify(largest);
	}
		
}

/* *******************************
   * MaxPriorityQueue Operations *
   *******************************  */

// Insert the new Job into the queue and then sort it.

void MaxPriorityQueue::insert(Job job)
{
	heap.push_back(job);

	for (int i = heap.size()/2; i>= 0; i--)
		heapify(i);
}

// Return the element with the highest priority.

Job MaxPriorityQueue::highest_priority()
{
	return heap[0];
}

// Remove Job with the highest priority from the queue.

void MaxPriorityQueue::extract_max()
{
	heap[0] = heap[int(heap.size() - 1)];
	heap.pop_back();
	heapify(0);
}

// Print out the size of the Priority Queue

int MaxPriorityQueue::size()
{
	return heap.size();
}

// Print out Jobs in the Priority Queue

void MaxPriorityQueue::print()
{	
	cout << setw(15) << "JOB ID" << setw(15) << "Job Priority" << setw(15) << "Job Time" << endl << endl;

	for (int i = 0; i < heap.size(); i++)
		cout << setw(15) << heap[i].Job_ID << setw(15) << heap[i].Job_Priority << setw(15) << heap[i].Job_Time << endl;

	cout << endl;
}