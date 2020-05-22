#include<iostream>

using namespace std;

/*
	一、继承的构造函数
		一个类，只继承其直接基类构造函数，默认、拷贝、移动构造函数是不能被继承的
		若基类中具有多个构造函数，则多数情况下，派生类会继承所有的构造函数，但是有如下例外情况：
			1、若在派生类中定义的构造函数与基类构造函数具有相同的参数列表,那么从基类中继承来的构造函数在派生类中被覆盖掉
			(相当于只继承了一部分构造函数)
			2、默认、拷贝、移动构造函数是不会被继承的 若类B只含有从A类中继承来的构造函数的话，编译器会给他合成默认的构造函数

	二、多重继承
		1、多重继承概述：若从多个父类产生出子类，就叫做多重继承
						 派生类对象会包含每个基类的子对象
		2、静态成员变量(静态成员属于类，不属于对象)

		3、派生类构造函数与析构函数
			1、构造一个派生类对象将同时构造并初始化所有的基类子对象
			2、派生类的构造函数初始化列表只初始化它的直接基类，每个类的构造函数都负责初始化它的直接基类
			   这样就可以保证所有的类都进行了初始化
			3、派生类构造函数的初始化列表，将实参分别传递给每个直接基类，基类的构造顺序和派生列表的基类的出现顺序保持一致(此时就是A、B)
			4、若基类中存在默认构造函数的话，在派生类继承他的时候，可以先不初始化该对象，事实上这里基类是使用了隐式的默认构造函数
			
		4、从多个基类继承构造函数

	三、类型转换
		基类指针可以指向一个派生类对象，编译器帮助我们隐式的执行了派生类到基类的转换，因为每一个派生类都包含一个基类部分
		所以基类的引用或者是指针是可以绑定到基类这部分对象上来的

	四、 虚基类、虚继承(虚派生)
		派生列表中，同一个基类只能出现一次，但是如下两种情况例外：
			1、派生类可以通过它的两个直接基类分别继承同一个间接基类
			2、直接继承某个基类，然后通过另一个基类间接继承该类
			但是继承两次基类是多余的，占用空间，而且还容易引起名字冲突，为了避免被重复继承，那么就引人了虚继承

		虚基类：无论这个类在继承体系中出现了多少次，派生类中，都只会包含唯一一个共享的虚基类子内容
				若继承基类时都采用的是虚继承，那么该基类就是一个虚基类
				其实虚继承只对最终间接继承两次的类有意义，对于上面直接继承的类是没有意义的
		虚继承格式：
			virtual是一种意愿：表示后续(A,A2)派生的类中应该共享虚基类的同一份实例
			class Grand{};
			class A : virtual public Grand{};  virtual与public的位置可以互换
			class A2 : virtual public Grand{};
			因为虚基类只有一份子内容，派生类的构造函数也要进行改动：
			class C public A, public A2 {C(int i, int j, int k) : A(i), A2(j), Grand(i), m_value(k){}};
			虚基类时，由孙子类初始化Grand，会使父类中对爷爷类的初始化就没有了意义(就不发挥作用了)

		说明：
			1、现在是C类初始化Grand，若是C类有孩子，那么Grand的初始化由C类的孩子来做；虚基类Grand是由最低层的派生类来进行初始化
			2、在初始化列表中的初始化顺序问题：先初始化虚基类部分，然后再按照派生列表中出现的顺序来初始化其他类
			   多个虚基类时，初始化顺序：系统会按照派生列表中的直接基类来往回追溯，看这些直接基类含有虚基类，反正是追溯到哪个虚基类就是
			   先初始化哪个。销毁顺序与构造顺序是相反的
		
		多重继承不太建议使用：
			只有在简单，不容易出现二义性，实在必要时才会使用多重继承，能用单一继承解决的问题，就不要用多重继承
*/

class A1 {
public:
	A1(){}
	A1(int i, int j, int k = 5) {

	}
};

class B1 : public A1 {
public:
	using A1::A1; // 继承A的构造函数  using 就是让某个名字在当前作用域内可见
				// 编译器会将基类的每一个构造函数，都生成一个与之对应的派生类的构造函数
				// 形式为：B(构造函数形参列表) ：A(照抄的构造函数形参列表){} 函数体为空
				// B(int i, int j, int k) : A(i, j, k) {}
				// 若类A具有默认参数的话，编译器就会在派生类B中，构造出多个派生函数来
				// 1、全参构造函数 2、其余的构造函数，每个省略一个参数，知道没有参数
};

