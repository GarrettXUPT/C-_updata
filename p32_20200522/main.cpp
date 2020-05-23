#include<iostream>
#include<string>
#include<vector>

using namespace std;

/*
	一、直接内存管理
		new出来的对象在堆上，new这种分配方式是动态分配(分配在堆上)，直接内存管理，new delete
		new和delete说明：
			new和delete要成对使用，delete回收一块使用new分配的内存(释放内存),将内存重新归还给系统
			若不是new出来的内存，不可以使用delete释放，否则就会报异常
			new出来的内存，只能被delete一次，不可多次delete，重复释放也会引出异常；delete后，这块内存就不可以被使用了
			空指针可以被释放多次，但是并没有啥意义
		注意事项：
			1、new出来的内存千万不要忘记delete，否则在长期运行下，程序就会崩溃
			2、delete后内存不能再使用，否则会报出异常
			3、delete后再加上pci = nullptr；提示也确保该指针不指向任何地址了
			4、一块内存不能被重复释放，使用new和delete一定要小心
		C++11开始出现智能指针，new出来忘记delete，智能指针可以自动delete

	二、创建新工程，观察内存泄漏
		MFC应用程序，可以在一定程度上(在程序退出的时候)帮助我们发现内存泄漏
		MFC是微软公司出的一个基础程序框架，特点：可以生成一个带窗口界面的程序框架，MFC简化了界面开发工作 

	三、new/delete
		1、什么是new和delete？
			sizeof(关键字/运算符)，它不是个函数，求占用的字节数
			new/delete也是关键字/运算符，不是函数
			malloc/free主要用于C语言编程中，new/delete用于C++编程，该两者都是用于在堆上进行动态内存分配
			malloc/free和new/delete的区别：
				1、new/delete比malloc/free完成了更多的工作，new不但分配内存，还会做一些初始化工作，delete不但会释放内存，还会完成一些清理工作
				2、new一个类对象，系统会调用该类的构造函数，delete一个类对象的时候，系统会调用类的析构函数
				3、new/delete具备对堆上所分配的内存进行初始化/释放的能力，这些事malloc/free所不具备的
		
		2、operator new()和operator delete()
			这里出现的operator new()和operator delete()这都是函数
			new完成的工作：
				1、分配内存：就是通过operator new()来分配内存
				2、调用类的构造函数来初始化内存
			delete完成的工作：
				1、调用析构函数
				2、释放内存：调用operator delete()释放内存
		
		3、基本new如何记录分配的内存大小供delete使用
			不同的编译器new内部具有不同的实现方式
			int* p = new int;  // 操作系统分配4个字节
			delete p;		// 释放内存的时候精确的释放4个字节，这是因为在new的内部具有记录机制
		
		4、申请和释放数组
			此处演示在memory_debug中，此处我们要注意的是，就是初始化一个空类，也会占用一个字节的内存
			/
				内置类型没有构造函数，所以不需要额外的内存记录
			/
			int* p = new int[2];  // 分配内存给长度为2的数组，即8个字节
			规范释放代码 delete[] p;
			/
				该处调用两次构造函数
				在new一个数组的时候，系统会开辟内存记录数组元素的个数
			/
			A* pa = new A[2]();  
			/
				该处调用两次析构函数
			/
			delete[]pa;    // 规范释放数组内存

		5、为什么new/delete、delete[]/new[]要配对使用
			内置类型不需要调用析构函数，所以new数组的时候，系统并没有多分配4字节出来，但是delete仍然可以正确的释放内存
			结论：
				若是一个对象使用new[]来分配内存，却使用单独的delete而不是delete[]来释放内存，仅限于以下情况，但是最好使用delete[]：
					1、对象类型是内置类型
					2、无自定义析构函数，在分配内存时，系统就没有使用4个字节来记录相关信息
				new出来的东西，也千万不要使用delete[]的形式来释放，否则系统会出现不可预测的行为
				new/delete和new[]/delete[]一定要配对使用

	二、智能指针综述
		new和delete的写法要十分小心，防止早早释放或者是忘记释放
		直接使用new返回的指针叫做裸指针(未经过任何包装)，这种指针强大灵活，但是开发者要全程维护，一不小心就容易犯错
		智能指针就是可以解决裸指针带来的各种问题
		智能指针是对裸指针进行了包装，给裸指针外面进行了包装，包装后为我们带来了优点：
			最突出的优点就是智能指针可以 自动释放 所指向对象的内存
		建议优先使用智能指针：使用智能指针的程序更容易编写和调试
		C++标准库中有四种智能指针：帮助我们动态分配对象的生命周期管理，可有效防止内存泄漏
			1、auto_ptr 目前完全被unique_ptr替代，C++11中反对使用auto_ptr(弃用)
			2、unique_ptr
			3、shared_ptr
			4、weak_ptr
		上述智能指针都是类模板，我们可以将new获得的地址赋值给他们，主要的核心是：
			1、shared_ptr(共享式指针：多个指针指向同一个对象，最后一个指针被销毁时该指针会被释放)，weak_ptr辅助shared_ptr
			2、unique_ptr独占式的指针，同一时间内只有一个指针可以指向该对象，当然该对象的所有权是可以移交出去的
		在我们忘记delete的时候，智能指针帮助我们delete，或者说，我们压根就不再需要delete，智能指针的本分就是帮助我们delete

	三、shared_ptr基础：共享所有权
		不是被一个shared_ptr拥有，而是被多个shared_ptr之间相互协作
		在使用的时候要考虑，指针指向的对象是否是要被共享，开销要比unique_ptr指针要大
		工作原理：引用计数：每个shared_ptr的拷贝都指向相同的内存，所以只有最后一个会指向该内存的shared_ptr指针不需要指向该对象的时候，
				  才去去释放指向的对象，最后一个指向该对象的shared_ptr释放的时机有两种：
							1、这个shared_ptr析构的时候；
							2、shared_ptr指向其他对象时
				 有点类似于垃圾回收机制，我们不再需要担心对象该何时被delete
		因为是类模板，所以用到<>,<>里就是指针指向的类型，后面再加上智能指针名
		格式：shared_ptr<指向的类型> 智能指针名
			shared_ptr<int> pi; 指向int的智能指针，名字为pi，但是只想为空，那就是空指针
		
		make_shared函数：
			是一个标准库里的函数模板，被认为是高效安全的分配和使用shared_ptr，他可以在堆中分配并初始化对象，然后返回此对象的shared_ptr


			
			


*/

