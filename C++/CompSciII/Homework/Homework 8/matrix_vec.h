//  File:    matrix_vec.h
//  Author:  Chuck Stewart
//  Purpose: Header file for the vector of vectors matrix
//     implementation.

#ifndef matrix_h_
#define matrix_h_

#include <iostream>
#include <vector>
using namespace std;


class matrix {
	public:
		matrix( );                        //  Empty --- 0 rows and 0 columns
		matrix( int nrows, int ncols );   //  initialize all values to 0
		matrix( matrix const& old );      //  copy constructor
		~matrix();

		matrix& operator=( matrix const& rhs );
		void resize( int new_nrows, int new_ncols );

		int nrows() const { return m_nrows; }
		int ncols() const { return m_ncols; }
		vector< vector<double> > get_array() const { return m_array; }	// New function added that will be 
																		// used to get the matrix array
		void set( unsigned int row, unsigned int col, double value );
		double get( unsigned int row, unsigned int col ) const;

		matrix transpose() const;
		matrix operator+( matrix const& rhs ) const;
		matrix operator*( matrix const& rhs ) const;

		void print_row( ostream& ostr, unsigned int r) const;
		void print_col( ostream& ostr, unsigned int c) const;
		friend ostream& operator<< ( ostream& ostr, matrix const& m );

	private:

		int m_nrows, m_ncols;
		vector< vector<double> > m_array;
};

#endif
