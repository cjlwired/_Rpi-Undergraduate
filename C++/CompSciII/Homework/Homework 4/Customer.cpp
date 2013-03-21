// Carlos Lazo
// 10-7-04
// Homework #4
// Customer.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>

#include "Customer.h"

using namespace std;

// Constructor

Customer::Customer(string& n)
{
	my_Name = n;
}

// Allows the name of the Customer to be changed

void Customer::set_Name(string& n)
{
	my_Name = n;
}

// Checks to see if the Song sent is already in the list
// If it is, return true - otherwise, return false

bool Customer::song_In_List (string search)
{
	list <Song>::iterator p = my_Songs.begin();

	for (; p != my_Songs.end(); p++)
	{
		if ((*p).get_Name() == search)
			return true;
	}

	return false;
}

// Finds the index at which the song is located in the list

list <Song>::iterator find_Song (string search, list <Song>& my_Songs)
{

	list <Song>::iterator p = my_Songs.begin();

	for (; p != my_Songs.end(); p++)
	{
		if ((*p).get_Name() == search)
			return p;
	}

	return p;
}

// Adds a song to the Customer's list
// If the song is not found, then add it to the list
// If the song is already in the list, then increment its download count by 1
	
void Customer::add_Song(Song& s)
{

	string search = s.get_Name();

	if (!(song_In_List(search)))
	{
		Song t(s.get_Name(), s.get_ID());
		
		my_Songs.push_back(t);
	}

	else
	{

		list <Song>::iterator p = find_Song(s.get_Name(), my_Songs);

		(*p).increment();
	}
}

double Customer::getCost()
{

	list <Song> songs = getSongs();

	double cost = 0.0;
	
	list <Song>::iterator p = songs.begin();

	for (; p != songs.end(); p++)
	{

		int count = (*p).get_Download_Count();

		cost = cost + .5;

		count = count - 5;

		if (count > 0)
		{
			cost = cost + (.5 * count);
		}
	}

	return cost;

}

// Prints the Songs of each Customer

void Customer::print_Songs()
{
	cout << getName() << " " << "$" << getCost() << endl;

	list <Song>::iterator p = my_Songs.begin();
	list <Song>::iterator q = my_Songs.end();
	
	if (my_Songs.size() == 1) // One song in the list
	{
		cout << " " << (*p).get_ID() << " " << (*p).get_Download_Count() << " " << endl;
	}

	else
	{

		for (; p != q; p++)
		{

			Song s = *p;

			int ID = s.get_ID();

			int dC = s.get_Download_Count();

			cout << " " << ID << " " << dC << " " << endl;

		}
	}
}