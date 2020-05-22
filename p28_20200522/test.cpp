#include<iostream>
#include"ca.h"

/*
	显式实例化手段中的实例化定义，这种实例化定义只需要在一个.cpp文件中就可以
	编译器遇到这个代码，就直接实例化出来一个A<float>类，减少代码开销
	该种实例化定义会实例化，该类模板的所有成员函数
*/
template A1<float>;
/*
	编译器会为其生成代码
*/
template int MyAdd(int v1, int v2);

void test03() {
	A1<float> a(1, 2);
}

