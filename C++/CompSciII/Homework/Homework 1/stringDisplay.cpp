//************************
//Carlos Lazo
//9-8-04
//CSCI II - Section 1
//Homework #1
//************************

#include <iostream>
#include <string>

using namespace std;	//Eliminates use of std:: in program

int main()
{
	
	string fN;	
	string lN;

	
	cout << "!!!!!!!!!!!!!!!!!!!!!!!! PART 1 !!!!!!!!!!!!!!!!!!!!!!!!" << endl << endl;

	//Reading in names here using input stream
	cout << "Please enter your first and last name:" << endl;
	cin >> fN >> lN;
	cout << endl << endl;

	string firstName = fN;	//variable used to store the first name of a person
	string  lastName = lN;	//variable used to store the last name of a person

	

	//Part #1 - Interchanging letters

	int firstLength = firstName.length();	//length of first name
	int  lastLength =  lastName.length();	//length of last name

	int shortestLength;	//will store shortest length to determine variable for loop

	//If statement to determine variable for loop

	if (firstLength < lastLength)
		shortestLength = firstLength;
	else
		shortestLength = lastLength;

	//The following statement was added so that any 3-letter last names would function
	//accordingly with the for loop that follows. Without this statement, the space following
	//the three letter name will be swapped as well.

	if (shortestLength == 3)
		shortestLength = 0;

	//For-loop which will iterate through the strings and change every third letter

	for (unsigned int i = 0; i <= shortestLength/3; i++)
	{
		//Simple swap function

		char temp = firstName[i*3];
		firstName[i*3] = lastName[i*3];
		lastName[i*3] = temp;
	}

	//Outputting name changes

	cout << "I will now output the first and last name with every 3rd character interchanged:" << endl;
	cout << firstName << " " << lastName << endl << endl;

	cout << "!!!!!!!!!!!!!!!!!!!!!!!! PART 2 !!!!!!!!!!!!!!!!!!!!!!!!" << endl << endl;

	//Part #2 - Framed right-justified greeting
	//utilizing variables from Part #1 to reduce duplication	

	firstName = fN;		//Re-assigning original input to string
	lastName  = lN;		//Re-assigning original input to string

	int longestLength;	//variable initialized to find longenst length of both strings

	//Loop where the longestLength that will be required for later is established

	if (firstLength > lastLength)
		longestLength = firstLength;
	else
		longestLength = lastLength;

	//This statement ensure that if both names happen to be less than 6 spaces,
	//the Hello! will be taken as the longest string of the three

	if (longestLength < 6)
		longestLength = 6;

	const string starLine(longestLength + 4, '*');		//used for the top and bottom lines of the greeting
	const string blankLine(longestLength + 2, ' ');
	const string emptyLine = '*' + blankLine + '*';		//used for the line after the top line and before the bottom line
	
	string spaceForHello = " ";	//Calculate spaces needed before Hello!
	string spaceForFirst = " ";	//Calculate spaces needed before firstName
	string  spaceForLast = " ";	//Calculate spaces needed before lastName

	//Loop deciding spaces before Hello!

	for (unsigned int a = 0; a < (longestLength - 6); a++)
		spaceForHello += " ";

	//Loop deciding spaces before firstName

	for (unsigned int b = 0; b < (longestLength - firstName.length()); b++)
		spaceForFirst += " ";

	//Loop deciding spaces before lastName

	for (unsigned int c = 0; c < (longestLength - lastName.length()); c++)
		spaceForLast += " ";
	

	cout << starLine << endl << emptyLine << endl;				//print starLine and emptyLine to set up the greeting
	cout << '*' << spaceForHello << "Hello!"  << " *" << endl;					//print    Hello! in proper location
	cout << '*' << spaceForFirst << firstName << " *" << endl;					//print firstName in proper location
	cout << '*' << spaceForLast  << lastName  << " *" << endl;					//print  lastName in proper location
	cout << emptyLine << endl << starLine << endl << endl;		//print starLine and emptyLine to end the greeting

	cout << "!!!!!!!!!!!!!!!!!!!!!!!! PART 3 !!!!!!!!!!!!!!!!!!!!!!!!" << endl << endl;

	string fullName = "Hello! " + firstName + " " + lastName;	//initializing string that will be printed

	string blanks;				//will help keep track of blanks in between letters
	string blanksFront = "";	//will help keep track of blanks in front of the letters

	for (unsigned int i = 0; i < fullName.length() - 2; i++)
		blanks += " ";

	/* EXPLANATION OF FOR LOOP:

	At first, the loop is initialized to run from 0 to 1 more than half the length of the fullName string.
	There are three parts to the loop. The first part prints the last letter of a fullName that has only
	one letter at the end. The next part is used to exit the loop after the two comparisons pass
	each other in the algorithm. The else statement prints the blanks in front first, then the
	fullName[i] letter in the string, and the fullName[fullName.length() - 1 - i] character in the string.
	With eery iteration of this loop, the next character from the front gets printed along with the next 
	character from the back. The front spacing and middle spacing is adjusted accordingly, ensuring that 
	nothing is done if the space string becomes empty ("").

	*/

	for (unsigned int i = 0; i < (fullName.length() / 2) + 1; i++)
	{			
			
		if (i == (fullName.length() - 1 - i))
		{
			cout << blanksFront + fullName[i] << endl;
			cout << endl << "THIS IS THE END OF THE PROGRAM, THANK YOU!" << endl << endl;
		}


		else if (i > (fullName.length() - 1 - i))
			cout << endl << endl << "THIS IS THE END OF THE PROGRAM, THANK YOU!" << endl << endl;
		
		else
		{
			cout << blanksFront << fullName[i] + blanks + fullName[fullName.length() - 1 - i] <<  endl;
			
			int blankLength = blanks.length();
			blanks = "";

			if (blankLength - 2 > 0)
			{
				for (unsigned int s = 0; s < blankLength - 2; s++)
				{
					blanks = blanks + " ";
				}
			}
					
			blanksFront += " ";
		}
	}

	//I learned to do this during high school - For some reason, when I run this program, it just exits, 
	//so the cin at the end freezes the screen.

	int freeze;
	cin >> freeze;
	return 0;
}

