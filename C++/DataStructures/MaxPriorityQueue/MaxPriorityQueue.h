// Carlos Lazo
// 10-11-05
// DSA Homework #3

#ifndef MaxPriorityQueue_H
#define MaxPriorityQueue_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Initial Declaration of the Job Class with appropriate member variables and functions.

struct Job
{
		string Job_ID;
		int Job_Priority;
		int Job_Time;
	
		Job() {}
		Job(string ID, int Priority, int Time)
			{ Job_ID = ID; Job_Priority = Priority; Job_Time = Time; }

		Job operator=(Job right)
		{	this->Job_ID = right.Job_ID;
			this->Job_Priority = right.Job_Priority;
			this->Job_Time = right.Job_Time; 
			return *this; }
};

class MaxPriorityQueue
{
	private:

		vector <Job> heap;

	public:

		MaxPriorityQueue();		// Default Constructor

		~MaxPriorityQueue();	// Destructor

		void insert (Job job);	// Insert a Job into the queue

		Job highest_priority();	// Return Job with the highest priority

		void extract_max();		// Remove Job with the highest priority from the queue

		int size();				// Return the total number of jobs in the queue

		void print();			// Print all the jobs in the queue in the current storage order

		/* *******************
		   * Heap Operations *
		   ******************* */

		void heapify (int index);	// Used to set elements of the heap in correct order

};

#endif
