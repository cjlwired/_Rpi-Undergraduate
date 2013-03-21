// Carlos Lazo
// 10-6-04
// Lab #6 - Generic Functions and String Manipulation

#include <iostream>
#include <cctype>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

bool non_Space (char c)
{
	return !isspace(c);
}

bool empty_Line (string line)
{
	if (find_if(line.begin(), line.end(), non_Space) == line.end())
		return true;

	return false;
}

string remove_Punct (const string& line)
{

	string s = line;

	string::iterator p = remove_if (s.begin(), s.end(), ispunct);

	s.erase(p, s.end());

	for (unsigned int i = 0; i < s.length(); i++)
		s[i] = tolower(s[i]);

	return s;
}

string remove_Space (const string& line)
{

	string::const_iterator beg = line.begin();	
	string::const_iterator end;

	string s = "";
	string temp;

	while (beg != line.end())
	{
		beg = find_if (beg, line.end(), isalnum);

		if (beg != line.end())
		{
		
			end = find_if (beg, line.end(), isspace);
 
			temp = string(beg, end);

			s = s + temp + ' ';

			beg = end;
		}
	}

	return s;

}

int main()
{

	string line;
	vector <string> strings;

	cout << "Please enter some lines of text: " << endl << endl;

	while (getline (cin, line))
	{

		if (!empty_Line (line))
		{
			strings.push_back(line);
		}
	}

	for (vector <string>::const_iterator p = strings.begin(); p != strings.end(); p++)
		cout << " " << *p << endl;

	cout << endl;

	string temp;

	cout << endl << "WITHOUT PUNCTUATION!!!" << endl << endl;

	for (unsigned int i = 0; i < strings.size(); i++)
	{
		temp = strings[i];
		strings[i] = remove_Punct(temp);
	}

	for (vector <string>::const_iterator p = strings.begin(); p != strings.end(); p++)
		cout << " " << *p << endl;

	cout << endl << "WITH PROPER SPACING!!!" << endl << endl;

	for (unsigned int i = 0; i < strings.size(); i++)
	{
		temp = strings[i];
		strings[i] = remove_Space(temp);
	}



	for (vector <string>::const_iterator p = strings.begin(); p != strings.end(); p++)
		cout << " " << *p << endl;

	for (unsigned int i = 0; i != -1; i++);		// Hold-loop for screen.

	int freeze;
	cin >> freeze;
	return 0;
}

