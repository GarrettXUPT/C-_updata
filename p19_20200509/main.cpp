#include<iostream>
#include"Human.h"
#include"Man.h"
#include"wowan.h"

using namespace std;

/*
	一、RTTI(run time type identifiaction)：运行时类型识别
		通过RTTI程序可以使用基类的指针或者引用来检查这些指针或者引用所指对象的实际派生类型
		RTTI将这个称呼看做为一种系统提供给我们的一种能力，或者是一种功能，这种功能或者能力是通过两个运算符来体现的
		1.dynamic_cast运算符，能够将基类的指针或者引用安全的转化为派生类的指针或者引用
		  再使用转化过的子类，正常的调用子类的成员
		2.typeid运算符：返回指针或者引用所指对象的实际类型
		注意：
			上述两个运算符想要能够正常工作，那么在基类中必须至少存在一个虚函数，否则，上述运算符就不能正常工作
			因为只有虚函数的存在，这两个运算符才会使用指针或者引用所绑定的对象的动态类型(new的类型)
			只有存在虚函数才能在系统中产生虚函数表，然后使用你指向对象的指定功能
		
		为了解决调用子类成员必须要求成员是继承父类的虚函数，所以引入了该方法  
	
	二、dynamic_cast
		如果该运算符能够转换成功，那么说明该指针实际上指向的就是那个要转换到的那个类型，可以做安全检查
		对于引用，若使用dynamic转化失败，系统会跑出一个std::bad_cast异常。一般使用try...catch()....

	三、typeid运算符
		typeid(类型)，这里的类型可以是指针，也可以是引用；也可以是typeid(表达式)
		拿到对象类型信息，typeid就会返回一个常量对象的引用，常量对象是一个标准库类型type_info
		
		typeid主要是为了比较两个指针是否指向同一种类型对象：
		两个指针定义的类型相同，使他们都指向Human

	四、type_info类/类类型
		1. .name获取所指向的对象名，返回一个C风格的字符串
		2. ==，!= ，该种比较方法也要求基类中有虚函数
	
	五、RTTI与虚函数表
		在C++中，若一个类含有虚函数，编译器就会对该类产生一个虚函数表(针对类而言的)
		虚函数表中含有很多项，每一项都是一个指针，每个指针指向的是这个类里的各个虚函数的入口地址
		虚函数表项里，第一个表项是很特殊的，它指向的不是虚函数的入口地址，它指向的是这个类所关联的type_info对象
*/


void test01() {
	/*
		父类指针指向子类对象
	*/
	Human* phuman = new Man;
	Human& q = *phuman;  // q是该对象的别名，*phuman表示指针phuman所指向的对象
	/*
		使用继承虚函数来使用子类成员方法
	*/
	phuman->eat();  // 男人喜欢吃面食 
	
	
	/*
		使用dynamic运算符，使父类指针直接访问子类的普通成员
	*/
	Human* phuman1 = new Man;
	
	// 使用C语言风格的强制类型转换,可能会有安全问题
	Man* pman1 = (Man*)phuman1;
	pman1->test01(); 
	
	Man* pman2 = dynamic_cast<Man*>(phuman1);
	if (pman2 != NULL) {  // 转换为Man成功
		pman2->test01();
		// 这里就可以操作Man中所有的成员，且安全
	}
	else  // 转换不成功，意味着phuman1不是指向Man类型
	{
		cout << "转换不成功" << endl;
	}

	Human* phuman2 = new Man;
	Human& q2 = *phuman2;  // 这就是引用
	try
	{
		// 可能会出现异常的代码
		// 转换不成功，则catch会捕获异常，如果不成功，则流程会继续向下
		Man& manbm = dynamic_cast<Man&>(q2);
		cout << "类型转换成功" << endl;
		manbm.test01();
	}
	catch (const std::bad_cast&)  // 转换失败的话 系统就会抛出异常
	{
		cout << "phuman实际不是一个man类型" << endl;
	}
	
	cout << typeid(*phuman2).name() << endl;  // class man
	cout << typeid(q2).name() << endl;	// class man

	/*
		比较两个指针是为同一个类型
	*/
	Human* phuman3 = new Man;
	Human* phuman4 = new Woman;
	if (typeid(phuman3) == typeid(phuman4)) {  // 现在他们都是指针类型都是Human，所以无论new的是啥，他们的typeid都相等
		cout << "两个指针是同一个类型的" << endl;
	}
	else
	{
		cout << "两个指针没是同一个类型的" << endl;
	}

	/*
		比较对象时，比较指针指向对象的类型，和定义该指针时，定义的类型没啥关系
	*/
	Human* phuman5 = new Man;
	Human* phuman6 = new Woman;
	Human* phuman7 = new Man;
	if (typeid(*phuman5) == typeid(*phuman6)) {
		cout << "两个指针指向的对象类型相同" << endl;
	}
	else
	{
		cout << "两个指针指向的对象类型不同" << endl;  // 两个指针指向的对象类型不同
	}

	if (typeid(*phuman5) == typeid(*phuman7)) {
		cout << "两个指针指向的对象类型相同" << endl;	 // 两个指针指向的对象类型相同
	}
	else
	{
		cout << "两个指针指向的对象类型不同" << endl; 
	}

	/*
		指针指向类型与类型相比，基类必须要有虚函数，这样才能知道指针实际指向的是Man
		若没有虚函数typeid返回的是表达式的静态类型(定义时的类型)
	*/
	Human* phuman8 = new Man;
	if (typeid(*phuman8) == typeid(Man)) {
		cout << "phuman8指向man对象" << endl;  // phuman8指向man对象
	}
	else{
		cout << "phuman8不指向man对象" << endl;
	}

	/*
		==，!= ，该种比较方法也要求基类中有虚函数
	*/
	Human* phuman9 = new Man;
	const type_info& tp2 = typeid(*phuman9);

	Human* phuman10 = new Man;
	const type_info& tp3 = typeid(*phuman10);

	Human* phuman11 = new Woman;
	const type_info& tp4 = typeid(*phuman11);


	if (tp2 == tp3) {
		cout << "类型相同" << endl;  // 类型相同
	}
	else
	{
		cout << "类型不同" << endl;
	}

	if (tp2 == tp4) {
		cout << "类型相同" << endl;  
	}
	else
	{
		cout << "类型不同" << endl;  // 类型不同
	}

	/*
		phuman对象里面有一个我们看不见的指针，这个指针指向谁，指向的是这个对象所在类man
		里面的虚函数表。
	*/
	Human* phuman12 = new Man;
	const type_info& ty = typeid(*phuman12);

	delete phuman;
	delete phuman1;
	delete phuman2;
	delete phuman3;
	delete phuman4;
	delete phuman5;
	delete phuman6;
	delete phuman7;
	delete phuman8;
	delete phuman9;
	delete phuman10;
	delete phuman11;

	delete pman1;
	delete pman2;

}

int main() {

	test01();

	return 0;
}