void test01() {
	//B ad1(3, 4, 5);
	B1 ad2(6, 7);
	B1 ad3();
}

/*
	多继承举例
*/
class grad {
public:
	grad(int i) : m_valueGrad(i) {
		cout << "grad构造函数执行" << endl;
	}

	virtual ~grad() {
		cout << "grad析构函数执行" << endl;
	};

	void myinfo() {
		cout << m_valueGrad << endl;
	}

public:
	int m_valueGrad;
};

// 定义父类A
class A : public grad {
public:
	/*
		每个子类的构造函数，都得解决父类的初始化问题
	*/
	A(int i) :grad(i), m_valueA(i) {
		cout << "A的构造函数执行" << endl;
	}

	virtual~A() {
		cout << "A的析构函数执行" << endl;
	}

	void myinfo() {
		cout << m_valueA << endl;
	}

public:
	int m_valueA;
public:
	/*
		为了能够使用静态成员变量(分配内存)
	*/
	static int m_static;
};
/*
	定义静态成员变量，若不使用静态成员的话，就可以不进行定义，若是在代码中使用的话，还是要定义
*/
int A::m_static = 10;

// 定义父类B，不继承自grad
class B {
public:
	B(int i) : m_valueB(i) {
		cout << "B的构造函数执行" << endl;
	}
	virtual ~B() {
		cout << "B的析构函数执行" << endl;
	}
	void myinfo() {
		cout << m_valueB << endl;
	}

public:
	int m_valueB;
};

// 定义类C同时继承父类A和父类B
class C : public A, public B {  // 若在这里不写权限标识符，那么就要看该类C是class还是struct，若是class则默认为private继承，若是struct默认为public继承
	
public:
	C(int i, int j, int k) :A(i), B(j), m_valueC(k) {
		cout << "C的构造函数执行" << endl;
	}

	virtual ~C() {
		cout << "C的析构函数执行" << endl;
	}

	void myinfo() {
		/*
			调用父类中myinfo函数的方式
		*/
		A::myinfo();
		B::myinfo();
		cout << m_valueC << endl;
	}

public:
	int m_valueC;
};

void test02() {
	/*
		分别调用了类A、类B的构造函数(在调用类A的构造函数时，还要先调动grad的构造函数)，最后才调用自己的类C的构造函数
	*/
	C ctest(10, 20, 50);
	ctest.myinfo(); // 50
	/*
		该种使用作用域的调用方式是为了避免调用函数的二义性
		若在自己的类中定义了myinfo就会覆盖掉父类中的同名函数
	*/
	ctest.A::myinfo();  // 10
	ctest.B::myinfo();  // 20 
	cout << "静态变量：" << A::m_static << endl;  // 10
	/*
		可以使用对象名来使用静态成员变量的
	*/
	cout << "静态变量：" << ctest.m_static << endl;  // 10
}

/*
	派生类构造函数与析构函数
*/
void test03() {
	C ctest(10, 20, 30);
}

/*
	从多个基类继承构造函数
	若一个类从他的基类中继承了相同的构造函数，那么该类必须为该同参数的构造函数定义它自己的版本
*/
class A2 {
public:
	A2(int tv) {};
};

class B2 {
public:
	B2(int tv) {};
};

class C2 : public A2, public B2 {
	using A2::A2;  // 继承A的构造函数  C2(int tv):A(tv){}
	using B2::B2;  // 继承B的构造函数  C2(int tv):B(tv){}  该种形式不可使用，因为不能同时出现相同的构造函数版本,需定义自己的版本解决
	/*
		定义自己版本的构造函数，使上述操作合法
	*/
	C2(int tv) :A2(tv), B2(tv) {};
};

/*
	类型转换
*/
void test04() {
	grad* pg = new C(1, 2, 3);
	/*
		只能使用基类的成员
	*/
	pg->myinfo();
	A* pa = new C(4, 5, 6);
	pa->myinfo();
	
	C myc(5, 7, 8);
	// 使用派生类成员
	grad mygrad(myc);
	// 使用基类成员
	mygrad.myinfo();
}

int main() {
	test04();
	return 0;
}