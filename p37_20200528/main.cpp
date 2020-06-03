#include<iostream>
#include<string>

using namespace std;

/*
	一、返回unique_ptr指针

	二、指定删除器
		1、指定删除器
			一般有缺省时，会指定默认删除器delete来释放对象
			格式：
				unique_ptr<指向的对象类型，删除器>智能指针变量名；
				先要在类型模板参数中传递进去类型名，然后在参数中再给具体的删除器函数名
		2、指定删除器额外说明
			就算两个智能指针(shared_ptr)指定的删除器不同，只要他们所指的对象相同，那么这两个智能指针也属于同一个类型
			但是unique_ptr不同，所以指定unique_ptr中的删除器一定会影响unique_ptr的类型，所以从灵活性来讲，shared_ptr更加灵活
			unique_ptr，若是删除器不同，那么就等于整个unique_ptr类型不同，这种类型不同的unique_ptr是没有办法放到同一个容器中的
	
	三、尺寸问题
		unique尺寸与裸指针一样，若我们自己添加删除器，则unique_ptr的尺寸可能增加也可能不增加
		1、若使用lambda表达式的删除器，那么unique_ptr的尺寸就没有变化
		2、若使用函数定义的删除器，那么尺寸就会增大，增加字节是对效率有影响的，所以自定义删除器要谨慎使用
		   shared_ptr，不管制定什么删除器，它的大小都不会变，都是普通指针的两倍

	四、智能指针总结
		1、智能指针的设计思想：
			主要目的是为了帮助我们释放内存，以防止忘记释放内存而导致的内存泄漏
			autoptr等价于unique_ptr指针
		2、auto_ptr为什么被废弃
			C++98的智能指针，它具有unique_ptr一部分的特性；auto_ptr不能再容器中保存，也不能从函数返回auto_ptr
			主要的原因是：设计的不好，容易被误用，引起程序崩溃
		3、智能指针的选择
			1、若程序要使用多个指向同一个对象的指针，那么就应该选择shared_ptr
			2、若程序不需要多个指向同一个对象的指针，那么就应该选择unique_ptr
			3、比较少的的情况会使用到shared_ptr所以unique_ptr是使用智能指针的首选
		
*/

/*
	返回unique_ptr指针,从函数返回一个局部的智能指针对象
	此时系统会给我们生成一个临时的unique_ptr对象，调用unique_ptr的移动构造函数
*/
unique_ptr<string> myfunc() {
	return make_unique<string>("I Love China");
}

void test01() {
	auto p1 = myfunc();  // 该处使用p1接收了临时对象，若是不接收，那么临时对象会在此处释放，同时会释放掉指向的对象
	cout << *p1 << endl;
}

/*
	指定删除器
*/
// 函数类型的删除器
void mydelete(string* pdel) {
	delete pdel;
	pdel = nullptr;
	// 这里可以打印下日志
}

void test02() {
	// 定义一个函数指针类型，类型为fp
	typedef void (*fp)(string*);
	
	// 使用using定义函数指针类型，类型名为fp2
	using fp2 = void(*)(string*); 
	
	// 使用函数类型的删除器
	unique_ptr<string, fp> ps1(new string("I Love China"), mydelete);

	typedef decltype(mydelete)* fp3;  // 这里定义了一个删除器函数类型fp3
	unique_ptr<string, fp3> ps2(new string("Garrett"), mydelete);
	cout << *ps2 << endl;  // Garrett

	unique_ptr<string, decltype(mydelete)*> fp4(new string("Walker"), mydelete);
	cout << *fp4 << endl;  // Walker

	// 使用lambda表达式写删除器，lambda表达式可以理解为带有operator类类型的对象，将lambda表达式理解为一个class
	auto mydela = [](string* pdel) {
		delete pdel;
		pdel = nullptr;
		// 可以打印日志
	};
	
	// 此时使用decltype推断出来就是一个类类型
	unique_ptr<string, decltype(mydela)> ps5(new string("Garrett_Walker"), mydela);
	cout << *ps5 << endl;  // Garrett_Walker



}

int main() {
	test02();
	return 0;
}