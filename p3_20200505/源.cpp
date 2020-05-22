#include<iostream>

using namespace std;

/*
	一、范围for语句(用于遍历一个序列)
		即为增强for循环

	二、动态内存分配问题
		C中：供用户使用的存储空间，有程序区、静态存储区、动态 存储区
		C++中：将内存进一步分为五个区 
			1、栈：函数中的局部变量都会保存在这里，编译器自动分配
			2、堆区：malloc / new 分配，使用free / delete释放
			3、全局/静态存储区：放全局变量和静态变量static，程序结束时释放
			4、常量存储区，字符串常量等
			5、程序代码区

			堆和栈不同的用途及区别：
				1、栈的空间是有限的，系统规定，分配速度快，要防止栈溢出
				2、堆：只要不超出实际拥有的物理内存，也在操作系统允许能够分配的最大内存大小之内，分配速度较慢
			在C语言中：使用malloc和free分配和释放内存
			在C++中，使用new和delete
			new一般使用格式：
				1、指针变量名 = new 类标识名；
				2、指针类型名 = new 类型标识符(初始值)；
				3、指针类型名 = new 类型标识符[内存单元个数]; 分配一个数组
		配对使用问题:
			1、有malloc/new,就必须有free / delete释放，释放也不要重复释放
			2、new与malloc的区别是，new不但开辟内存，而且还进行初始化 delete不仅释放内存，而且还会做清理工作

	三、nullptr
		是C++11中引入的新关键字
		nullptr代表的也是空指针，但是可以避免空指针与整数0进行混淆
		NULL与nullptr类型不同
		对于指针的初始化，能用nullptr的就使用nullptr而不是使用NULL,只有nullptr才被认为是真正的指针类型
*/

/*
	范围for语句示例
*/
void test01() {
	int arr[] = { 1, 2, 3, 4, 5 };
	for (auto x : arr) {  // 数组arr中每一个元素依次拷贝到x中并打印x的值
		cout << x << endl;
	}

	for (auto x : { 6, 7, 8,9,10 }) {
		cout << x << endl;
	}

	/*
		改进效率,省去了拷贝动作，提高了系统效率
	*/
	for (auto& x : arr) {
		cout << x << endl;
	}
}

/*
	动态内存分配及释放
*/
void test02() {
	int* myint = new int; // 开辟一个存储整数的存储空间，返回指向该内存的指针
	if (myint == nullptr) {
		cout << "内存分配失败" << endl;
		return;
	}
	*myint = 8;
	cout << *myint << endl;
	delete myint;  // 一定要记得释放空间


	int* myint1 = new int(18);
	if (myint1 == nullptr) {
		cout << "内存分配失败" << endl;
		return;
	}
	cout << *myint1 << endl;
	delete myint1;

	int* arr = new int[100];  // 开辟一个大小为100的整形数组
	if (arr == nullptr) {
		cout << "内存分配失败" << endl;
		return;
	}
	int* pointer = arr;
	*pointer++ = 12;   // [0] = 12
 	*pointer++ = 18;  // [1] = 18, 执行完这行，这个pointer其实已经指向了[2]
	cout << *arr << endl;
	cout << *(arr + 1) << endl;

	delete[] arr; // 释放数组空间，[]中不写数组大小

}

/*
	nullptr的使用,nullptr就是空指针
*/
void test03() {
	char* p1 = NULL;  // NULL实际上就是0
	char* p2 = nullptr;

	cout << typeid(NULL).name() << endl;  // int
	cout << typeid(nullptr).name() << endl;  // std::nullptr_t
}

int main() {
	/*
		增强for循环调用
	*/
	//test01();

	/*
		动态内存分配及释放
	*/
	//test02();

	test03();
	system("pause");
	return 0;
}