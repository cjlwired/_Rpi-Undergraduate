// Carlos Lazo
// 12-6-04
// Homework 8 - Matrices
// matrix_vec.cpp

#include <iostream>
#include <string>
#include <vector>

#include "matrix_vec.h"

using namespace std;

/*

	CONSTRUCTORS

				*/

// Default constructor, intializing the matrix rows, columns, and size to 0

matrix::matrix()
{
	m_array = m_array;
	m_ncols = 0;
	m_nrows = 0;
}

// Second constructor, initializing the matrix to the rows and columns given, and will
// set all values to 0.

matrix::matrix(int nrows, int ncols)
{
	m_ncols = ncols;
	m_nrows = nrows;

	vector <double> one_row (ncols, 0.0);

	vector <vector <double> > mat (nrows, one_row);
	
	m_array = mat;

}

// Third constructor, the copy constructor, initializing the matrix to be a copy of the matrix
// sent to this function.

matrix::matrix(const matrix& old)
{
	m_ncols = old.ncols();
	m_nrows = old.nrows();
	m_array = old.get_array();
}

/*

	DESTRUCTOR

				*/

matrix::~matrix()
{
	// cout << "DESTRUCTOR HAS	BEEN EVOKED." << endl;
}

/*
	
	ASSIGNMENT FUNCTIONS
							*/

// This function sets the current matrix that calls this function to the matrix that is being sent. Basically,
// the current matrix's private member variables are being reassigned.  

matrix&
matrix:: operator= (matrix const& rhs)
{
	m_ncols = rhs.ncols();
	m_nrows = rhs.nrows();
	m_array = rhs.get_array();

	return *this;
}

// This function resizes the current matrix to the size specified by the parameters sent.

void matrix::resize(int new_nrows, int new_ncols)
{
	
	// This checks for validity of the new row and column sent to the function

	if (new_nrows > 0 && new_ncols > 0)
	{
		// A temporary matrix is created and is set to have a matrix representation of the new dimensions.

		matrix resized (new_nrows, new_ncols);

		// The nested for-loop works like this:

			// This traverse each index of the new matrix created. If the loop reaches an element that is out
			// of scope in relation to the original matrix (in other words, the index is greater than the rows
			// or colums of the original matrix), it will place a 0.0 at that location. The set function is
			// being used here.

		for (unsigned int i = 0; i < new_nrows; i++)
		{
			for (unsigned int j = 0; j < new_ncols; j++)
			{
				if ((i > (nrows() - 1)) || (j > (ncols() - 1)))
					resized.set(i,j,0.0);
				else
					resized.set(i,j,m_array[i][j]);
			}
		}

		// Set the original matrix to the new matrix now created.

		m_array = resized.m_array;
		m_nrows = resized.nrows();
		m_ncols = resized.ncols();

	}

	else
		cout << "Cannot resize matrix to the sent parameters!" << endl;
}

// Sets the element at the position [row][col] in the matrix to the value sent, checking to make sure that
// the send parameters are within bounds.

void matrix::set( unsigned int row, unsigned int col, double value )
{

	// Preliminary check for validity of the location in the matrix. If found, set that location equal
	// to the value sent.

	if (row >= 0 && col >= 0 && (row < nrows()) && (col < ncols()))
		m_array[row][col] = value;
	else
		cout << "Coordinate in matrix does not exist." << endl;
}

/*

	RETRIEVAL FUNCTIONS

							*/

// Returns the element at the position [row][col] in the matrix, checking to make sure that the sent parameters
// are within bounds. Return -1.0 if the matrix element is invalid.

double matrix::get( unsigned int row, unsigned int col ) const
{

	// Preliminary check for validity of the location in the matrix. If found, return value at that location.

	if (row >= 0 && col >= 0 && (row < nrows()) && (col < ncols()))
		return m_array[row][col];
	else
	{
		cout << "Coordinate in matrix is invalid, returning -1." << endl;
	}

	return -1.0;
}

/*

	MUTATION FUNCTIONS

						*/

