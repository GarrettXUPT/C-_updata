#include<iostream>
#include<string>
#include"Myarray.h"

using namespace std;

/*
	一、typename的适用场合
		1、模板定义里，表明其后的模板参数是类型参数
			函数模板
			template<typename T>  //typename后面跟的是一个类型
			T funAdd(){...}
			类模板
			template<typename T>  名字为T的模板参数
			class MyClass{...};
			typename可以替换为class，这里虽然可以使用class，但是这里的class并不是类定义的意思
		2、使用类的类型成员，使用typename标识这是一个类型
			::表示作用域运算符，也可以访问类型成员
			typename通知编译器，一个名字代表的是一个类型
			size_type 类似于unsigned int 考虑到机器的差异

	二、函数指针做其他函数参数

	三、函数模板的使用举例
		可调用对象

	四、默认模板参数
		1、类模板，类模板名后边必须使用<>提供模板信息，<>表示这是一个模板
		2、C++11可以函数模板的默认模板参数
			注意：1、同时给模板和函数参数提供缺省值
				  2、注意写法 T2 funcpoint = T2()
				  3、tc重载()
		
		
*/
/*
	求字符串长度
*/
template<typename T>
typename T::size_type getlength(const T& str) {
	if (str.empty()) {
		return 0;
	}
	return str.size();
}

void test01() {
	string str = "Garrett";
	string::size_type length = getlength(str);
	cout << "length = " << length << endl;  // 7
}

/*
	函数指针做其他函数参数
	函数指针作为某个函数参数进行传递
	函数指针想作为函数的参数，就要如下方式定义
*/
// 定义了一个函数指针类型
typedef int(*FunType)(int, int);

int myAdd(int tmp1, int tmp2) {

	return tmp1 + tmp2;
}

int testfunc(int i, int j, FunType funpoint) {
	return funpoint(i, j);
}

void test02() {
	int res = testfunc(3, 4, myAdd);
	cout << "res = " << res << endl;  // 7
}

class tc;
/*
	函数模板的使用举例
	此处加入tc是为了演示函数模板的默认模板参数
*/
template<typename T1, typename T2 = tc>
	void testfun(const T1& i, const T1& j, T2 funcpoint = T2()) {
	cout << funcpoint(i, j) << endl;
}

void test03() {
	testfun(2, 3, myAdd);
}

/*
	可调用对象所代表的类
*/
class tc {
public:
	tc() { cout << "构造函数执行" << endl; }
	tc(const tc& t) { cout << "拷贝构造函数执行" << endl; }
	// 重载括号运算符
	int operator()(int v1, int v2) const {
		return v1 + v2;
	}
};

void test04() {
	tc tcobj;
	testfun(3, 4, tcobj);   // 7

	testfun(5, 6, tc());  //  11 使用临时对象，这样使用可以减少一次拷贝构造函数的使用
}

/*
	完全使用模板缺省值
*/
void test05() {
	MyArray<> abc;

	/*
		提供第一个非缺省值，使用第二个参数的缺省值
	*/
	MyArray<int> def;
}

/*
	函数模板的默认模板参数
*/
void test06() {
	testfun(2, 5);  // 7
}

int main() {
	test06();
	return 0;
}