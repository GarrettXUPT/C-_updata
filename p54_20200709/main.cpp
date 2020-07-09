#include<iostream>
#include<vector>
#include<list>

using namespace std;

/*
	һ�����������������������ܹ�����һ��ʹ��
		ÿһ��mallocʱ�򶼻��˷Ѻܶ��ڴ��������ڴ������
		ȷ�е�˵��ʵ���ڴ��������ͨ�����ٶ�malloc��ʹ������ʡ�ڴ棬��������һ���ַ���Ч�ʵ����
		�������ԣ�allocator���C++��׼���ṩ��ȱʡ���ڴ������������û�в����ڴ�صĹ������ƣ��������ڵײ�ֱ�ӵ��õ�malloc

	������������ʹ��

	����������������ԭ��
		���ǲ�д�� Ҳ�ò���
*/


void test01() {
	/*
		һ������£�����������ʹ��ϵͳĬ�ϵķ�����
	*/
	vector<int, std::allocator<int>> vec;

	list<int> mylist;  // ˫���б��ڴ��ǲ�Ҫ������
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
	��������ʹ��
		allactor��ʵ��һ����ģ�壬���ճ������У����ٻ�ֱ���õ������������Ǵ��﷨���������ǿ��Ա�ֱ��ʹ�õ�
*/
void test02() {
	/*
		����һ��alloc����Ϊ����Ϊint�Ķ�������ڴ�		
	*/
	allocator<int> alloc;
	/*
		����ڴ���Ա���3������Ϊint�Ķ���(12���ֽ�)
	*/
	int* p = alloc.allocate(3);  // allocate�Ƿ������е�һ����Ҫ�ĺ�������������һ��ԭʼ��δ��������ڴ�
}

int main() {
	test01();
	return 0;
}