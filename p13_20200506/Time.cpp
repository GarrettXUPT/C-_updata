
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

Time::Time(int hour, int minute, int second) :_hour(hour), _minute(minute), _second(second),valuable(10){ count++; };

void Time::printTime() const {
	cout << _hour << ":" << _minute << ":" << _second << endl;
}

/*
	������ص���ͨ����
*/
void printObj(Time& time) {
	time.printTime();
	time.printtimetmp();
}
