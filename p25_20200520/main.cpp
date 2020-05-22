#include<iostream>

using namespace std;

/*
	一、类型转换构造函数
		需要通过转换构造函数和类型转换运算符来实现类型转换
		比如：将一个数字转换为类对象
		构造函数种类：
			1、以类名作为函数名
			2、构造函数没有返回值
		在带一个或者多个参数的构造函数(类型转换构造函数)，主要的能力就是可以将某个其他的数据类型转换为该类类型的对象
		特点：
			1、只有一个参数，一般不是本类的const引用，该参数就是待转换的数据类型。所以待转换的数据类型都不应该是本类类型
			2、在类型转换构造函数中，我们需要指定转换的方法(在该函数中，要做什么)

	二、类型转换运算符(类型转换函数)
		作用：与类型转换构造函数恰好相反，是一种特殊的成员函数，可以将一个类类型对象转换为某个其他数据类型
		格式：operator type()const;
			1、const是可选项，表示一般不应该改变转换对象的内容，但不是必须的
			2、type表示要转换成的某种类型。只要能够作为函数返回的类型即可
			3、类型转换运算符没有形参，因为类型转换运算符一般都是隐式执行的，根本也就没有办法传递参数，同时也不能指定返回类型，
			   但是可以返回一个type指定的类型的值的
			4、必须定义为类的成员函数
		注意：在使用时，两个操作对象要有所关系
		1、显式的类型转换运算符
			要是不需要做隐式类型转换，但是会自动使用的话，就要在类型转换运算符时添加explict
		2、范例
			类对象转换为函数指针

	三、类型转换的二义性问题
		不明确的指令导致编译器报错,所以在一个类中最好只定义一个类型转换运算符

	四、类成员函数指针
		一个指针，指向类成员函数
		1、对于普通成员函数
			格式：类名::*函数指针变量名  来声明普通成员函数指针，使用&类名::成员函数名来获取类成员函数地址(这是真正的内存地址)
		2、对于虚函数

		3、对于静态成员函数

	五、类成员对象指针
		1、对于普通成员变量

		2、对于静态成员变量
*/

/*
	该类主要目的是为了保存0-100之间的数字
*/
class testInt {
public:
	/*
		定义一个函数指针类型，代表的函数带一个int形参，没有返回类型的
	*/
	typedef void(*typoint)(int);
	// 或者是
	using typoint1 = void(*)(int);

public:
	/*
		类型转换构造函数(也是一个只带一个参数的普通构造函数)，该函数的作用就是将一个整型数字转换为testInt类型
		explicit:该关键字的作用就是禁止做隐式类型转换
	*/
	//explicit testInt(int x = 0) :m_i(x) {
	testInt(int x = 0) :m_i(x) {
		if (m_i < 0) m_i = 0;
		if (m_i > 100) m_i = 100;
	};  

	/*
		类型转换运算符，可以将本类的类型对象转化为其他类型
	*/
	explicit operator int()const {
		return m_i;
	}
	/*
		将本类类型对象转换为函数指针类型
	*/
	operator typoint() {
		// 必须要返回一个函数指针
		return mysfunc;  // 函数地址(函数名)作为指针类型返回即可
	}

	/*
		定义一个静态成员函数
	*/
	static void mysfunc(int v1) {
		int test = 1;
	}

public:
	int m_i;
};

/*
	适用类型转换构造函数
*/
void test01() {
	//testInt ti1 = 12;  // 这里就存在隐式类型转换，这里将数字12转换为了testInt对象(调用了类型转换构造函数)
						// 编译器用12这个胡子通过调用testInt类的类型转换构造函数创建一个临时的testInt对象，并将对象构造到了ti1的预留空间中
	
	//testInt ti1 = testInt(12);  /// 该种方式会避免使用隐式类型转换，也调用类型转换构造函数
	
	//testInt ti2(22);   // 该种方式调用了类型转换构造函数，但是并没有隐式类型转换

	testInt ti1 = 12;
	testInt ti2;
	ti2 = 6;  // 编译器使用6生成临时的testInt对象(调用testInt类型转换构造函数)，调用赋值运算符，将临时对象的内容给了ti2

	//int res = ti2 + 5;  // 11  在这里隐式调用operator int() const 将ti2转化为int，再和5做加法运算，结果再返回给res

	int res = static_cast<int>(ti2) + 5;  // 需要经过强制的显式类型转换运算符来完成转换

	int res2 = ti2.operator int() + 5;  // 显式调用类型转换运算符
}

