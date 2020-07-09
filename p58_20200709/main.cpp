#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

/*
	一、适配器基本概念
		将一个既有的东西进行适当的改造，就构成了一个适配器
		三种适配器：
			1、容器适配器
				stack:
				queue
			2、算法适配器
				最典型的就是绑定器
				老版本：bind1st, bind2nd,在C++11中修改为bind
			3、迭代器适配器
				reverse_iterator:反向迭代器
*/


class A {
public:
	bool operator()(int i) {
		return i < 20;
	}
};

void test01() {
	vector<int> vec = { 10, 20, 32, 26, 14 };
	// 统计某个值出现的次数
	int myCount = count(vec.begin(), vec.end(), 26);
	cout << myCount << endl;  // 1 

	myCount = count_if(vec.begin(), vec.end(), A());
	cout << myCount << endl;

	myCount = count_if(vec.begin(), vec.end(), bind(greater<int>(), 20, placeholders::_1));
	cout << myCount << endl;

	/*
		反向迭代器
	*/
	auto start = vec.rbegin();
	while (start != vec.rend())
	{
		cout << *start++ << endl;
	}
}
int main() {
	test01();
	return 0;
}