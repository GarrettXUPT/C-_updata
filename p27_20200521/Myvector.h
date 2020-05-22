#pragma once
#include<iostream>
using namespace std;
#ifndef __MYVECTOR__H__
#define __MYVECTOR__H__

/*
	类模板定义
*/
template<typename T1>  // T1表示vector中存储的参数类型
class Myvector {
public:
	typedef T1* myiterator;  // 迭代器

public:
	Myvector();
	Myvector& operator=(const Myvector&);  // 在类模板内部使用模板名，并不需要提供模板参数

public:
	myiterator mybegin();  // 迭代器起始位置
	myiterator myend();  // 迭代器末尾元素的下一个位置
public:
	void myfunc(); // 将成员函数的函数体(函数的具体实现)放在类模板的定义中，系统就会内联成为内联函数
};

/*
	定义在类模板之外的函数
*/
template<typename T1>
void Myvector<T1>::myfunc() {
	cout << "类模板成员函数" << endl;
}

/*
	构造函数
*/
template<typename T1>
Myvector<T1>::Myvector() {
	cout << "这是类模板构造函数" << endl;
}
/*
	类模板外部实现赋值运算符重载
	<T1>表明返回的是一个实例化的Myvector
*/
template<typename T1>
Myvector<T1>& Myvector<T1>::operator=(const Myvector& vec) {
	return *this;
}

/*
	实现迭代器,此处typename是必须，下为必要性：::访问类型成员
	若此处不加typename的话，编译器就会认为myiterator是一个静态成员
	typename的目的就是显式的告诉编译器myiteator是一个类型
*/
template<typename T1>
typename Myvector<T1>::myiterator Myvector<T1>::mybegin() {

}

#endif // !__MYVECTOR__H__


