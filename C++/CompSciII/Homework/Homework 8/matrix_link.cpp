// Carlos Lazo
// 12-6-04
// Homework 8 - Matrices
// matrix_link.cpp

#include <iostream>
#include <string>
#include <vector>

#include "matrix_link.h"

using namespace std;

/*

	CONSTRUCTORS

				*/

// Default constructor of matrix. Initializes rows and columns to zero, leaving the vector
// pointers alone.

matrix::matrix()
{
	m_nrows = 0;
	m_ncols = 0;

	vector<Node*> m_row_ptrs = m_row_ptrs;
	vector<Node*> m_col_ptrs = m_row_ptrs;

}

// Second constructor of matrix. Initializes rows and colums to the sent parameters, and sets the
// size of each of the corresponding vectors in relation to the rows and columns sent.

matrix::matrix (int nrows, int ncols)
{

	m_nrows = nrows;
	m_ncols = ncols;

	for (unsigned int i = 0; i < m_nrows; i++)
	{
		Node* temp = new Node();
		m_row_ptrs.push_back(temp);
	}

	for (unsigned int j = 0; j < m_ncols; j++)
	{
		Node* temp = new Node();
		m_col_ptrs.push_back(temp);
	}

}

matrix::matrix(const matrix& old)
{
	copy_matrix(old);
}

/*

	DESTRUCTOR

				*/

matrix::~matrix()
{
	destroy_matrix();
}

/*
	
	ASSIGNMENT FUNCTIONS
							*/

// This function sets the current matrix that calls this function to the matrix that is being sent. Basically,
// the current matrix's private member variables are being reassigned.  

matrix&
matrix:: operator= (matrix const& rhs)
{ 
	copy_matrix (rhs);

	return *this;
}

// This function resizes the matrix to the set parameters. It takes care of all pointer operations.

