//Carlos Lazo
//9-1-04
//Lab 1 Checkpoint 3

#include <iostream>
#include <string>

int main()
{
	
	std::string first;
	std::string middle;
	std::string last;

	std::cout << "Please enter your first name: ";
	std::cin >> first;
	std::cout << "Please enter your middle name: ";
	std::cin >> middle;
	std::cout << "Please enter your last name: ";
	std::cin >> last;

	std::string fullName = first + " " + middle + " " + last;

	std::cout << "Your full name is " << fullName << "." << std::endl;

	std::cout << "The length of the first name is " << first.size() << " characters." << std::endl;
	std::cout << "The length of the last name is " << last.size() << " characters." << std::endl;
	std::cout << "The length of the full name is " << fullName.size() << " characters." << std::endl;

	return 0;
}