#include <iostream>
#include <vector>
#include "MinPriorityQueue.h"

using namespace std;
#define PARENT(n) ((n)/2)
#define INF 9999999

void MinPriorityQueue::insert(vertex_t v)
{
  vertex_t tmp = v;
  tmp.dist = INF;
  priority_queue.push_back(tmp);
  queue_pos.push_back((int)(priority_queue.size()-1));
  decrease_key(v);
}

void MinPriorityQueue::decrease_key(vertex_t v)
{
  int idx = queue_pos[v.id];
  vertex_t tmp;
  if (v.dist < priority_queue[idx].dist) {
    priority_queue[idx].dist = v.dist;
    while (idx > 0 && priority_queue[PARENT(idx)].dist > priority_queue[idx].dist) {
      tmp = priority_queue[PARENT(idx)];
      priority_queue[PARENT(idx)] = priority_queue[idx];
      queue_pos[priority_queue[idx].id] = PARENT(idx);
      priority_queue[idx] = tmp;
      queue_pos[tmp.id] = idx;
      idx = PARENT(idx);
    }
  }
}

vertex_t MinPriorityQueue::extract_min()
{
  vertex_t v = priority_queue[0];
	priority_queue[0] = priority_queue[int(priority_queue.size()-1)];
  queue_pos[v.id] = -1;
	priority_queue.pop_back();
	heapify(0);
  return v;
}

void MinPriorityQueue::heapify(int index)
{
	int left = 2*index+1;
	int right = 2*index+2;
	int smallest, temp_pos;
	if(left < (int)priority_queue.size() && priority_queue[left].dist < priority_queue[index].dist)
		smallest = left;
	else
		smallest = index;
	if(right < (int)priority_queue.size() && priority_queue[right].dist < priority_queue[smallest].dist)
		smallest = right;
	if(smallest != index)
	{
		vertex_t temp = priority_queue[index];
    temp_pos = queue_pos[temp.id];
    priority_queue[index] = priority_queue[smallest];
    queue_pos[priority_queue[smallest].id] = index;
		priority_queue[smallest] = temp;
    queue_pos[temp.id] = smallest;
		heapify(smallest);
	}
}

