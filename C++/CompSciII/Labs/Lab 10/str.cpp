
#include "str.h"
#include <iostream>
#include <cctype>

using namespace std;

//  The default constructor does not allocate an array and initializes
//  the size to 0.

str :: str( )
  : arr_( 0 ), size_(0), alloc_(0) 
{
}


//  Create a str from a single character.  Initialize an array and
//  make the size 1.

str :: str( char c )
  : arr_( new char[1] ), size_(1), alloc_(1) 
{
  arr_[0] = c;
}


//  Create a str from C-style string (char array terminated by '\0').
//  Find the size of the char array by looking for the null char.
//  Then allocate the internal array (the member variable arr_) to
//  hold the chars.  Finally, copy the chars.

str :: str( const char* cstr )
{
  //  Determine the size.  This is the number of chars before
  //  reaching the null char.

  size_ = 0;
  for ( ; cstr[size_] != '\0'; ++size_ )
    ;

  //  Allocate enough to hold the chars.

  alloc_ = size_;
  arr_ = new char[ alloc_ ];

  // Copy the chars into the allocated array

  for( unsigned int i=0; i<size_; ++i )
    arr_[i] = cstr[i];
}
  

//  Create a str by copying an existing str.  Use the copy member
//  function.

str :: str( str const& old )
  : arr_(0)
{
  this -> copy( old );
}


//  The destructor's job is to clean-up after a class object is no
//  longer in use.  In particular the destructor is called in one of
//  two cases: (1) when an automatic object goes out of scope, or (2)
//  when a dynamically allocated object is explicitly deleted.  A
//  destructor can never be called explicitly.  
//
//  The clean-up job of a destructor is to delete any dynamically
//  allocated memory owned by the object.  Therefore, an object has no
//  dynamic member, it is generally not necessary to write a
//  destructor.

str :: ~str( )
{
  delete [] arr_;
  arr_ = 0;
}


//  Change the current str by assigning the rhs str.  Don't make the
//  copy for a self-assignment (address of the rhs str equals the
//  address stored in the this pointer).  Delete the current char
//  array and copy the rhs str.  Return a reference to the current
//  str.
//  
//  Assignment operators are usually (but not alway) unnecessary for
//  an object that does not have dynamic memory.  The reason is that
//  without a user-defined assignment operator the compiler
//  automatically generates an assignment operator that applies the
//  assignment operator to each member variable.  This is generally
//  the right thing to do.

str& 
str :: operator=( str const& rhs )
{
  if ( &rhs != this )
    {
      delete [] arr_;
      arr_ = 0;
      this -> copy( rhs );
    }
  return *this;
}



//  Add a single char to the back of the str, and return a reference
//  to the str.  This is easy unless the size has reached the size of
//  the allocation (the upper limit of the array).
//

str& 
str :: operator+=( char c )
{
  if ( size_ == alloc_ ) 
    {
      alloc_ *= 2;
      if ( alloc_ == 0 ) alloc_ = 1;  // handles the initially empty str
      char * old = arr_;
      arr_ = new char[ alloc_ ];
      for ( unsigned int i = 0; i<size_; ++i )
        arr_[i] = old[i];
    }
  arr_[ size_ ] = c;       //  Place the char in the last loc
  size_ ++ ;
  return *this;
}


//  Add all of the chars in str s to the current string and return a
//  reference to the current string.  This demonstrates the use of
//  char iterators.  It uses the += operator that handles single chars
//  to do most of the work.

str& 
str :: operator+=( str const& s )
{

	int max_size = this->size_ + s.size_;

	if (this->alloc_ < max_size)
	{

		this->alloc_ += s.size_;

		char* old = arr_;

		arr_ = new char[ alloc_ ];

		for (unsigned int i = 0; i < this->size_; i++)
		{
			this->arr_[i] = old[i];
		}

		str::const_iterator itr = s.cstr();

		for (unsigned int i = this->size_; i < max_size; i++, itr++)
		{
			//cout << "LOOP 2" << endl;
			//arr_[i] = s.arr_[i - this->size_];
			this->arr_[i] = *itr;
		}

		size_ = max_size;
	}

	else
	{
		str::const_iterator itr = s.cstr();

		for (unsigned int i = this->size_; i < this->size_ + s.size_; i++)
			this->arr_[i] = *itr;
	}

	//for ( str::const_iterator itr = s.begin(); itr != s.end(); ++itr )
	//	this -> operator+= ( *itr );
	return *this;
}


