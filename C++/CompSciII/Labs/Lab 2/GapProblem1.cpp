//Carlos Lazo
//9-8-04
//Gap Problem

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

int main()
{

	vector <double> numbers;

	double x;			//Variable used with input stream
	bool flag = true;	//Variable used with input stream

	cout << "Please enter double values, ending the sequence by entering .12345: " << endl << endl;

	while (flag == true)
	{
		cin >> x;

		if (x == .12345)
			flag = false;
		else
			numbers.push_back(x);
	}

	//Bounds checking
	if (numbers.size() == 0)
	{
		cout << "No doubles entered! Please try again." << endl;
		return 1;
	}

	if (numbers.size() == 1)
	{
		cout << "Only one double entered, not enough to make a comparison. Please try again." << endl;
		return 1;
	}

	//Loop to find the largest gap
	double largest;
	double smallest;

	double temp1 = numbers[0];
	double temp2 = numbers[1];

	if (temp1 < temp2)
	{
		smallest = numbers[0];
		largest  = numbers[1];
	}

	else 
	{
		smallest = numbers[1];
		largest  = numbers[0];
	}

	for (unsigned int i = 2; i < numbers.size(); i++)
	{
		double compare = numbers[i];

		if (compare < smallest)
			smallest = numbers[i];
		else if (compare > largest)
			largest  = numbers[i];
	}	

	if (smallest < 0.0)
		smallest = fabs(smallest);

	double largeGap = largest + smallest;

	cout << endl << "The largest gap in the list of doubles is " << largeGap << "." << endl;

	//Loop to find the smallest gap
	
	double smallGap;

	if (numbers[0] < numbers[1])
		smallGap = numbers[1] - numbers[0];
	else if (numbers[0] > numbers[1])
		smallGap = numbers[0] - numbers[1];


	for (unsigned int i = 0; i < numbers.size() - 2; i++)
	{
		double compareOne = numbers[i];

		for (unsigned int j = i + 1; j < numbers.size() - 1; j++)
		{
			double compareTwo = numbers[j];
			double tempGap;

			if (compareOne < compareTwo)
			{
				tempGap = compareTwo - compareOne;
				if (tempGap < smallGap)
					smallGap = tempGap;
			}

			else if (compareOne > compareTwo)
			{
				tempGap = compareOne - compareTwo;

				if (tempGap < smallGap)
					smallGap = tempGap;
			}
		}
	}

	cout << endl << "Smallest gap between two numbers is " << smallGap << "." << endl << endl;

	return 0;

}
