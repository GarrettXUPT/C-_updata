#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

/*
	一、函数对象/仿函数回顾
		在stl中函数对象一般都是和算法配合使用的，从而实现一些特定的功能，这些函数对象主要用来服务于算法

	二、标准库中定义的函数对象
		标准库中也提供了很多可以拿来使用的函数对象，使用他们之前，要包含一个头文件functional
		
	三、标准库中定义的函数对象范例
			

*/

class A {
public:
	bool operator()(int i, int j) {
		return i > j;
	}
};

void test01() {
	vector<int> myvec = { 10, 20, 30, 29 };
	sort(myvec.begin(), myvec.end(), [](int i, int j) {
		return i > j;  // 由大到小
	});
	auto start = myvec.begin();
	while (start != myvec.end())
	{
		cout << *start++ << endl;
	}

	A mya;  // mya就是一个函数对象
}

void test02() {
	plus<int>();  // 临时对象，即为可调用对象
	plus<int> myplus;  // 可调用对象
}

/*
	标准库中可调用对象使用范例
*/
void test03() {
	vector<int> vec = { 10, 20, 32, 23 };
	sort(vec.begin(), vec.end(), greater<int>());  // 由大到小
	auto start = vec.begin();
	while (start != vec.end())
	{
		cout << *start++ << endl;
	}
}

int main() {
	test03();
	return 0;
}