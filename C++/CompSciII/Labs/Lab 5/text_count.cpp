
//  Program:  text_count.cpp
//  Author:   Chuck Stewart
//  Purpose:  Count the lines, characters (non-whitespace), and words
//    in a text file.   Count the occurrences of each letter and the
//    occurrences of each word.  Ignore punctuation in the words.

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <list>


using namespace std;

unsigned int count_characters( const string& a_line );
void add_to_letter_counts( const string & a_line, 
                           vector<int>& letter_counters );
vector<string> break_up_line( const string& a_line );
void count_word_occurrences( list<string> & words );

int
main()
{
  unsigned int character_count = 0;
  unsigned int line_count = 0;
  vector<int> letter_counters(26, 0 );  // counts for the individual letters
  list<string> all_words;

  //  Handle one line at a time...

  string a_line;
  while ( getline( cin, a_line ) )
    {
      line_count ++ ;
      character_count += count_characters( a_line );
      add_to_letter_counts( a_line, letter_counters );
      vector<string> words_in_line = break_up_line( a_line );
      
      //  Add all words to the back of the all_words vector.
      for ( vector<string>::iterator p = words_in_line.begin(); 
            p != words_in_line.end(); ++ p )
        all_words.push_back( *p );
    }

  //  Output char, word and line counters

  cout << "\nHere are the statistics on the input text file:\n"
       << "  char count = " << character_count << "\n"
       << "  word count = " << all_words.size() << "\n"
       << "  line count = " << line_count << "\n";

  //  Output the letter counts

  cout << "\nHere are the letter counts:\n";
  for ( unsigned int i = 0; i < 26; ++ i )
    {
      cout << "  " << char( 'a' + i ) << ":  " << letter_counters[ i ] << "\n";
    }

  count_word_occurrences( all_words );

  for (unsigned int i = 0; i != -1; i++); //Hold loop
}


// Return the number of alphabetic characters on the line

unsigned int 
count_characters( const string& a_line )
{
  unsigned int count = 0;
  for ( unsigned int i = 0; i < a_line.size(); ++ i )
    {
      if ( ! isspace( a_line[i] ) )
        ++ count ;
    }
  return count;
}


//  For each letter seen add to the appropriate count in the vector.

void
add_to_letter_counts( const string & a_line, 
                      vector<int>& letter_counters )
{
  for ( unsigned int i = 0; i < a_line.size(); ++ i )
    {
      if ( isalpha( a_line[i] ) )
        ++ letter_counters[ tolower( a_line[i] ) - 'a' ];
    }
}


//  Break up a string storing a line of input into a vector of strings
//  storing the words from the line

vector<string> 
break_up_line( const string& a_line )
{
  vector<string> words;
  unsigned int i=0, j;

  //  Outer loop goes one word at a time

  while ( i != a_line.size() )
    {
      //  Skip to first alphabetic char.  Always check for the end of
      //  the string (line) before testing the letter.

      while ( i != a_line.size() && !isalpha( a_line[i] ) )
        ++ i;

      //  Break out if end is found before a new word is found

      if ( i == a_line.size() ) break;

      //  Find the end of the word
      
      for ( j = i+1; j != a_line.size() && isalpha( a_line[j] ); ++ j )
        ;   // empty loop body - everything is done in the control

      //  Form word and convert to lower case:

      string new_word = a_line.substr( i, j-i );
      for ( string::iterator q = new_word.begin(); q != new_word.end(); ++q )
        *q = tolower( *q );

      //  Add to the result

      words.push_back( new_word );

      i = j;  //  jump to the end
    }
  return words;
}


//  Count and output the number of occurrences of each word in
//  alphabetical order.  The words vector can have multiple copies of
//  each word.  After sorting the instances of each word will be
//  adjacent to each other, so counting is straightforward.

void printList(list <string> words)
{

	list<string>::iterator p = words.begin();

	for (; p!= words.end(); p++)
		cout << *p << " ";

	cout << endl;
}

void
count_word_occurrences( list<string> & words )
{

  if ( words.size() == 0)
    {
      cout << "\nNo words...\n";
      return;
    }

  printList(words);

  words.sort();  //  alphabetic order

  printList(words);

  list<string>::iterator p = words.begin(); 
  string current = *p;      // record the first word
  unsigned int count = 1;   // it has been seen once
  ++ p;                     // start at second word

  while( p != words.end() )
    {

	  cout << *p;

      if ( *p == current )
        {   // same word, so increment the count
          count ++ ;  
        }
      else
        {  //  new word
          cout << current << ":  " << count << "\n";
          current = *p;     // record the word
          count = 1;     // reset counter
        }
      ++ p;
    }
  cout << current << ":  " << count << "\n" << endl;

}