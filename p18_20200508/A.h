#pragma once

#ifndef __A__H__
#define __A__H__
#include"C.h"
// class C;�����Ǹ�������

class A {
	friend void C::callCAF(int a, A& obj);
private:
	int data;
};

#endif // !__A__H

