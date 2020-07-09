
#include<iostream>

using namespace std;

/*
	内存高级话题
	1、new
		1.new类对象的时候，加不加括号有啥差别
			a、若为空类，两种写法没有区别，现实中不可能只写一个空类
			b、在类中存在成员变量:带括号的初始化方式会将一些与成员变量有关的内存清零，但是不是整个对象的内存全部清零
			c、若类中有构造函数:两种写法得到的结果是一样的，也是没啥差别
			d、若类中有虚函数，则与类中有成员变量的结果相同，一个被清零，另一个还是随机值；若类中存在虚函数，那么编译器会自动生成默认构造函数
			e、看上去的感觉：没有啥区别
		2、new的作用(此处就演示了new/malloc delete/free的区别)
			new是一个关键字/操作符，主要作用：调用operator new函数，调用类A的构造函数
			A* pa1 = new A();
				operator new();函数
					_malloc();分配内存
				A::A();调用了类A的构造函数,若该类中有构造函数，则调用，若没有，则不调用，若编译器产生，则也是要调用

			delete pa1;  // delete过程与new过程相反
				A::~A();
				operator delete();
					free();
		3、malloc的作用
			分配内存

	new的细节、重载类内的operator new、delete
		1、new内存分配细节
			一块内存的回收，影响的范围很广，远远不止分配的空间那么大
			new/delete内部使用的是malloc/free，但是仅仅是mallco/free也是很复杂的
			分配内存的时候，为了记录和管理分配出去的内存，所以多分配了很多内存，造成浪费，尤其是多次申请小块内存，造成的浪费更加明显，更加严重
		2、重载类中的operator new/delete
			这种操作的作用是可以在这中间统计我们想要的数据
		3、重载类中的operator new[]/delete[]
			
			
			
*/

class A {
public:
	A() { cout << "调用了构造函数" << endl; };
	~A() { cout << "调用了析构函数" << endl; };
	/*
		重载operator new
	*/
	static void* operator new(size_t size);
	/*
		重载operator delete
	*/
	static void operator delete(void* phead);

	/*
		重载operator new[]
	*/
	static void* operator new[](size_t size);
	/*
		重载operator delete[]
	*/
	static void operator delete[](void* phead);


private:
	int m_i;
};

void* A::operator new(size_t size) {
	A* ppoint = (A*)malloc(size);
	cout << "重载new" << endl;
	return ppoint;
}

void A::operator delete(void* phead) {
	cout << "重载delete" << endl;
	free(phead);
}

void* A::operator new[] (size_t size) {
	A* ppoint = (A*)malloc(size);
	cout << "重载new[]" << endl;
	return ppoint;
}

void A::operator delete[](void* phead) {
	cout << "重载delete[]" << endl;
	free(phead);
}


/*
	1.new类对象的时候，加不加括号有啥差别
*/
void test01() {
	A* pa1 = new A();
	A* pa2 = new A;
	// ....
	// 一块内存的回收，影响的范围很广，远远不止分配的空间那么大
	delete pa1;

	/*
		简单类型
	*/
	int* p1 = new int();  // 初值为零
	int* p2 = new int;  // 初值随机
	int* p3 = new int(100);  // 初值为100
}

void test02() {
	char* cpoint = new char[10];
	memset(cpoint, 0, 10);  // 将10个字节进行清零
	delete[] cpoint;

	// 在此处分配内存的时候，并不是简单的分配出4个字节，而是在这4个字节周围编译器进行了很多处理(记录分配出去的字节数等)
	int* ipoint = new int(10);  // 此处内部记录了分配内存的大小
	delete ipoint;  
}


void test03() {
	/*
		重载operator new
	*/
	void* temp = operator new(sizeof(A));
	A* pa = static_cast<A*>(temp);
	pa->A::A();

	/*
		重载operator delete
	*/
	pa->A::~A();
	operator delete(pa);
}

/*
	调用重载后的new/delete
*/
void test04() {
	A* pa = new A();
	delete pa;

	/*
		调用系统的new/delete
	*/
	A* pa2 = ::new A();
	::delete pa2;  // ::全局操作符，调用系统的new/delete
}

void test05() {
	/*
		 这样使用的是数组的operator new[]/delete[],而不是单个对象的分配函数
		 构造函数和析构函数被调用了三次，但是operator new[]/delete[]仅仅被调用了一次
	*/
	A* pa = new A[3]();
	delete[] pa;
}

int main() {
	test05();
	return 0;
}