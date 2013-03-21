// Carlos Lazo
// 11-1-04
// Homework 6
// Flight.h

#ifndef Schedule_h_
#define Schedule_h_

#include <iostream>
#include <string>
#include <vector>

#include "Time.h"
#include "Flight.h"

class Schedule
{

	public:

		Schedule(); 

		// Functions used to access private data of a Schedule

		Time get_Current_Time() const { return current_Time; }
		vector <Flight> get_My_Flights() const { return my_Flights; }
		string get_Current_City() const { return current_City; }
		double get_Total_Cost() const { return total_Cost; }

		// Generic function prototypes

		void change_Current_Time (Time t);
		void change_Current_City (string c);
		void add_Flight (Flight f);
		void add_Cost (double c);

	private:

		Time current_Time;
		vector <Flight> my_Flights;
		string current_City;
		double total_Cost;

};

#endif