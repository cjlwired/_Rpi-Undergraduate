#include <iostream>
#include <string>
#include "BinarySearchTree.h"

using namespace std;

/* Default Constructor */
BinarySearchTree::BinarySearchTree()
{
  m_root = NULL;
}

/* Default Destructor - Frees any memory allocated for tree nodes */
BinarySearchTree::~BinarySearchTree()
{
  deleteSubTree(m_root);
}

/* Destroys the given node and all its children */
void BinarySearchTree::deleteSubTree(TreeNode *node) {
  if (node) {
    deleteSubTree(node->left);
    deleteSubTree(node->right);
    delete node;
  }
}

/* Returns a pointer to a pointer to a node in the tree containing the
 * specified num's information, or NULL if no match is
 * found.
 */
TreeNode** BinarySearchTree::find(int num, TreeNode **ppNode)
{
  if (*ppNode) {
    if ((*ppNode)->value > num) {
      ppNode = find(num, &(*ppNode)->left);
    } else if ((*ppNode)->value < num) {
      ppNode = find(num, &(*ppNode)->right);
    }
  }
  return ppNode;
}

/* Inserts a new TreeNode with the given an integer as its value */
void BinarySearchTree::insert(int num)
{
  TreeNode *ptr, *newNode;

  /* Create the new node */
  newNode = new TreeNode;
  newNode->value = num;
  newNode->left = newNode->right = NULL;

  if (!m_root) {
    m_root = newNode;
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
        break;
      } 
    }
  }
}

void BinarySearchTree::remove(int num)
{
  TreeNode **ppNode = find(num, &m_root);

  if (*ppNode) {
    if (*ppNode == m_root) {
      remove(&m_root);
    } else {
      remove(ppNode);
    }
  }
}

void BinarySearchTree::remove(TreeNode **ppNode)
{
  TreeNode *ptr;

  if (*ppNode) {
    if ((*ppNode)->right == NULL) {
      /* Delete node and reattach left child */
      ptr = *ppNode;
      *ppNode = (*ppNode)->left;
    } else if ((*ppNode)->left == NULL) {
      /* Delete node and reattach right child */
      ptr = *ppNode;
      *ppNode = (*ppNode)->right;
    } else {
      /* Node has two children */
      ptr = (*ppNode)->right;
      while (ptr->left)
        ptr = ptr->left;
      ptr->left = (*ppNode)->left;
      ptr = *ppNode;
      *ppNode = (*ppNode)->right;      
    }
    delete ptr;
  }
}

bool BinarySearchTree::contains(int num)
{
  return (*find(num, &m_root) != NULL);
}

int BinarySearchTree::get(int num)
{
  TreeNode *ptr = *find(num, &m_root);
  if (ptr) {
    return ptr->value;
  }
  return 0;
}

int BinarySearchTree::size(TreeNode *ptr) 
{
  if (ptr) {
    return size(ptr->left) + size(ptr->right) + 1;
  }
  return 0;
}

int BinarySearchTree::size()
{
	return size(m_root);
}

int BinarySearchTree::height(TreeNode *ptr)
{
	if (!ptr)
		return 0;
	else 
	{
		int leftDepth  = height(ptr->left);
		int rightDepth = height(ptr->right);

		if (leftDepth > rightDepth) 
			return(leftDepth + 1);
		else 
			return(rightDepth + 1);
  }
} 

int BinarySearchTree::height()
{	
	return height(m_root);
}

void BinarySearchTree::printInOrder(TreeNode *node)
{
  if (node) {
    printInOrder(node->left);
    cout << node->value << endl;
    printInOrder(node->right);
  }
}

void BinarySearchTree::printInOrder()
{
  printInOrder(m_root);
}