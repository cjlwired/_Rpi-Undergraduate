

#include "tree.h"


int
main()
{
  TreeNode<int> * root = 0;  //  Initially an empty tree.
  
  insert( 12, root );
  insert( 13, root );
  insert( 18, root );
  insert( 4, root);
  insert( 6, root );
  insert( 17, root );

  print_as_sideways_tree( cout, root );

  cout << endl;

  if (find (root, 2))
      cout << "2 WAS found in the tree!" << endl;
  else
	  cout << "2 was NOT found in the tree!" << endl;

  if (find (root, 6))
	  cout << "6 WAS found in the tree!" << endl;
  else
	  cout << "6 was NOT found in the tree!" << endl;

  cout << endl;

  cout << "Sum of all elements in the tree is: " << add(root) << endl << endl;

  cout << "---------------------------------------------------" << endl << endl;

  cout << "COPIED TREE SHOULD BE THE SAME: " << endl << endl;

  TreeNode<int>* new_Tree = copy(root);

  print_as_sideways_tree (cout, new_Tree);

  cout << endl << endl;

  cout << "---------------------------------------------------" << endl << endl;

  cout << "TEST TO MAKE SURE THAT TREES ARE DIFFERENT: " << endl << endl;

  insert ( 99, root);

  print_as_sideways_tree (cout, root);

  cout << endl << endl;

  print_as_sideways_tree (cout, new_Tree);

  return 0;
}
