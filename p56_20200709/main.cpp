#include<iostream>
#include<algorithm>
#include<list>
#include<map>
#include<vector>
#include<unordered_map>

using namespace std;

/*
	һ���㷨�������ɼ����Ϊ����ģ��(ȫ�ֺ���/ȫ�ֺ���ģ��)
		���磺���ҡ�����ȣ������ڲ�������
		�㷨��ǰ�����βε����ͣ�һ�㶼�ǵ����������ͣ�������ʾĳ�������������䣬�������������һ��ǰ�պ󿪵�����[begin, end)
		ǰ�պ�����ĺô���
			1���㷨ֻҪ�жϵ�����ֻҪ���ں�����������䣬��ô�ͱ�ʾ��������
			2������һ���βε��ڵڶ����βΣ���ô�ͱ�ʾ��������һ��������
		�㷨��һ�ִ����������ʹ�õ�ȫ�ֺ������㷨������������û�й�����ֻ��������й�����ֻ��Ҫ���ݵ������������㷨������Ҫ�������������
		�Ӷ��������㷨���뿪���ĵ���(�����)���㷨���ַ��ͱ�̷�ʽ����������ԣ�����ȷ��ȱʧ��ֱ���ԣ�ĳЩ���ݽṹ���㷨֮��ļ����Բ����ر��

	�����㷨�ڲ���һЩ����
		�㷨����ݴ��ݽ����ĵ�����������������������(����֮һ)����ͬ���͵ĵ��������㷨���в�ͬ�Ĵ���Ҫ��д��ͬ�Ĵ�����Ӧ�ԣ�
		���ֱ�д��ͬ�Ĵ�����Դ���ͬ���������ܹ�ֱ��Ӱ�쵽�㷨��ִ��Ч��(Ч����һ������Ҫ��ָ��)

	����һЩ�����㷨ʹ�÷���
*/

void test01() {
	list<int> mylist = {10, 20, 30};
	/*
		ָ���һ��Ԫ��
	*/
	list<int>::iterator start = mylist.begin();
	/*
		ָ�����һ��Ԫ�ص���һ��λ��
	*/
	list<int>::iterator end = mylist.end();
}

/*
	�㷨������ʾ
*/
/*
	for_each
		�Դ������Ĳ���Ҫ�������е�Ԫ�����ͱ���һ��
		����ԭ�����ϵص���������������������֮���Ԫ�أ�Ȼ���õ����Ԫ�أ������Ԫ��Ϊʵ�ε���myfunc��
		for_each��Դ��˵���������⣺
			1���㷨���ֵ��������࣬�����������ĳЩ�㷨��Ч��
			2��f(*first):����һ���ɵ��ö���
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
	for_each(mylist.begin(), mylist.end(), myfunc);  // myfunc�ǿɵ��ö���
}

/*
	find
		����Ա������ȫ�ֺ���ͬʱ���ڵ�ʱ�����ȿ���ʹ��ͬ���ĳ�Ա��������û��ͬ���ĳ�Ա�������Żῼ��ʹ����Щȫ�ֺ���

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
	mymap.insert(make_pair(1, "С��"));
	mymap.insert(make_pair(2, "С�� "));
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
		return false; // ֹͣ����
	});
	if (result == mylist.end()) {
		cout << "û�ҵ�" << endl;
	}
	else
	{
		cout << "�ҵ��ˣ�Ԫ��Ϊ��" << *result << endl;
	}
}

/*
	sort����
		list���͵�����
*/
bool myfunc1(int i, int j) {
	return i > j;  // �Ӵ�С����
}

class A {
public:
	/*
		�Ӵ�С���� 
	*/
	bool operator ()(int i, int j) {
		return i > j;
	}
};

void test05() {
	vector<int> mylist = { 10, 20, 30, 40 };
	sort(mylist.begin(), mylist.end());  // ȱʡʱ���Ǵ�С�����������ģ���Ҫ�Ӵ�С����Ҫ�Լ�д��Ϻ���
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
		ʹ���������Ϊ�ɵ��ö���
	*/
	A mya;
	sort(mylist.begin(), mylist.end(), mya);
	auto start3 = mylist.begin();
	while (start3 != mylist.end())
	{
		cout << *start3++ << endl;
	}

	list<int> mylst = { 10, 20, 30, 40 };
	//mylst.sort();  // Ĭ����С����
	mylst.sort(myfunc1);  // �ɴ�С
	auto start4 = mylst.begin();
	while (start4 != mylst.end())
	{
		cout << *start4++ << endl;
	}
	
	/*
		�ٷ����ʱ���Զ�����
	*/
	map<int, string> mymap;
	mymap.insert(make_pair(10, "С��"));
	mymap.insert(make_pair(2, "С�� "));
	mymap.insert(make_pair(20, "С�� "));

	auto start5 = mymap.begin();
	while (start5 != mymap.end())
	{
		cout << start5->first << " : " << start5->second << endl;
		start5++;
	}

	unordered_map<int, string> mymap2;  // ��������Զ�����
	mymap2.insert(make_pair(10, "С��"));
	mymap2.insert(make_pair(2, "С�� "));
	mymap2.insert(make_pair(20, "С�� "));
}

int main() {
	test05();
	return 0;
}