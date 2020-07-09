#include<iostream>
#include<ctime>

using namespace std;

/*
	内存池概念、代码实现和详细分析
	一、内存池的概念和实现原理概述
		malloc:会造成内存浪费，频繁的分配小块内存会使浪费更加明显
			1、内存池就是可以减少上述内存的浪费，通过减少malloc的调用次数
			2、减少的调用次数，会有一些速度和运行效率上的提升，但是提升不明显
		内存池的实现原理：
			1、用malloc申请一大块内存，当需要分配内存的时候，就一点一点的将内存分配出去，当一大块内存分配差不多的时候，
			   再使用malloc申请一块内存，再一点一点的分配出去
			2、存在的根本就是减少内存浪费，提高运行效率
	
	二、内存池实现演示代码
		针对一个类的内存池的实现，使用内存池来实现new/delete一个对象

	三、内存池代码后续说明
		在内存池释放内存的时候，并不是真正的归还给系统，而是放回到内存池中


*/

class A {
public:
	/*
		重载操作符new
	*/
	static void* operator new(size_t size);
	/*
		重载操作符delete
	*/
	static void operator delete(void* phead);

	/*
		统计分配内存的次数
	*/
	static int m_count;
	/*
		malloc使用次数统计
	*/
	static int malloc_count;
private:
	A* next; // 
	static A* m_free_pos;  // 总是指向一块可以分配出去的内存的首地址
	static int m_sTrunkCount;  // 一次分配多少倍的该类内存
};
int A::m_count = 0;

int A::malloc_count = 0;

A* A::m_free_pos = nullptr;

int A::m_sTrunkCount = 50; // 一次分配五倍的内存作为内存池的大小

void* A::operator new(size_t size) {
	A* tmplink;
	if (m_free_pos == nullptr) {
		// 为空 在申请一大块内存
		size_t realisize = m_sTrunkCount * size;  // 申请m_sTrunckCount这么多倍的内存
		m_free_pos = reinterpret_cast<A*>(new char[realisize]);  //  此处的new使用的是系统底层的malloc，即系统自带的new
		tmplink = m_free_pos;
		/*
			将分配出来的一大块(五小块)内存彼此要连起来，供后续使用
		*/
		for (; tmplink != &m_free_pos[m_sTrunkCount - 1]; tmplink++) {
			tmplink->next = tmplink + 1;
		}
		tmplink->next = nullptr;
		malloc_count++;
	}
	tmplink = m_free_pos;
	m_free_pos = m_free_pos->next;
	m_count++;
	return tmplink;
}

void A::operator delete(void* phead) {
	static_cast<A*>(phead)->next = m_free_pos;
	m_free_pos = static_cast<A*>(phead);
}

void test01() {
	clock_t start, end;
	start = clock();
	for (int i = 0; i < 500'0000; i++) {
		A* pa = new A();
	}
	end = clock();
	cout << "申请内存分配的次数：" << A::m_count << endl;
	cout << "实际malloc的次数为：" << A::malloc_count << endl;
	cout << "该过程用时(ms)：" << end - start << endl;
}

int main() {
	test01();
	return 0;
}