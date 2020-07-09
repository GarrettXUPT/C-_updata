#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

/*
	一、迭代器的基本概念
		迭代器是一个可遍历STL全部或者是部分元素的对象(行为类似于指针的对象)；
		迭代器用来表现容器中的某一个位置；迭代器紧密依赖于容器，迭代器是容器提供的,迭代器和容器是绑定在一起的

	二、迭代器的分类：不同的容器使用的迭代器是不同的
		分类的依据是：迭代器的移动特性和在迭代器上支持的操作
		迭代器用来表示一个位置，像是指针，也是依据指针的跳跃能力，每一个分类是一个对应的struct
			1、输出型迭代器:output iterator
				一步一步向前走，并且能够通过这个种类的迭代器来改写容器中的数据
			2、输入型迭代器:input iterator
				一次一个以向前的方向读取元素，按照顺序一个一个返回元素值
			3、前向迭代器:forward iterator
				前向迭代器继承自input迭代器，因此它可以向前的方向读取元素
			4、双向迭代器:bidrectional iterator
				双向迭代器继承自单向迭代器：在前向迭代器的基础上，增加了反向迭代功能呢
			5、随机访问迭代器:random access iterator
				继承双向迭代器，在双向迭代器的基础上增加了随机访问能力，也就是增减某个偏移量，可以计算距离，直接访问到目标元素
		上述结构都是有继承关系的
		大多数容器里面都有一个::iterator的迭代器类型，并不是所有容器中都有迭代器(stack，queue等)

*/

/*
	迭代器的使用
*/
void test01() {
	vector<int> vec = { 100, 200, 300 };
	/*
		迭代器的定义
	*/
	vector<int>::iterator start = vec.begin();
	/*
		迭代器的遍历
	*/
	while (start != vec.end())
	{
		cout << *start++ << endl;
	}
}

void test03() {

	struct output_iterator_tag;  // 输出型迭代器

	struct input_iterator_tag;  // 输入型迭代器
	
	struct forward_iterator_tag;  // 双向迭代器

	struct bidrectional_iterator_tag;  // 双向迭代器

	struct random_access_iterator_tag;  // 随机访问迭代器

	
	
}

int main() {
	test01();
	return 0;
}