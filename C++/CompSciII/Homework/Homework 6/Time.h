//  File:    Time.h
//  Author:  Chuck Stewart
//  Purpose: Represent a time of day, including hours and minutes.
//    A function is provided to compute the difference in minutes
//    between two times, and operators are provided to compare times.
//    In addition, an output operator is defined. 
 
#ifndef Time_h_
#define Time_h_

#include <iostream>
using namespace std;

class Time {
 public:
  Time( int hour0=0, int minute0=0 )
    : m_hour(hour0), m_minute(minute0) {}
  int hour() const { return m_hour; }
  int minute() const { return m_minute; }
 private:
  int m_hour, m_minute;
};

//  Return the difference in minutes between two times.  If you want
//  to know how much later in the day time x is than time y then you
//  should make the function call
//     diff_in_minutes( x, y )
int diff_in_minutes( Time const& t0, Time const& t1 );

bool operator< ( Time const& t0, Time const& t1 );

bool operator== ( Time const& t0, Time const& t1 );

//  Function to provide output so that a Time t can be output simply
//  as 
//     cout << t;
ostream& operator<< ( ostream& ostr, Time const& t );

#endif
