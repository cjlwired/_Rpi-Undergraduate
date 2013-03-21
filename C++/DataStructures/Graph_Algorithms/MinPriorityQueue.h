#include <iostream>
#include <vector>
#include <string>
#include "vertex.h"

using namespace std;

class MinPriorityQueue {
public:
	MinPriorityQueue(){}
	~MinPriorityQueue() { priority_queue.clear(); }

	void insert(vertex_t v);
  void decrease_key(vertex_t v);
	vertex_t extract_min();
	int size() { return (int)priority_queue.size(); }
  void print();

private:
  /* Tracks position of items in the priority queue
   * so we can find them in O(1) time. */
  vector<int> queue_pos;

	vector<vertex_t> priority_queue;
	void heapify(int index);
};
