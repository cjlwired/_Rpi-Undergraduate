// Carlos Lazo
// 10-7-04
// Homework #4
// Song.h

#ifndef song_h_
#define song_h_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Song
{
	public:

		Song (string n, int ID);

		string get_Name() { return song_Name;}
		int get_ID() {return song_ID;}
		int get_Download_Count() {return download_Count;}

		void set_Name (string s);
		void set_ID (int ID);
		void set_Download_Count(int dC);

		void increment ();

	private:

		string song_Name;
		int song_ID;
		int download_Count;
	
};

#endif
