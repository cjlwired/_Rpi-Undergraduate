// Carlos Lazo
// 11-1-04
// Homework 6
// Flight.cpp

#include "Flight.h"


bool operator< ( Flight const f0, Flight const f1 )
{
	return f0.get_ID() < f1.get_ID();
}

bool operator== ( Flight const f0, Flight const f1 )
{
	return f0.get_ID() == f1.get_ID();
}
