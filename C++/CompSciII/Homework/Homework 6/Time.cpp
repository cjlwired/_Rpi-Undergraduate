//  File:    Time.cpp
//  Author:  Chuck Stewart
//  Purpose: Implementation of comparison and output functions for
//    the Time class.
 
#include "Time.h"

int 
diff_in_minutes( Time const& t0, Time const& t1 )
{
  int t0_minutes = t0.hour()*60 + t0.minute();
  int t1_minutes = t1.hour()*60 + t1.minute();
  return t0_minutes - t1_minutes;
}

bool
operator< ( Time const& t0, Time const& t1 )
{
  return t0.hour() < t1.hour() || 
    ( t0.hour() == t1.hour() && t0.minute() < t1.minute() );
}

bool
operator== ( Time const& t0, Time const& t1 )
{
  return t0.hour() == t1.hour() && t0.minute() == t1.minute();
}

//  Function to provide output so that a Time t can be output simply
//  as 
//     cout << t;
ostream&
operator<< ( ostream& ostr, Time const& t )
{
  if ( t.minute() < 10 )
    ostr << t.hour() << ":0" << t.minute();
  else
    ostr << t.hour() << ":" << t.minute();
  return ostr;
}

