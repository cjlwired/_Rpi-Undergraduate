// Carlos Lazo
// 12-6-04
// Homework 8 - Matrices
// main.cpp

#include <iostream>
#include <string>
#include <vector>

#include "matrix_vec.h"

using namespace std;

int main()
{
	cout << "~ WELCOME TO THE MATRIX TEST MAIN ~ " << endl;
	cout << "BELOW ARE THE MATRIX FUNCTIONS BEING TESTED OUT." << endl << endl;

	cout << "----------------------------------------------------------" << endl << endl;

	cout << "Matrix is being instantiated with the default constructor." << endl;
	cout << "Row and Column size should be 0." << endl << endl;

	matrix def;

	cout << "Row : " << def.nrows() << endl;
	cout << "Col : " << def.ncols() << endl;

	cout << endl;

	cout << "----------------------------------------------------------" << endl << endl;

	cout << "Matrix is being instantiated with the second constructor." << endl;
	cout << "Row should be 4 and column should be 5." << endl << endl;

	matrix con2(4,5);

	cout << "Row : " << con2.nrows() << endl;
	cout << "Col : " << con2.ncols() << endl;

	cout << endl;

	cout << "----------------------------------------------------------" << endl << endl;

	cout << "Matrix is being instantiated using the third constructor, the copy constructor." << endl;
	cout << "It is a copy of the matrix from the second constructor, therefore, the row " << endl;
	cout << "should be 4 and the column should be 5." << endl << endl;

	matrix con3(con2);

	cout << "Row : " << con3.nrows() << endl;
	cout << "Col : " << con3.ncols() << endl;

	cout << endl;

	cout << "----------------------------------------------------------" << endl << endl;

	cout << "A 2x2 matrix has been created using the second constructor and the set function.";
	cout << "It will now be outputed, using the operator<< function declared in the class." << endl << endl;

	matrix mat (2,2);

	mat.set(0,0,1.1);
	mat.set(0,1,2.2);
	mat.set(1,0,3.3);
	mat.set(1,1,4.4);

	cout << mat << endl;

	cout << "Row : " << mat.nrows() << endl;
	cout << "Col : " << mat.ncols() << endl;

	cout << endl;

	cout << "----------------------------------------------------------" << endl << endl;

	cout << "The same matrix from above will be assigned to a new matrix utilizing the " << endl;
	cout << "operator= function declared in the class. It will then have the top left " << endl;
	cout << "and bottom right elements removed (set to 0) with the set function." << endl << endl;

	mat.set(0,0,0.0);
	mat.set(1,1,0.0);

	cout << mat << endl;

	cout << endl;

	cout << "----------------------------------------------------------" << endl << endl;

	cout << "Creating a 3x4 matrix that will be added to itself to create a new " << endl;
	cout << "function. I will test the get function, the transpose function, and" << endl;
	cout << "the print row and print col functions." << endl << endl;

	matrix mat2 (3,4);

	for (unsigned int i = 0; i < mat2.nrows(); i++)
	{
		for (unsigned int j = 0; j < mat2.ncols(); j++)
		{
			mat2.set(i, j, i+j+.1);
		}
	}

	cout << mat2 << endl;

	cout << "The above matrix added to itself yields the resulting matrix: " << endl << endl;

	matrix add = mat2 + mat2;

	cout << add << endl;

	cout << "Here are some elements that are being tested with the get function" << endl;
	cout << "in the addition matrix." << endl << endl;

	cout << "Element at (0,0) is : " << add.get(0,0) << endl;
	cout << "Element at (1,3) is : " << add.get(1,3) << endl;
	cout << "Element at (2,1) is : " << add.get(2,1) << endl;

	cout << endl;

	cout << "Transposition of the added matrix is the following: " << endl << endl;

	matrix trans = add.transpose();

	cout << trans << endl << endl;

	cout << "----------------------------------------------------------" << endl << endl;

	cout << "The added matrix and another matrix will be multiplied and" << endl;
	cout << "will form a new matrix. Rows and Columns will then be printed" << endl;
	cout << "out. Afterwards, the matrix will be resized and printed out." << endl << endl;

	matrix mult_by (4,5);

	for (unsigned int i = 0; i < mult_by.nrows(); i++)
	{
		for (unsigned int j = 0; j < mult_by.ncols(); j++)
		{
			mult_by.set(i, j, i+j+.1);
		}
	}

	matrix mult = add * mult_by;

	cout << "Multiply this matrix: " << endl << endl;

	cout << add;

	cout << endl << endl;

	cout << "By this matrix: " << endl << endl;

	cout << mult_by << endl << endl;

	cout << "Multiplied Matrix is: " << endl << endl;

	cout << mult; 

	cout << endl << endl;

	// Setting first row to all zero.

	for (unsigned int i = 0; i < mult.ncols(); i++)
		mult.set(0,i,0.0);

	// Setting first column to all zero.

	for (unsigned int j = 0; j < mult.nrows(); j++)
		mult.set(j,0,0.0);

	cout << "Set first row and column to all zero - New matrix is : " << endl << endl;

	cout << mult;

	cout << endl << endl;

	cout << "First row is     : ";
	mult.print_row(cout, 0);
	cout << endl;
	cout << "First column is  : ";
	mult.print_col(cout, 0);
	cout << endl;
	cout << "Second row is    : ";
	mult.print_row(cout, 1);
	cout << endl;
	cout << "Second column is : " ;
	mult.print_col(cout, 1);
	cout << endl;

	cout << endl;

	cout << "----------------------------------------------------------" << endl << endl;

	cout << "Now taking the the add matrix from above and resizing it to (6,7)." << endl << endl;

	cout << "Old add matrix: " << endl << endl;

	cout << add;

	cout << endl << endl;
	
	add.resize(6,7);

	cout << "New add matrix: " << endl << endl;

	cout << add;

	cout << endl;

	cout << "Add matrix row is now: " << add.nrows() << endl;
	cout << "Add matrix col is now: " << add.ncols() << endl;

	cout << endl;

	cout << "Matrix above is now being shrunk to a 2x2 matrix." << endl;
	cout << "New matrix is: " << endl << endl;

	add.resize(2,2);

	cout << endl;

	cout << "Add matrix row is now: " << endl << endl;

	cout << add << endl;

	cout << endl;

	cout << "Add matrix row is now: " << add.nrows() << endl;
	cout << "Add matrix col is now: " << add.ncols() << endl;

	cout << endl;

	cout << "----------------------- FIN --------------------------" << endl << endl;
	



	return 0;
}
