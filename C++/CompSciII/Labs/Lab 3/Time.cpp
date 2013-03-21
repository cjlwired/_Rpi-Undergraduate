//Carlos Lazo
//9-15-04
//Lab #3

#include <iostream>
#include "Time.h"

using namespace std;

Time::Time()
{
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time (int h, int m, int s)
{
	hour = h;
	minute = m;
	second = s;
}

int Time::getHour() const
{
	return hour;
}

int Time::getMinute() const
{
	return minute;
}

int Time::getSecond() const
{
	return second;
}

void Time::setHour(int h)
{
	hour = h;
}

void Time::setMinute(int m)
{
	minute = m;
}

void Time::setSecond(int s)
{
	second = s;
}

void Time::printAmPm() const
{
	
	if (getHour() == 12)
	{
		if (getMinute() < 10)
		{
			if (getSecond() < 10)
				cout << getHour() << ":0" << getMinute() << ":0" << getSecond() << " PM";
			else
				cout << getHour() << ":0" << getMinute() << ":" << getSecond() << " PM";
		}

		else
		{
			if (getSecond() < 10)
				cout << getHour() << ":" << getMinute() << ":0" << getSecond() << " PM";
			else
				cout << getHour() << ":" << getMinute() << ":" << getSecond() << " PM";
		}
	}

	else if (getHour() > 12)
	{
		if (getMinute() < 10)
		{
			if (getSecond() < 10)
				cout << (getHour() - 12) << ":0" << getMinute() << ":0" << getSecond() << " PM";
			else
				cout << (getHour() - 12) << ":0" << getMinute() << ":" << getSecond() << " PM";
		}

		else
		{
			if (getSecond() < 10)
				cout << (getHour() - 12) << ":" << getMinute() << ":0" << getSecond() << " PM";
			else
				cout << (getHour() - 12) << ":" << getMinute() << ":" << getSecond() << " PM";
		}
	}

	else
	{
		if (getMinute() < 10)
		{
			if (getSecond() < 10)
				cout << getHour() << ":0" << getMinute() << ":0" << getSecond() << " AM";
			else
				cout << getHour() << ":0" << getMinute() << ":" << getSecond() << " AM";
		}

		else
		{
			if (getSecond() < 10)
				cout << getHour() << ":" << getMinute() << ":0" << getSecond() << " AM";
			else
				cout << getHour() << ":" << getMinute() << ":" << getSecond() << " AM";
		}
	}

	return ;
}


void Time::printTime() const
{
	if (getMinute() < 10)
		cout << getHour() << ":0" << getMinute() << ":" << getSecond();
	else
		cout << getHour() << ":" << getMinute() << ":" << getSecond();
	
	return ;
}

bool isEarlierThan (const Time& t1, const Time& t2)
{
	
	if (t1.getHour() < t2.getHour())
		return true;
	else if (t1.getHour() > t2.getHour())
		return false;
	else
	{
		if (t1.getMinute() < t2.getMinute())
			return true;
		else if (t1.getMinute() > t2.getMinute())
			return false;
		else
		{
			if (t1.getSecond() < t2.getSecond())
				return true;
			else if (t1.getSecond() > t2.getSecond())
				return false;
			else
				return true;
		}
	}

	return true;
}