#include<iostream>
#include"Time.h"

using namespace std;

/*
	一、在类中实现inline函数，类内的成员函数定义

	二、成员函数末尾的const
		在成员函数后面增加const，不但要在声明处增加const，也要在定义中增加
		作用：
			通知系统，该函数不会修改该对象里任何成员变量的值等等，这个成员函数不会修改对象的任何状态
			也称为常量成员函数
		const成员函数，则不管是const对象还是一般对象都可以调用，但是非const成员函数，就不可以被const对象调用
	
	三、mutable(不稳定，容易改变) const的反义词
		mutable的引用可以突破const的限制
		用mutable修饰成员变量，若一个成员变量被mutable修饰，就表示这个成员变量永远处于可被修改状态，即便是在const结尾的成员函数中
	
	四、返回自身对象的引用this
		调用成员函数时，编译器负责把这个对象地址(&time)传递给成员函数中的一个隐藏this形参
		1.this指针只能在成员函数中使用，全局函数、静态函数都不能使用this指针
		2.在普通函数中，this是一个指向非const对象的const指针，若类型为Time，则this就是Time* const this(this只能指向当前对象，而不能指向其他对象)
		3.在const成员函数中，this指针是一个指向const对象的const指针
	
	五、stactic成员
		属于整个类的成员变量/成员函数，就叫做静态成员变量/静态成员函数
		特点：
			不属于某个对象，属于整个类，我们一旦在某个对象中修改了该值，则在该类的其他对象中也可看到修改
		如何定义静态成员变量：
			我们会在一个.cpp文件开头来定义静态成员变量，这样就可以保证在调用任何函数之前已经被初始化了
		静态成员函数是不能够修改与对象相关的成员变量
*/		

/*
	类的使用
*/
void test01() {

	Time time1(11, 12, 34);
	time1.printTime();  // 11:12:34
	
	time1.addhour(2);
	time1.printTime();  // 13:12:34

	time1.addminutes(10);
	time1.printTime();  // 13:22:34

	time1.addseconds(20);
	time1.printTime();  // 13:22:54

	/*
		因为返回的是对象自己，所以可以链式编程
	*/
	time1.addminutes(10).addseconds(2).printTime();  // 13:32:56
}

/*
	static成员
*/
void test02() {
	Time time1(11, 11, 11);
	Time time2(12, 12, 12);
	time1.printTime();	// 11:11:11 
	time2.printTime();	// 12:12:12 

	time1.printtimetmp();  // count = 2
}

int main() {

	test02();

	system("pause");
	return 0;
}