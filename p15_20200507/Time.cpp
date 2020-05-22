
#include<iostream>
#include"Time.h"
using namespace std;

/*
	类的定义
*/

int Time::count = 0;  // 静态成员变量的初始化

/*
	打印计数
*/
void Time::printtimetmp() {
	cout << "count = " << count << endl;
}

//Time::Time(int hour, int minute, int second) :_hour(hour), _minute(minute), _second(second),valuable(10){ count++; };
/*
	构造函数
*/
Time::Time(int hour, int minute, int second) :_hour(hour), _minute(minute), _second(second){ count++; };

/*
	对象打印函数
*/
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

/*
	赋值运算符重载
*/
Time& Time:: operator=(const Time& tmpTime) {
	cout << "调用了赋值运算符" << endl;
	this->_hour = tmpTime._hour;
	this->_minute = tmpTime._minute;
	this->_second = tmpTime._second;
	return *this;
}

/*
	重载比较==运算符
*/
bool Time::operator==(const Time& time) {
	cout << "调用了重载运算符==" << endl;
	if (this->_hour == time._hour && this->_minute == time._minute && this->_second == time._second) {
		return true;
	}
	return false;
}