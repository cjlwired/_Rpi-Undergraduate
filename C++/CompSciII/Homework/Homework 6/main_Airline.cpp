// Carlos Lazo
// 11-1-04
// Homework 6
// main_Airline.cpp

#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Flight.h"
#include "Time.h"
#include "Name.h"
#include "Schedule.h"

using namespace std;

// This is a function that can be used to print all the Flights inputed

void print_Flights ( map <Flight, int> f)
{

	for (map <Flight, int>:: iterator p = f.begin(); p != f.end(); p++)
	{

		cout << p->first.get_ID() << " " << p->first.get_Departure_City() << " " << p->first.get_Departure_Time() << " " << p->first.get_Arrival_City()
		 << " " << p->first.get_Arrival_Time() << " " << p->first.get_Cost() << " " << p->first.get_Capacity() << "\n\n";
	}

}

// Function checks to see if the Flight with f_ID is a valid Flight

bool valid_Flight (map <Flight, int>& all_Flights, int f_ID)
{

	for (map <Flight, int> :: iterator p = all_Flights.begin(); p != all_Flights.end(); p++)
	{
		if (p->first.get_ID() == f_ID)
			return true;
	}

	return false;
}

// Function returns an iterator where the given Flight is located

map <Flight, int> :: iterator get_Flight (map <Flight, int>& all_Flights, int f_ID)
{

	for (map <Flight, int> :: iterator p = all_Flights.begin(); p != all_Flights.end(); p++)
	{
		if (p->first.get_ID() == f_ID)
			return p;
	}

	return all_Flights.end();
}

// Function that checks whether or not passenger has a schedule conflict or not

bool check_Valid_Time ( map <Flight, int> :: iterator f, map <Name, Schedule> :: iterator p)
{

	return ( diff_in_minutes (f->first.get_Departure_Time(), p->second.get_Current_Time())) >= 30;
}

// Function ensures that the passenger is taking a Flight from the arrival city of the previous Flight

bool check_Valid_Travel ( map <Flight, int> :: iterator f, map <Name, Schedule> :: iterator p)
{
	
	if (p->second.get_My_Flights().size() == 0)
		return true;

	else
		return (p->second.get_Current_City() == f->first.get_Departure_City());

	return false;
}


// DECLARATION OF QUERY FUNCTIONS

// add_Flight will serve as the input query for 0.

void add_Flight (map <Flight, int>& all_Flights, map <Name, Schedule>& passengers )
{

	int f_ID;	

	cin >> f_ID;	// read in Flight ID

	string f_Name;	// read in corresponding first and last name
	string l_Name;

	cin >> f_Name;
	cin >> l_Name;

	Name my_Name (f_Name, l_Name);	// initialize a Name using two previous variables

	// Checks to see if ID is in the Flight map

	if ( valid_Flight(all_Flights, f_ID))
	{

		map <Flight, int> :: iterator f = get_Flight (all_Flights, f_ID);

		// Checks to see if the Flight is full

		if (f->first.get_Capacity() == f->second)
			cout << "Flight " << f_ID << " is full" << endl << endl;

		else
		{

			// First, check to see if passenger is already in the passenger map
			// If not, add passenger

			if (passengers.find (my_Name) == passengers.end())
			{

				Schedule x;
			
				passengers.insert (make_pair (my_Name, x));	// Insert new passenger into map

			}

			map <Name, Schedule> :: iterator p = passengers.find (my_Name);		// Find the passenger in the map

			// Just for reference, at this point, iterator f refers to the Flight in question
			// and iterator p referes to the passenger

			// If time and destination are valid according to passengers schedule, add the flight to his vector of Flights.
			// Change his current_Time to that of the arrival time of the arriving flight. Also, increase the
			// capacity of the flight by one. Then print out confirmation.

			if (check_Valid_Time (f, p) && check_Valid_Travel (f ,p))
			{

				p->second.add_Flight(f->first);		// Add Flight to passengers Schedule

				Time new_Time = f->first.get_Arrival_Time();

				p->second.change_Current_Time (new_Time);	// Change passengers current time

				p->second.change_Current_City (f->first.get_Arrival_City());	// Change passengers current city

				p->second.add_Cost (f->first.get_Cost());	// Add cost of Flight to passengers total_Cost

				f->second++;	// Increase # of passengers on the given Flight by 1

				cout << my_Name.first() << " " << my_Name.last() << " was added to Flight " << f_ID << endl << endl;

			}
			
			else 
			{
				cout << "Conflicts with schedule of " << my_Name.first() << " " << my_Name.last() << endl << endl;
			}

		}
	}

	// If f_ID is not a valid Flight, output the following statement
	else
		cout << "No flight " << f_ID << endl << endl;

}

// list_Flights will serve as the input query for 1.

