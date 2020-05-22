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

	const int _value = 10;  // const��Ա�����ĳ�ʼ��
	
	//const int valuable; // �ڹ��캯��ʱ�ĳ�ֵ

	//Time(){};

	Time() = default;  // ������Ϊ����=default�ĺ����Զ����ɺ�����,�൱�ڴ�����һ��Ĭ�Ϲ��캯��

	/*
		�������캯��
	*/
	Time(const Time& tmpTime);

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
	/*
		���ڳ�ʼֵ
	*/
	mutable int _hour = 0;
	int _minute = 0;
	int _second = 0;

};

/*
	������ص���ͨ����
*/
void printObj(Time& time);

#endif 

