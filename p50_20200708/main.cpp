#include<iostream>

using namespace std;

/*	嵌入式指针概念及范例、内存池改进版
	一、嵌入式指针概念
		该种指针一般应用于内存池相关的代码中：成功使用嵌入式指针的前提条件：类A对象的sizeof必须不小于四个字节
		工作原理：借用A对象所占内存的内存空间的前四个字节，这四个字节用来连住这些空闲的内存块
				  但是某一块一旦被分配出去，那么该块的前四个字节就不需要了，此时这四个字节可以被正常使用

	二、嵌入式指针演示
		超过4个字节的类，就可以安全地使用嵌入式指针，借用类内存，保存空闲块

	三、内存池代码的改进
		单独的内存池技术类

*/

/*
	内存池实现类
*/
class MyAllocator {  // 使用该类时，必须保证应用本类的类的sizeof()不少于4个字节，否则会崩溃
public:
	/*
		分配内存接口
	*/
	void* allocate(size_t size);
	/*
		重载操作符delete
	*/
	void deallocate(void* phead);


private:
	struct obj{
		struct obj* next;  // 嵌入式指针
	};
	int m_sTrunkCount = 0;
	obj* m_free_pos = nullptr;
};


void* MyAllocator::allocate(size_t size) {
	obj* tmplink;
	if (m_free_pos == nullptr) {
		// 为空 在申请一大块内存
		size_t realisize = m_sTrunkCount * size;  // 申请m_sTrunckCount这么多倍的内存
		m_free_pos = (obj*)malloc(realisize);  //  此处的new使用的是系统底层的malloc，即系统自带的new
		tmplink = m_free_pos;
		/*
			将分配出来的一大块(五小块)内存彼此要连起来，供后续使用
		*/
		for (int i = 0; i < m_sTrunkCount - 1; i++) {
			tmplink->next = (obj*)((char*)tmplink + size);
			tmplink = tmplink->next;
		}
		tmplink->next = nullptr;
	}
	tmplink = m_free_pos;
	m_free_pos = m_free_pos->next;
	return tmplink;
}

void MyAllocator::deallocate(void* phead) {
	((obj*)phead)->next = m_free_pos;
	m_free_pos = (obj*)(phead);
}


/*
	嵌入式指针演示
*/
class B {
public:
	int m_i;
	int m_j;
public:
	// 也可以将该结构体放在类外，但是那样的话其他的成员也就可以访问它，所以放在类内可以限制该结构体的作用域范围
	struct obj
	{
		// 成员是个指针，还是指向该结构，next就是个嵌入式指针，自己是一个obj对象，将自己对象的next指针指向另一个obj结构对象，最终将自己类型
		// 的多个结构体串在一起
		struct obj* next;
	};
};

/*
	嵌入式指针使用
*/
void test02() {
	B mB;
	cout << sizeof(mB) << endl;

	B::obj* ptmp; // 定义一个指针
	ptmp = (B::obj*)&mB;  // 该指针指向mB的首地址
	cout << sizeof(ptmp) << endl;  
	cout << sizeof(ptmp->next) << endl;  // 此时ptmp和ptmp->next指向的都是mB的首地址
	ptmp->next = nullptr;  // 借用了mB8个字节的前4个字节
}


/*
	在该类中使用内存池类,此时就是该类使用内存池分配内存
*/
class C {
public:
	int m_i;
	int m_j;
public:
	static MyAllocator myalloc;  
	static void* operator new(size_t size) {
		return myalloc.allocate(size);
	}

	static void  operator delete(void* phead) {
		return	myalloc.deallocate(phead);
	}
};
MyAllocator C::myalloc; // 定义静态成员变量

void test03() {
	C* mypa[100];
	for  (int i = 0; i < 15; ++i) {  // ++i可以少产生一次中间变量
		mypa[i] = new C();
		cout << mypa[i] << endl;
	}

	for (int i = 0; i < 15; i++) {
		delete mypa[i];
	}

}

int main() {
	test03();
	return 0;
}