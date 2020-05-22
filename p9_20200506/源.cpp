#include<iostream>

using namespace std;

/*
	一、隐式类型转换
		系统自动进行，不需要开发人员介入

	二、强制类型转换
		(int)3.2 表示C语言风格的强制类型转换，int(3.2)函数类型的强制类型转换
		C++强制类型转换分为4种(命名的强制类型转换)，每种强制类型转换都用于不同的目的，更好地类型检查，方便代码的书写和维护：
			1.static_cast静态转换
				编译时进行类型转换的检查，代码中要保证转换的安全性和正确性，含义与C中的强制类型转换差不多
				用途：
					1.相关类型转换(比如整型和实型之间的转换)
					2.在类中子类转换为父类的时候，也使用static_cast转换
					3.void*与其他类型指针之间的转换
						void* 无类型指针，可以指向任何指针类型
				不可用：
					一般不能用于指针类型之间的转换，比如int*转化为double*,float*转换为double*					
			2.dynamic_cast
				主要用于运行时类型的识别和检查，主要用来父类型和子类型之间的转换(父类型指针指向子类型对象)
			3.const_cast
				去除指针或者是去除const类型，可以去除const性质，编译时类型转换
			4.reinterpret_cast
				编译时类型转换，重新解释，将操作数内容另外解释为不同的类型
				无关类型转换，两个转换类型之间没有什么关系

		总结：
			1.强制类型转换，不建议使用，强制类型转换可以抑制编译器报错
			2.学习目的是为了认识这些类型转换符，方便阅读代码
			3.reinterpret_cast很危险，使用const_cast意味着设计缺陷
			4.不要再使用C风格的类型转换

		通用形式：强制类型转换名<type>(express)，强制类型转换名就是上述四个名字之一，type转换的目标类型
*/

/*
	static_cast
*/
void test01() {
	float f1 = 3.14f;
	int i = static_cast<int>(f1);
	cout << "转换后的类型" << typeid(i).name() << endl;   // 转换后的类型int

	int a = 10;
	int* p = &a;
	// 将int*指针转换为空指针
	void* q = static_cast<void*>(p);
	// 再将void*指针转化为int*
	int* p2 = static_cast<int*>(q);
}

/*
	const_cast
*/
void test02() {
	const int i = 90;
	const int* pointer_tmp = &i;
	int* pinter = const_cast<int*>(pointer_tmp);
	
}
int main() {

	test02();

	system("pause");
	return 0;
}