#include"C.h"
#include"A.h"


void C::callCAF(int a, A& obj) {
	obj.data = a;
	std::cout << "��Ԫ��Ա�������óɹ�" << std::endl;
}