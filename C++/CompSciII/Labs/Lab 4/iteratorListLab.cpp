//Carlos Lazo
//9-22-04
//Lab #4

#include <algorithm>
#include <iostream>
#include <string>
#include <list>

using namespace std;

void printV(list<double> v);

void reverseDouble(list <double> & d);

int main()
{
	/*vector <int> numbers;

	int x;

	cout << "Please enter in some integers:\n\n";

	while (cin >> x)
	{
		numbers.push_back(x);
	}

	cout << "\nThis is a vector of the integers you just entered:" << endl << endl;

	printV(numbers);

	cout << "\n\nThis is that same vector in reverse order:" << endl << endl;

	reverseVector(numbers);

	printV(numbers);
	
	cout << endl << endl;

	*/
	
	cout  << "Please enter a list of doubles" << endl << endl;

	list <double> doubles;

	double x;

	while (cin >> x)
	{
		doubles.push_back(x);
	}

	cout << "\nThis is a list of the doulbes you just entered:" << endl << endl;

	printV(doubles);

	cout << "\n\nThis is the list of doubles in reverse order:" << endl << endl;

	reverseDouble(doubles);

	printV(doubles);

	for (unsigned int i = 0; i != -1; i++) //Loop to hold

	int freeze;
	cin >> freeze;
	return 0;
}

void printV(list <double> v)
{

	list <double>::iterator x = v.begin();

	for (; x != v.end(); x++)
		cout << *x << " ";
}

void reverseDouble(list <double> & v)
{
	list <double>::reverse_iterator ri = v.rbegin();
	list <double>::iterator begin = v.begin();

	if (v.size() == 0)
		cout << "Vector is empty, cannot reverse order!";
	else if (v.size() == 1)
		return ;
	else if (v.size() == 2)
	{

		double temp;

		temp = *ri;
		*ri = *begin;
		*begin = temp;
	}

	else if (v.size() % 2 == 0)
	{

		double temp;

		for (unsigned int i = 0; i < v.size() / 2; begin++, ri++, i++)
		{
			temp = *ri;
			*ri = *begin;
			*begin = temp;
		}
	}

	else
	{

		double temp;

		for (unsigned int i = 0; i < v.size() / 2; begin++, ri++, i++)
		{
			temp = *ri;
			*ri = *begin;
			*begin = temp;
		}
	}

	return ;
}