void list_Flights (map <Flight, int>& all_Flights)
{

	string city_One;

	cin >> city_One; // read in departure city

	string city_Two;

	cin >> city_Two; // read in arrival city

	map <Flight, int> store_Flights;	// will be used to store all matching Flights from city_One to city_Two
	vector <int> current_Capacity;		// Will be used to store current capacity of Flight when added to map


	// For-loop that adds a Flight to the map store_Flights if it is going from city_One
	// to city_Two.

	for (map <Flight, int> :: iterator f = all_Flights.begin(); f != all_Flights.end(); f++)
	{
		
		string compare1 = f->first.get_Departure_City();	// Get corresponding 
		string compare2 = f->first.get_Arrival_City();

		if (compare1 == city_One && compare2 == city_Two)
			store_Flights.insert (make_pair (f->first, f->second));
	}

	cout << "Flights between " << city_One << " and " << city_Two << endl;

	// If the map is empty, then there are no Flights from city_One to city_Two
	
	if (store_Flights.begin() == store_Flights.end())
		cout << "none\n\n";

	// Otherwise, output the required information

	else
	{
		for (map <Flight, int>:: iterator f = store_Flights.begin(); f != store_Flights.end(); f++)
		{

			cout << f->first.get_ID() << " " << f->first.get_Departure_Time() << " " << f->first.get_Arrival_Time() 
				<< " $" << f->first.get_Cost() << " " << (f->first.get_Capacity() - f->second) << "\n";
		}

		cout << endl;
	}

}

// print_Schedule will serve as the input query for 2

void print_Schedule (map <Name, Schedule>& passengers)
{

	string f_Name;	// read in corresponding first and last name
	string l_Name;

	cin >> f_Name;
	cin >> l_Name;

	Name my_Name (f_Name, l_Name);	// initialize a Name using two previous variables

	// If passenger does not exist of if his Flight vector is empty, he has no travel schedule

	if ((passengers.find (my_Name) == passengers.end()) || (passengers.find (my_Name)->second.get_My_Flights().size() == 0))
		cout << my_Name.first() << " " << my_Name.last() << " has no travel schedule\n\n";

	// Otherwise, print all of the required data

	else 
	{

		// Get the Flights (stored as a vector) of the passenger

		vector <Flight> my_Flights = passengers.find (my_Name)->second.get_My_Flights();

		cout << "Travel schedule for " << my_Name.first() << " " << my_Name.last() << endl;

		for (int i = 0; i < my_Flights.size(); i++)
			cout << my_Flights[i].get_ID() << " " << my_Flights[i].get_Departure_City() << " " << my_Flights[i].get_Departure_Time()
			<< " " << my_Flights[i].get_Arrival_City() << " " << my_Flights[i].get_Arrival_Time() << endl;

		double total_Cost = passengers.find (my_Name)->second.get_Total_Cost();

		cout << "$" << total_Cost << endl << endl;

	}
}

// passenger_List will serve as the input query for 3

void passenger_List (map <Flight, int>& all_Flights, map <Name, Schedule>& passengers)
{	
	int f_ID;

	cin >> f_ID;	// read in Flight ID

	// Checks to see if the Flight beging asked for is in the map

	if ( valid_Flight(all_Flights, f_ID))
	{
		
		map <Name, Schedule> store_Passengers;

		int passengers_On_Flight = 0;		// Used to keep track of # of passengers that are on the given Flight

		bool flag;							// Helping efficiency by exiting the inner while loop when the Flight is found

		// For loop will check to see if a passenger is on the given Flight. If so, add him to a map for storage

		for (map <Name, Schedule> :: iterator p = passengers.begin(); p != passengers.end(); p++)
		{
			flag = true;

			// get the Flights of the passenger and create an iterator from that vector

			vector <Flight> my_Flights = p->second.get_My_Flights();

			vector <Flight> :: iterator f = my_Flights.begin();

			// As long as the flag is true and you don't reach the end of the iterator,
			// check to see if the Flight ID of the current Flight matches the ID that was
			// inputed.  If so, store this passenger into a map, set the flag equal to false
			// to kick out of the loop, and increment the number of people taking this flight by one.

			while (flag && f != my_Flights.end())
			{

				if (f->get_ID() == f_ID && flag)
				{

					string first  =  p->first.first();
					string last = p->first.last();

					Name temp (first, last);

					store_Passengers.insert (make_pair (temp, p->second));

					flag = false;

					passengers_On_Flight++;
				}

				f++;	// Increment iterator to check next Flight
			}
		}

		cout << "Passengers for Flight " << f_ID << endl;

		// If the map size is 0, which means that no passengers are on the Flight, print the following

		if (store_Passengers.size() == 0)
			cout << "none\n$0\n\n";

		else
		{

			int counter = 1;	// Used for printing purposes

			// Print out all required passenger information along with total cost of Flight

			for (map <Name, Schedule> :: iterator p = store_Passengers.begin(); p != store_Passengers.end(); p++, counter++)
			{
				cout << counter << ". " << p->first.last() << ", " << p->first.first() << endl;
			}

			// Find Flight and print out the total cost for the passengers on the Flight

			map <Flight, int> :: iterator x = get_Flight (all_Flights, f_ID);

			cout << "$" << (x->first.get_Cost() * passengers_On_Flight) << endl << endl;

		}

	}

	else
		cout << "Flight " << f_ID << " does not exist.\n\n";

}

