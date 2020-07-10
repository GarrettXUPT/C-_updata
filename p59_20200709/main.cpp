#include<iostream>
#include<map>
#include<functional>

using namespace std;

/*
	一、C++小知识
		1、funct()，元加括号就是函数调用的标记，也就是函数调用运算符；若在类中重载了函数调用运算符，那么就可以像使用函数一样使用该对象
		   调用方式就是：对象();定义了函数对象以后，就可以像调用函数一样调用该对象
		   只要该对象的类重载了函数调用运算符()，那么该对象就变成了可以调用的多个版本的()，只要是类型和数量上有差别
		   该类重载()以后，该类对象就可以作为函数对象

		2、不同调用对象的相同调用格式
			函数echovalue和类biggerthanTwo重载的()，调用参数和返回值相同，就叫做调用形式相同
			一种调用形式，对应一个函数类型,他们的函数类型都是int(int)
			函数echovalue和重载的()都属于可调用对象
			讲这些可调用对象的指针保存起来，目的是我们可以随时调用这些可调用对象

	二、万能引用
		1、类型区别基本概念

		2、universal_reference	 
			&&表示右值引用 主要是绑定在右值上

		3、万能引用
			1、剥夺：const修饰词会剥夺一个引用成为万能引用的资格，会将其变为右值引用
			2、辨认：
			
*/

/*
	函数对象的定义
*/
class biggerThanTwo {
public:

	biggerThanTwo(int i) {
		//cout << "构造函数被执行" << endl;
	}

	biggerThanTwo() {};

	int operator()(int value) const {
		return value; 
	}
};
/*
	调用函数对象
*/
void test01() {
	biggerThanTwo bgt;
	cout << bgt(3) << endl; // 1  等价于调用bgt.operator()(i)
	cout << bgt(1) << endl;  // 0

	/*
		这里代表的是对象定义并且初始化,调用的构造函数而不是调用operator()(i)
	*/
	biggerThanTwo bt(1);
}

/*
	普通函数,打印value值并将其原样返回
*/
int echovalue(int value) {  // 调用参数和返回值相同
	cout << value << endl;
	return value;
}

/*
	函数echovalue和类biggerthanTwo重载的()，调用参数和返回值相同，就叫做调用形式相同
	一种调用形式，对应一个函数类型,他们的函数类型都是int(int)
*/
void test02() {
	/*
		定义一个可调用对象的指针
	*/
	map<string, int(*)(int)> myoper;
	myoper.insert({ "echovalue", echovalue });  // 将函数指针键值对放入map容器中

	/*
		含有函数调用运算符的对象
	*/
	biggerThanTwo obj;

	/*
		functional类模板，要提供模板参数来表示function类型能够表示的对象调用形式
		定义一个function用来表示一个可调用对象,若普通函数echovalue进行了重载，那么就不可以放到该function<>类型的对象中，这个问题可以通过函数指针来解决

	*/
	function<int(int)> f1 = echovalue;
	function<int(int)> f2 = obj;  // 可以放类对象，因为类中存在函数调用运算符的重载
	function<int(int)> f3 = biggerThanTwo();  // 也可以使用类名生成临时对象
	
	cout << f3(2) << endl;  // 2
	map<string, function<int(int)>> myoper1 = { {"ev", echovalue}, {"bt", obj} ,{"bt2", biggerThanTwo()} };

	/*
		map中可调用对象的使用
	*/
	cout << myoper1["bt2"](12) << endl;  // 12

	/*
		定义函数指针不会产生二义性,因为函数指针中有对象的参数类型和返回值类型，可以和原来的echovalue进行比对
	*/
	int(*fp)(int) = echovalue;
	function<int(int)> f4 = fp; // 直接塞进去函数指针而不是函数名  
}

/*
	
*/
void func(const int& abc){}  // abc的类型就是：const int&  

/*
	这里T的类型和abc的类型往往不同
*/
template <typename T>
void func1(const T& abc){}

void test03() {
	// T的类型时int型,abc的类型就是const int&
	// 1、调用函数模板时的参数10会对T的类型产生影响
	// 2、abc的类型会对T的类型产生影响 
	func1(10);
}

void myfunc2(int&& tmprv) {
	cout << tmprv << endl;
	return;
}

/*
	将其函数改造为函数模板
*/
template<typename T>
void myfunc2(T&& tmprv) {  // 这里的&&是属于形参类型的一部分，与T类型是无关的
	cout << tmprv << endl;
	return;
}


void test04() {
	/*
		这样调用是可以的
	*/
	myfunc2(10);
	/*
		右值引用不能绑左值
	*/
	int i = 100;
	//myfunc2(i);  这就是对右值引用绑定左值

	/* 
		若定义了函数模板类型，那么传入左值是可以的
		1、tmprv既能接受左值，又能接受右值
		2、T&&都是tmprv的类型
		万能引用需要的语境：1、必须是函数模板 2、必须发生了模板类型推断 必须得长这样T&&
		满足上述语境才可发生，auto也存在万能引用这个概念，万能引用的形式就是T&&
		万能引用和右值引用的区别：
			1、右值 引用得传递右值，否则编译器报错
			2、万能引用做函数形参的时候，我们可以传递给他左值，也可以传递给他右值，视传入参数而定
		tmprv或者是T&&才是万能引用，而单独的T不是万能引用，若传递进来的是一个整型的右值，tmprv就应该被推断成int&&类型

		1、void func(int&& param)  // 右值引用，因为不是模板所以不是万能引用
		2、template<typename T> void func(T&& tmpvalue);  // 万能引用
		3、template<typename T> void func(vector<T>&& param) 这只有右值引用 不是万能引用

	*/
	myfunc2(i);
}

int main() {
	test02();
	return 0;
}