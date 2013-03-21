// Carlos Lazo
// 11-15-04
// Homework #7
// Occurence.cpp

#include "Occurence.h"

// Constructor for Occurence

Occurence :: Occurence (string n, string k, map <string, int> keywords)
{
	// Assign n to Occurence's name

	name = n;

	// Assign k to Occurence's keyword

	keyword = k;

	//Take the map and iterate through it until it finds k.
	// Then assign Occurence's count to that keyword's count.

	bool flag = true;

	for (map <string, int> :: iterator m = keywords.begin(); m != keywords.end() && flag; m++)
	{
		if (m->first == k)
		{
			flag = false;
			count = m->second;
		}
	}

}

bool compare (const Occurence& left, const Occurence& right)
{
	return (left.get_Count() > right.get_Count()) ||
		((left.get_Count() == right.get_Count()) && (left.get_Name() < right.get_Name()));
}