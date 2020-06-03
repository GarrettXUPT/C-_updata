#pragma once
#include<iostream>

using namespace std;
class TA {
public:
	TA(int i) : m_i(i){
		cout << "对象被构造" << endl;
	}

	TA(const TA& ta) :m_i(ta.m_i) {
		cout << "拷贝构造函数执行" << endl;
	}

	~TA() {
		cout << "对象被销毁" << endl;
	}
	/*
		重载()运算符
	*/
	void operator()() {  
		cout << "my operator begin" << endl;
		cout << "m_i = " << m_i << endl;
		cout << "my operator end" << endl;
	}
private:
	int m_i;
};
