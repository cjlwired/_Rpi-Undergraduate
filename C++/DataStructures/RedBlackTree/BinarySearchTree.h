#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>
#include <iostream>

using namespace std;

/* A structure representing one node in a binary tree */
struct TreeNode {
  int value;
  TreeNode *left;
  TreeNode *right;
};

class BinarySearchTree
{
  private:
    /* Root of the tree */
    TreeNode *m_root;

    /* Returns the size of the tree starting at the given node */
    int size(TreeNode *ptr);

	/* Return the height of the tree starting at the given node */

	int height (TreeNode *ptr);

    /* Destroys the given node and all its children */
    void deleteSubTree(TreeNode *node);

    /* Returns a pointer to a pointer to a node in the tree containing the
     * specified contact's information, or NULL if no match is
     * found .
     */
    TreeNode** find(int num, TreeNode **ppNode);

    /* Prints the contents of the tree starting at the given node */
    void printInOrder(TreeNode *node);

    /* Removes a node from the tree given a pointer to the node to be deleted */
    void remove(TreeNode **ppNode);

  public:
    /* Default Constructor */
    BinarySearchTree();

    /* Default Destructor */
    ~BinarySearchTree();

    /* Add a node to the binary tree */
    void insert(int num);

    /* Delete a node from the binary tree */
    void remove(int num);

    /* Returns true if a given number exists in the tree */
    bool contains(int num);

    /* Returns the total number of nodes in the tree */
    int size();

	/* Return the height of the tree */
	int height();

    /* Return a given number */
    int get(int num);

    /* Print an in-order traversal of the binary tree */
    void printInOrder();
};
#endif
