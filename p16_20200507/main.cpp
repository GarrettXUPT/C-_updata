#include<iostream>
#include"Human.h"
#include"Man.h"

using namespace std;

/*
	一、派生类
		类与类之间的层次关系，即父类和子类之间的关系，这种层次关系就是继承
		继承和多态是面向对象程序设计的核心思想
		父类：定义公用的成员变量和成员函数，我们通过继承来构建新的类，即子类
		子类：特定的功能
		一个子类可以继承多个父类

	二、派生类对象定义时，调用构造函数的顺序
		先调用父类的构造函数，再调用子类的构造函数

	三、public private protected 访问权限
		public：可以被任意实体访问
		private：只允许本类的成员函数访问
		protected：只允许本类或者子类的成员函数访问

	四、函数遮蔽
		子类中如果有一个同名函数与父类的一个函数相同，那么该函数被重写，也就是说，子类无法再访问该函数

	说明：
		1、using Human::somefunc; 使用该种格式，凡是基类中的public protected的成员函数在子类中都可见
		2、using引入的主要目的是用来实现在子类对象中调用父类的重载版本，该函数在父类中的参数和子类中的参数要满足重载条件
*/

/*
	类的使用
*/
void test01() {
	
	Man man;
	man.setHuman(12, "Walker");
	man.printHuman();  // name: Walker age: 12

}



int main() {
	test01();
	system("pause");
	return 0;
}