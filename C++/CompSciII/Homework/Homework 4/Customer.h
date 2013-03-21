// Carlos Lazo
// 10-7-04
// Homework #4
// Customer.h

#ifndef customer_h_
#define customer_h_

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "Song.h"

using namespace std;


class Customer
{
	public:

		Customer (string& n);

		string getName() { return my_Name;}
		list <Song> getSongs() {return my_Songs;}

		void set_Name (string& n);
		void add_Song (Song& s);
		void print_Songs ();

		double getCost();

		bool song_In_List (string search);

	private:
	
		string my_Name;
		list <Song> my_Songs;

};

#endif
