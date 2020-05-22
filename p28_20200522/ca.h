
#include<iostream>
#ifndef __CA__H__
#define __CA__H__

template<typename C>  // 类的模板参数
class A1 {		// 类模板
public:
	template<typename T1>
	A1(T1 v1, T1 v2);  // 在构造函数中引入模板和整个类的模板无关


	template<typename T>
	void myft(T tmpt) {  // 成员函数模板
		std::cout << tmpt << std::endl;
	}

	void myfuncpt() {};
public:
	C m_ic;
};
/*
	如何将成员函数模板在类外定义
	1、先写类的成员函数列表
	2、再写成员函数自己的模板参数列表
*/
template<typename C>
template<typename T1>
A1<C>::A1(T1 v1, T1 v2) {
	std::cout << "v1 = " << v1 << " v2 = " << v2 << std::endl;
}

template<typename T>
T MyAdd(T v1, T v2) {
	return v1 + v2;
}


#endif // !__CA__H__