/*
	类对象转换为函数指针
*/
void test02() {
	testInt myi(12);
	myi(123);  // 看起来像一个可调用对象，调用转换为函数指针的类型转换运算符
				// 这里相当于调用了两个函数 
				// 1、类型转换运算符(转换为函数指针类型)	2、通过函数指针调用具体的函数

	/*
		另一种调用方式
		123表示函数
		第一个括号对应的是operator typoint()函数，(123)调用的是static void mysfunc(int v1)，这里v1就是123
	*/
	(myi.operator testInt::typoint())(123);
}

class CT1 {
public:
	CT1(int ct) {};  // 类型转换构造函数
};

class CT2 {
public:
	CT2(int ct) {};  // 类型转换构造函数
};
/*
	重载函数
*/
void testfunc(const CT1& C) {};
void testfunc(const CT2& C) {};

/*
	类型转换的二义性
*/
void test03() {
	testInt aa;
	// int abc = aa + 12;  // 该处出现的就是二义性问题，该处可以转换为整型或者是函数指针都可以，所以产生二义性
	//testfunc(101);  // 根据重载函数来讲，101既可以转换为CT1也可以转换为CT2并不具有辨识度，所以导致二义性问题
	testfunc(CT1(101));  // 必须将101转换为一定的明确类型才不会引起二义性问题，这种手段表明代码设计不好
}

class CT3 {
public:
	void ptfunc(int tmpvalue) {
		cout << "普通成员函数被调用, value = " << tmpvalue << endl;
	}

	virtual void virtualfunc(int tmpvalue) {
		cout << "虚成员函数被调用, value = " << tmpvalue << endl;
	}

	static void jtfunc(int tmpvalue) {
		cout << "静态成员函数被调用, value = " << tmpvalue << endl;
	}
public:
	/*
		普通成员变量
	*/
	int m_i;
	/*
		声明静态成员变量
	*/
	static int m_static;
};
/*
	静态成员变量定义
*/
int CT3::m_static = 1;



/*
	类成员函数指针
*/
void test04() {
	/*
		对普通成员函数
	*/
	// 定义一个普通的类成员指针
	// 这就是一个类成员函数指针变量的定义，变量名为myfpointpt
	void (CT3:: *myfpointpt)(int);
	/*
		类的成员函数地址和类对象无关，成员函数地址指归属于类，而不是归属于某一个对象
		但若是要使用该成员函数指针，那么就必须将它绑定到一个类对象上
	*/
	myfpointpt = &CT3::ptfunc;  // 类成员函数指针被赋值， myfpointpt指针指向成员函数
	/*
		使用函数指针的格式：类对象名.*函数指针变量名 
							指针名->*函数指针变量名
	*/
	CT3 ct, *pct;
	pct = &ct;
	(ct.*myfpointpt)(100);  // 对象ct，调用指针变量mypointpt所指向的成员函数：ptfunc
	(pct->*myfpointpt)(200); // 对象指针调用

	/*
		对虚函数
		在使用时，也必须得绑定到类对象上才能使用
		在类中声明虚函数时，编译器会生成虚函数表，当生成一个类对象时，若该类中含有虚函数表，则对象中就会有一个指向该虚函数表的指针
		该指针占有四个字节
	*/
	void (CT3:: * myfpointvirtual)(int) = &CT3::virtualfunc;  // 虚函数地址是个真正的内存地址
	(ct.*myfpointvirtual)(300);
	(pct->*myfpointvirtual)(400);
	/*
		对于静态成员函数
		声明静态成员函数指针的方法：
			格式：*函数变量名
		使用&类名::成员函数名 来获取类成员函数地址 (这个也是真正的地址)
	*/
	// 定义一个静态成员函数并赋值
	void(*myfpointjt)(int) = &CT3::jtfunc;
	/*
		使用静态成员函数指针
	*/
	myfpointjt(500);
	/*
		类成员变量指针
	*/
	// 1、对于普通成员变量，定义指向普通成员变量的指针，成员变量不是一个真正意义上的指针(不是指向某一块内存)，而是该成员变量与该类对象之间的偏移量
	int CT3::*mp = &CT3::m_i;  // 定义一个类成员指针
	// 通过对类成员指针赋值来修改对象中的成员
	CT3 ctest;
	ctest.*mp = 189;  // 该处的作用就是等价于ct.m_i = 189

	// 2、静态成员变量：指向静态成员变量的指针是有真正意义上的地址
	int* stcp = &CT3::m_static;  // 定义一个静态成员变量指针
	*stcp = 796;  // 等价于CT3::m_static = 796;
	cout << *stcp << endl;
}

int main() {
	test04();
	return 0;
}