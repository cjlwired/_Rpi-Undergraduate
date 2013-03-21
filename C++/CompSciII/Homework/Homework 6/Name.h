//  File:    Name.h
//  Author:  Chuck Stewart
//  Purpose: Represent a name, including first and last name strings,
//    and provide comparison operators.  The implementation of the 
//    comparison operators is in Name.cpp.

#ifndef Name_h_
#define Name_h_

#include <string>
using std::string;

class Name {
public:
  Name( string const& in_first, string const& in_last ) :
    m_first( in_first ), m_last( in_last ) {}

  const string& first() const { return m_first; }
  const string& last() const { return m_last; }

private:
  string m_first;
  string m_last;
};


bool operator< ( const Name& left, const Name& right );

bool operator== ( const Name& left, const Name& right );

#endif

