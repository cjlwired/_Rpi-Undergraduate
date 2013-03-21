//Carlos Lazo
//9-23-04
//Homework #3 - Diver Program -> Diver.h

#ifndef diver_h_
#define diver_h_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Diver
{
	public:

		bool read(istream& in_str);

		const string getName() const { return name;}
		const string getCountry() const {return country;}
		const int getID() const { return ID; }
		const int getPlace() const {return place;}
		const double getScore() const
		{
			double score = 0.0;

			for (unsigned int i = 0; i < scores.size(); i++)
				score += scores[i];
					
			return score;
		}

		void setName(string);
		void setID(int);
		void setCountry(string);
		void setPlace(int);
		
		void addScore(double);

		ostream& outputDiver (ostream&, int) const;

	private:
	
		string name;
		string country;
		int place;
		int ID;
		vector <double> scores;

};

bool greater_Scores(const Diver& div1, const Diver& div2);
bool ID_sort(const Diver& div1, const Diver& div2);

#endif

