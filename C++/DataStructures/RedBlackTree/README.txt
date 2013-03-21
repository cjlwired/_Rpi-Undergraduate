Carlos Lazo
DSA HW #2
Section 02

Test function:

/////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "BinarySearchTree.h"
#include "RedBlackTree.h"
using namespace std;

int main()
{
	srand(time(0));

	BinarySearchTree BST;
	RedBlackTree RBT;

	cout << "Inserting 1000 ordered elements into a Binary Search Tree and a Red Black Tree:" << endl << endl;

	for (int i = 0; i < 1000; i++)
	{
		BST.insert(i);
		RBT.insert(i);
	}

	cout << "Height of the Binary Search Tree: " << BST.height() << endl;
	cout << "Height of the Red Black Tree: "     << RBT.height() << endl;

	cout << endl;
	
	BinarySearchTree BST2;
	RedBlackTree RBT2;

	cout << "Inserting 1000 random elements into a Binary Search Tree and a Red Black Tree:" << endl << endl;

	int r;

	for (int i = 0; i < 1000; i++)
	{
		r = rand() % 1000;

		BST2.insert(r);
		RBT2.insert(r);
	}

	cout << "Height of the Binary Search Tree: " << BST2.height() << endl;
	cout << "Height of the Red Black Tree: "     << RBT2.height() << endl;

	cout << endl;
	
}

/////////////////////////////////////////////////////////////////////////////

Outputs generated:

1)

Inserting 1000 ordered elements into a Binary Search Tree and a Red Black Tree:

Height of the Binary Search Tree: 1000
Height of the Red Black Tree: 17

Inserting 1000 random elements into a Binary Search Tree and a Red Black Tree:

Height of the Binary Search Tree: 23
Height of the Red Black Tree: 12

2)

Inserting 1000 ordered elements into a Binary Search Tree and a Red Black Tree:

Height of the Binary Search Tree: 1000
Height of the Red Black Tree: 17

Inserting 1000 random elements into a Binary Search Tree and a Red Black Tree:

Height of the Binary Search Tree: 20
Height of the Red Black Tree: 12

3)

Inserting 1000 ordered elements into a Binary Search Tree and a Red Black Tree:

Height of the Binary Search Tree: 1000
Height of the Red Black Tree: 17

Inserting 1000 random elements into a Binary Search Tree and a Red Black Tree:

Height of the Binary Search Tree: 19
Height of the Red Black Tree: 11

/////////////////////////////////////////////////////////////////////////////

Analysis:

          For all of the cases, it is apparent that the height of the BST is much
greater than that of the RBT. It would make sense since the RBT algorithm ensures
that the tree keeps itself balanced with the use of colors, reducing the overall 
height compared to the BST inesrtion algorithm. If you insert a large amount of
elements, the true power of the RBT is evident.

