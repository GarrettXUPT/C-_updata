#pragma once
#ifndef __TIME__H__
#define __TIME__H__
/*
	�������
*/
class Time {
public:
	Time();
	/*
		����Ĭ�ϲ����Ĺ��캯��
	*/
	explicit Time(int hour, int minute, int second = 59);
	void printTime();

private:
	int _hour;
	int _minute;
	int _second;
};


#endif 