void matrix::resize(int new_nrows, int new_ncols)
{

	if (new_nrows >= 0 && new_ncols >= 0)
	{
		// Case : Both the new rows and columns are greater than the previous dimensions.
		// In this case, the vectors will simply be resized.

		if (new_nrows >= nrows() && new_ncols >= ncols())
		{

			// Resize both vectors to accomodate matrix change.
			
			m_row_ptrs.resize(new_nrows, new Node());
			m_col_ptrs.resize(new_ncols, new Node());

			// Change private member variables

			m_nrows = new_nrows;
			m_ncols = new_ncols;
		}

		// CASE : The columns are getting larger and the rows are getting smaller. Increment and decrement 
		// the matrix accordingly.

		else if (new_nrows < nrows() && new_ncols >= ncols())
		{
			// Increment the columns of the matrix and set the private variable to the new column number

			m_col_ptrs.resize(new_ncols, new Node());

			m_ncols = new_ncols;

			// Take care of deleting nodes that are past the row limit.

			for (unsigned int i = 0; i < ncols(); i++)
			{

				// P is a reference to the first Node in a row.

				Node *p = m_col_ptrs[i]->next_in_col;

				// If this row has atleast one Node, search through these Nodes and delete all Nodes that are
				// past the limit of column.

				if (p != 0)
				{
					// Flag is used to limit searching through nodes. This flag will be turned false when the Node that passes
					// the column size is found.

					bool flag = true;

					// This node will hold the first that crosses the threshold. From here, the deleting will be done.

					Node* limit = p->next_in_col;

					// Find the Node that is stored at a place that is greater than the column that this matrix will
					// be shrunk to.

					while (limit != 0 && flag)
					{
						if (limit->row > new_nrows)
							flag = false;
						else
						{
							p = limit;
							limit = limit->next_in_col;
						}
					}

					// Set the rest of p to be zero, therefore severing the link in the rows.

					p->next_in_col = 0;

					// Delete excess Nodes that will be cut off when resized.

					while (limit != 0)
					{
						Node* temp = limit;
						limit = limit->next_in_col;
						delete temp;
					}

				}

			}

			m_row_ptrs.resize(new_nrows);

			m_nrows = new_nrows;

		}

		// CASE : The rows are getting larger and the columns are getting smaller. Increment and decrement 
		// the matrix accordingly.

		else if (new_nrows >= nrows() && new_ncols < ncols())
		{
			// Increment the rows of the matrix and set the private variable to the new row number

			m_row_ptrs.resize(new_nrows,new Node());

			m_nrows = new_nrows;

			// Take care of deleting nodes that are past the column limit.

			for (unsigned int i = 0; i < nrows(); i++)
			{

				// P is a reference to the first Node in a row.

				Node *p = m_row_ptrs[i]->next_in_row;

				// If this row has atleast one Node, search through these Nodes and delete all Nodes that are
				// past the limit of column.

				if (p != 0)
				{
					// Flag is used to limit searching through nodes. This flag will be turned false when the Node that passes
					// the column size is found.

					bool flag = true;

					// This node will hold the first that crosses the threshold. From here, the deleting will be done.

					Node* limit = p->next_in_row;

					// Find the Node that is stored at a place that is greater than the column that this matrix will
					// be shrunk to.

					while (limit != 0 && flag)
					{
						if (limit->col > new_ncols)
							flag = false;
						else
						{
							p = limit;
							limit = limit->next_in_row;
						}
					}

					// Set the rest of p to be zero, therefore severing the link in the rows.

					p->next_in_row = 0;

					// Delete excess Nodes that will be cut off when resized.

					while (limit != 0)
					{
						Node* temp = limit;
						limit = limit->next_in_row;
						delete temp;
					}

				}

			}

			m_col_ptrs.resize(new_ncols, new Node());

			m_ncols = new_ncols;

		}

		// CASE : Both of the dimensions will be decresed. Change vectors accordingly.

		else 
		{

			// Take care of deleting nodes that are past the row limit.

			for (unsigned int i = 0; i < ncols(); i++)
			{

				// P is a reference to the first Node in a row.

				Node *p = m_col_ptrs[i]->next_in_col;

				// If this row has atleast one Node, search through these Nodes and delete all Nodes that are
				// past the limit of column.

				if (p != 0)
				{
					// Flag is used to limit searching through nodes. This flag will be turned false when the Node that passes
					// the column size is found.

					bool flag = true;

					// This node will hold the first that crosses the threshold. From here, the deleting will be done.

					Node* limit = p->next_in_col;

					// Find the Node that is stored at a place that is greater than the column that this matrix will
					// be shrunk to.

					while (limit != 0 && flag)
					{
						if (limit->row > new_nrows)
							flag = false;
						else
						{
							p = limit;
							limit = limit->next_in_col;
						}
					}

					// Set the rest of p to be zero, therefore severing the link in the rows.

					p->next_in_col = 0;

					// Delete excess Nodes that will be cut off when resized.

					while (limit != 0)
					{
						Node* temp = limit;
						limit = limit->next_in_col;
						delete temp;
					}

				}

			}

			m_row_ptrs.resize(new_nrows);

			m_nrows = new_nrows;

			// Take care of deleting nodes that are past the column limit.

			for (unsigned int i = 0; i < nrows(); i++)
			{

				// P is a reference to the first Node in a row.

				Node *p = m_row_ptrs[i]->next_in_row;

				// If this row has atleast one Node, search through these Nodes and delete all Nodes that are
				// past the limit of column.

				if (p != 0)
				{
					// Flag is used to limit searching through nodes. This flag will be turned false when the Node that passes
					// the column size is found.

					bool flag = true;

					// This node will hold the first that crosses the threshold. From here, the deleting will be done.

					Node* limit = p->next_in_row;

					// Find the Node that is stored at a place that is greater than the column that this matrix will
					// be shrunk to.

					while (limit != 0 && flag)
					{
						if (limit->col > new_ncols)
							flag = false;
						else
						{
							p = limit;
							limit = limit->next_in_row;
						}
					}

					// Set the rest of p to be zero, therefore severing the link in the rows.

					p->next_in_row = 0;

					// Delete excess Nodes that will be cut off when resized.

					while (limit != 0)
					{
						Node* temp = limit;
						limit = limit->next_in_row;
						delete temp;
					}

				}

			}

			m_col_ptrs.resize(new_ncols, new Node());

			m_ncols = new_ncols;
			
		}

	}

	else
		cout << "Cannot resize matrix to the specified parameters. No changes made." << endl;


}

