// Carlos Lazo
// 9-19-05
// DSA: HW #1
// BinarySearchTree.cpp

#include "BinarySearchTree.h"

using namespace std;
 
//////////////////////////////
// PRIVATE HELPER FUNCTIONS //
//////////////////////////////

void BinarySearchTree::tree_Delete(TreeNode*& p)
{

    if (p)
	{
		tree_Delete(p->left);
		tree_Delete(p->right);
		delete p;
		p = 0;
    }
}

void BinarySearchTree::tree_Insert(TreeNode*& p, Contact contact)
{
	if (!p)
    {
		p = new TreeNode();  
		p->value = contact;
    }

	else if (contact < p->value)
		tree_Insert(p->left, contact);
	else if (contact > p->value)
		tree_Insert(p->right, contact);
	else  
		p->value = contact;

}

bool BinarySearchTree::tree_Contains(TreeNode*& p, string name)
{
	if (!p)
		return false;
	else if (p->value == name)
		return true;
	else if (p->value > name)
		return tree_Contains(p->left, name);
	else 
		return tree_Contains(p->right, name);

}

void BinarySearchTree::tree_Print(TreeNode*& p)
{
    if (p)
    {
		tree_Print(p->left);
		cout << p->value << "\n";
		tree_Print(p->right);
    }
}

Contact BinarySearchTree::tree_Get(TreeNode*& p, string name)
{

	if (p->value == name)
		return p->value;
	else if (p->value > name)
		return tree_Get(p->left, name);
	else 
		return tree_Get(p->right, name);
}

int BinarySearchTree::tree_Size(TreeNode*& p)
{
	if (!p)
		return 0;
	else
		return 1 + tree_Size(p->left) + tree_Size(p->right);
}

void BinarySearchTree::tree_Remove(TreeNode*& p, string name)
{
    
 	if ((p->value == name) && (p->left == 0) && (p->right == 0))	//If there is only one node, delete that and make the tree empty.
	{
		delete p;
		p = 0;
	}

	else
	{
		TreeNode* q = p;	// Create another pointer that will keep track of the current node's parent.
		TreeNode* r = q;
	
		bool trav_Flag = true;	// This flag will be used to tell the last direction used to travel
								// to the next TreeNode. True is for the right, False is for the left.

		while (r->value != name)	// After this loop, q will be pointing to the node which will be
		{							// deleted and r will point to the it's parent.
			q = r;

			if (r->value > name)
			{
				r = q->left;
				trav_Flag = false;
			}
			else
			{
				r = q->right;
				trav_Flag = true;
			}
		}

		if ((r->left == 0) && (r->right == 0))	// If the node found has no children, simply delete it.
		{
			delete r;	// Delete Node
			r = 0;

			if (trav_Flag)		//Set correct pointer from parent to that Node = null
				q->right = 0;
			else
				q->left = 0;
		}

		else if ((r->left != 0) && (r->right == 0))	// If the node found has 1 child to the left, set the correct parent
		{											// pointer to the current node's left child, then delete it.

			if (p->value == r->value)	// Root Case
			{
				if (p->left->left == 0)	// Only two nodes
				{
					p->value = q->left->value;
					p->left = 0;

					q = q->left;

					delete q;
					q = 0;
				}

				else
				{
					q = q->left;
					p->left  = q->left;

					delete q;
					q = 0;
	
				}
			}

			else
			{
				if (trav_Flag)
					q->right = r->left;
				else
					q->left = r->left;

				delete r;
				r = 0;
			}
		}

		else if ((r->right != 0) && (r->left == 0)) // If the node found has 1 child to the right, set the correct parent
		{											// pointer to the current node's right child, then delete it.
			if (p->value == q->value)	// Root Case
			{
				if (p->right->right == 0)	// Only two nodes
				{
					p->value = q->right->value;
					p->right = 0;

					q = q->right;

					delete q;
					q = 0;
				}

				else
				{
					q = q->right;
					p->right  = q->right;

					delete q;
					q = 0;
	
				}
			}

			else
			{
				if (trav_Flag)
					q->right = r->left;
				else
					q->left = r->left;

				delete r;
				r = 0;
			}
		}

		else	// If the node has two children, find smallest element in the right subtree, switch it with the node to be deleted,
		{		// then delete the smallest node and reassign the appropriate pointers.
		
			TreeNode* s = r->right;
			TreeNode* t = r->right;

			while (s->left != 0)	// Find smallest node in right subtree.
			{
				t = s;
				s = s->left;
			}

			if ((s->right == 0) && (p->right == s))	// Deleting root case with ONLY 2 children - change pointers accordingly.
			{
				p->value = s->value;
				p->right = 0;

				delete s;
				s = 0;
			}

			else if (r == p)	// If you are deleting the root node
			{
				p->value = s->value;
				p->right = q->right;

				delete s;
				s = 0;

				t->left = 0;
			}

			else if (s->right == 0)	// If the smallest node, s, has no children, simply delete it.
			{
  				r->value = s->value;
				r->right = 0;
				
				delete s;
				s = 0;
			}

			else	// Smallest node has a right child, reattach it to the parent's left.
			{
				r->value = s->value;
				r->right = s->right;
				
				delete s;
				s = 0;
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

BinarySearchTree::~BinarySearchTree()
{
	tree_Delete(root);

	cout << "Destructor has been evoked!" << endl;
}

void BinarySearchTree::insert(Contact contact)
{
	tree_Insert(root, contact);
}

void BinarySearchTree::remove(string name)
{
	tree_Remove(root, name);
}

bool BinarySearchTree::contains(string name)
{
	return tree_Contains(root, name);
}

int BinarySearchTree::size()
{
	return tree_Size(root);
}

Contact BinarySearchTree::get(string name)
{
	return tree_Get(root, name);
}

void BinarySearchTree::printInOrder()
{
	tree_Print(root);
}