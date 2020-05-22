#include<iostream>

#include"head1.h"
#include"head2.h"

using namespace std;

/*
	�ֲ���������ʼ����
		��ʱ�ã���ʱ����
		int value{1} Ч���� value = 1��ͬ
	auto���Զ������ƶ�
		auto������������ʱ�򣬸��ݱ�����ʼֵ�������Զ�Ϊ����ѡ��ƥ�������(����ʱ���븳ֵ)
		�Զ������ƶϷ����ڱ����ڼ䣬��ʹ��ʱ���ᵼ�³��������Ч�ʽ���

	ͷ�ļ���������
		#ifndef __HEAD1__H__
		#define __HEAD1__H__
		int g_value1 = 8;
		#endif // __HEAD1__

	���ã�
		Ϊ�����������ʹ��&��ʾ���������֮�󣬱��������������Կ���ͬһ�����������Ҳ�����ռ���ڴ棬���ú�ԭ����ռ��һ���ڴ�
		�������Ǳ������ʵ���ϲ���ռ��ͬһ���ڴ�
		1����������ʱ������ʼ��
		2������ֻ�ܰ󶨵������У����ܰ󶨵�������

	������
		const�ؼ��֣���ʾ����
		const int var = 7;  // ��ʾ�ñ�����ֵ�����������ط��ı䣬����������
		constexpr �ؼ��֣�ֻ����C++11�б����ã� ��ʾ�ڱ����ʱ����ֵ�������������

*/

/*
	�Զ�����ת����ʾauto
*/
void test01() {
	auto bevalue = true;  // bool
	auto ch = 'a';  // char
	auto dv1 = 1.2;  //double
	auto dv2 = 1.2f;  //float
}

/*
	����ʾ��
*/
void test02() {
	int value1 = 1;
	int& refvalue = value1;  // value��������refvalue,&����ʾȡ��ַ��ֻ�����ʶ����
	cout << "ԭ�� value1 = " << value1 << endl;  
	cout << "���� refvalue = " << ++refvalue << endl;
	cout << "�������º��ԭ��" << value1 << endl;
}

/*
	���ú���ʾ��
*/
void swap(int& a, int& b) {  // �β����������ͣ��ı����ֵ��Ӱ�쵽���
	int tmp = a;
	a = b;
	b = tmp;
}

/*
	����ʾ��
*/

constexpr int sum_test() {
	int a = 1;
	int b = 2;
	return a + b;
}

void test03() {
	const int var = 7;
	cout << "��������var = " << var << endl;
	int& var2 = (int&)var;
	var2 = 18;
	cout << "var = " << var << endl;  // 7
	cout << "var2 = " << var2 << endl;  // 18  �ɴ˿ɼ�������ԭ������ռ��ͬһ���ڴ�

	constexpr int varable = sum_test();  //  ��ʾ�ڱ����ʱ����ֵ�������������
	cout << varable << endl;
	
}

int main() {

	/*
		ͷ�ļ�����ʾ��
	*/
	cout << g_value1 << endl;
	cout << g_value2 << endl;
	
	/*
		��������ʾ��
	*/
	test02();
	int a = 1, b = 2;
	cout << "����ǰ " << "a = " << a << " b = " << b << endl;
	swap(a, b);
	cout << "������ " << "a = " << a << " b = " << b << endl;

	/*
		��������ʾ��
	*/
	test03();

	system("pause");
	return 0;
}