// This function changes the value at location (row,col) in the sparse matrix to the sent parameter.
// If the value is 0.0, then then node must be removed from the sparse matrix.

void matrix::set( unsigned int row, unsigned int col, double value )
{
	// Bounds checking

	if (row >= 0 && row < nrows() && col >= 0 && col < ncols())
	{
		// If value is equal to 0.0, then a node might be deleted.

		if (value == 0.0)
		{

			// If the row has atleast one element in it stemming out, begin to search for the element.

			if (m_row_ptrs[row]->next_in_row != 0)
			{
				// Boolean variable defined to start searching for the Node in question.

				bool flag = false;

				Node* found = m_row_ptrs[row]->next_in_row;

				// While-loop searches through the Nodes of the row, trying to find the Node in question.

				while (found != 0 && !flag)
				{
					// Element was found, have the Node stay stored in found pointer.

					if (found->row == row && found->col == col)
						flag = true;

					// Otherwise, keep searching the row for the Node.

					else
						found = found->next_in_row;
				}

				// If the Node was found, take appropriate measures to delete the Node.

				if (flag)
				{
					// Keep track of two column Nodes at the same time since pointers have to be changed.

					Node* c  = m_col_ptrs[col];
					Node* nc = c->next_in_col;

					// While-loop runs until the nc Node is equal to the Node that is to be deleted.

					while (nc != found)
					{
						c  = nc;
						nc = nc->next_in_col;
					}

					// Set column pointer from Node BEFORE the "found" Node to the one AFTER
					// the "found" node, effectively removing it from the column.

					c->next_in_col = nc->next_in_col;

					// Keep track of two row Nodes at the same time since pointers have to be changed.

					Node* r  = m_row_ptrs[row];
					Node* nr = r->next_in_row;

					// While-loop runs until the nr Node is equal to the Node that is to be deleted.

					while (nr != found)
					{
						r  = nr;
						nr = nr->next_in_row;
					}

					// Set row pointer from Node BEFORE the "found" Node to the one AFTER
					// the "found" node, effectively removing it from the row.

					r->next_in_row = nr->next_in_row;

					// Now that pointers are reassigned, delete Node found.

					delete found;

				}

				// If the element isn't there, that means that it is already 0.0 - 
				// Print out appropriate message.

				else
					cout << "Element is already set to 0." << endl;

			}

			// If no pointers were found to other Nodes in the row, print out appropriate message.

			else
				cout << "Row was all zero to begin with, no changes made." << endl;


		}

		// If value is not equal to 0.0, either add a Node or change a value, changing the appropriate pointers

		else
		{
			// If the vector is empty, add the Node.
			
			if (m_row_ptrs[row]->next_in_row == 0)
			{
				// Create a new Node to be inserted into the sparse matrix.

				Node* add = new Node (row, col, value);

				// Set the next_in_row of the appropriate row vector element to this Node.
	
				m_row_ptrs[row]->next_in_row = add;
				add->next_in_row = 0;	// Set next_in_row to null.

				// Set the next_in_col of the appropriate column vector element to this Node.
					
					// Check to see if column vector element is empty

				if (m_col_ptrs[col]->next_in_col == 0)
				{
					m_col_ptrs[col]->next_in_col = add;
					add->next_in_col = 0;	// Set next_in_col to null
				}

				else
				{

					// Keep track of two column pointers at the same time, since column pointers 
					// must be changed.

					Node*  c = m_col_ptrs[col]->next_in_col;
					Node* nc = c->next_in_col;

					// While loop will find the correct place for insertion between the two column nodes.
					// It uses the row as the limiting agent when looking for the correct insertion point.

						// Check to make sure that there isn't only one element in the matrix.

					if (nc != 0)
					{
						
						// Using a boolean variable, and always checking bounds, find the exact location
						// where the node should be inserted.

						bool check = true;

						while (check && nc != 0)
						{
							if (c->row < add->row && nc->row > add->row)
								check = false;

							else
							{
								c = nc;
								nc = nc->next_in_col;
							}
						}
					}

					// Reassign pointers accordingly, inserting new Node between the two.

					c->next_in_col = add;
					add->next_in_col = nc;

				}

			}

			// If the vector is not empty, search for the Node and then process it accordingly

			else
			{

				// Search for the Node in question

				bool flag = false;

				Node* found = m_row_ptrs[row]->next_in_row;

				// While-loop searches through the Nodes of the row, trying to find the Node in question.

				while (found != 0 && !flag)
				{
					// Element was found, have the Node stay stored in found pointer.

					if (found->row == row && found->col == col)
						flag = true;

					// Otherwise, keep searching the row for the Node.

					else
						found = found->next_in_row;
				}

				// If the Node was found, simply change its value to the one sent to this function.

				if (flag)
					found->value = value;
				
				// If the Node is not found, take proper measure to insert it into the sparse matrix.

				else
				{
					
					// Create a pointer to the node that is to be added.

					Node* add = new Node (row, col, value);

					// Keep track of two row pointers at the same time, since row pointers 
					// must be changed.

					Node*  r = m_row_ptrs[row]->next_in_row;
					Node* nr = r->next_in_row;

					// Check to see if Node should be inserted at the head of the sparse matrix row

					if (add->row < r->row)
					{
						m_row_ptrs[row]->next_in_row = add;
						add ->next_in_row = r;
					}

					else
					{
						// While loop will find the correct place for insertion between the two column nodes.
						// It uses the row as the limiting agent when looking for the correct insertion point.

							// Check to make sure that there isn't only one element in the matrix.

						if (nr != 0)
						{
							
							// Using a boolean variable, and always checking bounds, find the exact location
							// where the node should be inserted.

							bool check = true;

							while (check && nr != 0)
							{
								if (r->col < add->col && nr->col > add->col)
									check = false;

								else
								{
									r = nr;
									nr = nr->next_in_row;
								}
							}
						}

						// Reassign pointers accordingly, inserting new Node between the two.

						r->next_in_row = add;
						add->next_in_row = nr;

					}

					// Check to see if column is empty

					if (m_col_ptrs[col]->next_in_col == 0)
					{	
						m_col_ptrs[col]->next_in_col = add;
						add->next_in_col = 0;	// Set next_in_col to null
					}

					else
					{

						// Keep track of two column pointers at the same time, since column pointers 
						// must be changed.

						Node*  c = m_col_ptrs[col]->next_in_col;
						Node* nc = c->next_in_col;

						// Check to see if element should be the head of the sparse matrix column element.

						if (add->col < c->col)
						{
							m_col_ptrs[col]->next_in_col = add;
							add->next_in_col = c;
						}

						else
						{

							// While loop will find the correct place for insertion between the two column nodes.
							// It uses the row as the limiting agent when looking for the correct insertion point.

								// Check to make sure that there isn't only one element in the matrix.

							if (nc != 0)
							{
								
								// Using a boolean variable, and always checking bounds, find the exact location
								// where the node should be inserted.

								bool check = true;

								while (check && nc != 0)
								{
									if (c->row < add->row && nc->row > add->row)
										check = false;

									else
									{
										c = nc;
										nc = nc->next_in_col;
									}
								}
							}

							// Reassign pointers accordingly, inserting new Node between the two.

							c->next_in_col = add;
							add->next_in_col = nc;

						}

					}

				}

			}

		}

	}

	else
		cout << "Invalid position in the matrix." << endl;



}

