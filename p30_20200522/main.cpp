#include<iostream>

using namespace std;

/*
	一、类模板特化
		特化与泛化相反，可以随便指定类型是泛化，对特殊的类型(类型模板参数)进行特殊的对待，给他写适合他的专用代码
		1、类模板的全特化
			1、常规全特化
				必须先由泛化版本才能存在特化版本，只要有特化，就一定有泛化
			2、特化成员函数而不是模板
		2、类模板的偏特化(局部特化)
			偏特化从两方面出发：
				1、从模板参数数量
					
				2、从模板参数范围上
		局部特化特化完成以后，本质上还是模板

	二、函数模板特化
		1、函数模板全特化

		2、函数模板偏特化

	三、模板特化版本 放置位置建议
		模板定义、实现都放在.h文件中
		模板的特化版本和模板的泛化版本都放在同一个.h文件中
		.h文件中前面放泛化版本，后面放特化版本

*/

/*
	常规全特化
*/
template<typename T, typename U>
struct TC  // 泛化的TC类模板
{
	void functest() {
		cout << "这是泛化版本" << endl;
	}
};
/*
	特化处理方式：当T、U类型模板参数都是int类型时，我们希望针对该情况做一个特化版本
	全特化指的就是：所有类型模板参数(这里指的是T、U)，都得用具体的类型代表
*/
template<> // 全特化指的是所有类型模板参数都用具体类型代表，所以template后的<>就是空
struct TC<int, int> {

	TC() {
		cout << "这是int int特化的构造函数" << endl;
	}

	// 这里可以对该特化版本做进一步的处理
	void functest() {
		cout << "这是两个类型都是int的特化版本" << endl;
	}
};

template<> // 全特化指的是所有类型模板参数都用具体类型代表，所以template后的<>就是空
struct TC<double, int> {
	// 这里可以对该特化版本做进一步的处理
	void functest() {
		cout << "这是一个是double,一个是int的特化版本" << endl;
	}
};

// 在调用的时候，优先考虑的是特化的类型
void test01() {
	TC<int, int> tc1;
	tc1.functest();  // 这是两个类型都是int的特化版本

	TC<double, int>tc2;  
	tc2.functest();  // 这是一个是double,一个是int的特化版本

	//TC<double, double>tc3;
	//tc3.functest();  // 这是泛化版本
}

/*
	特化成员函数而不是模板
*/
template<>
void TC<double, double>::functest() {
	cout << "这是两个类型都是double的functest特化版本" << endl;
}

void test02() {
	TC<double, double> tcobj;  // 虽然此处的tc是泛化版本的对象，但是我们特化了double double的functest函数，所以此处调用的就是特化的functest函数
	tcobj.functest();
}


/*
	类模板的偏特化(局部特化)
*/
template<typename T, typename U, typename Q>
struct TC1  // 泛化的TC类模板
{
	void functest() {
		cout << "这是泛化版本" << endl;
	}
};
/*
	从参数数量上,进行偏特化
	现在确定两个类型参数，留一个模板类型参数
*/
template<typename U> // 因为另外两个绑定到具体类型
struct TC1<int, U, double> {
	void functest() {
		cout << "这是数量偏特化版本" << endl;
	}
};

void test03() {
	TC1<int, double, double> tcTest1;
	tcTest1.functest();  // 这是数量偏特化版本

	TC1<double, int, double> tcTest2;
	tcTest2.functest();  // 这是泛化版本 
}

/*
	从模板参数范围上,进行偏特化 int 变为const int范围大，原来类型为T变为T*，也是范围上缩小
	局部特化特化完成以后，本质上还是模板
*/
template<typename T>
struct TC2  // 泛化的TC类模板
{
	void functest() {
		cout << "这是泛化版本" << endl;
	}
};

template<typename T>
struct TC2<const T> {  // const的特化版本
	void functest() {
		cout << "这是const T特化版本" << endl;
	}
};

template<typename T>
struct TC2<T*> {  // T*的特化版本，告诉编译器若是使用指针则调用
	void functest() {
		cout << "这是T*特化版本" << endl;
	}
};

template<typename T>
struct TC2<T&> {  // T&(左值引用)的特化版本，告诉编译器若是使用指针则调用
	void functest() {
		cout << "这是T&(左值引用)特化版本" << endl;
	}
};

void test04() {
	TC2<double> td;
	td.functest();  // 这是泛化版本

	TC2<double*> tdx;
	tdx.functest();  // 这是T*特化版本

	TC2<double&> tdy;
	tdy.functest();  // 这是T&(左值引用)特化版本
}

/*
	函数模板全特化
	全特化函数模板实际上等价于实例化一个函数模板，并不是等价于一个函数重载
	若既存在重载函数又存在全特化版本，系统会选择重载函数，编译器的选择原则是：有普通函数则优先，若没有，则使用特化版本，若没有特化版本，那么就选泛化版本
	void tfunc(int, double)(int&, double&);
	若传递字符串给特化版本，若有数组类型模板参数，指针类型模板参数，编译器会认为数组类型模板参数比指针类型模板参数更合适
	编译器会选择数组类型的模板参数的特化版本
*/
template<typename T, typename U>   // 泛化版本
void tfunc(T& tmp1, U& tmp2) {
	cout << "这是一个泛化函数模板" << endl;
	cout << "tmp1 = " << tmp1 << endl;
	cout << "tmp2 = " << tmp2 << endl;
}
 
// T = int, U = double
template<>
void tfunc(int& tmp1, double& tmp2) {
	cout << "这是一个全特化函数模板" << endl;
	cout << "tmp1 = " << tmp1 << endl;
	cout << "tmp2 = " << tmp2 << endl;
}

void test05() {
	const char* p = "Garrett";
	int i = 12;
	tfunc(p, i);

	/*
		此处调用的时候，不要输入常量表达式
	*/
	double ad = 1.2;
	tfunc(i, ad);	// 这是一个全特化函数模板
}

/*
	函数模板不能偏特化版本
*/
//template<typename T, typename U>   // 泛化版本
//void tfunc1(T& tmp1, U& tmp2) {
//	cout << "这是一个泛化函数模板" << endl;
//	cout << "tmp1 = " << tmp1 << endl;
//	cout << "tmp2 = " << tmp2 << endl;
//}
//
//template<typename U>
//void tfunc1<double, U>(double& tmp1, U& tmp2) {
//
//}

int main() {

	test05();
	return 0;
}