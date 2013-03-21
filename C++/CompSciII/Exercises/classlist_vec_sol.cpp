//  Program:  classlist
//  File:     classlist_vec.cpp
//  Author:   Chuck Stewart
//  Purpose:  Build and maintain a list of students enrolled in a
//     class and a waiting list.  This is done for only one class and
//     is just done for demonstration.  This program will be converted
//     to use iterators and then converted again to use std::list.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void enroll_student( const string& id_number, 
                     unsigned int max_students,
                     vector<string>& enrolled,
                     vector<string>& waiting );
void remove_student( const string& id_number, 
                     unsigned int max_students,
                     vector<string>& enrolled,
                     vector<string>& waiting );
void erase_from_vector( unsigned int i,
			vector<string>& v );

int
main()
{
  // Read in the maximum number of students in the course
  unsigned int max_students;
  cout << "\nWelcome to the enrollment program for CSci 1200\n"
       << "Please enter the maximum number of students allowed\n";
  cin >> max_students;

  // Initialize the vector
  vector<string> enrolled;
  vector<string> waiting;

  // Prompt 
  //
  //  Invariant:
  //
  //   (1) enrolled contains the students already in the course,
  //   (2) waiting contains students who would like to be admitted
  //       into the course when the course is full;  they are admitted
  //       to the course in the order they requested admission,
  //   (3) enrolled.size() <= max_students,
  //   (4) if the course is not filled ( enrolled.size() !=
  //       max_students ) then waiting is empty

  do
    {
      cout << "\nOptions:\n"
	   << "  To enroll a student type 0\n"
	   << "  To remove a student type 1\n"
	   << "  To end type 2\n"
	   << "Type option ==> ";
      int option;

      //  If we can't read the input integer, then just fail.
      //  Later we will learn about how to recover from 
      //  such input.

      if ( !(cin >> option ) )
        {
          cout << "Illegal input.  Good-bye.\n";
          return 1;
        }

      //  If the option is 2 then quit by breaking out of the loop.

      else if ( option == 2 )
        {
          break;
        }

      // 
      else if ( option != 0 && option != 1 )
        {
          cout << "Invalid option.  Try again.\n";
        }

      else // option is 0 or 1
        {
          string id_number;
          cout << "Enter student id: ";
          if ( !( cin >> id_number ) )
            {
              cout << "Illegal imput.  Good-bye.\n";
              return 1;
            }
          else if ( option == 0 )
            {
              enroll_student( id_number, max_students, enrolled, waiting );
            }
          else
            {
              remove_student( id_number, max_students, enrolled, waiting ); 
            }
        }
    }
  while ( true );

  //
  sort( enrolled.begin(), enrolled.end() );
  cout << "\nAt the end of the enrollment period, the following students\n"
       << "are in the class:\n\n";
  for ( unsigned int i=0; i<enrolled.size(); ++i )
    {
      cout << enrolled[i] << endl;
    }

  if ( ! waiting.empty() )
    {
      cout << "\nStudents are on the waiting list in the following order:\n";
      for ( unsigned int j=0; j<waiting.size(); ++j )
        {
          cout << waiting[j] << endl;
        }
    }
  return 0;
}


// Enroll a student in the course if there is room and if the student
// is not already in the course or on the waiting list.

void
enroll_student( const string& id_number, 
                unsigned int max_students,
                vector<string>& enrolled,
                vector<string>& waiting )
{
  // Check to see if the student is already enrolled.  If so, output a
  // message and return.

  unsigned int i;
  for ( i=0; i < enrolled.size(); ++i )
    {
      if ( enrolled[ i ] == id_number )
        {
          cout << "Student " << id_number
	       << " is already enrolled." << endl;
          return;
        }
    }

  //  If the course isn't full, add the student.  Then return.

  if ( enrolled.size() < max_students )
    {
      enrolled.push_back( id_number );
      cout << "Student " << id_number << " added.\n"
	   << enrolled.size() << " students are now in the course."
	   << endl;
      if ( enrolled.size() == max_students )
	cout << "Course is now full." << endl;
      return;
    }

  //  Otherwise, we have to deal with the waiting list.  Check to see
  //  if the student is already on the waiting list.

  for ( i=0; i < waiting.size(); ++i )
    {
      if ( waiting[ i ] == id_number )
        {
          cout << "Student " << id_number
	       << " is already on the waiting list." << endl;
          return;
        }
    }

  //  Otherwise, add the student to the waiting list.

  waiting.push_back( id_number );
  cout << "The course is full.  Student " << id_number
       << " has been added to the waiting list.\n"
       << waiting.size() << " students are on the waiting list."
       << endl;
}


//  Remove a student from the course or from the waiting list.  If
//  removing the student from the course opens up a slot, then the
//  first person on the waiting list is placed in the course.

void 
remove_student( const string& id_number, 
                unsigned int max_students,
                vector<string>& enrolled,
                vector<string>& waiting )
{
  //  Check to see if the student is on the course list.
  bool found = false;
  unsigned int loc=0;
  while ( !found && loc < enrolled.size() )
    {
      found = enrolled[ loc ] == id_number;
      if ( !found ) ++ loc;
    }

  //  If so, remove the student and see if a student can be taken from
  //  the waiting list.
  if ( found )
    {
      erase_from_vector( loc, enrolled );
      cout << "Student " << id_number << " removed from the course."
	   << endl;
      if ( waiting.size() > 0 )
        {
          enrolled.push_back( waiting[ 0 ] );
          cout << "Student " << waiting[ 0 ] << " added to the course "
	       << "from the waiting list." << endl;
          erase_from_vector( 0, waiting );
          cout << waiting.size() << " students remain on the waiting list."
	       << endl;
          
        }
      else
        {
          cout << enrolled.size() << " students are now in the course."
	       << endl;
        }
    }

  //  If not, check to see if the student is on the waiting list
  else 
    {
      found = false;
      loc = 0;
      while ( !found && loc < waiting.size() )
        {
          found = waiting[ loc ] == id_number;
          if ( ! found ) ++ loc;
        }

      if ( found )
        {
          erase_from_vector( loc, waiting );
          cout << "Student " << id_number
               << " removed from the waiting list.\n"
               << waiting.size() << " students remain on the waiting list."
               << endl;
        }
      else
        {
          cout << "Student " << id_number
	       << " is in neither the course nor the waiting list" << endl;
        }
    }
}


//  To be written as an exercise in lecture
void
erase_from_vector( unsigned int i,
                   vector<string>& v )
{
  //  Copy the values at and above i down, one at a time.
  for ( ; i < v.size()-1; ++ i )
    v[ i ] = v[ i+1 ];

  //  Remove the last item.
  v.pop_back();
}
        

      
      
