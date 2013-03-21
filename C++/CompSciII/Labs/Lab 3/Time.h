//Carlos Lazo
//9-15-04
//Lab #3 - Time.h

class Time
{
	public:

		Time();
		Time(int h, int m, int s);

		int getHour() const;
		int getMinute() const;
		int getSecond() const;

		void setHour(int h);
		void setMinute(int m);
		void setSecond(int s);

		void printAmPm() const;
		void printTime() const;

	private:
		
		int hour;
		int minute;
		int second;
};

bool isEarlierThan (const Time& t1, const Time& t2);