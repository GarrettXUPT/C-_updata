#pragma once

#include<iostream>
#ifndef __C__H__
#define __C__H__

/*
	只是使用了A的名字，并没有对A进行操作
*/
class A;


class C {
public:
	/*
		成为类A的友元函数，只有public类的函数才能成为其他类的友元成员函数
	*/
	void callCAF(int a, A& obj);
};

#endif // !__C__H__

