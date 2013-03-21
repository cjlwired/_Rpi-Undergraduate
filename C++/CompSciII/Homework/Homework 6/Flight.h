// Carlos Lazo
// 11-1-04
// Homework 6
// Flight.h

#ifndef Flight_h_
#define Flight_h_

#include <iostream>
#include <string>

#include "Time.h"

using namespace std;

class Flight
{

	public: 

		// Constructor is being defined here in the following code. 

		Flight (int ID, string dep_City, Time dep_Time, string arr_City, Time arr_Time, float cost, int capacity)
		:
		  my_ID (ID), departure_City (dep_City), departure_Time (dep_Time), arrival_City (arr_City),
			  arrival_Time (arr_Time), my_Cost (cost), my_Capacity (capacity) {}

		// Functions defined below are all to return the private variables of a Flight

		int get_ID() const { return my_ID; }
		string get_Departure_City() const { return departure_City; }
		Time get_Departure_Time() const { return departure_Time; }
		string get_Arrival_City()  const { return arrival_City; }
		Time get_Arrival_Time() const { return arrival_Time; }
		float get_Cost() const { return my_Cost; }
		int get_Capacity() const { return my_Capacity; }

		// Generic function prototypes

	private:

		int my_ID;				// Flight's ID
		string departure_City;  // Flight's Departure City
		Time departure_Time;    // Flight's Departure Time
		string arrival_City;	// Flight's Arrival City
		Time arrival_Time;		// Flight's Arrival Time
		float my_Cost;			// Flight's Cost
		int my_Capacity;		// Flight's Maximum Capacity

};

bool operator< ( Flight const f0, Flight const f1 );

bool operator==  ( Flight const f0, Flight const f1 );

#endif

