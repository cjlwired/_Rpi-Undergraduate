#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <string>
#include <iostream>

using namespace std;

// Representation of a Red-Black Tree Node, with an added parent pointer and boolean value for color.

struct RBTreeNode 
{
  int value;
  RBTreeNode *left;
  RBTreeNode *right;
  RBTreeNode *parent;
  bool color;			// Red = 1, Black = 0
};

class RedBlackTree
{
  private:
    /* Root of the tree */
    RBTreeNode *m_root;

    /* Returns the size of the tree starting at the given node */
    int size(RBTreeNode *ptr);

	/* Return the height of the tree starting at the given node */

	int height (RBTreeNode *ptr);

    /* Destroys the given node and all its children */
    void deleteSubTree(RBTreeNode *node);

	/* Will perform a left rotate on the tree when needed. */
	void leftRotate(RBTreeNode *p);

	/* Will perform a right rotate on a tree when needed. */
	void rightRotate(RBTreeNode *p);

	/* Will return true if the node is red. False indicated it's black.*/
	bool isRed(RBTreeNode *ptr);

  public:
    /* Default Constructor */
    RedBlackTree();

    /* Default Destructor */
    ~RedBlackTree();

    /* Add a node to the Red-Black tree */
    void insert(int num);

    /* Returns the total number of nodes in the tree */
    int size();

	/* Return the height of the tree */
	int height();

};
#endif
