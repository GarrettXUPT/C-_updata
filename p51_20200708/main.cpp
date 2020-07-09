#include<iostream>

using namespace std;

/*
	一、重载全局operator new/delete操作符
		一般不会这么做，若在类中也重载了operator new/delete，那么类内重载的函数就会覆盖掉全局的重载函数

	二、定位new(placement new)
		有placement new，但是没有palcement delete
		功能：在已经分配的原始内存中初始化一个对象
			  1、已经分配，定位new并不分配内存，需要提前将定位new所需要的内存分配出来
			  2、初始化一个对象，也就是调用该对象的构造函数
			  定位new就是在一个预先分配好的内存地址中构造一个对象
		格式：
			new (已经分配内存的首地址) 类类型()
		
*/

/*
	重载全局的operator new/delete
*/
void* operator new(size_t size) {
	return malloc(size);
}

void* operator new[](size_t size) {
	return malloc(size);
}

void operator delete(void* phead) {
	free(phead);
}

void operator delete[](void* phead) {
	free(phead);
}

class A {
public:
	A() { cout << "调用了A的构造函数" << endl; }
	~A() { cout << "调用了A的析构函数" << endl; }

public:
	void* operator new(size_t size) {
		A* ppint = (A*)malloc(size);
		return ppint;
	}

	void operator delete(void* phead) {
		free(phead);
		phead = nullptr;
	}
	
	/*
		重载定位new
	*/
	void* operator new(size_t size, void* phead) {
		return phead;   // 因为收到的是内存的开始地址，那么我们直接原样返回就行
	}
};

void test01() {
	int* pint = new int(12);
	delete pint;

	char* pchar = new char[10];
	delete[] pchar;

	A* pa1 = new A();
	delete pa1;

	A* pa2 = new A[2]();
	delete[] pa2;
}


/*
	定位new的使用
*/
class B {
public:
	int m_a;
	B(int i_a) :m_a(i_a) {};
	B() { m_a = 0; };
	~B() {};
};

void test02() {
	/*
		将内存事先分配出来
	*/
	void* mymempoint = (void*)new char[sizeof(A)];
	/*
		在这块内存中初始化一个对象，这里并不会额外分配内存
	*/
	B* pmyobj1 = new(mymempoint) B(12);

	/*
		释放已经初始化的对象,手动调用析构函数是可以的，但是还没有见过手动调用构造函数
	*/
	pmyobj1->~B();

	/*
		释放内存
	*/
	delete[] pmyobj1;
}

/*
	多种版本的operator new/delete
*/


int main() {
	test02();
	return 0;
}