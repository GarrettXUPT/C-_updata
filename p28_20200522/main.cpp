#include<iostream>
#include"ca.h"

using namespace std;

/*
	显式实例化手段中的实例化定义
	extern不会在本文件中生成一个extren后面所表示的模板的实例化代码
	extern目的是告诉编译器，在其他的文件中已经有了一个模板的实例化版本了
*/
extern template A1<float>;

extern template int MyAdd(int v1, int v2);

/*
	一、普通类的成员函数模板
		不管是普通类还是类模板，它的成员函数可以是一个函数模板，成为成员函数模板(不可以是虚函数)

	二、类模板的成员函数模板
		类模板的模板参数必须使用<>指定，成员函数模板或者是函数模板的参数都可以进行推断
		类模板的成员函数只有被调用时，该函数才会被实例化(在代码中出现了，才进行实例化)
		若某函数从未使用，则不会实例化该成员函数
	三、模板显示实例化，模板声明
		每个.cpp文件都是独立编译的，就是自己编译自己的
		为了防止在多个.cpp文件中，都实例化相同的类模板，所以C++11中提出解决方法，即为显式实例化
		通过显式实例化，来避免这种生成多个相同类模板示例的开销

		像这种template int MyAdd(int v1, int v2);实例化定义只能有一个，但是extern template int MyAdd(int v1, int v2); 实例化声明可以有多个
	
*/

class A {  // 普通类
public:
	template<typename T>
	void myft(T tmpt) {  // 成员函数模板
		cout << tmpt << endl;
	}
};

void test01() {
	A a;
	a.myft(3.14);   // 编译器在遇到这条语句的时候，编译器会实例化函数模板
}


void test02() {
	A1<float> a1(10, 20);
	A1<float> a2(1.1, 2.2);
}

int main() {
	test02();
	return 0;
}