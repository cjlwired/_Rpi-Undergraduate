
//  File:     str.h
//  Author:   Chuck Stewart
//
//  Purpose: Our own string class.  This uses a dynamically-allocated,
//     internal char array.  Therefore, it is a good starting point
//     for demonstrating classes that have their own internal dynamic
//     memory.  This necessitates writing a correct copy constructor,
//     a correct assignment operator, and a correct destructor.
//
//     One special challenge of str class objects is that they can
//     grow and shrink during their lifetimes.  Growth occurs through
//     the += operator and shrinking occurs through the erase
//     function.  Shrinking is easy, but growth is hard.  If the
//     growth reaches the size of the array we have a problem.  In
//     this case we allocate a new array that has twice the entries of
//     the current array, and then copy the contents of the current
//     array into the new one.   While this seems expensive, it does
//     not occur very often.
//
//  Member variables:  With the foregoing in mind, here's an outline
//     of the class member variables and their purpose:
//
//        arr_      -  the array to hold the chars 
//        size_     -  the number of chars in the array
//        alloc_    -  the number of chars in the array allocation
//
//     We could have made each of these a pointer.  Think about how!
//


#include <iostream>
#include <vector>

using std::istream;
using std::ostream;

class str {
public:
  typedef char*  iterator;
  typedef const char* const_iterator;

private:   // placed here to see them before the member functions
  char * arr_;
  unsigned int size_;
  unsigned int alloc_;

public:
  //  four constructors
  str( );
  str( char c );
  str( const char * cstr );
  str( const str& old );
  
  //  Destructor
  ~str(); 

  //  Assignment
  str& operator=( str const& rhs );

  //  Subscripting operators just use the array subscripting
  //  operators.
  char& operator[] ( int i ) { return arr_[i]; }
  const char& operator[] ( int i ) const { return arr_[i]; }

  unsigned int size() const { return size_; }

  //  Return the pointer to the array.  This is a const char* to
  //  prevent it from being changed
  const char* cstr() const { return arr_; }

  //  Append operators
  str& operator+= ( char c );
  str& operator+= ( str const& s );

  /*

  operator< as a member function

  bool operator< (str const& right) const;

  */

  //  Functions to remove the contents
  void clear() { size_ = 0; }
  iterator erase( iterator p );

  //  Create a new str from an interval within the current str.
  str substr( unsigned int start, unsigned int num_chars );

  //  Iterator definitions and functions
  iterator begin() { return arr_; }
  iterator end() { return arr_ + size_; }
  const_iterator begin() const { return arr_; }
  const_iterator end() const { return arr_ + size_; }

private:
  //  Member function that is private because it is 
  //  only used internally.
  void copy( const str& s );
};


//  Stream operator prototypes.  They are neither members nor friends
//  because the operations on the str they require are available
//  through the public interface.

ostream& operator<<( ostream& ostr, const str& s );
istream& operator>>( istream& istr, str& s );


//  operator==  doesn't need to be a member function and
//  doesn't need to be a friend.  It interacts with the class
//  through its public member functions

bool operator== ( const str& s, const str& t );

bool operator< (const str& s, const str& t);

