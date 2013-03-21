// Carlos Lazo
// 11-21-05
// DSA HW 7

#include <iostream>
#include <string>
#include <vector>

#include "MinPriorityQueue.h"

using namespace std;

// Print the MinPriorityQueue

void print_queue(MinPriorityQueue queue)
{
	for (int i = 0; i < queue.size(); i++)
	{
		cout << "Symbol: " << queue.priority_queue[i].symbol << "\t Frequency: " << queue.priority_queue[i].frequency << endl;
	}

	cout << endl << endl;
}


// Returns the size of a tree given a pointer to a node.

int tree_Size(Node* p)
{
	if (!p)
		return 0;
	else
		return 1 + tree_Size(p->left) + tree_Size(p->right);
}

// Set the Node* variables a Nodes variables.

void set_Pointer(Node* l, Node r)
{
	l->frequency = r.frequency;
	l->symbol = r.symbol;
	l->left  = r.left;
	l->right = r.right;
}

// Function that will recursively find the Huffman codes and print them for all the characters in the Leaf Tree.

void find_Codes(Node* p, string s)
{
	// If the symbol exists and is a Leaf Node, then print it out along with it's Huffman Code.

	if (p && (p->symbol != "EMPTY"))
		cout << "Character: " << p->symbol << " with frequency " << p->frequency << "\t, Huffman Code is --> " << s << endl;
	
	else
	{
		find_Codes(p->left,  (s+"0"));
		find_Codes(p->right, (s+"1"));
	}
}

int main()
{
	MinPriorityQueue queue;

	// Insert Nodes into the minimum priority queue.
	// To insert a Node, simply use the syntax: queue.insert(Node("x", y)) --> where x = symbol, y = x's frequency

	queue.insert(Node("a", 246));
	queue.insert(Node("b", 485));
	queue.insert(Node("c", 168));
	queue.insert(Node("d", 440));
	queue.insert(Node("e", 425));
	queue.insert(Node("f", 450));
	queue.insert(Node("g",  72));
	queue.insert(Node("h", 376));
	queue.insert(Node("i", 301));
	queue.insert(Node("j", 264));
	queue.insert(Node("k", 358));
	queue.insert(Node("l", 424));
	queue.insert(Node("m", 393));
	queue.insert(Node("n", 239));
	queue.insert(Node("o", 102));
	queue.insert(Node("p", 341));
	queue.insert(Node("q", 265));
	queue.insert(Node("r", 475));
	queue.insert(Node("s", 201));
	queue.insert(Node("t", 395));
	queue.insert(Node("u",  15));
	queue.insert(Node("v", 142));
	queue.insert(Node("w", 438));
	queue.insert(Node("x", 258));
	queue.insert(Node("y", 273));
	queue.insert(Node("z", 147));
	queue.insert(Node("A", 385));
	queue.insert(Node("B", 437));
	queue.insert(Node("C", 468));
	queue.insert(Node("D", 298));

	// TEST 1

	/*

	queue.insert(Node("I", 38));
	queue.insert(Node("L", 21));
	queue.insert(Node("O", 10));
	queue.insert(Node("V",  6));
	queue.insert(Node("E", 44));
	queue.insert(Node("N", 19));
	queue.insert(Node("W", 15));
	queue.insert(Node("Y",  5));
	queue.insert(Node("R", 27));
	queue.insert(Node("K", 30));

	// TEST 2

	*/

	/*

	queue.insert(Node("C", 25));
	queue.insert(Node("O", 12));
	queue.insert(Node("M", 99));
	queue.insert(Node("P", 10));
	queue.insert(Node("U", 50));
	queue.insert(Node("T", 34));
	queue.insert(Node("E", 24));
	queue.insert(Node("R",  8));

	*/

	// TEST 3

	/*

	queue.insert(Node("Q", 87));
	queue.insert(Node("U", 12));
	queue.insert(Node("I", 60));
	queue.insert(Node("C",  7));
	queue.insert(Node("K", 99));
	queue.insert(Node("B", 11));
	queue.insert(Node("R", 24));
	queue.insert(Node("O", 42));
	queue.insert(Node("W", 33));
	queue.insert(Node("N", 71));
	queue.insert(Node("F", 56));
	queue.insert(Node("X",  1));

	*/

	cout << "The following symbols and frequencies have been inserted into the queue: " << endl << endl;

	// Print out the elements in the MinPriorityQueue

	print_queue(queue);

	cout << "-----------------------------------------------------------------------" << endl << endl;

	// While the size of the queue is greater than 2, take out the two elements that have the highest priority.
	// Merge them into one single tree, then reinsert back into the queue. Repeat this process until two trees
	// are left.

	while (queue.size() > 2)
	{

		Node* l; 
		Node* r; 
		Node merge;

		l = new Node(); 
		r = new Node();

		Node s = queue.extract_max();
		Node t = queue.extract_max();

		// Copy information to new pointers.

		set_Pointer(l, s);
		set_Pointer(r, t);

		// Set up the new merged Node. Set the symbol for non-symbol Nodes to be "EMPTY".
		// This will be used later in printing out the characters and codes.

		merge.frequency = s.frequency + t.frequency;
		merge.symbol = "EMPTY";
		merge.left  = l;
		merge.right = r;

		// Reinsert into the MinPriorityQueue

		queue.insert(merge);
	}

	// Perform the FINAL merge:

	Node* l; 
	Node* r; 
	Node merge;

	l = new Node(); 
	r = new Node();

	Node s = queue.extract_max();
	Node t = queue.extract_max();

	set_Pointer(l, s);
	set_Pointer(r, t);

	merge.frequency = s.frequency + t.frequency;
	merge.symbol = "EMPTY";
	merge.left  = l;
	merge.right = r;

	queue.insert(merge);

	// Assign a pointer to the root node of the newly created Leaf Tree (stored in only element of the MinPriorityQueue).

	Node* root;
	root = new Node();

	root->frequency = queue.priority_queue[0].frequency;
	root->symbol    = queue.priority_queue[0].symbol;
	root->left      = queue.priority_queue[0].left;
	root->right     = queue.priority_queue[0].right;

	// Find and print out the Huffman Codes of the tree.

	find_Codes(root, "");
	
	cout << endl;

	return 0;
}