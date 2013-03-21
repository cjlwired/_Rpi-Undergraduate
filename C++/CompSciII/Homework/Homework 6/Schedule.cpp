// Carlos Lazo
// 11-1-04
// Homework 6
// Schedule.cpp

#include "Schedule.h"

Schedule :: Schedule ()
{
	Time t;

	current_Time = t;

	total_Cost = 0.0;
}

void Schedule ::  change_Current_Time (Time t)
{
	current_Time = t;
}

void Schedule :: add_Flight (Flight f)
{
	my_Flights.push_back(f);

}

void Schedule :: change_Current_City (string c)
{
	current_City = c;
}

void Schedule :: add_Cost (double c)
{ 
	total_Cost = total_Cost + c;
}