// Carlos Lazo
// 9-19-05
// DSA: HW #1
// BinarySearchTree.h

#ifndef BinarySearchTree_h_
#define BinarySearchTree_h_

#include <iostream>
#include <string>
#include "Contact.h"

using namespace std;

class TreeNode 
{
	public:

		// Public member variables

		Contact value;
		TreeNode* left;
		TreeNode* right;

		// Constructor

		TreeNode() : left(0), right(0) {}
};

class BinarySearchTree
{
	public:

		// Public member variables

		TreeNode* root;

		// Constructor + Destructor
	
		BinarySearchTree() : root(0){}
		~BinarySearchTree();

		void insert (Contact contact);
		void remove (string name);
		bool contains (string name);
		int size();
		Contact get (string name);
		void printInOrder();

	private:

		void tree_Insert (TreeNode*& p, Contact contact);
		bool tree_Contains (TreeNode*& p, string name);
		Contact tree_Get (TreeNode*& p, string name);
		void tree_Print (TreeNode*& p);
		int tree_Size(TreeNode*& p);
		void tree_Remove (TreeNode*& p, string name);
		void tree_Delete (TreeNode*& p);

};

#endif