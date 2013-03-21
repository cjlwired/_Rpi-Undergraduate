
//  Program:  break_up.cpp
//  Author:   Chuck Stewart
//  Purpose:  Demonstrate use of generic functions in breaking up
//     input lines of text into strings of non-whitespace characters. 


#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> breakup_v1( const string& line );
vector<string> breakup_v2( const string& line );

int
main()
{
  cout << "Enter lines of text and the program will break it up into strings";
  string line;

  //  Handle one line at a time.
  while( getline( cin, line ) )
    {
      //  vector<string> strings = breakup_v1( line );
      vector<string> strings = breakup_v2( line );
      cout << "\n" << line << endl;

      if ( strings.empty() )
        {
          cout << "***  No strings ***\n";
        }
      else
        {
          for ( vector<string>::const_iterator p = strings.begin();
                p != strings.end(); ++p )
            cout << "  " << *p << "\n";
        }
    }
}

//  Version based on indexing

vector<string> breakup_v1( const string& line )
{
  vector<string> strings;
  unsigned int i=0, j;

  while ( i < line.size() )
    {
      //  Find the beginning of the next string
      for ( ; i < line.size() && isspace( line[i] ); ++i )
        ;

      //  If there is another string, find the end and copy it
      if ( i != line.size() )
        {
          for ( j = i+1; j != line.size() && !isspace( line[j] ); ++j )
            ;
          string s = line.substr( i, j-i );
          strings.push_back( s );
          i = j;
        }
    }

  return strings;
}

//  Return true if a char is not a whitespace char
bool
nonspace( char c )
{
  return !isspace(c);
}

//  The following is needed to handle a current weirdness in the
//  behavior of the g++ compiler.  On .NET you should be able to replace
//  the use of my_isspace 10 lines below with just isspace. 
bool
my_isspace( char c )
{
  return isspace(c);
}


//  Version based on iterators and the generic find_if function.

vector<string> breakup_v2( const string& line )
{
  vector<string> strings;
  string::const_iterator beg = line.begin();
  string::const_iterator end;

  while ( beg != line.end() )
    {
      //  Find the beginning of the next string
      beg = find_if( beg, line.end(), nonspace );

      if ( beg != line.end() )
        {
          end = find_if( beg, line.end(), my_isspace );  // compiler weirdness
          strings.push_back( string(beg, end ) );
          beg = end;
        }
    }

  return strings;

}


