//  File:     stats.cpp
//  Author:   Chuck Stewart
//  Purpose:  Demonstrate file streams and specifying file names in
//     command-line arguments.   These are explained in great detail
//     below. 


#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>


using std::accumulate;    //  defined in numeric
using std::cerr;          //  defined in iostream
using std::endl;          //  defined in iostream
using std::ifstream;      //  defined in fstream
using std::ofstream;      //  defined in fstream
using std::sort;          //  defined in algorithm
using std::vector;        //  defined in vector


//  The main function can have parameters, just like other functions.
//  These parameters are called "command-line arguments".  Here's how
//  they work.  Suppose you have created a program called prog.exe.
//  Now suppose you run this program from the command line, as we have
//  been doing all semester, by typing
// 
//     prog.exe foo bar 3.14
//
//  When you've typed this line and hit the enter (return) key, the
//  command shell interpreter packages what you've typed into an array
//  of C-style strings and passes them to the function called main.
//  (This is why you always need a "main" function --- the interpreter
//  looks for it to start your program.)  The function main, in the
//  source code, has either 0 or 2 parameters.  When it has 0
//  parameters, as we have written all semester, the command-line
//  arguments are ignored (redirection of files to cin and cout
//  through < and > is handled differently).  When it has two
//  parameters, the first, is an integer which is always called argc.
//  This is the number of arguments.  In the example above, argc==4.
//  The second parameter, always called argv, is an array of argc
//  C-style char strings.  In our example,
//
//     argv[0] == "prog.exe"
//     argv[1] == "foo"
//     argv[2] == "bar"
//     argv[3] == "3.14"
//
//  Observe that the name of the program is always included as
//  argv[0], which is why argv==4, not 3, as might be expected. The
//  C-style strings in argv are not the standard library string
//  objects that we have been working with all semester.  You can
//  convert them to standard strings; for example,
//
//     string s( argv[1] );
//
//  We don't often do this, however.  Instead we generally will treat
//  the command-line arguments (strings) in one of two ways.  One way
//  is as values to be used in the program computations.  An example
//  is illustrated with argv[3] from above.  This appears to be
//  intended to be a floating-point value, but when it is input, it is
//  a string.  Fortunately, we can trivially convert this argument to
//  a float (or double) using the function function atof, which is
//  defined in the include file cstdlib:
//
//     double pi = atof( argv[3] );
//
//  The second common use of command-line arguments is as names of
//  data files.  The C-style strings stored in argv are treated as
//  names of files and passed to constructors of "stream" objects.
//  These objects are "attached" to the files in order to read and
//  write the files.  Details are given in the program.

int
main( int argc, char* argv[] )
{
  //  Make sure the names of an input and an output file are both
  //  specified on the command-line and nothing else is.  Note that
  //  cerr is an already existing output stream like cout.  It writes
  //  to the command display, and is traditionally used for error
  //  messages.

  if ( argc != 3 )
    {
      cerr << "Usage:  " << argv[0] << " infile outfile\n";
      return 1;
    }
  
  //  Create an ifstream object (variable) called data_str and attach
  //  it to the file specified in argv[1].  The name ifstream stands
  //  for "input file stream", and the ifstream constructor does the
  //  work of opening the file.  Once data_str is properly
  //  constructed, it can be treated EXACTLY LIKE cin.  Note that we
  //  provide the name of the file directly from the C-style string
  //  from the command-line arguments.

  ifstream data_str( argv[1] );

  //  Check to see if the ifstream object is ready to be read.  If it
  //  has not been opened correctly, most likely because the file does
  //  not exist (at least not in the place you think it exists), the !
  //  operator will return true.

  if ( !data_str )
    {
      cerr << "Could not open " << argv[1] << " to read numbers.\n";
      return 1;
    }

  //  Create an ofstream object (variable) called result_str and
  //  attach it to the file specified in argv[2].  The ofstream
  //  constructor does the work of opening the file for output.
  //  (Anything that was in the file will be lost.)  Once result_str
  //  is properly constructed, it can be treated EXACTLY LIKE cout.

  ofstream result_str( argv[2] );

  //  Check to see if the ofstream is ready to be written to.  If it
  //  has not been opened correctly, the ! operator will return true.

  if ( !result_str )
    {
      cerr << "Could not open " << argv[2] << " to write the results.\n";
      return 1;
    }

  vector<double> values;
  double x;
  
  //  Read each of the doubles in the file argv[1] and put it on the
  //  end of the vector.  This will continue until the end of file is
  //  reached or until a non-double is read.

  while ( data_str >> x ) values.push_back( x );

  // Close the file attached to the ifstream.  Once this is done,
  // reading from data_str will not succeed.

  data_str.close(); 

  //  Make sure at least one value was read.

  if ( values.empty() )
    {
      cerr << "Ended reading " << argv[1] << " before finding any doubles.\n";
      return 1;
    }

  //  Compute the average and median using generic functions.

  double avg = accumulate( values.begin(), values.end(), 0.0 ) 
    / values.size();
  sort( values.begin(), values.end() );
  int mid = values.size() / 2;
  double median =
    ( values.size()%2 == 1 ) ? values[mid] : (values[mid-1] + values[mid])/2.0;

  //  Write to the output file.  Note how the C-style string name of
  //  the input file is output easily.

  result_str << "There are " << values.size() << " values in " << argv[1] 
             << "\nThe average value is " << avg << "\n"
             << "\nThe median value is " << median << endl;
  result_str.close();

  return 0;
}