//Carlos Lazo
//9-8-04
//Gap Problem

#include <algorithm>
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

	double largest;

	sort(numbers.begin(), numbers.end());

	if (numbers[0] < 0.0)
	{
		largest = fabs(numbers[0]) + numbers[numbers.size() - 1];
	}
	
	else
		largest = numbers[0] + numbers[numbers.size() - 1];

	double smallest;

	smallest = numbers[numbers.size()/2] - numbers[numbers.size()/2 - 1];

	cout << "Largest gap is: " << largest << endl;
	cout << "Smallest gap is " << smallest << endl;
	

	int freeze;
	cin >> freeze;
	return 0;
}