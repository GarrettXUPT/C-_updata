#include<iostream>
#include<algorithm>
#include<list>
#include<map>
#include<vector>
#include<unordered_map>

using namespace std;

/*
	一、算法概述：可简单理解为函数模板(全局函数/全局函数模板)
		比如：查找、排序等，数量在不断上涨
		算法的前两个形参的类型，一般都是迭代器的类型，用来表示某容器的作用区间，这个作用区间是一个前闭后开的区间[begin, end)
		前闭后开区间的好处：
			1、算法只要判断迭代器只要等于后面这个开区间，那么就表示迭代结束
			2、若第一个形参等于第二个形参，那么就表示该区间是一个空区间
		算法是一种搭配迭代器来使用的全局函数，算法与具体的容器并没有关联，只与迭代器有关联，只需要根据迭代器来开发算法，不需要理会具体的容器，
		从而增加了算法代码开发的弹性(灵活性)，算法这种泛型编程方式增加了灵活性，但是确是缺失了直观性；某些数据结构和算法之间的兼容性不是特别好

	二、算法内部的一些处理
		算法会根据传递进来的迭代器分析出迭代器的种类(五种之一)，不同类型的迭代器，算法会有不同的处理，要编写不同的代码来应对；
		这种编写不同的代码可以处理不同迭代器，能够直接影响到算法的执行效率(效率是一个很重要的指标)

	三、一些典型算法使用范例
*/

void test01() {
	list<int> mylist = {10, 20, 30};
	/*
		指向第一个元素
	*/
	list<int>::iterator start = mylist.begin();
	/*
		指向最后一个元素的下一个位置
	*/
	list<int>::iterator end = mylist.end();
}

/*
	算法范例演示
*/
/*
	for_each
		自处理函数的参数要与容器中的元素类型保持一致
		工作原理：不断地迭代给进来的两个迭代器之间的元素，然后拿到这个元素，以这个元素为实参调用myfunc，
		for_each的源码说明两个问题：
			1、算法区分迭代器种类，该种类决定着某些算法的效率
			2、f(*first):这是一个可调用对象
*/
template<typename InputIterator, typename Function>
Function My_for_each(InputIterator first, InputIterator last, Function f) {
	for (; first != last; ++first) {
		f(*first);
	}
	return f;
}

void myfunc(int i) {
	cout << i << endl;
}

void test02() {
	list<int> mylist = { 10, 20, 30, 40 };
	for_each(mylist.begin(), mylist.end(), myfunc);  // myfunc是可调用对象
}

/*
	find
		当成员函数和全局函数同时存在的时候，优先考虑使用同名的成员函数，若没有同名的成员函数，才会考虑使用这些全局函数

*/
void test03() {
	list<int> mylist = { 10, 20, 30, 40 };
	auto finditer = find(mylist.begin(), mylist.end(), 400);
	if (finditer != mylist.end()) {
		cout << "can find the element" << endl;
	}
	else
	{
		cout << "can't find the element" << endl;
	}

	map<int, string> mymap;
	mymap.insert(make_pair(1, "小李"));
	mymap.insert(make_pair(2, "小王 "));
	auto iter = mymap.find(2);
	if (iter != mymap.end()) {
		cout << "can find the element: " << iter->first << ":" << iter->second << endl;
	}
	else
	{
		cout << "can't find the element" << endl;
	}
}

/*
	find_if
*/
void test04() {
	list<int> mylist = { 10, 20, 30, 40 };
	auto result = find_if(mylist.begin(), mylist.end(), [](int val) {
		if (val > 15) {
			return true;
		}
		return false; // 停止遍历
	});
	if (result == mylist.end()) {
		cout << "没找到" << endl;
	}
	else
	{
		cout << "找到了，元素为：" << *result << endl;
	}
}

/*
	sort排序
		list类型的容器
*/
bool myfunc1(int i, int j) {
	return i > j;  // 从大到小排序
}

class A {
public:
	/*
		从打到小排序 
	*/
	bool operator ()(int i, int j) {
		return i > j;
	}
};

void test05() {
	vector<int> mylist = { 10, 20, 30, 40 };
	sort(mylist.begin(), mylist.end());  // 缺省时，是从小到大进行排序的，若要从大到小就需要自己写配合函数
	auto start1 = mylist.begin();

	while (start1 != mylist.end())
	{
		cout << *start1++ << endl;
	}

	sort(mylist.begin(), mylist.end(), myfunc1);

	auto start2 = mylist.begin();
	while (start2 != mylist.end())
	{
		cout << *start2++ << endl;
	}

	/*
		使用类对象作为可调用对象
	*/
	A mya;
	sort(mylist.begin(), mylist.end(), mya);
	auto start3 = mylist.begin();
	while (start3 != mylist.end())
	{
		cout << *start3++ << endl;
	}

	list<int> mylst = { 10, 20, 30, 40 };
	//mylst.sort();  // 默认由小到大
	mylst.sort(myfunc1);  // 由大到小
	auto start4 = mylst.begin();
	while (start4 != mylst.end())
	{
		cout << *start4++ << endl;
	}
	
	/*
		再放入的时候自动排序
	*/
	map<int, string> mymap;
	mymap.insert(make_pair(10, "小李"));
	mymap.insert(make_pair(2, "小王 "));
	mymap.insert(make_pair(20, "小黄 "));

	auto start5 = mymap.begin();
	while (start5 != mymap.end())
	{
		cout << start5->first << " : " << start5->second << endl;
		start5++;
	}

	unordered_map<int, string> mymap2;  // 不会进行自动排序
	mymap2.insert(make_pair(10, "小李"));
	mymap2.insert(make_pair(2, "小王 "));
	mymap2.insert(make_pair(20, "小黄 "));
}

int main() {
	test05();
	return 0;
}