#pragma once

#ifndef __A__H__
#define __A__H__
#include"C.h"
// class C;仅仅是个类声明

class A {
	friend void C::callCAF(int a, A& obj);
private:
	int data;
};

#endif // !__A__H

