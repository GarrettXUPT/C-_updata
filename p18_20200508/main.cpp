#include<iostream>
#include"Man.h"
#include"func.h"
#include"A.h"
#include"C.h"

using namespace std;

/*
	一、友元函数
		只要使函数func成为Man的友元函数，那么func就可以访问Man的所有成员,不管是共有还是私有
		友元函数声明是不受权限控制符的限制

	二、友元类
		类可以将其他的类定义成友元类
		友元类可以访问该类中的所有成员
		每个类都要负责控制自己的友元类和友元函数，所以
		1.友元关系不可继承
		2.友元关系是单向的
		3.友元关系也没有传递性

	三、友元成员函数
		使用友元成员函数，必须要注意代码的组织结构，因为该处有声明和定义的依赖关系
		只有public类的函数才能成为其他类的友元成员函数

	友元的优点及缺点：
		优点：允许特定情况下，某些非成员函数访问类的protected及private成员，从而提出友元概念
			  使程序具有较高的灵活性
		缺点：
			这也就破坏了类的封装性，降低了类的可靠性和可维护性
*/

/*
	友元函数使用
*/

void test01() {
	Man man;
	func(man);
}

/*
	友元类
*/

//class B; // 类B声明
//
//class A {
//private:
//	int data;
//	/*
//		友元类的声明，虽然此时类C没有定义，所以说明编译器此时没有判断该类C是否存在，若在其他编译器有报错，则在前面增加原型
//	*/
//	friend class B;
//
//};
//
//class B {
//public:
//	/*
//		给A中的私有变量赋值
//	*/
//	void callCAF(int x, A& a) {
//		a.data = x; 
//		cout << "修改私有变量成功" << endl;
//	}
//
//};

/*
	友元成员函数
*/
void test02() {
	A a;
	C c;
	c.callCAF(3, a);

}

int main() {

	/*
		友元函数
	*/
	test01();

	/*
		友元成员函数
	*/
	test02();
	system("pause");
	return 0;
}