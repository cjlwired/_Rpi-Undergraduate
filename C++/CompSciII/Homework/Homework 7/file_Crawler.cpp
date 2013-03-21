// Carlos Lazo
// 11-15-04
// Homework #7
// file_Crawler.cpp

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

#include "File.h"
#include "Occurence.h"

using namespace std;

/* DESIGN:

		This is my plan for design. I am creating a separate class called File. This class will be able
	to store certain variables: the file name, the actual words that are contained within the File, the
	links to other Files that were found within that File, and a map that will store the instances of keywords.
	The constructor of each individual File will take care of the parsing, assigning all words to its vector
	of strings and the File links to the corresponding variable. To keep track of which files have been opened 
	already to prevent the creation of mulitple instances of the same text file, I created two vectors at the
	beginning of the main. It will be compared before any Files are actually created. If a File is valid, and since
	all of the parsing work is done in the constructor, I pushback all of the words of that File into a vector.
	Once this is done for all of the current Files, and after the current Files vector is cleared, a set will be 
	created that to hold one copy of these files (stored as strings). These will then be copied back into the current
	Files vector and the process will be repeated. The loop will stop once the current Files vector is of size 0.
	A vector of Files will be used to contain all of the valid Files. The files in the argv vector are evaluated first,
	and then their linked Files follow. 

		Once this information is outputted, I will created a separate class called Occurences. 
	
	
	
	My code will be heavily commented for further clarification.

*/

// This function checks to see if the file sent here has already been opened
// or if it has failed to be opened.

bool find_File (string f, vector <string> oF, vector <string> uF)
{

	// Make sure that the size of the opened Files vector is greater than 0.
	// If it is, then search through it's Files. If the file is already there,
	// then there is no need to open it again. 

	if (oF.size() > 0)
	{
		for (unsigned int i = 0; i < oF.size(); i++)
			if (oF[i] == f)
				return true;
	}

	// Make sure that the size of the unopened Files vector is greater than 0.
	// If it is, then search through it's Files. If the file is already there,
	// then there is no need to attempt to open it again. 

	if (uF.size() > 0)
	{
		for (unsigned int i = 0; i < uF.size(); i++)
			if (uF[i] == f)
				return true;
	}

	return false;
}

