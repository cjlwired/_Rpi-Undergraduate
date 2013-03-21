// Carlos Lazo
// 11-15-04
// Homework #7
// Occurence.h

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Occurence
{

	public:

		// Constructor

		Occurence (string name, string keyword, map <string, int>);

		// Functions to return private varibles

		string get_Name() const { return name; }
		string get_Keyword() const { return keyword; }
		int get_Count() const { return count; }

	private:

		string name;
		string keyword;
		int count;

};

// Used to compare two Occurences

bool compare (const Occurence& left, const Occurence& right);