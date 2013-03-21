// Carlos Lazo
// 10-13-04
// Computer Science II
// Homework #5 - Pair.h

#include <iostream>
#include <string>

using namespace std;

class Pair
{
	
	public:

		Pair (string& s);

		string get_Name() { return my_Name;}
		int get_Count() { return my_Count;}

		void increment();

	private:
		
		string my_Name;
		int my_Count;

};

bool count_Greater( Pair one, Pair two );
