#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

/*
	һ����������������
		��һ�����еĶ��������ʵ��ĸ��죬�͹�����һ��������
		������������
			1������������
				stack:
				queue
			2���㷨������
				����͵ľ��ǰ���
				�ϰ汾��bind1st, bind2nd,��C++11���޸�Ϊbind
			3��������������
				reverse_iterator:���������
*/


class A {
public:
	bool operator()(int i) {
		return i < 20;
	}
};

void test01() {
	vector<int> vec = { 10, 20, 32, 26, 14 };
	// ͳ��ĳ��ֵ���ֵĴ���
	int myCount = count(vec.begin(), vec.end(), 26);
	cout << myCount << endl;  // 1 

	myCount = count_if(vec.begin(), vec.end(), A());
	cout << myCount << endl;

	myCount = count_if(vec.begin(), vec.end(), bind(greater<int>(), 20, placeholders::_1));
	cout << myCount << endl;

	/*
		���������
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