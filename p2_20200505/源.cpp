#include<iostream>

#include"head1.h"
#include"head2.h"

using namespace std;

/*
	局部变量及初始化：
		随时用，随时定义
		int value{1} 效果与 value = 1相同
	auto：自动类型推断
		auto在声明变量的时候，根据变量初始值的类型自动为变量选择匹配的类型(声明时必须赋值)
		自动类型推断发生在编译期间，在使用时不会导致程序的运行效率降低

	头文件防卫申明
		#ifndef __HEAD1__H__
		#define __HEAD1__H__
		int g_value1 = 8;
		#endif // __HEAD1__

	引用：
		为变量起别名，使用&表示，起完别名之后，别名与变量本身可以看做同一个变量，而且不额外占用内存，引用和原变量占用一块内存
		但是这是编译表象，实际上并不占用同一块内存
		1、定义引用时候必须初始化
		2、引用只能绑定到变量中，不能绑定到常量上

	常量：
		const关键字：表示不变
		const int var = 7;  // 表示该变量的值不会再其他地方改变，编译器会检查
		constexpr 关键字，只有在C++11中被引用， 表示在编译的时候求值，可以提高性能

*/

/*
	自动类型转换演示auto
*/
void test01() {
	auto bevalue = true;  // bool
	auto ch = 'a';  // char
	auto dv1 = 1.2;  //double
	auto dv2 = 1.2f;  //float
}

/*
	引用示例
*/
void test02() {
	int value1 = 1;
	int& refvalue = value1;  // value别名就是refvalue,&不表示取地址，只是起标识作用
	cout << "原名 value1 = " << value1 << endl;  
	cout << "别名 refvalue = " << ++refvalue << endl;
	cout << "别名更新后的原名" << value1 << endl;
}

/*
	引用函数示例
*/
void swap(int& a, int& b) {  // 形参是引用类型，改变这个值会影响到外界
	int tmp = a;
	a = b;
	b = tmp;
}

/*
	常量示例
*/

constexpr int sum_test() {
	int a = 1;
	int b = 2;
	return a + b;
}

void test03() {
	const int var = 7;
	cout << "命名常量var = " << var << endl;
	int& var2 = (int&)var;
	var2 = 18;
	cout << "var = " << var << endl;  // 7
	cout << "var2 = " << var2 << endl;  // 18  由此可见别名与原名不是占用同一块内存

	constexpr int varable = sum_test();  //  表示在编译的时候求值，可以提高性能
	cout << varable << endl;
	
}

int main() {

	/*
		头文件防卫示例
	*/
	cout << g_value1 << endl;
	cout << g_value2 << endl;
	
	/*
		调用引用示例
	*/
	test02();
	int a = 1, b = 2;
	cout << "交换前 " << "a = " << a << " b = " << b << endl;
	swap(a, b);
	cout << "交换后 " << "a = " << a << " b = " << b << endl;

	/*
		命名常量示例
	*/
	test03();

	system("pause");
	return 0;
}