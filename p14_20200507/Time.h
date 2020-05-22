#pragma once
#ifndef __TIME__H__
#define __TIME__H__
/*
	类的声明
*/
class Time {
public:

	static int count;  // 声明静态成员变量，没有分配内存，不能进行初始化

	static void printtimetmp();  // 静态成员函数

	const int _value = 10;  // const成员变量的初始化
	
	//const int valuable; // 在构造函数时改初值

	//Time(){};

	Time() = default;  // 编译器为这种=default的函数自动生成函数体,相当于创建了一个默认构造函数

	/*
		拷贝构造函数
	*/
	Time(const Time& tmpTime);

	/*
		带有默认参数的构造函数
	*/
	explicit Time(int hour, int minute, int second = 59);

	/*
		在类中直接实现的成员函数，会被当做inline内联函数来处理
	*/
	inline void addhour(int tmphour) const{
		_hour += tmphour;
	}

	/*
		将对象自己返回
	*/
	Time& addminutes(int tmpminute) {
		_minute += tmpminute;
		return *this;
	}

	/*
		若形参和变量名重名
	*/
	Time& addseconds(int _second) {
		this->_second += _second;
		return *this;
	}

	void printTime() const;

private:
	/*
		类内初始值
	*/
	mutable int _hour = 0;
	int _minute = 0;
	int _second = 0;

};

/*
	与类相关的普通函数
*/
void printObj(Time& time);

#endif 