// This will take the matrix and invert the rows and columns, creating a new matrix.

matrix
matrix::transpose() const
{

	// Inverted matrix with n x m dimensions created
	
	matrix trans(ncols(), nrows());

	vector< vector<double> > m = m_array;

	// The nested for-loop works like this:

			// This traverses the original matrix normally and sets the element as the value to
			// the appropriate element in the transposed matrix.

	for (unsigned int i = 0; i < nrows(); i++)
	{
		for (unsigned int j = 0; j < ncols(); j++)
		{
			// Notice that it trans[j][i] is set to m[i][j] - This is what allows for the transposition.

			trans.set(j,i,m[i][j]);
		}
	}

	return trans;
}

// This will create a new matrix where the elements in the new matrix are a sum of elements in the same
// location of the individual matrices. ASSUMING that the matrices are of the same dimensions.      

matrix
matrix::operator+( matrix const& rhs ) const
{
	// New matrix created representing the right hand side matrix.

	matrix addition (rhs);

	vector< vector<double> > l = get_array();

	// The nested for-loop works like this:

			// The left side matrix elements are being added to the corresponding right hand 
			// matrix elements.

	for (unsigned int i = 0; i < nrows(); i++)
	{
		for (unsigned int j = 0; j < ncols(); j++)
		{
			addition.m_array[i][j] += l[i][j];
		}
	}
	
	return addition;

}

// This will create a new matrix where the dimensions are the rows of the left matrix and the columns of 
// the right matrix. ASSUMING that the matrices sent are of dimensions (m x n) and (n x p)

matrix
matrix::operator*( matrix const& rhs ) const
{

	// Both left and right side matrices are being defined below.

	vector< vector<double> > left = get_array();

	vector< vector<double> > right = rhs.get_array();

	// A new matrix is created with the rows of the left matrix and the columns of the right matrix

	matrix multiplication (nrows(), rhs.ncols());

	// The nested for-loop works like this:

			// This traverse each index of the new matrix created. Within the inner for-loop, a variable is 
			// instantiated to keep a running sum of elements that will be placed within an element in the
			// new matrix. After the computational for-loop is done processing, which calculates the sum that
			// should be placed within the new element, set the appropriate location in the new matrix to the sum.

	for (unsigned int i = 0; i < multiplication.nrows(); i++)
	{
		for (unsigned int j = 0; j < multiplication.ncols(); j++)
		{

			double sum = 0.0;

			for (unsigned int a = 0; a < ncols(); a++)
			{
				sum += left[i][a] * right[a][j];
			}

			multiplication.set(i, j, sum);
		}
	}

	return multiplication;

}

/*

	PRINTING FUNCTIONS
					
						*/

// Prints out the rth row of the matrix, checking to ensure that it is within the bounds of the matrix itself.

void matrix::print_row( ostream& ostr, unsigned int r) const
{

	vector< vector<double> > print = get_array();

	if (r >= 0 && r < nrows())
	{
		for (unsigned int i = 0; i < ncols(); i++)
			cout << print[r][i] << " ";

		cout << endl << endl;
	}

	else
		cout << "Row is invalid." << endl << endl;

}

// Prints out the cth column of the matrix, checking to ensure that it is within the bounds of the matrix itself.

void matrix::print_col( ostream& ostr, unsigned int c) const
{
	vector< vector<double> > print = get_array();

	if (c >= 0 && c < ncols())
	{
		for (unsigned int i = 0; i < nrows(); i++)
			cout << print[i][c] << " ";

		cout << endl << endl;
	}

	else
		cout << "Column is invalid." << endl << endl;
}

// This is a print function that simplifies displaying a matrix.

ostream& operator<< ( ostream& ostr, matrix const& m )
{
	for (unsigned int i = 0; i < m.m_nrows; i++)
	{
		for (unsigned int j = 0; j < m.m_ncols; j++)
		{
			cout << m.m_array[i][j] << " ";
		}

		cout << endl;
	}

	return cout;
}