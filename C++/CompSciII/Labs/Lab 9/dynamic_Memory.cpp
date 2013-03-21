// Carlos Lazo
// 11-3-04
// Lab #9
// dynamic_Memory.cpp

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{

	/*

	PART 1

	// Size of new array

	int n = argc - 1;

	// Dynamically allocates enough memory in this array for the doubles from the command line

	double *a = new double [n];

	for (int i = 0; i < n; i++)
		a[i] = atof (argv[i+1]);

	sort (a, a+n);

	for (int i = 0; i < n; i++)
		cout << a[i] << " ";

	cout << endl;

	*/

	/*

	PART 2

	ifstream data_str( argv[1] );

	if ( !data_str )
	{
		cerr << "Could not open " << argv[1] << " to read strings.\n";
		return 1;
	}

	vector <string> my_Strings;

	string read;

	while (data_str >> read)
		my_Strings.push_back(read);

	data_str.close();

	sort (my_Strings.begin(), my_Strings.end());

	for (int i = 0; i < my_Strings.size(); i++)
		cout << my_Strings[i] << " ";

	cout << endl << endl;

	*/

	// Opening input file

	ifstream data_str( argv[1] );

	if ( !data_str )
	{
		cerr << "Could not open " << argv[1] << " to read strings.\n";
		return 1;
	}

	int n = 5;	// integer which will be used to keep track of array size

	int counter = 0;	// will be used to keep track of elements in current array

	string *a = new string[n];	// string array declaration

	string read;	// used to read in strings

	while (data_str >> read)
	{

		if (counter == n)
		{

			string *temp = new string [n*2];

			for (int i = 0; i < n; i++)
				temp[i] = a[i];

			delete[] a;

			a = temp;

			n = n * 2;
		}

		a[counter] = read;

		counter++;
	}

	sort (a, a+n);

	cout << endl;

	for (int i = 0; i < n; i++)
		cout << a[i] << " ";

	cout << endl;

	return 0;

}