int main (int argc, char* argv[])
{
	
	vector <string> opened_Files;		// this vector will keep track of the files that have already been opened
	vector <string> unopened_Files;		// this vector will keep track of the files that were not opened
	
	vector <string> keywords;			// this will store the keywords that the files will be searched for

	vector <string> current_Files;		// originally this will hold the files read in from the command line,
										// later they will keep track of the files ofund within other files

	vector <File> all_Files;			// this is the vector that will keep track of all files that are valid

	string temp_Keyword;	// variable used to read in keywords

	// Read in keywords from the cin stream
	// * Notice that this loop takes care of the case of the keywords, making them all lowercase letters

	while (cin >> temp_Keyword)
	{

		string lower_Case_Keyword;

		for (unsigned int i = 0; i < temp_Keyword.size(); i++)
		{
			lower_Case_Keyword += tolower (temp_Keyword[i]);
		}

		keywords.push_back(lower_Case_Keyword);
	}

	// Read in files from argv vector that were specified on the command line

	for (unsigned int i = 1; i < argc; i++)
		current_Files.push_back(argv[i]);

	// Main while-loop for reading Files. Keep doing this loop as long as the flag is true and
	// as long as the current_Files are greater than 0.

	int c = 0;

	while (current_Files.size() > 0 && c != 2)
	{

		// Vector created to hold temporary files of all files in the current_File vector

		vector <string> temp_LF;

		for (unsigned int i = 0; i < current_Files.size(); i++)
		{

			// Take the current_Files vector and check to see if the Files have already been opened.

			if (! (find_File (current_Files[i], opened_Files, unopened_Files)))
			{

				ifstream data_str (current_Files[i].c_str());

				// First, check to see if the file could be opened.

				if (! data_str)
				{
					data_str.close();

					unopened_Files.push_back(current_Files[i]);
				}

				// Close the file and create a new File, adding the string to the opened_File
				// vector and add the actual File to the File vector. Add the linked files of
				// the opened files to a set of strings that will keep track of the linked files
				// of all Files that have been created.

				else
				{
					data_str.close();

					opened_Files.push_back(current_Files[i]);

					File x (current_Files[i], keywords);

					all_Files.push_back(x);

					vector <string> lF = x.get_Linked_Files();

					for (unsigned int i = 0; i < lF.size(); i++)
						temp_LF.push_back(lF[i]);
					
				}
			}
		}

		// Clear the file vector

		current_Files.clear();

		// Now that the vector is cleared, check to see if there is atleast one linking file found
		// in all of the Files that were scanned. 

		if (temp_LF.size() > 0)
		{
			// Create a set of strings that will hold all of the files found once, since that is all that is 
			// needed. Copy these files into the current_Files vector. 

			set <string> unique_File;

			for (unsigned int i = 0; i < temp_LF.size(); i++)
				unique_File.insert (unique_File.begin(), temp_LF[i]);

			for (set <string> :: iterator p = unique_File.begin(); p != unique_File.end(); p++)
				current_Files.push_back (*p);

		}

		// Repeat the process of scanning files and checking to see if they have already been opened with this
		// new current_Files vector.
	}

	// Print out Files that were opened and File links that were found but that could not be opened.

	cout << "FILES OPENED" << endl;

	sort (opened_Files.begin(), opened_Files.end());

	for (unsigned int i = 0; i < opened_Files.size(); i++)
		cout << opened_Files[i] << endl;

	cout << endl << "FILE LINKS FOUND THAT COULD NOT BE OPENED" << endl;

	sort (unopened_Files.begin(), unopened_Files.end());

	for (unsigned int i = 0; i < unopened_Files.size(); i++)
		cout << unopened_Files[i] << endl;

	cout << endl;

	// Here, a for loop will be used to print out the keywords that have appeared the most frequently
	// in all of the valid Files that have been found above.

	for (unsigned int i = 0; i < keywords.size(); i++)
	{
		// Create a vector that will store Occurences

		vector <Occurence> key_Occur;

		// Create an Occurence for each keyword of each valid File and add it to the vector

		for (unsigned int j = 0; j < all_Files.size(); j++)
		{
			Occurence temp (all_Files[j].get_Link_Name(), keywords[i], all_Files[j].get_Keyword_Count());
			key_Occur.push_back (temp);
		}

		// Sort Occurences comparing their keyword count

		sort (key_Occur.begin(), key_Occur.end(), compare);

		// Check to see if the first element is not zero. This is valid because if in fact the keyword count of the
		// first element is zero, that would tell you that there are no counts of the keyword in any of the files.

		cout << keywords[i] << " appears in files " << endl;;

		// Find out how far away from the beginning of the vector the Files turn up with a count of zero.

		int index_To_Zero = 0;

		while ((key_Occur[index_To_Zero].get_Count() != 0) && (index_To_Zero < key_Occur.size()))
			index_To_Zero++;

		// If the file has found no instances of the word, print appropriate message

		if (index_To_Zero == 0)
			cout << "-none-" << endl << endl;

		// If there are less than 5 files that have a count greater than 0, print appropriate message
		 
		else if (index_To_Zero < 5)
		{

			for (unsigned int k = 0; k != index_To_Zero; k++)
				cout << key_Occur[k].get_Name() << endl;
		}

		// Otherwise, print elements in the list. Once the fourth element is found, check to see if the remaining ones
		// have that same count. If they do, print them out.

		else
		{
			for (unsigned int k = 0; k < 5; k++)
			{
				cout << key_Occur[k].get_Name() << endl;

				if (k == 4)
				{
					while ((key_Occur[k].get_Count() == key_Occur[k+1].get_Count()) && (k+1 < key_Occur.size()))
					{
						cout << key_Occur[k+1].get_Name() << endl;
						k++;
					}
				}
			}
		}

		cout << endl;

	}

	return 0;
}