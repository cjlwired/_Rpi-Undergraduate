// Carlos Lazo
// 10-13-04
// Computer Science II
// Homework #5 - web_Browser.cpp

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#include "Pair.h"

using namespace std;

/*

* Note - This paragraph is being done prior to writing any C++ code.

Design:

     Upon reading the task in front of me, it would seem logical that the first thing to do is to read in
all of the information from the input file and immediately split the paragraph/sentences into seperate words,
which would be stored in a vector. Upon doing that, words that are less than the given integer would be removed
from the vector, probably added into a new vector. After that, all words that are less than the first integer
inputed, m, will be removed from the vector, again, it will probably be added to another vector. Upon the
elimination, all of the remaining elements will be made all lowercase for easier comparing. Afterwards, comparisons 
will be made one element of a vector and the adjacent elements till the nth element, always ensuring that the comparing
does not go over the size of the vector itself. The words will then be checked and inserted into a new vector together
in alphabetical order. They will be inserted in this way because the new vector will then be sorted, and all pairs 
will be next to each other. A new class Pair will be created to store the names of the Pairs and their individual
counts. Using this new class, they will be sorted according to their names and finally printed out.

*/

// This function does just what it says, removes all punctuation from the string
// and makes all letters lowercase.

string remove_Punct_And_Lower (const string& line)
{

	string s = line;

	string::iterator p = remove_if (s.begin(), s.end(), ispunct);

	s.erase(p, s.end());

	for (unsigned int i = 0; i < s.length(); i++)
		s[i] = tolower(s[i]);

	return s;
}

// This function splits the line into individual words

vector <string> split_Into_Words ( const string& x )
{
  vector <string> strings;
  unsigned int i=0, j;

  string line = remove_Punct_And_Lower (x);

  while ( i < line.size() )
    {
      //  Find the beginning of the next string
      for ( ; i < line.size() && isspace( line[i] ); ++i )
        ;

      //  If there is another string, find the end and copy it
      if ( i != line.size() )
        {
          for ( j = i+1; j != line.size() && !isspace( line[j] ); ++j )
            ;
          string s = line.substr( i, j-i );
          strings.push_back( s );
          i = j;
        }
    }

  return strings;
}

string order_Pair (string& s1, string& s2)
{

	if (s1 < s2)
		return (s1 + " " + s2);

	return (s2 + " " + s1);
}

vector <string> find_Pairs (vector <string>& all_Words, int adj_Pair)
{

	vector <string> pairs;

	for (unsigned int i = 0; i < all_Words.size(); i++)
	{

		for (unsigned int j = 1; j <= adj_Pair + 1; j++)
		{
			if ((i + j < all_Words.size()) && (all_Words[i] != all_Words[i+j]))
				pairs.push_back(order_Pair (all_Words[i], all_Words[i+j]));
		}
	}

	return pairs;

}

int main()
{

	string line;

	vector <string> beg_Vec;	// Vector will contain all words in the input file

	int min_Word_Length;		// min_Word_Length will eliminate all words that aren't bigger that it

	cin >> min_Word_Length;

	int adj_Pair;				// adj_Pair will store an integer that will be used to form word pairs
								// with the next adj_Pair words

	cin >> adj_Pair;

	// Read in all values 

	while (getline (cin, line))
	{

		vector <string> temp = split_Into_Words (line);

		for (unsigned int i = 0; i < temp.size(); i++)
			beg_Vec.push_back(temp[i]);
	}

	vector <string> all_Words;	// all_Words will store all valid words according to the assignment definition

	// push_back all strings that are at least of size min_Word_Length into all_Words

	for (unsigned int i = 0; i < beg_Vec.size(); i++)
	{
		if (beg_Vec[i].length() >= min_Word_Length)
			all_Words.push_back(beg_Vec[i]);
	}

	vector <string> word_Pairs = find_Pairs (all_Words, adj_Pair); // Store all valid word pairs in this vector

	sort (word_Pairs.begin(), word_Pairs.end()); // Sort vector to place all word pairs that are alike next to each other


	vector <Pair> hold_Pairs;		// Vector to store Pairs

	Pair p (word_Pairs[0]);			// Add first Pair to the vector of Pairs

	hold_Pairs.push_back(p);

	unsigned int count = 0;		    // Counter used to iterator through all indices of vector

	unsigned int index = 0;		    // Counter used to keep track of index of Pair vector


	// While-loop creates Pair instances. Since the list is sorted now, whenever a Pair is repeated more than once
	// it's count is incremented.

	while (count < word_Pairs.size() - 1)
	{
		if (word_Pairs[count] != word_Pairs[count + 1])
		{
			Pair temp (word_Pairs[count + 1]);

			hold_Pairs.push_back(temp);

			index++;
		}

		else
		{
			hold_Pairs[index].increment();
		}

		count++;
	}

	vector <Pair> valid_Pairs;	// Will store all valid Pairs that are found more than once in the vector

	for (unsigned int i = 0; i < hold_Pairs.size(); i++)
	{
		if (hold_Pairs[i].get_Count() > 1)
			valid_Pairs.push_back(hold_Pairs[i]);
	}

	// sort Pairs according to their download counts

	sort (valid_Pairs.begin(), valid_Pairs.end(), count_Greater);

	// print out Pairs

	for (unsigned int i = 0; i < valid_Pairs.size(); i++)
		cout << valid_Pairs[i].get_Name() << " " << valid_Pairs[i].get_Count() << endl;

	int freeze;
	cin >> freeze;
	return 0;
}