// one_Stop_Flights will serve as the input query for 4

void one_Stop_Flights (map <Flight, int> all_Flights)
{

	string city_One;
	string city_Two;

	cin >> city_One;	// read in names of the two cities in questionsh
	cin >> city_Two;

	cout << "One stop flights from " << city_One << " to " << city_Two << endl;

	bool flag = true;	// Will be used to see if a one stop Flight is ever found

	// Find Flights from city_One to an intermediate city

	for (map <Flight, int> :: iterator f = all_Flights.begin(); f != all_Flights.end(); f++)
	{
		// Run code in in if statement if a Flight leaves from city_One to an intermediate city

		if (city_One == f->first.get_Departure_City())
		{

			// Create another iterator that again starts at the beginning of the Flight vector

			for (map <Flight, int> :: iterator g = all_Flights.begin(); g != all_Flights.end(); g++)
			{

				// Now, check the following conditions
					// Check to see if the intermediate city can connect to city_Two
					// Check to see that intermediate city has a connecting Flight elsewhere
					// Check to see if the time difference between the second Flight and the first Flight >= 30 minutes

						// If all of the following are true, print out the information for the first Flight and the
						// second Flight. Print out total cost as well.
				

				if ((city_Two == g->first.get_Arrival_City()) && 
					(f->first.get_Arrival_City() == g->first.get_Departure_City()) &&
					(diff_in_minutes (g->first.get_Departure_Time(), f->first.get_Arrival_Time()) >= 30))
				{

					cout << f->first.get_ID() << " " << city_One << " " << f->first.get_Departure_Time()
						 << " " << f->first.get_Arrival_City() << " " << f->first.get_Arrival_Time() << endl;

					cout << g->first.get_ID() << " " << g->first.get_Departure_City() << " " << g->first.get_Departure_Time()
						 << " " << g->first.get_Arrival_City() << " " << g->first.get_Arrival_Time() << endl;

					cout << "$" << (f->first.get_Cost() + g->first.get_Cost()) << endl;

					flag = false;	// If this flag becomes false, then atleast one connecting Flight was found
				}	
			}
		}	
	}

	if (flag == false)
		cout << endl;	// For formatting purposes

	// If the flag is still true, this means that no connecting Flights were found. Show that there
	// are no connecting Flights.

	if (flag)	
		cout << "none\n\n";
}


// ***************************************
//              MAIN FUNCTION
// ***************************************


int main()
{
	map <Flight, int> all_Flights;	// This map will read in and hold all of the available Flights
									// with the key being the flight and the int being the number 
									// being the number of passengers on the flight

	
	int read_ID; // Used to read in the flight ID's		

	while ((cin >> read_ID) && (read_ID != 0))
	{

		string read_DC;

		cin >> read_DC;	// read in departing city of Flight

		int dcT1;
		int dcT2;

		cin >> dcT1;	// read in both numbers of the departing city of Flight
		cin >> dcT2;

		Time read_DT (dcT1, dcT2);	// create departing time of Flight

		string read_AC;

		cin >> read_AC; // read in arrival city of Flight

		int acT1;
		int acT2;

		cin >> acT1;	// read in both numbers of the arrival city of Flight
		cin >> acT2;
		
		Time read_AT (acT1, acT2);
		
		float read_Cost;

		cin >> read_Cost;	// read in cost of Flight

		int read_Capacity;

		cin >> read_Capacity; // read in capacity of Flight

		// create Flight and add it to the vector

		Flight f (read_ID, read_DC, read_DT, read_AC, read_AT, read_Cost, read_Capacity);

		all_Flights.insert ( make_pair (f, 0));
		
	}

	map <Name, Schedule> passengers;	// Map created to store passengers and their Schedules

	int choice;		// integer declared that will be used to take in the input queries

	while (cin >> choice && choice != 5)
	{
		if (choice == 0)	// If choice is 0, add a Flight to the given passenger
	
			add_Flight (all_Flights, passengers);	// Adds Flight to the passenger

		if (choice == 1)	// If choice is 1, print out Flights from city_One to city_Two

			list_Flights (all_Flights);

		if (choice == 2)	// If choice is 2, print out Schedule for the given passenger

			print_Schedule (passengers);

		if (choice == 3)	// If choice is 3, print out all passengers on the requested Flight

			passenger_List (all_Flights, passengers);

		if (choice == 4)	// If choice 

			one_Stop_Flights (all_Flights);

	}

	return 0;

}

