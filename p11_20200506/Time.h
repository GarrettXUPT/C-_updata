#pragma once
#ifndef __TIME__H__
#define __TIME__H__
/*
	类的声明
*/
class Time {
public:
	Time();
	/*
		带有默认参数的构造函数
	*/
	explicit Time(int hour, int minute, int second = 59);
	void printTime();

private:
	int _hour;
	int _minute;
	int _second;
};


#endif 

