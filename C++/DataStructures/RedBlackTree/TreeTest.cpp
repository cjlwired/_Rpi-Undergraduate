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