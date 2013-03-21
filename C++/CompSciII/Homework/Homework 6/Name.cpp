//  File:    Name.cpp
//  Author:  Chuck Stewart
//  Purpose: Implementation of comparison functions for
//    the Name class.
 

#include "Name.h"

bool operator< ( const Name& left, const Name& right )
{
  return left.last() < right.last() ||
    ( left.last() == right.last() && left.first() < right.first() );
}

bool operator== ( const Name& left, const Name& right )
{
  return left.last() == right.last() && left.first() == right.first();
}
