
#include<iostream>
#ifndef __CA__H__
#define __CA__H__

template<typename C>  // ���ģ�����
class A1 {		// ��ģ��
public:
	template<typename T1>
	A1(T1 v1, T1 v2);  // �ڹ��캯��������ģ����������ģ���޹�


	template<typename T>
	void myft(T tmpt) {  // ��Ա����ģ��
		std::cout << tmpt << std::endl;
	}

	void myfuncpt() {};
public:
	C m_ic;
};
/*
	��ν���Ա����ģ�������ⶨ��
	1����д��ĳ�Ա�����б�
	2����д��Ա�����Լ���ģ������б�
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
