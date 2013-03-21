
//  File: tree.h 
//
//  Purpose: A collection of functions to implement basic
//     binary search tree operations.  To keep things simple, 
//     these are not wrapped inside a class.   In Lectures 23
//     and 24, similar functions are used to implement our 
//     own version of a set.

#ifndef tree_h_
#define tree_h_
#include <iostream>
using namespace std;

template <class T>
class TreeNode {
public:
  TreeNode() : left(0), right(0) {}
  TreeNode(const T& init) : value(init), left(0), right(0) {}
  const T value;
  TreeNode* left;
  TreeNode* right;
};


template <class T>
bool
insert( T const& key_value, TreeNode<T>*& p )
{
  //  Recursive.  p initially references the root
  if ( !p )  //  empty spot
    {
      p = new TreeNode<T>( key_value );  // new node
      return true;
    }
  else if ( key_value < p->value )
    return insert( key_value, p->left );
  else if ( key_value > p->value )
    return insert( key_value, p->right );
  else  //  equal, can't insert repeated value
    return false;
}


template <class T>
void print_as_sideways_tree( ostream& ostr, const TreeNode<T>* p,
			     int depth )
{
  if ( p ) 
    {
      print_as_sideways_tree( ostr, p->right, depth+1 );
      for ( int i=0; i<depth; ++i ) ostr << "    ";
      ostr << p->value << "\n";
      print_as_sideways_tree( ostr, p->left, depth+1 );
    }
}


template <class T>
void print_as_sideways_tree( ostream& ostr, const TreeNode<T>* p )
{
  print_as_sideways_tree( ostr, p, 0 );
}
/*

// RECURSIVE VERSION

template <class T>
bool find ( TreeNode <T>* root, T const& value)
{
	if (root == 0)
		return false;
	else if (root->value == value)
		return true;
	else if (root->value > value)
		find (root->left, value);
	else 
		find (root->right, value);

}

*/

// NON-RECURSIVE VERSION

template <class T>
bool find ( TreeNode <T>* root, T const& value)
{
	while (root != 0)
	{
		if (root->value == value)
			return true;
		else if (root->value > value)
			root = root->left;
		else
			root = root->right;
	}

	return false;

}

template <class T>
T add( TreeNode<T>* root)
{
	if (root == 0)
		return 0;
	else
		return root->value + add(root->left) + add(root->right);
}

template <class T>
TreeNode<T>* copy( TreeNode<T>* root)
{
	if (root == 0)
		return 0;

	TreeNode<T>* n_root = new TreeNode<T> (root->value);

	n_root->left =  copy(root->left);
	n_root->right = copy(root->right);

	return n_root;

}

#endif
