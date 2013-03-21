
//  Use a map to count the number of words that appear in the input.
//  This does not convert upper case letters to lower case, so for
//  example Hi and hi are treated differently.  This could be changed

// disable warning C4786 -- only needed for Visual Studio 6.  This is
// used to prevent a large set of irrelevant warnings about the size
// of identifiers created by use of maps.
// #pragma warning( disable : 4786 )

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
  string s;
  map<string, int> counters; // store each word and an associated counter

  // read the input, keeping track of each word and how often we see it
  while (cin >> s)
    ++counters[s];

  // write the words and associated counts
  for (map<string, int>::const_iterator it = counters.begin();
       it != counters.end(); ++it) {
    cout << it->first << "\t" << it->second << endl;
  }
  return 0;
}

