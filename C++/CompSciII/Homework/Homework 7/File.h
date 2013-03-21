// Carlos Lazo
// 11-15-04
// Homework #7
// File.h

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class File
{

	public:

		File (string n, vector <string> keywords);

		// Return functions to access private variables defined here

		string get_Link_Name() const { return file_Name; }
		vector <string> get_File_Words() const { return file_Words; }
		vector <string> get_Linked_Files() const { return linked_Files; }
		map <string, int> get_Keyword_Count() const { return keyword_Count; }
	



	private:
	
		string file_Name;					// This string will hold the name of the file
		vector <string> file_Words;				// This string will hold the words of the file
												// which will be read during the constructor
		vector <string> linked_Files;		// This vector store all of the linking files
											// that have been found within the file itself
		map <string, int> keyword_Count;		// As the constructor searches for the keywords,
												// brought in by the cin stream, it will keep
												// track of them individually.

};