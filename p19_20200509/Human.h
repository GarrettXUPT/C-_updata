#pragma once

#include<string>
#include<iostream>

using namespace std;

#ifndef __HUMAN__H__
#define __HUMAN__H__


class Human {
public:
	/*
		构造函数
	*/
	Human();
	Human(int age, string name);

	/*
		拷贝构造函数
	*/
	Human(const Human& tmphuman) {
		//.....各种操作
	}

	/*
		打印对象
	*/
	void printHuman();

	/*
		调用测试函数
	*/
	inline void testHuman() { cout << "调用的是父类对象" << endl; };
	/*
		虚函数声明
	*/
	virtual void testClass();

	/*
		纯虚函数声明：没有虚函数，只有一个函数声明
	*/
	virtual void eat() = 0;

	virtual ~Human();

protected:

	/*
		获取年龄
	*/
	inline int getAge() { return m_Age; };
	/*
		设置年龄
	*/
	void setAge(int age);

	/*
		设置姓名
	*/
	void setName(string name);

	/*
		获取姓名
	*/
	inline string getName() { return m_Name; };

private:
	int m_Age;  //年龄 
	string m_Name;  // 姓名
};

#endif // !__HUMAN__H__