/*

	RETRIEVAL FUNCTIONS

							*/

// Function searches through the sparse matrix for the element at the specified location.
// If found, it returns the element. If not, an appropriate message is printed and a value
// of -1.0 is returned.


double matrix::get( unsigned int row, unsigned int col ) const
{ 

	// Bounds checking

	if (row >= 0 && row < nrows() && col >= 0 && col < ncols())
	{
		Node* p = m_row_ptrs[row];

		// If the row has no linking nodes, this means that the entire row is full of 0's

		if (p->next_in_row == 0)
			return 0.0;
		else
		{
			p = p->next_in_row;

			while (p != 0)
			{

				// If the column value sent matches the Node, return that value

				if (p->col == col)
					return p->value;

				// Move to the next linked value in the sparse matrix
				
				p = p->next_in_row;

			}

			return 0.0;
		}

	}

	cout << "Invalid dimensions sent to get function, returning 0" << endl;
	return 0.0;

}

/*

	MUTATION FUNCTIONS

						*/

matrix
matrix::transpose() const
{	

	// Create a matrix where the rows and columns of the (this) matrix are inverted.

	matrix trans (ncols(), nrows());

	for (unsigned int i = 0; i < nrows(); i++)
	{

		Node* p = m_row_ptrs[i]->next_in_row;

		// If there is atleast one Node in this linked list, set all of the new nodes
		// into their corresponding slots in the transposed matrix.

		if (p != 0)
		{

			while (p != 0)
			{
				trans.set(p->col, p->row, p->value);

				p = p->next_in_row;

			}

		}

	}

	return trans;

}

