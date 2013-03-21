//Carlos Lazo
//9-26-04
//Palindrome Test

#include <iostream>
#include <cctype>
#include <string>


using namespace std;

bool isPalindrome(const string& str)
{
	string temp;
	string::const_iterator i;

	for (i = str.begin(); i != str.end(); i++)
	{
		if (isalpha(*i))
		{
			temp += tolower(*i);
		}
	}

	if (temp.empty()) 
			return false;

	string::const_iterator left, right;

	left = temp.begin();
	right = temp.end();
	right--;

	while (left < right)
	{
		if(*left == *right)
		{
			left++;
			right--;
		}
		else
			return false;
	}

	return true;
}

int main()
{

	string str;

	getline (cin, str);

	if (isPalindrome(str))
		cout << "THE STRING ENTERED IS A PALINDROME!" << endl;

	else
		cout << "The string entered is NOT a palindrome!" << endl;

	int freeze;
	cin >> freeze;
	return 0;

}