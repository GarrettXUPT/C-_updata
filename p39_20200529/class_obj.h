#pragma once
#include<iostream>

using namespace std;
class TA {
public:
	TA(int i) : m_i(i){
		cout << "���󱻹���" << endl;
	}

	TA(const TA& ta) :m_i(ta.m_i) {
		cout << "�������캯��ִ��" << endl;
	}

	~TA() {
		cout << "��������" << endl;
	}
	/*
		����()�����
	*/
	void operator()() {  
		cout << "my operator begin" << endl;
		cout << "m_i = " << m_i << endl;
		cout << "my operator end" << endl;
	}
private:
	int m_i;
};
