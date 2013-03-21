//Carlos Lazo
//9-15-04
//Lab #3

#include <iostream>
#include "Time.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{

	/*
	cout << "Please enter a number of hours, minutes, and seconds:\n\n";

	int h, m, sec;

	cin >> h >> m >> sec;

	cout << endl << endl;

	Time one;			//Default constructor

	Time two(h, m, sec);	//Constructor with 3 variables
	
	cout << "Time one is : ";
	one.printTime();
	cout << endl;
	cout << "Time two is : ";
	two.printTime();
	cout << endl << endl;

	one.setHour(13);
	one.setMinute(9);
	one.setSecond(45);

	one.printAmPm();
	cout << endl;
	two.printAmPm();
	cout << endl << endl;
	*/

	cout << "Please continue entering different times:" << endl;

	int h, m, s;

	vector <Time> times;

	while (cin >> h >> m >> s)
	{
		Time temp(h,m,s);
		times.push_back(temp);
	}

	cout << endl;

	sort (times.begin(), times.end(), isEarlierThan);

	for (unsigned int i = 0; i < times.size(); i++)
	{
		times[i].printAmPm();
		cout << endl;
	}

	for (unsigned int i = 0; i < 2; i++)
		i = 0;
		
	int freeze;
	cin >> freeze;
	return 0;
}