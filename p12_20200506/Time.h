#pragma once
#ifndef __TIME__H__
#define __TIME__H__
/*
	�������
*/
class Time {
public:

	static int count;  // ������̬��Ա������û�з����ڴ棬���ܽ��г�ʼ��

	static void printtimetmp();  // ��̬��Ա����

	Time();
	/*
		����Ĭ�ϲ����Ĺ��캯��
	*/
	explicit Time(int hour, int minute, int second = 59);

	/*
		������ֱ��ʵ�ֵĳ�Ա�������ᱻ����inline��������������
	*/
	inline void addhour(int tmphour) const{
		_hour += tmphour;
	}

	/*
		�������Լ�����
	*/
	Time& addminutes(int tmpminute) {
		_minute += tmpminute;
		return *this;
	}

	/*
		���βκͱ���������
	*/
	Time& addseconds(int _second) {
		this->_second += _second;
		return *this;
	}

	void printTime() const;

private:
	mutable int _hour;
	int _minute;
	int _second;
};


#endif 

