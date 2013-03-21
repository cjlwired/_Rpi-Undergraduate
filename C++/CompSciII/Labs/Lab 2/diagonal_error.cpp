
// Program:  diagonal_name
// Author:   Chuck Stewart
// Purpose:  A program that outputs an input name along a diagonal.

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
  cout << "What is your first name? ";
  string first;
  cin >> first;
  
  const string star_line( first.size()+4, '*' );
  const string blanks( first.size()+2, ' ' );
  const string empty_line = '*' + blanks + '*';

  cout << endl
       << star_line << endl
       << empty_line << endl;


  //  Invariant at start of loop : the first i letter of the first
  //  name have been output

  // ***** changed size to 0
  string::size_type i = 0;

  while ( i < first.size() )
    {
      //  Job of loop body is to write a row of output containing *'s
      //  in the first (0-th) and last columns, the i-th letter in
      //  column i+2, and a blank everywhere else.

      for ( string::size_type j = 0; j < first.size()+4; ++ j )
        {
		  // ***** changed to 3
          if ( j == 0 || j == first.size()+3 )
            cout << '*';

		  // ***** changed to 2
          else if ( j == 2 )
		  {
			int temp = 0;

			while (temp < first.size() - i)
			{			
				cout << first[temp];
				temp++;
			}

			j = j + temp - 1;
		  }

          else
            cout << ' ';
        }
      cout << endl;
      ++ i;
    }

  cout << empty_line << endl
       << star_line << endl;

  return 0;
}
