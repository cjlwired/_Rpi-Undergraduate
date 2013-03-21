// Carlos Lazo
// 10-20-04
// CSCI II Lab 7
// map_Lab.cpp

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>

using namespace std;

int main()
{
/*
	int hold;	// Variable to input numbers

	map <int, int> occurrences;	// Map to keep track of integers and number of times they appear

	while (cin >> hold)			// Loop to read in values and add them to the map
		++occurrences[hold];

	map <int, int>::iterator p = occurrences.begin();

	pair <int, int> mode = make_pair (p->first, p->second);

	p++;

	for (; p != occurrences.end(); p++)
		if (p->second > mode.second)
			mode = make_pair (p->first, p->second);

	cout << "MODE : " << mode.first << "\tOccurrences: " << mode.second << endl << endl;
*/
	cout << "************************" << endl;
	cout << "******** PART 2 ********" << endl;
	cout << "************************" << endl << endl;

	string temp;
	vector <string> read_Words;

	while (cin >> temp)
		read_Words.push_back(temp);

	map <string, set<string> > nearby_Words;

	for (unsigned int i = 0; i < read_Words.size(); i++)
	{ 

		for (unsigned int j = 1; j <= 3; j++)
		{
			if ( i + j < read_Words.size())
			{
				string place = read_Words[i];
				string next  = read_Words[i+j];

				nearby_Words[place].insert(next);

			}

			if ( i-j >= 0 && i > 2)
			{
				string place = read_Words[i];
				string next  = read_Words[i-j];
				
				//cout << "i" << ":" << i << endl;
				//cout << "j" << ":" << j << endl;
				//cout << "i-j" << ":" << i-j << endl << endl;
				nearby_Words[place].insert(next);
			}
		}
	}

	for (map <string, set<string> >::iterator p = nearby_Words.begin(); p != nearby_Words.end(); p++)
	{
		cout << p->first << ": ";

		for (set<string>::iterator q = p->second.begin(); q != p->second.end(); q++)
			cout << *q << " ";

		cout << endl;

	}

	return 0;
}


