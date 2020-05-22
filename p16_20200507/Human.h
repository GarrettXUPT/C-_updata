#pragma once

#include<string>
#include<iostream>

using namespace std;

#ifndef __HUMAN__H__
#define __HUMAN__H__


class Human {
public:
	/*
		���캯��
	*/
	Human();
	Human(int age, string name);

	/*
		��ӡ����
	*/
	void printHuman();

protected:

	/*
		��ȡ����
	*/
	inline int getAge() { return m_Age; };
	/*
		��������
	*/
	void setAge(int age);

	/*
		��������
	*/
	void setName(string name);

	/*
		��ȡ����
	*/
	inline string getName() { return m_Name; };

private:
	int m_Age;  //���� 
	string m_Name;  // ����
};

#endif // !__HUMAN__H__

