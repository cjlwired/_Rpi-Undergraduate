//Carlos Lazo
//9-23-04
//Homework #3 - Diver Program ~ .cpp file

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "Diver.h"

using namespace std;

void Diver :: setName (string n)
{
	name = n;
}

void Diver :: setID (int id)
{
	ID = id;
}

void Diver :: setCountry (string c)
{
	country = c;
}

void Diver :: setPlace (int p)
{
	place = p;
}

bool Diver :: read(istream& in_str)
{

	in_str >> name;

	if (name[0] == '-')
		return false;
	
	
	in_str >> ID >> country;

	return true;
}

void Diver :: addScore (double d)
{
	scores.push_back(d);
}

ostream& Diver :: outputDiver (ostream & out_str, int choice) const
{
	if (choice == 0)
		out_str << ID << " " << name << " " << country << " " << getScore() << endl ;
	else
		out_str << ID << " " << name << " " << country << " " << getScore() << " " << getPlace() << endl ;

	return out_str;
}


bool greater_Scores (const Diver& div1, const Diver& div2)
{
	return (div1.getScore() > div2.getScore());
}

bool ID_sort (const Diver& div1, const Diver& div2)
{
	return (div1.getID() < div2.getID());
}
