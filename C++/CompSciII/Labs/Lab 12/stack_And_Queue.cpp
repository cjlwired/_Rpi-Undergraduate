// Carlos Lazo
// 12-1-04
// Lab 12 - Stack and Queue

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "cs2queue.h"
#include "cs2stack.h"

using namespace std;

int main()
{

	/*

	// USING STD LIB STACK + QUEUE

	//#include <queue>
	//#include <stack>

	cout << "Please enter a string to test to see if it is a palindrome: " << endl << endl;

	string palindrome;

	char c;

	bool flag = true;

	while (flag)
	{

		cin.get(c);

		if (c == '\n')
			flag = false;

		else
		{
			if (isalpha(c))

				palindrome += tolower(c);
		}
	}

	cout << endl << endl;

	stack <char> s;
	queue <char> q;

	for (int i = 0; i < palindrome.size(); i++)
	{
		s.push(palindrome[i]);
		q.push(palindrome[i]);
	}

	bool is_Palindrome = true;

	while (s.size() > 1 && q.size() > 1 && is_Palindrome)
	{
		char is_Same  = s.top();
		char is_Same2 = q.front();

		s.pop();
		q.pop();

		if (is_Same < is_Same2 || is_Same > is_Same2)
		{
			is_Palindrome = false;
		}

	}

	if (is_Palindrome)
		cout << "The string entered IS a palindrome!" << endl << endl;

	else
		cout << "The string entered is NOT a palindrome!" << endl << endl;

	*/

	// TESTING cs2stack.h

	stack <int> s;

	s.push(1); s.push(2); s.push(3);

	cout << "Stack size should be 3: " << endl;
	cout << s.size() << endl << endl;

	cout << "Stack top should be 3:" << endl;
	cout << s.top() << endl << endl;

	s.pop();

	cout << "Now that an element was popped off, stack top should be 2:" << endl;
	cout << s.top() << endl << endl;

	while (s.size() != 0)
		s.pop();

	cout << "Stack should now be empty!" << endl;
	if (s.empty())
		cout << "IT IS!" << endl;
	else
		cout << "IT ISNT!" << endl << endl;

	cout << endl;

	queue <int> q;

	q.push(1); q.push(2); q.push(3);

	cout << "Queue size should be 3:" << endl;
	cout << q.size() << endl << endl;

	cout << "Queue front should be 1:" << endl;
	cout << q.front() << endl << endl;

	cout << "Queue back should be 3:" << endl;
	cout << q.back() << endl << endl;

	q.pop();

	cout << "After popping an element, queue front should be 2:" << endl;
	cout << q.front() << endl << endl;

	while (q.size() != 0)
		q.pop();

	cout << "Queue should now be empty!" << endl;
	if (q.empty())
		cout << "IT IS!" << endl << endl;
	else
		cout << "IT ISNT!" << endl << endl;
	
	return 0;
}
