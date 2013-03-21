//   File: str_main.cpp
//
//   Main program to test the str class.  Every member function is
//   exercised at least once.  Note carefully the use of the
//   iterators.

#include <cctype>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;;

#include "str.h"

int
main()
{
  // Use default constructor
  str s1;
  cout << "Size (should be 0):  " << s1.size() << endl;

  str s2( 'a' );
  cout << "Size (should be 1):  " << s2.size() << ", s2 = "
       << s2 << endl;

  str s3( "abc" );
  cout << "Size (should be 3):  " << s3.size() << ", s3 = "
       << s3 << endl;

  str s4( s3 );
  cout << "Size (should be 3):  " << s4.size() << ", s4 = "
       << s4 << endl;

  s1 = s4;
  cout << "Size (should be 3):  " << s1.size() << ", s1 = "
       << s1 << endl;

  cout << "s1[1] = " << s1[1] << endl;

  s3 = "def";
  cout << "s3 is now " << s3 << endl;
  s4 += s3;
  cout << "s4 after += s3:  " << s4 << endl;

  s4 += 'g';
  cout << "s4 after += 'g':  " << s4 << endl;

  s2.clear();
  cout << "After clearing s2, s2.size() = " << s2.size() << endl;

  //  Onto str iterators:
  s2 = "ABcdeFgHiJKLmnopQrSTuvWXyXZ";
  cout << "\nUsing iterators and erase to remove the caps from s2: "
       << s2 << endl;
  str::iterator i = s2.begin();
  while ( i != s2.end() )
    {
      if ( isupper( *i ) )
        i = s2.erase(i);
      else
        ++i;
    }

  cout << "Afterwards, s2 = " << s2 << endl;

  s3 = "abcdefghijklmnop";
  cout << "s3 = " << s3 << "\n"
       << "s3.substr( 5, 4 ) = " << s3.substr(5,4) << endl;

  s1 = "abc";
  s2 = "abcd";
  s3 = "Abc";
  s4 = "abc";
  cout << "Testing operator== \n"
       << s1 << " == " << s2 << " is " << (s1 == s2) << "\n"
       << s1 << " == " << s3 << " is " << (s1 == s3) << "\n"
       << s1 << " == " << s4 << " is " << (s1 == s4) << "\n";

  //  Add tests for erase here.

  cout << "\n\nTESTING ERASE:\n\n" << endl;

  str::iterator gone = s1.begin();

  str::iterator gone2 = s2.begin();
	gone2++;
  str::iterator gone3 = s3.begin();
	gone3++;
	gone3++;

  s1.erase(gone);

  cout << "s1 : " << s1 << endl;

  s2.erase(gone2);
  
  cout << "s2 : " << s2 << endl;;

  s3.erase(gone3);

  cout << "s3 : " << s3 << endl << endl;

  //  Tests for operator<
  cout << "s1 < s2 (should be 1) " << (s1<s2) << endl;
  cout << "s2 < s3 (should be 0) " << (s2<s3) << endl; 

  return 0;
  //  Destructors are called automatically for each of s1, s2, s3, s4
}
