#pragma once
#ifndef __TIME__H__
#define __TIME__H__
/*
	ÀàµÄÉùÃ÷
*/
class Time {
public:
	Time();
	Time(int hour, int minute, int second);
	void printTime();

private:
	int _hour;
	int _minute;
	int _second;
};


#endif 

