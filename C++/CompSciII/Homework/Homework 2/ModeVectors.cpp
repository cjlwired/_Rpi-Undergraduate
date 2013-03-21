//************************
//Carlos Lazo
//9-14-04
//CSCI II - Section 1
//Homework #2
//************************

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
	vector <string> parallelNames;		//vector created to bring in names
	vector <int> parallelGrades;		//vector created to bring in test grades

	string x;				//used for taking in names
	int y;					//used for taking in test scores
	bool flag = true;		//used for ending the while loop

	cout << "Please enter a name followed by a grade.\n";
	cout << "If you wish to stop, type in any characters with a grade lower than 0.\n\n";

	cin >> x >> y;

	/* The only reason that I did the loop this way using a boolean variable
	was because I don't know what the escape sequence is while running the actual
	program to stop the input. I tried out different Ctrl-? combinations but nothing 
	worked. So I did it this way, hope it is acceptable. */

	while (flag)
	{
		if (y < 0)
			flag = false;
		else
		{
			parallelNames.push_back(x);
			parallelGrades.push_back(y);

			cin >> x >> y;
		}
	}

	vector <int> sortedGrades;	//this vector will be a copy of parallelNames, only sorted

	//copying elements of parallelGrades into sortedGrades

	for (unsigned int i = 0; i < parallelGrades.size(); i++)
		sortedGrades.push_back(parallelGrades[i]);

	//sorting of sortedGrades

	sort(sortedGrades.begin(), sortedGrades.end());

	vector <int> possibleModes;		//vector that will be holding the possible modes
	int tracker = sortedGrades[0];	//variable that will be used to help add possible modes to vector

	possibleModes.push_back(tracker);	//add first element of sortedGrades to possibleModes to begin for loop


	//This for-loop will add each unique mode to possibleModes using a tracker 
	//to prevent duplicates

	for (unsigned int i = 1; i < sortedGrades.size(); i++)
	{
		if (tracker != sortedGrades[i])
		{
			possibleModes.push_back(sortedGrades[i]);
			tracker = sortedGrades[i];
		}
	}

	vector <int> modeCount(possibleModes.size(), 0);	//will keep track of the amount of times a mode appears

	tracker = sortedGrades[0];	//reset the tracker to the first element of sortedGrades
	int trackerCount = 0;		//variable used to change positions in the modeCount array
	
	//for-loop iterates through sortedGrades and counts the number of times a specific mode
	//is in the vector, placing it in modeCount (which is parallel to the elements in possibleModes


	for (unsigned int i = 0; i < sortedGrades.size(); i++)
	{
		if (sortedGrades[i] == tracker)
			modeCount[trackerCount]++;
		else
		{
			tracker = sortedGrades[i];
			
			trackerCount++;

			modeCount[trackerCount]++;
		}
	}

	int maxTimes = modeCount[0];	//variable used to help determine which numbers show up the most

	//for-loop for finding out max times each numbers appear

	for (unsigned int i = 0; i < modeCount.size(); i++)
	{
		if (maxTimes < modeCount[i])
			maxTimes = modeCount[i];
	}

	vector <int> actualModes;	//vector used to keep track of OFFICIAL modes

	//for-loop to store actual modes of the list of grades (incase there are more than one)

	for (unsigned int i = 0; i < modeCount.size(); i++)
	{
		if (modeCount[i] == maxTimes)
			actualModes.push_back(possibleModes[i]);
	}

	//OUTPUT

	cout << "\nNumber of modes: " << actualModes.size() << endl;
	cout << "Modes: ";

	for (unsigned int i = 0; i < actualModes.size(); i++)
		cout << actualModes[i] << " ";

	cout << endl;

	cout << "Mode students:" << endl;

	vector <string> modeStudents;	//used to store names of students with an actual mode

	/*
	
	Here, a nested for-loop is used for finding out which students have one of the actual modes
	Essentially, it looks at every single grade checking to see if it is one of the actual modes,
	and if so, it will add the corresponding name of that grade to the modeStudents vector.

	*/

	for (unsigned int i = 0; i < parallelGrades.size(); i++)
	{
		for (unsigned int j = 0; j < actualModes.size(); j++)
		{
			if (parallelGrades[i] == actualModes[j])
				modeStudents.push_back(parallelNames[i]);
		}
	}
	
	//sorting modeStudents

	sort(modeStudents.begin(), modeStudents.end());

	//for-loop used for printing out mode students

	for (unsigned int i = 0; i < modeStudents.size(); i++)
		cout << modeStudents[i] << endl;
	
	int freeze;
	cin >> freeze;
	return 0;
}

/*

OUTPUT #1

Ghandi 123
Khan 45
Thatcher 90
Churchill 123
Simpson 22
Spears 15
Nero 45
Yeltsin 86
Grant 87
McKinley 80
Alexander 90
Garfield 22
xxxxxxxx -1

Number of modes: 3
Modes: 22 90 123
Mode students:
Alexander
Bumsted
Churchill
Garfield
Ghandi
Jefferson
Simpson
Thatcher
Washington

*/

/*

OUTPUT #2

Please enter a name followed by a grade.
If you wish to stop, type in any characters with a grade lower than 0.

Carlos 100
Raphael 0
Shawn 0
Andy 0
Nick 100
Chihiro 100
Dan 76
Tomas 89
Karsten 0
Kenny 100
xxxxxxxxxx -1

Number of modes: 2
Modes: 0 100
Mode students:
Andy
Carlos
Chihiro
Karsten
Kenny
Nick
Raphael
Shawn

*/