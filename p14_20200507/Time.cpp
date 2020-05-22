
#include<iostream>
#include"Time.h"
using namespace std;

/*
	类的定义
*/

int Time::count = 0;  // 静态成员变量的初始化

void Time::printtimetmp() {
	cout << "count = " << count << endl;
}

//Time::Time(int hour, int minute, int second) :_hour(hour), _minute(minute), _second(second),valuable(10){ count++; };
Time::Time(int hour, int minute, int second) :_hour(hour), _minute(minute), _second(second){ count++; };

void Time::printTime() const {
	cout << _hour << ":" << _minute << ":" << _second << endl;
}

/*
	与类相关的普通函数
*/
void printObj(Time& time) {
	time.printTime();
	time.printtimetmp();
}

/*
	拷贝构造函数
*/
Time::Time(const Time& tmpTime) {
	cout << "调用了拷贝构造函数" << endl;
	this->_hour = tmpTime._hour;
	this->_minute = tmpTime._minute;
	this->_second = tmpTime._second;
}