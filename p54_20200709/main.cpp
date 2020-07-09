#include<iostream>
#include<vector>
#include<list>

using namespace std;

/*
	一、分配器概述：和容器紧密关联，一起使用
		每一次malloc时候都会浪费很多内存来用在内存管理上
		确切的说其实是内存分配器，通过减少对malloc的使用来节省内存，甚至还有一部分分配效率的提高
		经过测试，allocator这个C++标准库提供的缺省的内存分配器根本就没有采用内存池的工作机制，估计是在底层直接调用的malloc

	二、分配器的使用

	三、其他分配器及原理
		还是不写了 也用不上
*/


void test01() {
	/*
		一般情况下，分配器都是使用系统默认的分配器
	*/
	vector<int, std::allocator<int>> vec;

	list<int> mylist;  // 双向列表内存是不要求连续
	mylist.push_back(10);
	mylist.push_back(20);
	mylist.push_back(30);

	auto start = mylist.begin();
	while (start != mylist.end())
	{
		cout << *start << "'s address is ";
		printf("%p\n", &(*start));
		start++;
	}
}

/*
	分配器的使用
		allactor其实是一个类模板，在日常工作中，极少会直接用到分配器，但是从语法上来讲，是可以被直接使用的
*/
void test02() {
	/*
		定义一个alloc对象，为类型为int的对象分配内存		
	*/
	allocator<int> alloc;
	/*
		这段内存可以保存3个类型为int的对象(12个字节)
	*/
	int* p = alloc.allocate(3);  // allocate是分配器中的一个重要的函数，用来分配一段原始的未被构造的内存
}

int main() {
	test01();
	return 0;
}