
#include<iostream>
#include"Time.h"
using namespace std;

/*
	��Ķ���
*/

int Time::count = 0;  // ��̬��Ա�����ĳ�ʼ��

void Time::printtimetmp() {
	cout << "count = " << count << endl;
}

Time::Time(int hour, int minute, int second) :_hour(hour), _minute(minute), _second(second) { count++; };

void Time::printTime() const {
	cout << _hour << ":" << _minute << ":" << _second << endl;
}