//  Erase a char from the string.  This requires copying each char
//  down in the array starting from the location indicated by the
//  iterator.  Notice that we have to declare the return type as
//
//     str :: iterator
//
//  rather than just
// 
//     iterator
//
//  This is because we are outside class scope when specifying the
//  return type here

str :: iterator
str :: erase( iterator p )
{

	str::iterator itr = this->arr_;
	bool flag = true;

	for (unsigned int i = 0; i != size_ && flag; i++, itr++)
	{
		if (itr == p)
		{

			flag = false;

			size_ = size_ - 1;

			for (int j = i; j < size_; j++)
			{
				arr_[j] = arr_[j+1];
			}

			return (itr++);

		}

	}

	return p;
}


//  Build a new str from an existing one by copying a section of the
//  array.

str
str :: substr( unsigned int start, unsigned int num_chars )
{
  str s;    //  create a default str
  
  s.arr_ = new char[ num_chars ];
  s.alloc_ = num_chars;
  s.size_ = num_chars;

  for ( unsigned int i = 0; i<num_chars; ++i )
    s.arr_[i] = arr_[ start+i ];

  return s;
}


//  Copy an existing string.  The size and alloc are the same, and the
//  array is a copy of the array.

void 
str :: copy( str const& s )
{
  size_ = s . size_;
  alloc_ = s . alloc_;
  arr_ = new char[ this -> alloc_ ];

  for ( unsigned int i=0; i < this -> size_; ++i )
    arr_[ i ] = s . arr_[ i ];
}


//  Output a string, one character at a time.
 
ostream& operator<<( ostream& ostr, str const& s )
{
  for ( str::const_iterator itr = s.begin(); itr != s.end(); ++itr )
    ostr << *itr;
  return ostr;
}


//  The input operator is quite a bit more complicated than the output
//  operator.  This operator is exactly the same as the one for our
//  version of str based on vectors.

istream& operator>>( istream& istr, str& s )
{
  char c;

  // Read the first non-whitespace char.  (Recall that istr>>c will
  // skip over spaces.)  If none are there, the end of file will be
  // reached, and as a result, !(istr>>c) will be true.  Just return
  // the stream in this case.

  if ( ! ( istr >> c  ) )
    return istr;   

  s = c;   //  The char c is automatically converted to a str here.

  //  While there is more data on the input stream, get the next char
  //  and test if it is a whitespace char.  If it is, then put it back
  //  on the input stream and return.  If it is not then append it onto
  //  the str being built and keep going.

  while( istr.get(c) )
    {
      if ( isspace(c) )
        {
          istr.unget();   // put the whitespace char back on the input stream
          return istr;
        }
      s += c;             // append the non-whitespace char onto the str
    }

  //  At this point, the end of file will have been reached.  If
  //  the istr were returned as is, the current str will likely be
  //  ignored.  Therefore, clear the end of file flag.  The next
  //  time the function is called, the end of file will be
  //  detected right at the top.
  
  istr.clear(); 
  return istr;
}


//  Return true if and only if the two strs have exactly the same chars.

bool operator== ( str const& s, str const& t )
{
  //  A quick test is to compare sizes.  If they are different the two
  //  strs can not be equal.

  if ( s.size() != t.size() ) return false;

  //  Compare the two strs char by char.  If any differences are found
  //  the strs are different.

  for ( unsigned int i=0; i < s.size(); ++i )
    if ( s[i] != t[i] )
      return false;

  return true;
}

/*operator< as a member function : 

bool operator< (str const& right) const
{
	const char* s_itr = this.arr_;
	const char* t_itr = right.arr_;

	int bound;

	if (s.size_ < t.size_)
		bound = s.size_;
	else
		bound = t.size_;

	for (unsigned int i = 0; i < bound; i++, s_itr++, t_itr++)
	{
		if (*s_itr < *t_itr)
			return true;

		else if (*s_itr > *t_itr)
			cout << *s_itr << " " << *t_itr << endl;

	}

	return (s.size_ < t.size_);

}*/

bool operator< (str const& s, str const& t)
{
	const char* s_itr = s.cstr();
	const char* t_itr = t.cstr();

	int bound;

	if (s.size() < t.size())
		bound = s.size();
	else
		bound = t.size();

	for (unsigned int i = 0; i < bound; i++, s_itr++, t_itr++)
	{
		if (*s_itr < *t_itr)
			return true;

		else if (*s_itr > *t_itr)
			return false;

	}

	return (s.size() < t.size());

}


