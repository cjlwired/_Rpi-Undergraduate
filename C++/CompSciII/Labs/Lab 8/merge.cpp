// Carlos Lazo
// 10-27-04
// Lab 8 - merge.cpp

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{

	if ( argc != 4 )
	{
		cerr << "Usage:  " << argv[0] << " infile outfile\n";
		return 1;		
	}

	ifstream data_str1( argv[1] );

	if ( !data_str1 )
    {
      cerr << "Could not open " << argv[1] << " to read numbers.\n";
      return 1;
    }

	ifstream data_str2( argv[2] );

	if ( !data_str2 )
    {
      cerr << "Could not open " << argv[2] << " to read numbers.\n";
      return 1;
    }

	ofstream result_str( argv[3] );
	
	if ( !result_str )
    {
      cerr << "Could not open " << argv[3] << " to write the results.\n";
      return 1;
    }

	bool flag = true;

	string check1;
	string check2;

	if (data_str1 >> check1)
		result_str << argv[1] << " is NOT empty." << endl;
	else
	{
		result_str << argv[1] << " IS empty." << endl;

		result_str << "\nTherefore, the merged files would simply be that of " << argv[2] << ":" << endl << endl;

		while (data_str2 >> check2)
			result_str << check2 << endl;

		flag = false;
	}

	if (flag)
	{
		if (data_str2 >> check2)
			result_str << argv[2] << " is NOT empty." << endl;
		else
		{
			result_str << argv[2] << " IS empty." << endl;

			result_str << "\nTherefore, the merged files would simply be that of " << argv[1] << ":" << endl << endl;

			result_str << check1 << endl;

			while (data_str1 >> check1)
				result_str << check1 << endl;
		}
	}

	result_str << endl;

	if (flag)
	{
		while (flag)
		{
			if (check1 < check2)
			{
				result_str << check1 << endl;

				if (data_str1 >> check1)
					flag = true;
				else
				{
					while (data_str2 >> check2)
						result_str << check2 << endl;

					flag = false;
				}
			}

			else
			{
				if (flag)
				{
					result_str << check2 << endl;

					if (data_str2 >> check2)
						flag = true;
					else
					{
						while (data_str1 >> check1)
							result_str << check1 << endl;

						flag = false;
					}
				}
			}
		}
	}
}