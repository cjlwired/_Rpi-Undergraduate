// Carlos Lazo
// 10-11-05
// DSA Homework #3

#include <iomanip>
#include <iostream>
#include <vector>

#include "MaxPriorityQueue.h"

using namespace std;

int main()
{

	MaxPriorityQueue queue;

	// Insert elements into the Priority Queue.
	
	queue.insert(Job("0010", 5, 80));
	queue.insert(Job("1011", 2, 100));
	queue.insert(Job("0001", 4, 55));
	queue.insert(Job("1110", 7, 125));
	queue.insert(Job("1101", 3, 250));
	queue.insert(Job("0011", 9, 60));
	queue.insert(Job("0100", 10, 240));
	queue.insert(Job("1100", 0, 160));
	queue.insert(Job("1010", 6, 120));
	queue.insert(Job("0101", 11, 80));
	queue.insert(Job("0110", 8, 145));
	queue.insert(Job("0111", 1, 130));

	cout << "Items in the INITIAL Max Priority queue: " << endl << endl;

	queue.print();

	cout << "Please input a time for Jobs to be completed: ";
	int time;
	cin >> time;

	cout << endl << endl;

	vector<Job> finished_Jobs;	// Used to store jobs done

	int total = 0;	// Counter variable

	while ((total <= time) && (queue.size() != 0))
	{
		if ((total + queue.highest_priority().Job_Time) <= time)
		{			
			finished_Jobs.push_back(queue.highest_priority());	// Add the Job taken out to the finished_Job vector

			total = total + queue.highest_priority().Job_Time;	// Update Time 

			queue.extract_max();								// Remove the Job

		}

		else
			break;
	}

	cout << "Jobs that have been COMPLETED:" << endl << endl;

	cout << setw(15) << "JOB ID" << setw(15) << "Job Priority" << setw(15) << "Job Time" << endl << endl;

	for (int i = 0; i < finished_Jobs.size(); i++)
		cout << setw(15) << finished_Jobs[i].Job_ID << setw(15) << finished_Jobs[i].Job_Priority << setw(15) << finished_Jobs[i].Job_Time << endl;

	cout << endl;

	cout << "Jobs REMAINING in the queue: " << endl << endl;

	queue.print();

}