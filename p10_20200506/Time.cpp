
#include<iostream>
#include"Time.h"
using namespace std;

/*
	类的定义
*/

Time::Time(int hour, int minute, int second) {
	_hour = hour; _minute = minute; _second = second;
}

void Time::printTime() {
	cout << _hour << ":" << _minute << ":" << _second << endl;
}