// This function adds both of the matrices that are sent to it.
// ASSUMING that the matrices are of the same dimensions.

matrix
matrix::operator+( matrix const& rhs ) const
{ 

	// Create a matrix that is equivalent to the one sent to this function.

	matrix addition (rhs);

	for (unsigned int i = 0; i < nrows(); i++)
	{

		Node* p = m_row_ptrs[i] ->next_in_row;

		if (p != 0)
		{
			while (p!= 0)
			{

				// If there is nothing currently at that location in the sparse matrix,
				// meaning that there is a zero there, set the location to the location in
				// the left matrix.

				if (addition.get(p->row, p->col) == 0)
					addition.set(p->row, p->col, p->value);

				// Otherwise, add value from the left matrix to the one that is already
				// at that location in the addition sparse matrix.

				else
				{
					double old_val = addition.get(p->row, p->col);
					addition.set(p->row, p->col, p->value + old_val);
				}

				p = p->next_in_row;

			}

		}

	}

	return addition;
}


matrix
matrix::operator*( matrix const& rhs ) const
{ 

	/* NOTE :

		This function follows the guidelines stated within the homework. The rules are that we cannot iterate through
		an entire matrix checking every single row and column location possible. This function checks every single Node
		in the rows of the left matrix, and then utilizes the get function to find the corresponding elements in the 
		right matrix. There is no need to check every element since the non-existant Nodes in the left matrix will turn
		up a product of 0 anyway. Added this in here for clarification. */

	// Initialize a matrix that will have it's row equal to the left matrix's rows and the
	// columns equal to the right matrix's columns.

	matrix multiplication (nrows(), rhs.ncols());

	for (unsigned int i = 0; i < nrows(); i++)
	{

		Node* test = m_row_ptrs[i]->next_in_row;

		// If the row in the left matrix is not empty, or has all 0's, then
		// begin doing calculations and placing multiplied elements in the
		// right location in the matrix.

		if (test != 0)
		{
			// Setting up for-loop to access elements in the right matrix

			for (unsigned int j = 0; j < rhs.ncols(); j++)
			{

				Node*p = m_row_ptrs[i]->next_in_row;

				double sum = 0.0;

				while (p != 0)
				{
					sum += p->value * rhs.get(p->col, j);

					p = p->next_in_row;

				}

				multiplication.set(i, j, sum);

			}

		}

	}

	return multiplication;

}

