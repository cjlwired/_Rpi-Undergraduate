//Carlos Lazo
//9-23-04
//Homework #3 - Diver Program -> main_Diver.cpp

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include "diver.h"

using namespace std;

bool validDives (int numDives)
{
	return numDives > 0;
}

int getPosition (int ID, vector <Diver> divers)
{

	for (unsigned int i = 0; i < divers.size(); i++)
	{
		if (divers[i].getID() == ID)
			return i;
	}

	return -1;
}

void computeScore (Diver& x, vector <double> jScores, double degOfDiff)
{
	
	sort (jScores.begin(), jScores.end());
	
	double sum = 0.0;

	for (unsigned int i = 0; i < 5; i++)
		sum += jScores[i+1];

	double average = sum / 5.0;

	double score = average * degOfDiff;

	x.addScore(score);

}

void getDive (vector <Diver>& divers)
{
		
	int ID;						// Keeps track of ID of the Diver
	int diverPos;				// Keeps track of Diver position in the array
	double degOfDiff;			// Keeps track of degree of difficulty for dive
	double j;					// Helps to read in judges scores'
	vector <double> jScores;	// Keeps track of the judges scores'	 

	for (unsigned int i = 0; i < divers.size() + 1; i++)
	{

		cin >> ID;	

		// If the ID equals zero, end reading in for this dive.
		if (ID == 0)
			return ;

		cin >> degOfDiff;

		diverPos = getPosition(ID, divers);

		for (unsigned int c = 0; c < 7; c++)
		{
			cin >> j;

			jScores.push_back (j);
		}

		computeScore (divers[diverPos], jScores, degOfDiff);

		jScores.clear();
	}

}

void outputRound (vector <Diver> divers, int n, ostream& out_str)
{
	cout << "\nAfter " << n << " rounds, these are the top five Divers:" << endl;

	for (unsigned int i = 0; i < 5; i++)
	{
		out_str << (i+1) << ": ";
		divers[i].outputDiver(cout,0);
	}

}

void outputFinal (vector <Diver> divers, ostream& out_str, int choice)
{

	if (choice == 0)
	{
		for (unsigned int i = 0; i < divers.size(); i++)
		{
			out_str << (i+1) << ": ";
			divers[i].outputDiver(cout,0);
		}
	}

	else
	{
		for (unsigned int i = 0; i < divers.size(); i++)
		{
			out_str << (i+1) << ": ";
			divers[i].outputDiver(cout,1);
		}
	}

}


// ********************
// ********************
//     MAIN PROGRAM
// ********************
// ********************


int main()
{
	vector <Diver> divers;

	Diver one_diver;

	while (one_diver.read(cin))
	{
		divers.push_back(one_diver);
	}

	int numDives;

	cin  >> numDives;

	int diveNumPrint = 1;		// Will be sent to output function to keep track of Dive #

	while (validDives(numDives))
	{
		getDive(divers);
		sort(divers.begin(), divers.end(), greater_Scores);

		if (numDives != 1)
			outputRound(divers, diveNumPrint, cout);

		numDives--;
		diveNumPrint++;
	}

	cout << "\nFinal Places:\n";

	outputFinal (divers, cout, 0);

	for (unsigned int i = 0; i < divers.size(); i++)
		divers[i].setPlace(i+1);

	sort(divers.begin(), divers.end(), ID_sort);

	cout << "\nResults in order of ID:\n";

	outputFinal (divers, cout, 1);

	for (unsigned int i = 0; i != -1; i++) //Hold-loop for program

	int freeze;
	cin >> freeze;
	return 0;
}

