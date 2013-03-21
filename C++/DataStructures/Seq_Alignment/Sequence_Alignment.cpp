// Carlos Lazo
// 12-5-05
// DSA HW #8

/* Create a struct called Node that will store the penalty of a spot in the cost
   matrix, along with the row and column of where it came from.					 */

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <stdio.h>

using namespace std;

// Create class Node to use within the cost matrix.

struct Node
{
	Node() : value(0), prev_row(0), prev_col(0) {}

	int value;		// Store penalty

	int prev_row;	// Store previous row
	int prev_col;	// Store previous column
};

// Return true if the character is a vowel.

bool isVowel(char x)
{
	return (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u');
}

// Used to calculate the cost between two characters in the cost matrix.

int calc_cost(char x, char y, int vv_cc_cost, int v_c_cost)
{

	// If the letters are equal, incur no penalty.

	if (x == y)
		return 0;

	// If one is a vowel and the other in a consonant, then return the vowel/consonant mismatch cost.

	if ((isVowel(x) && !isVowel(y)) || (isVowel(y) && !isVowel(x)))
		return v_c_cost;

	// If not, return the matching cost.

	return vv_cc_cost;
}

// Return the smallest of the three integers given.

int minimum (int a, int b, int c)
{

	int smallest;

	if (a < b)
		smallest = a;
	else
		smallest = b;

	if (smallest < c)
		return smallest;

	return c;
}

/* ******************************************************************************************** */

int main()
{
 
	int gap_cost;		// Store penalty for each gap.
	int	vv_cc_cost;		// Store penalty for vowel to vowel and consonant to consonant mismatch.
	int v_c_cost;		// Store penalty for vowel/consonant mismatch.

	cout << "Please enter the gap penalty:" << endl;
	cin  >> gap_cost;
	cout << endl;

	cout << "Please enter the vowel to vowel and consonant to consonant mismatch penalty:" << endl;
	cin  >> vv_cc_cost;
	cout << endl;

	cout << "Please enter the vowel to consonant mismatch penalty: " << endl;
	cin  >> v_c_cost;
	cout << endl;

	string x;
	string y;

	cout << "Please enter the first string to be compared: " << endl;
	cin  >> x;
	cout << endl << endl;

	cout << "Please enter the second string to be compared: " << endl;
	cin  >> y;
	cout << endl << endl;

	cout << "------------------------------------------------------------" << endl << endl;

	// Create a vector of vectors that will store the cost matrix for the strings.

	vector<vector<Node> > cost_matrix;		
	
	vector<Node> row (y.size() + 1);
	
	// Create cost matrix to be the right size.

	for (int i = 0; i < x.size() + 1; i++)
			cost_matrix.push_back(row);

	// Initialize columns and rows to equal the index * the gap cost. Also, set the prev_row and prev_col.

	for (int i = 0; i < cost_matrix.size(); i++) 
	{
		cost_matrix[i][0].value = i * gap_cost;
		cost_matrix[i][0].prev_row = i-1;
		cost_matrix[i][0].prev_col = 0;
	}

	for (int j = 0; j < cost_matrix[0].size(); j++)
	{
		cost_matrix[0][j].value = j * gap_cost;
		cost_matrix[0][j].prev_row = 0;
		cost_matrix[0][j].prev_col = j-1;
	}

	cost_matrix[0][0].prev_row = -1;
	cost_matrix[0][0].prev_col = -1;

	// Implement the minimum alignment cost recurrence:

	for (int i = 1; i < cost_matrix.size(); i++) 
	{
		for (int j = 1; j < cost_matrix[0].size(); j++)
		{
			// Calculate the alpha cost, which is dependant on the strings 

			int alpha_cost = calc_cost(x[i-1], y[j-1], vv_cc_cost, v_c_cost);

			// Find out the values of the three possible choices for the current OPT(i,j).

			int a = alpha_cost + cost_matrix[i-1][j-1].value;
			int b = gap_cost + cost_matrix[i-1][j].value;
			int c = gap_cost + cost_matrix[i][j-1].value;

			// Assign OPT(i,j) by taking the minimum of the values found.

			cost_matrix[i][j].value = minimum (a,b,c);

			// Assign the predecessor of the current OPT(i,j) value.

			if (cost_matrix[i][j].value == a)
			{
				cost_matrix[i][j].prev_row = i-1;
				cost_matrix[i][j].prev_col = j-1;
			}

			else if (cost_matrix[i][j].value == b)
			{
				cost_matrix[i][j].prev_row = i-1;
				cost_matrix[i][j].prev_col = j;
			}

			else
			{
				cost_matrix[i][j].prev_row = i;
				cost_matrix[i][j].prev_col = j-1;
			}
		}
	}

	// Print out the cost matrix in format where element (0,0) is in the bottom left corner:

	cout << "Values in the cost matrix are: " << endl << endl;

	cout << setw(3);

	for (int i = cost_matrix.size() - 1; i >= 0; i--)
	{
		for (int j = 0; j < cost_matrix[0].size(); j++)
			cout << cost_matrix[i][j].value << setw(3);

		cout << endl;
	}

	cout << endl;

	// Print out the path taken in format where (-,-) is in the bottom left corner:

	cout << "Path's taken to each part of the cost matrix are: " << endl << endl;

	cout << setw(3);

	for (int i = cost_matrix.size() - 1; i >= 0; i--)
	{
		for (int j = 0; j < cost_matrix[0].size(); j++)
		{
			if (i == 0 && j == 0)
				cout << "  (-,-)" << setw(3);
			else
				cout << "(" << cost_matrix[i][j].prev_row << "," << cost_matrix[i][j].prev_col << ")" << setw(3);
		}

		cout << endl;
	}

	cout << endl;

	return 0;

}