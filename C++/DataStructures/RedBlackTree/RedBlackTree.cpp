#include <iostream>
#include <string>
#include "RedBlackTree.h"

using namespace std;

/* Default Constructor */
RedBlackTree::RedBlackTree()
{
  m_root = 0;
}

/* Default Destructor - Frees any memory allocated for tree nodes */
RedBlackTree::~RedBlackTree()
{
  deleteSubTree(m_root);
}

/* Destroys the given node and all its children */
void RedBlackTree::deleteSubTree(RBTreeNode *node) {
  if (node) {
    deleteSubTree(node->left);
    deleteSubTree(node->right);
    delete node;
  }
}

void RedBlackTree::leftRotate(RBTreeNode *p)
{
    RBTreeNode *dir, *q;

    q = p->right;

    // Make q's left subtree p's right subtree
    p->right = q->left;

	// Set q's left child's parent to p
    if ( q->left != 0)
        q->left->parent = p;
    
	// Set q's new parent to p's old parent
    q->parent = p->parent;

	// - Set p's parent to point to p instead of q

    // Check for root case first
    if ( p->parent == 0 ) 
		m_root = q;
    else
	{
		dir = p->parent;

		if ( p == dir->left)
		{
            // p was on left side of parent
            p->parent->left = q;
		}
        else
		{
            // p was on right side of parent
            p->parent->right = q;
		}
	}
   
	q->left = p;	// put p on q's left
	p->parent = q;	// make p's parent q
    
}

void RedBlackTree::rightRotate(RBTreeNode *q)
{    
    RBTreeNode *dir, *p;

    p = q->left;

    // Make p's right subtree q's left subtree
    q->left = p->right;

	// Set p's right child's qarent to q
    if ( p->right != 0)
        p->right->parent = q;
    
	// Set p's new qarent to q's old qarent
    p->parent = q->parent;

	// - Set q's qarent to point to q instead of p

    // Check for root case first
    if ( q->parent == 0 ) 
		m_root = p;
    else
	{
		dir = q->parent;

		if ( q == dir->right)
		{
            // q was on right side of qarent
            q->parent->right = p;
		}
        else
		{
            // q was on left side of qarent
            q->parent->left = p;
		}
	}
   
	p->right = q;	// qut q on p's right
	q->parent = p;	// make q's qarent p
    
    
}

bool RedBlackTree::isRed(RBTreeNode *ptr)
{
	// Check to see if node is null
	if (ptr == 0)
		return 0;
	if (ptr->color == 1)
		return 1;

	return 0;
}

void RedBlackTree::insert(int num)
{
	// Modified regular BST Insert, now with the parent pointer taken into account.

	RBTreeNode *ptr, *newNode;

	/* Create the new node */

	newNode = new RBTreeNode;
	newNode->value = num;
	newNode->left = newNode->right = NULL;

	if (!m_root) {
		m_root = newNode;
		m_root->parent = newNode;
	} else {
		ptr = m_root;

		/* Find a place to insert the new node */
		while (ptr) {
		if (num < ptr->value) {
			if (ptr->left) {
			ptr = ptr->left;
			} else {
			ptr->left = newNode;
			break;
			}
		} else if (num > ptr->value) {
			if (ptr->right) {
			ptr = ptr->right;
			} else {
			ptr->right = newNode;
			break;
			}
		} else {
			/* Duplicate node value */
			ptr->value = num;
			delete newNode;	// Inserted this comment to correct memory leak.
			break;} 
		}
	}

	// Set parent pointer.

	newNode->parent = ptr;

	// Begin the re-coloring process by setting the newNode's color to red.

	RBTreeNode *p, *q;

	p = newNode;

	newNode->color = 1;	// Set color to red.

	// Taken directly from pseudocode - all cases.

	while ((p != m_root) && isRed(p->parent))
	{
		if (p->parent == p->parent->parent->left)
		{
			q = p->parent->parent->right;

			if (isRed(q))
			{
				p->parent->color = 0;
				q->color = 0;
				p->parent->parent->color = 1;
				p = p->parent->parent;
			}
			else
			{
				if (p == p->parent->right)
				{
					p = p->parent;
					leftRotate(p);
				}

				p->parent->color = 0;
				p->parent->parent->color = 1;
				rightRotate(p->parent->parent);
			}
		}

		else
		{
			q = p->parent->parent->left;

			if (isRed(q))
			{

				p->parent->color = 0;
				q->color = 0;
				p->parent->parent->color = 1;
				p = p->parent->parent;
			}
			else
			{
				if (p == p->parent->left)
				{
					p = p->parent;
					rightRotate(p);
				}

				p->parent->color = 0;
				p->parent->parent->color = 1;
				leftRotate(p->parent->parent);
			}
		}
	}

	m_root->color = 0;

}

int RedBlackTree::size(RBTreeNode *p) 
{
  if (p) {
    return size(p->left) + size(p->right) + 1;
  }
  return 0;
}

int RedBlackTree::size()
{
	return size(m_root);
}

// Return the height of the tree.

int RedBlackTree::height(RBTreeNode *p)
{
	if (!p)
		return 0;
	else 
	{
		int leftDepth  = height(p->left);
		int rightDepth = height(p->right);

		if (leftDepth > rightDepth) 
			return(leftDepth + 1);
		else 
			return(rightDepth + 1);
	}
} 

int RedBlackTree::height()
{	
	return height(m_root);
}