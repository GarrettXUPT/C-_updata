#include<iostream>
#include<string>
#include"Myarray.h"

using namespace std;

/*
	һ��typename�����ó���
		1��ģ�嶨�����������ģ����������Ͳ���
			����ģ��
			template<typename T>  //typename���������һ������
			T funAdd(){...}
			��ģ��
			template<typename T>  ����ΪT��ģ�����
			class MyClass{...};
			typename�����滻Ϊclass��������Ȼ����ʹ��class�����������class�������ඨ�����˼
		2��ʹ��������ͳ�Ա��ʹ��typename��ʶ����һ������
			::��ʾ�������������Ҳ���Է������ͳ�Ա
			typename֪ͨ��������һ�����ִ������һ������
			size_type ������unsigned int ���ǵ������Ĳ���

	��������ָ����������������

	��������ģ���ʹ�þ���
		�ɵ��ö���

	�ġ�Ĭ��ģ�����
		1����ģ�壬��ģ������߱���ʹ��<>�ṩģ����Ϣ��<>��ʾ����һ��ģ��
		2��C++11���Ժ���ģ���Ĭ��ģ�����
			ע�⣺1��ͬʱ��ģ��ͺ��������ṩȱʡֵ
				  2��ע��д�� T2 funcpoint = T2()
				  3��tc����()
		
		
*/
/*
	���ַ�������
*/
template<typename T>
typename T::size_type getlength(const T& str) {
	if (str.empty()) {
		return 0;
	}
	return str.size();
}

void test01() {
	string str = "Garrett";
	string::size_type length = getlength(str);
	cout << "length = " << length << endl;  // 7
}

/*
	����ָ����������������
	����ָ����Ϊĳ�������������д���
	����ָ������Ϊ�����Ĳ�������Ҫ���·�ʽ����
*/
// ������һ������ָ������
typedef int(*FunType)(int, int);

int myAdd(int tmp1, int tmp2) {

	return tmp1 + tmp2;
}

int testfunc(int i, int j, FunType funpoint) {
	return funpoint(i, j);
}

void test02() {
	int res = testfunc(3, 4, myAdd);
	cout << "res = " << res << endl;  // 7
}

class tc;
/*
	����ģ���ʹ�þ���
	�˴�����tc��Ϊ����ʾ����ģ���Ĭ��ģ�����
*/
template<typename T1, typename T2 = tc>
	void testfun(const T1& i, const T1& j, T2 funcpoint = T2()) {
	cout << funcpoint(i, j) << endl;
}

void test03() {
	testfun(2, 3, myAdd);
}

/*
	�ɵ��ö������������
*/
class tc {
public:
	tc() { cout << "���캯��ִ��" << endl; }
	tc(const tc& t) { cout << "�������캯��ִ��" << endl; }
	// �������������
	int operator()(int v1, int v2) const {
		return v1 + v2;
	}
};

void test04() {
	tc tcobj;
	testfun(3, 4, tcobj);   // 7

	testfun(5, 6, tc());  //  11 ʹ����ʱ��������ʹ�ÿ��Լ���һ�ο������캯����ʹ��
}

/*
	��ȫʹ��ģ��ȱʡֵ
*/
void test05() {
	MyArray<> abc;

	/*
		�ṩ��һ����ȱʡֵ��ʹ�õڶ���������ȱʡֵ
	*/
	MyArray<int> def;
}

/*
	����ģ���Ĭ��ģ�����
*/
void test06() {
	testfun(2, 5);  // 7
}

int main() {
	test06();
	return 0;
}