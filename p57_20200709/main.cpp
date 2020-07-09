#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

/*
	һ����������/�º����ع�
		��stl�к�������һ�㶼�Ǻ��㷨���ʹ�õģ��Ӷ�ʵ��һЩ�ض��Ĺ��ܣ���Щ����������Ҫ�����������㷨

	������׼���ж���ĺ�������
		��׼����Ҳ�ṩ�˺ܶ��������ʹ�õĺ�������ʹ������֮ǰ��Ҫ����һ��ͷ�ļ�functional
		
	������׼���ж���ĺ���������
			

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
		return i > j;  // �ɴ�С
	});
	auto start = myvec.begin();
	while (start != myvec.end())
	{
		cout << *start++ << endl;
	}

	A mya;  // mya����һ����������
}

void test02() {
	plus<int>();  // ��ʱ���󣬼�Ϊ�ɵ��ö���
	plus<int> myplus;  // �ɵ��ö���
}

/*
	��׼���пɵ��ö���ʹ�÷���
*/
void test03() {
	vector<int> vec = { 10, 20, 32, 23 };
	sort(vec.begin(), vec.end(), greater<int>());  // �ɴ�С
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