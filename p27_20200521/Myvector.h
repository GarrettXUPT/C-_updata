#pragma once
#include<iostream>
using namespace std;
#ifndef __MYVECTOR__H__
#define __MYVECTOR__H__

/*
	��ģ�嶨��
*/
template<typename T1>  // T1��ʾvector�д洢�Ĳ�������
class Myvector {
public:
	typedef T1* myiterator;  // ������

public:
	Myvector();
	Myvector& operator=(const Myvector&);  // ����ģ���ڲ�ʹ��ģ������������Ҫ�ṩģ�����

public:
	myiterator mybegin();  // ��������ʼλ��
	myiterator myend();  // ������ĩβԪ�ص���һ��λ��
public:
	void myfunc(); // ����Ա�����ĺ�����(�����ľ���ʵ��)������ģ��Ķ����У�ϵͳ�ͻ�������Ϊ��������
};

/*
	��������ģ��֮��ĺ���
*/
template<typename T1>
void Myvector<T1>::myfunc() {
	cout << "��ģ���Ա����" << endl;
}

/*
	���캯��
*/
template<typename T1>
Myvector<T1>::Myvector() {
	cout << "������ģ�幹�캯��" << endl;
}
/*
	��ģ���ⲿʵ�ָ�ֵ���������
	<T1>�������ص���һ��ʵ������Myvector
*/
template<typename T1>
Myvector<T1>& Myvector<T1>::operator=(const Myvector& vec) {
	return *this;
}

/*
	ʵ�ֵ�����,�˴�typename�Ǳ��룬��Ϊ��Ҫ�ԣ�::�������ͳ�Ա
	���˴�����typename�Ļ����������ͻ���Ϊmyiterator��һ����̬��Ա
	typename��Ŀ�ľ�����ʽ�ĸ��߱�����myiteator��һ������
*/
template<typename T1>
typename Myvector<T1>::myiterator Myvector<T1>::mybegin() {

}

#endif // !__MYVECTOR__H__


