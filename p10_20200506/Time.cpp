
#include<iostream>
#include"Time.h"
using namespace std;

/*
	��Ķ���
*/

Time::Time(int hour, int minute, int second) {
	_hour = hour; _minute = minute; _second = second;
}

void Time::printTime() {
	cout << _hour << ":" << _minute << ":" << _second << endl;
}