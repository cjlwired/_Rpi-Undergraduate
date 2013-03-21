// Carlos Lazo
// 10-13-04
// Computer Science II
// Homework #5 - Pair.cpp

#include <iostream>
#include <string>

#include "Pair.h"

using namespace std;

Pair::Pair (string& s)
{
	my_Name = s;

	my_Count = 1;
}

void Pair::increment ()
{
	my_Count++;
}

bool count_Greater( Pair one, Pair two )
{
  return one.get_Count() > two.get_Count();
}

