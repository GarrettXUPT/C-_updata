#include"C.h"
#include"A.h"


void C::callCAF(int a, A& obj) {
	obj.data = a;
	std::cout << "友元成员函数设置成功" << std::endl;
}