
//  File:    test_cs2list.cpp
//  Author:  Chuck Stewart
//  Purpose:  Test some of the member functions of our own 
//   version of a list-like generic container class.

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

#include "cs2list.h"

//  Adding operator== and operator!= to aid in testing....
//

template <class T>
bool operator==( cs2list<T>& lft, cs2list<T>& rgt )
{
  if ( lft.size() != rgt.size() ) return false;

  //  The use of "typename" here looks a bit confusing.  It eliminates
  //  a warning issued by advanced compilers.  It is not clear to the
  //  compiler that cs2list<T>::iterator is a real type because T
  //  hasn't yet be specified.  
  //
  //  If you didn't get that, don't worry about it.  You will not be
  //  tested on it!

  typename cs2list<T>::iterator lft_itr = lft.begin();
  typename cs2list<T>::iterator rgt_itr = rgt.begin();
  while ( lft_itr != lft.end() )
    {
      if ( *lft_itr != *rgt_itr ) return false;
      lft_itr ++ ;
      rgt_itr ++ ;
    }
  return true;
}

template <class T>
bool operator!=( cs2list<T>& lft, cs2list<T>& rgt )
{
  return ! ( lft == rgt );
}



int
main()
{
  const int n1=20;
  int i;
  cs2list<double> list1;
  for ( i=0; i<n1; ++i )
    list1.push_back( sqrt( double((i+1)*(i+1)) ));

  cout << "list1.size() = " << list1.size() << " --- should be 20" << endl;
  cout << "list1.front() = " << list1.front() << " --- should be 1.0 " << endl;
  cout << "list1.back() = " << list1.back() << " --- should be 20.0" << endl;

  cout << "\nOutputting in reverse order:\n";
  cs2list<double>::iterator itr;

  for ( i=0; i<10; ++i )
    list1.pop_front();

  cout << "\nAfter popping 10 items off the front:\n"
       << "list1.size() = " << list1.size() << " should be 10\n";

  for ( itr = list1.begin(); itr != list1.end(); ++itr )
    cout << *itr << "\n";

  cs2list<int> int_list;
  int_list.push_back( 24 );  int_list.push_back( 33 );  int_list.push_back( 35 );
  int_list.push_back( 15 );  int_list.push_back( 66 );  int_list.push_back( 48 );
  int_list.push_back( 32 );  int_list.push_back(  3 );  int_list.push_back( 21 );

  cout << "\nHere's an int list:  " << endl;
  cs2list<int>::iterator p;
  for ( p = int_list.begin(); p != int_list.end(); ++p )
    cout << *p << endl;

  p = int_list.begin();
  while ( p != int_list.end() )
    if ( *p % 2 == 1 )
      p = int_list.erase( p );
    else
      p ++ ;

  cout << "\nHere's the int list after erasing odds:" << endl;
  for ( p = int_list.begin(); p != int_list.end(); ++p )
    cout << *p << endl;

  cs2list<string> b;
  b.push_back( string("hi") );
  cs2list<string>::iterator s_itr = b.begin();
  s_itr = b.insert( s_itr, string("low") );
  s_itr = b.insert( s_itr, string("lower") );
  b.push_back( string("higher") );
  s_itr ++ ; //  should be at low
  s_itr ++ ; //  should be at hi
  s_itr ++ ; //  should be at higher 
  s_itr = b.insert( s_itr, string("high") );

  cout << "\n\nlist of strings should be:  lower, low, hi, high, higher\nIt is:  "
       << endl;
  for ( s_itr = b.begin(); s_itr != b.end(); ++ s_itr )
    cout << *s_itr  << " ";

  cout << endl;

  cout << endl << "TESTING OUT CLEAR FUNCTION" << endl << endl;

  b.clear();

  cout << "The new list is: ";

  for ( s_itr = b.begin(); s_itr != b.end(); ++ s_itr )
    cout << *s_itr  << " "; 

  cout << "\nThis should be empty!" << endl << endl;

  s_itr = b.begin();

  s_itr = b.insert( s_itr, string("low") );
  s_itr = b.insert( s_itr, string("lower") );
  s_itr = b.insert( s_itr, string("high") );

  for ( s_itr = b.begin(); s_itr != b.end(); ++ s_itr )
    cout << *s_itr  << " ";

  cout << endl << endl;

  return 0;
}