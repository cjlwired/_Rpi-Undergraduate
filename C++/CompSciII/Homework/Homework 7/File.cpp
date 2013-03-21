// Carlos Lazo
// 11-15-04
// Homework #7
// File.cpp

#include "File.h"

// Constructor for all Files - all parsing will be done here

File::File (string n, vector <string> keywords)
{

	file_Name = n;

	// Assigning the File map to the values in the keywords vector
	// and initializing their word counts to 0.

	for (unsigned int i = 0; i < keywords.size(); i++)
	{
		keyword_Count.insert ( make_pair (keywords[i], 0));
	}

	// Opening data-file by converting the file name to a C-style string

	ifstream data_str (file_Name.c_str());

	char c;		// Input from the data stream will be read in character by character

	bool flag = true;	// This flag will help limit the function of the parsing algorithm

	// PARSING ALGORITHM

	while (data_str.get(c))
	{

		string s;	// This will be used to add words to either of the File's vectors
		
		// If an alphabetic character is found 

		if (isalpha(c))
		{
			// Find the word converting all of the characters to lowercase

			while (isalpha(c))
			{
				s.push_back(tolower(c));
				data_str.get(c);
			}

			// Check for validity, making sure that the size of the word is greater than 3

			if (s.size() > 3)
				file_Words.push_back(s);

			// Initialize the flag to false and put the last character taken back on the input stream

			flag = false;

			data_str.putback(c);
		}

		// If the character is a <

		if (c == '<' && flag)
		{
			// Keep getting characters until an alphabetic character is found

			while (!isalpha(c))
				data_str.get(c);

			// Compile the file name and assign it to s - keep adding to the file name
			// until a < or a space is found. 

			while ((! (c == ' ') ) && (! (c == '>')) && (! (c == '\n')))
			{

				if (isalpha(c))
					s.push_back(tolower(c));
				else
					s.push_back(c);

				data_str.get(c);
			}

			// Add the string found to the File's linked_Files

			linked_Files.push_back(s);

			// Putback the last character found from the previous loop and search for the end of the file if necessary

			data_str.putback(c);

			while (! (c == '>'))
				data_str.get(c);

		}

		flag = true;
	}

	// Here, the File's words will be searched for keywords and the map will be updated accordingly
	// I decided to use the find function to see if the word is in the map, so as not to add extra
	// words into it that are not keywords.

	for (unsigned int i = 0; i < file_Words.size(); i++)
	{
		
		map <string, int> :: iterator m = keyword_Count.find(file_Words[i]);

		if (m != keyword_Count.end())
		{
			m->second++;
		}

	}


}