/*

	PRINTING FUNCTIONS
					
						*/

// Function prints the appropriate row in the sparse matrix.
// NOTE : This was implemented prior to the implementation of get.

void matrix::print_row( ostream& ostr, unsigned int r) const
{
	// Bounds checking

	if (r >= 0 && r < nrows())
	{
		// If the row is empty, that is, it is not pointing to anything, print out that it contains all zeros

		if (m_row_ptrs[r]->next_in_row == 0)
			cout << "All zero" << endl;
		else
		{

			Node* p = m_row_ptrs[r]->next_in_row;

			while (p != 0)
			{
				cout << p->col << ":" << p->value << ", ";
				 
				p = p->next_in_row;
			}
		}
	}

	else
		cout << "Row is invalid." << endl << endl;

}

// Function prints the appropriate column in the sparse matrix.
// NOTE : This was implemented prior to the implementation of get.

void matrix::print_col( ostream& ostr, unsigned int c) const
{

	// Bounds checking

	if (c >= 0 && c < ncols())
	{
		// If the column is empty, that is, it is not pointing to anything, print out that it contains all zeros

		if (m_col_ptrs[c]->next_in_col == 0)
			cout << "All zero" << endl;

		
		else
		{

			Node* p = m_col_ptrs[c]->next_in_col;

			while (p != 0)
			{
				cout << p->row << ":" << p->value << ", ";
				 
				p = p->next_in_col;
			}
		}
	}

	else
		cout << "Column is invalid." << endl << endl;

}

// This function will use the get function to print out the matrix.

ostream& operator<< ( ostream& ostr, matrix const& m )
{ 

	for (unsigned int i = 0; i < m.nrows(); i++)
	{
		for (unsigned int j = 0; j < m.ncols(); j++)
		{
			cout << m.get(i,j) << " ";
		}
		
		cout << endl;

	}

	return cout;
}

/*

	UTILITY FUNCTIONS

						*/

// The destructor of this program will delete all nodes within the sparse matrix.

void matrix::destroy_matrix()
{

	for (unsigned int i = 0; i < nrows(); i++)
	{
		Node *p = m_row_ptrs[i]->next_in_row;

		// If there is atleast one Node in the row, go down the list and delete all Nodes
		// within that row.

		if (p != 0)
		{

			while (p != 0)
			{
				Node* temp = p;
				p = p->next_in_row;
				delete temp;
			}
		}
	}
}

// This function is used to copy matrices. It ensures that a different instance of the 
// sparse matrix is created, and that it does not refer to the same pointer representation.
// NOTE : This was implemented prior to the implementation of get.

void matrix::copy_matrix( matrix const& old )
{


	// Copy private dimensions to the beginning matrix

	m_nrows = old.m_nrows;
	m_ncols = old.m_ncols;

	// Since each matrix needs to be unique, a new sparse matrix must be created to keep one
	// matrix from changing the other.

		// Assigning new sparse matrix vector pointers to 0 for now.

	for (unsigned int x = 0; x < m_nrows; x++)
	{
		Node* temp = new Node();
		m_row_ptrs.push_back(temp);
	}

	for (unsigned int y = 0; y < m_ncols; y++)
	{
		Node* temp = new Node();
		m_col_ptrs.push_back(temp);
	}

	// Traverse the old sparse matrix, and using the set function, arrange the appropriate nodes
	// within the new matrix. This will be done using the row pointers.

	for (unsigned int i = 0; i < old.nrows(); i++)
	{

		Node* p = old.m_row_ptrs[i]->next_in_row;

		// If there is atleast one Node in this linked list, set all Nodes of this one to the new matrix.

		if (p != 0)
		{

			while (p != 0)
			{
				set(p->row, p->col, p->value);

				p = p->next_in_row;

			}

		}

	}

}
