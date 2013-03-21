//  File:    matrix_link.h
//  Author:  Chuck Stewart
//  Purpose: Header file for the sparse, linked matrix
//     implementation.  Matrix entries that have 0 value will not be
//     represented.

#ifndef matrix_h_
#define matrix_h_

#include <iostream>
#include <vector>
using namespace std;

//  A simple node class storing the row, col and value for the matrix
//  entry and pointers to the node for the next non-zero entry in the
//  row and in the column

class Node {
 public:
  Node( ) : next_in_row(0), next_in_col(0) {}
  Node( unsigned int r, unsigned int c, double v )
    : row(r), col(c), value(v), next_in_row(0), next_in_col(0) {}
  unsigned int row, col;
  double value;
  Node * next_in_row;
  Node * next_in_col;

};


//  The matrix header itself.  A few of the functions have been inlined.

class matrix {
 public:
	matrix( );                           //  Empty --- 0 rows and 0 columns
	matrix( int nrows, int ncols );      //  initialize all values to 0
	matrix( matrix const& old );         //  copy constructor
	~matrix();

	matrix& operator=( matrix const& rhs );
	void resize( int new_nrows, int new_ncols );

	int nrows() const { return m_nrows; }
	int ncols() const { return m_ncols; }
	void set( unsigned int row, unsigned int col, double value );
	double get( unsigned int row, unsigned int col ) const;

	matrix transpose() const;
	matrix operator+( matrix const& rhs ) const;
	matrix operator*( matrix const& rhs ) const;

	void print_row( ostream& ostr, unsigned int r) const;
	void print_col( ostream& ostr, unsigned int c) const;
	friend ostream& operator<< ( ostream& ostr, matrix const& m );

 private:  //  Utility functions 
	void destroy_matrix();
	void copy_matrix( matrix const& old );

 private:
  //  Maintain the number of rows and columns for easy access and
  //  maintain pointers to the first node in each row and column.

	int m_nrows, m_ncols;
	vector<Node*> m_row_ptrs;
	vector<Node*> m_col_ptrs;
};

#endif