class A {
public:
	A() {
		cout << "类A对象被创建" << endl;
	}
};

void func() {
	/*
		临时对象在栈中
	*/
	int i = 5;
	/*
		局部静态对象，在静态内存区
	*/
	static int j = 2;

	//A a;  // 编译器帮我们创建和自动销毁
	// 上述情况不需要我们自己动手销毁，编译器会帮我们做这些事情

	/*
		初始化动态分配的对象
	*/
	int* point = new int;  // 此处初值未定义
	cout << *point << endl;  // -842150451

	string* mystr = new string;  // 这里调用了string的默认构造函数，这些构造函数里将类初始化为空字符串
	cout << *mystr << endl;  // 空串

	int* point1 = new int(100);  // 此处进行了初始化
	cout << *point1 << endl; // 100

	string* mystr2 = new string("Hello,World");
	string* mystr3 = new string(5, 'a');  // 生成5个a的字符串

	cout << *mystr2 << endl;    // Hello,World
	cout << *mystr3 << endl;    // aaaaa

	vector<int>* pointVec = new vector<int>{ 1, 2, 3, 4, 5 };

	/*
		值初始化
		在new对象的时候，可以进行值初始化，就进行值初始化为好，防止它的值没有被初始化
	*/
	string* mystr4 = new string();  // 使用空括号来初始化，就是值初始化，初始化为一个空串
	int* point2 = new int();  // 使用值初始化，将point的值初始化为了0

	A* pa = new A;  // 类A被创建
	A* pa1 = new A();  // 在自己定义的类对象，是否使用值初始化，效果都是一样的

	/*
		在C++11中可以将new和auto配合使用
	*/
	string* mystr5 = new string(5, 'b');
	auto mystr6 = new auto(mystr5);  // mystr6推断出来的结果是string**
	/*
		利用mystr5初始化mystr6，此时mystr5和mystr6指向的是同一块内存，释放的时候，释放一次就行
	*/
	cout << *mystr6 << endl;

	delete mystr6;  // 此时销毁mystr6并不会释放掉mystr5的内存，而是释放掉了mystr6本身的内存
	delete mystr5;

	/*
		const对象也是可以动态分配的,现在的pointci就不可被修改
	*/
	const int* pointci = new const int(200);

	/*
		此处省略若各个delete，有new就一定要有delete
	*/
}

/*
	operator new()和operator delete()
	这里出现的operator new()和operator delete()这都是函数
	new完成的工作：
		1、分配内存：就是通过operator new()来分配内存
		2、调用类的构造函数来初始化内存
	delete完成的工作：
		1、调用析构函数
		2、释放内存：调用operator delete()释放内存
*/
void test01() {
	int* pi = new int;
	delete pi;
}




/*
	shared_ptr基础
*/
void test02() {
	shared_ptr<int> ptr(new int(100));  // ptr指向值为100的int型数据
	//shared_ptr<int> ptr = new int(100);  // 智能指针是explicit 不可以进行隐式类型转换，必须使用直接初始化形式
}

/*
	返回值是shared_ptr的
*/
shared_ptr<int> makes(int value) {
	return shared_ptr<int>(new int (value));  // 显式的使用int*创建shared_ptr<int>
}

void test03() {
	/*
		shared_ptr的调用
		智能指针不要穿插使用
	*/
	shared_ptr<int> pi = makes(100);
}

/*
	make_shared函数,创建shared_ptr指针，有点类似于int* pi = new int(100);
*/
void test04() {
	shared_ptr<int> pi = make_shared<int>(100);

	shared_ptr<string> pstr = make_shared<string>("Garrett");
	cout << *pstr << endl;  // Garrett

	shared_ptr<int> p2 = make_shared<int>();  // 创建一个指向0的shared_ptr指针
	p2 = make_shared<int>(400);  // p2指向新内存400，原内存被释放

	/*
		使用auto比较方便
	*/
	auto p3 = make_shared<string>("Walker");
	cout << *p3 << endl;  // Walker
}

int main() {
	test04();
	return 0;
}