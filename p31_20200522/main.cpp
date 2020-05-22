#include<iostream>

using namespace std;

/*
	一、可变参数模板(Variadic Template):允许模板中含有0-任意个模板参数，在语法上与传统模板不同
		要注意的是：
			1、我们将args成为一包/一堆参数，而且类型是可以各不相同的，我们在理解T类型的时候，它并不是一个类型，要理解成0到多个不同的类型
			   对应的参数也是不同类型的参数
			2、一包参数中可以容纳0-多个模板参数，模板参数可以为任意类型
			3、将名字理顺，T后面加了...，所以我们称呼T为可变参类型，它看起来是一个类型，实际上是0-多个不同的类型，args为可变形参(一包形参)
			4、在具体的函数形参中，&位置出现在了类型名的后面
		参数包的展开：
			拿到参数包中的各个参数，展开套路比较固定，一般都是用递归的方式来展开函数包
			要求我们在代码编写中具有参数包展开函数，和一个同名的递归终止函数

	二、可变参类模板
		允许模板中定义0-任意个模板参数
		通过递归方式展开参数包
		
*/


/*
	可变参数模板范例
*/
template<typename...T>
void myfunct1(T...args) {
	cout << "模板参数数量为：" << sizeof...(args) << endl;
	cout << "类型：" << sizeof...(T) << endl;
}

template<typename T, typename...U>
void myfunct2(const T& firstarg, const U&...secondargs) {
	cout << "第一个参数大小" << sizeof(firstarg) << endl;
	cout << "第二个参数大小" << sizeof...(secondargs) << endl;  // sizeof...可变参的数量为2
}

void test01() {
	myfunct1();
	myfunct1(10, 20, "str", "ing");  // 4 4

	myfunct2(10);   // 4

	myfunct2(10, "abc", 12.7);  // 4  2
}

/*
	参数包的展开
	第一个参数是一个参数，但是第二个参数是函数包，这种写法最适合参数包的展开
	递归终止函数
*/
void myfunc3() {
	cout << "执行了展开终止函数" << endl;
}

template<typename T, typename...U>
void myfunc3(const T& firstarg, const U&...secondargs) {
	cout << "收到的参数值为：" << firstarg << endl;
	myfunc3(secondargs...);  // 使用递归展开函数包
}

void test02() {
	myfunc3(1, 2, 3, 4, 5, 6);
}

/*
	可变参类模板
*/
template<typename...Args> class MyClass {};  // 主模板

template<typename First, typename...Others>
class MyClass<First, Others...> :private MyClass<Others...> {  // 偏特化
public:
	MyClass() : m_i(0) {
		printf("MyClass::MyClass()执行了，this = %p\n", this);
	}

	MyClass(First parf, Others...paro) :m_i(parf), MyClass<Others...>(paro...) {
		printf("MyClass::MyClass()执行了，this = %p\n", this);
	}
public:
	First m_i;
};

/*
	零个模板参数特化版本
*/
template<>class MyClass<> {
public:
	MyClass() {
		cout << "执行了0个参数特化版本" << endl;
	}
};

void func() {
	// 使用上述继承方法，将参数包拆分为一个参数和另一个参数包，直至拆分完毕
	MyClass<int, float, double>myc1;
	cout << endl;
	MyClass<int, float, double>myc2(125, 12.5, 1.25);
	/*
		递归继承方式展开参数包
		
		执行了0个参数特化版本
		MyClass::MyClass()执行了，this = 012FFCE8
		MyClass::MyClass()执行了，this = 012FFCE8
		MyClass::MyClass()执行了，this = 012FFCE8
	*/
}

int main() {
	func();
	return 0;
}