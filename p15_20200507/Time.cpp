
#include<iostream>
#include"Time.h"
using namespace std;

/*
	��Ķ���
*/

int Time::count = 0;  // ��̬��Ա�����ĳ�ʼ��

/*
	��ӡ����
*/
void Time::printtimetmp() {
	cout << "count = " << count << endl;
}

//Time::Time(int hour, int minute, int second) :_hour(hour), _minute(minute), _second(second),valuable(10){ count++; };
/*
	���캯��
*/
Time::Time(int hour, int minute, int second) :_hour(hour), _minute(minute), _second(second){ count++; };

/*
	�����ӡ����
*/
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

/*
	�������캯��
*/
Time::Time(const Time& tmpTime) {
	cout << "�����˿������캯��" << endl;
	this->_hour = tmpTime._hour;
	this->_minute = tmpTime._minute;
	this->_second = tmpTime._second;
}

/*
	��ֵ���������
*/
Time& Time:: operator=(const Time& tmpTime) {
	cout << "�����˸�ֵ�����" << endl;
	this->_hour = tmpTime._hour;
	this->_minute = tmpTime._minute;
	this->_second = tmpTime._second;
	return *this;
}

/*
	���رȽ�==�����
*/
bool Time::operator==(const Time& time) {
	cout << "���������������==" << endl;
	if (this->_hour == time._hour && this->_minute == time._minute && this->_second == time._second) {
		return true;
	}
	return false;
}