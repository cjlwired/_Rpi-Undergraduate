// Carlos Lazo
// 10-7-04
// Homework #4
// Song.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>

#include "Song.h"

using namespace std;

// Constructor

Song::Song(string n, int ID)
{
	song_Name = n;
	song_ID = ID;
	download_Count = 1;
}

void Song::set_Name(string s)
{
	song_Name = s;
}

void Song::set_ID (int ID)
{
	song_ID = ID;
}

void Song::set_Download_Count(int dC)
{
	download_Count = dC;
}

void Song::increment()
{
	download_Count++;
}
