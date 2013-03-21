// Carlos Lazo
// 10-7-04
// Homework #4
// music_Database.cpp

#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <list>
#include <vector>

#include "Customer.h"
#include "Song.h"

using namespace std;

bool customer_In_Vector (string search, vector <Customer> customers)
{
	vector <Customer>::iterator p = customers.begin();

	for (; p != customers.end(); p++)
	{
		if ((*p).getName() == search)
			return true;
	}

	return false;
}

vector <Customer>::iterator find_Customer (string search, vector <Customer>& customers)
{
	//cout << "(find_Customer) : Searching for customer \"" << search << "\"" << endl;

	vector <Customer>::iterator p = customers.begin();

	for (; p != customers.end(); p++)
	{
		//cout << "(find_Customer) :   Testing \"" << search << "\" = \"" << p->getName() << "\"" << endl;
                if ((*p).getName() == search)
			return p;
	} 

	return p;
}

void printInfo (vector <Customer>& customers)
{
	
	// Store all songs that are found all Customer Song lists

	vector <string> temp;

	for (unsigned int i = 0; i < customers.size(); i++)
	{
		list <Song> songs = customers[i].getSongs();

		list <Song>::iterator p = songs.begin();

		for (; p != songs.end(); p++)
		{
			temp.push_back((*p).get_Name());
		}
	}

	sort (temp.begin(), temp.end());

	// Take temporary string vector and eliminate all copies

	vector <string> sNames;

	sNames.push_back(temp[0]);

	for (unsigned int i = 0; i < temp.size() - 1; i++)
	{
		if (temp [i] != temp [i+1])
			sNames.push_back(temp [i+1]);
	}

	// Store all instances of the Songs in an integer array

	vector <int> sCount (sNames.size(), 0);

	for (unsigned int c = 0; c < sNames.size(); c++)
	{

		string compare = sNames[c];

		for (unsigned int i = 0; i < customers.size(); i++)
		{
			list <Song> songs = customers[i].getSongs();

			list <Song>::iterator p = songs.begin();

			for (; p != songs.end(); p++)
			{
				if ((*p).get_Name() == compare)
					sCount[c]++;
			}
		}
	}

	for (unsigned int x = 0; x < sNames.size(); x++)
		cout << sNames[x] << " " << sCount[x] << endl;

}
	
int main()
{

	// Temporary variables used to read in values

	string cname;
	int ID;
	string sname;

	// The following three vectors will be used as parallel vectors and will
	// not be changed or altered.

	vector <string> customer_Name;
	vector <int> song_ID;
	vector <string> song_Name;

	while (cin >> cname >> ID >> sname)
	{
		customer_Name.push_back(cname);
		song_ID.push_back(ID);
		song_Name.push_back(sname);
	}

	// A vector of Customers is created to store all of the information

	vector <Customer> customers;

	// Adding the first member of the list

	Customer c (customer_Name[0]);
	Song s (song_Name[0], song_ID[0]);
	c.add_Song (s);
	customers.push_back(c);
        //cout << "Interaction #1: Name=\"" << c.getName() << "\" Song=\"" << s.get_Name() << "\" (ID: \"" << s.get_ID() << "\")" << endl;

	for (unsigned int i = 1; i < customer_Name.size(); i++)
	{

		//cout << "Interaction #" << (i + 1) << ": Name=\"" << customer_Name[i] << "\" Song=\"" << song_Name[i] << "\" (ID: \"" << song_ID[i] << "\")" << endl;;

		if (!(customer_In_Vector (customer_Name[i], customers)))
		{
			//cout << "  Customer \"" << customer_Name[i] << "\" not found." << endl;
                        Customer x (customer_Name[i]);
			Song t (song_Name[i], song_ID[i]);
			x.add_Song(t);
			customers.push_back(x);
                        //cout << "  New customer!  \"" << x.getName() << "\" downloaded song \"" << t.get_Name() << "\" (ID: \"" << t.get_ID() << "\")" << endl;
		}

		else
		{
			//cout << "  Found old customer: \"" << customer_Name[i] << "\"" << endl;
			vector <Customer>::iterator p = find_Customer(customer_Name[i], customers);
			Song t (song_Name[i], song_ID[i]);
                        //cout << "  \"" << p->getName() << "\" downloaded song \"" << t.get_Name() << "\" (ID: \"" << t.get_ID() << "\")" << endl;
			(*p).add_Song (t);
			
		}
	}

	printInfo(customers);

	cout << endl;
	
	for (unsigned int i = 0; i < customers.size(); i++)
	{
		customers[i].print_Songs();
		cout << endl;
	}

}