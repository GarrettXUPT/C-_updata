#pragma once

#include<iostream>
#ifndef __C__H__
#define __C__H__

/*
	ֻ��ʹ����A�����֣���û�ж�A���в���
*/
class A;


class C {
public:
	/*
		��Ϊ��A����Ԫ������ֻ��public��ĺ������ܳ�Ϊ���������Ԫ��Ա����
	*/
	void callCAF(int a, A& obj);
};

#endif // !__C__H__