/*

OUTPUT #1:

!!!!!!!!!!!!!!!!!!!!!!!! PART 1 !!!!!!!!!!!!!!!!!!!!!!!!

Please enter your first and last name:
Jay Smith


I will now output the first and last name with every 3rd character interchanged:

Say Jmith

!!!!!!!!!!!!!!!!!!!!!!!! PART 2 !!!!!!!!!!!!!!!!!!!!!!!!

**********
*        *
* Hello! *
*    Jay *
*  Smith *
*        *
**********

!!!!!!!!!!!!!!!!!!!!!!!! PART 3 !!!!!!!!!!!!!!!!!!!!!!!!

H              h
 e            t
  l          i
   l        m
    o      S
     !
         y
       Ja


THIS IS THE END OF THE PROGRAM, THANK YOU!
*/

/*

OUTPUT #2:

!!!!!!!!!!!!!!!!!!!!!!!! PART 1 !!!!!!!!!!!!!!!!!!!!!!!!

Please enter your first and last name:
Donald Knuth


I will now output the first and last name with every 3rd character interchanged:

Kontld Dnuah

!!!!!!!!!!!!!!!!!!!!!!!! PART 2 !!!!!!!!!!!!!!!!!!!!!!!!

**********
*        *
* Hello! *
* Donald *
*  Knuth *
*        *
**********

!!!!!!!!!!!!!!!!!!!!!!!! PART 3 !!!!!!!!!!!!!!!!!!!!!!!!

H                 h
 e               t
  l             u
   l           n
    o         K
     !
            d
       D   l
        o a
         n

THIS IS THE END OF THE PROGRAM, THANK YOU!

*/

/*

OUTPUT #3:

!!!!!!!!!!!!!!!!!!!!!!!! PART 1 !!!!!!!!!!!!!!!!!!!!!!!!

Please enter your first and last name:
Raphael Chabaneix


I will now output the first and last name with every 3rd character interchanged:

Capbaee Rhahanlix

!!!!!!!!!!!!!!!!!!!!!!!! PART 2 !!!!!!!!!!!!!!!!!!!!!!!!

*************
*           *
*    Hello! *
*   Raphael *
* Chabaneix *
*           *
*************

!!!!!!!!!!!!!!!!!!!!!!!! PART 3 !!!!!!!!!!!!!!!!!!!!!!!!

H                      x
 e                    i
  l                  e
   l                n
    o              a
     !            b
                 a
       R        h
        a      C
         p
          h  l
           ae


THIS IS THE END OF THE PROGRAM, THANK YOU!

*/