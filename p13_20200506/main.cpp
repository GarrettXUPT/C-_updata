#include<iostream>
#include"Time.h"
using namespace std;

/*
	һ������صķǳ�Ա����

	�������ڳ�ʼ��
		��C++11�п���Ϊ���ڵĳ�Ա�����ṩ��ʼֵ����ô�����ڴ��������ʱ�򣬾Ϳ���������ʼ����Ա����
	
	����const��Ա�����ĳ�ʼ��

	�ġ�Ĭ�Ϲ��캯��
		���������Ĺ��캯��������Ĭ�Ϲ��캯��
		û�й��캯�������������Զ����㲹��һ��Ĭ�Ϲ��캯������ΪĬ�ϳ�ʼ��
		���г�ʼ�����򽫳�ʼ����������û�г�ʼ���������Ա����������ֵ
		�������е��������࣬��ô�Ͳ���ʹ��Ĭ�ϳ�ʼ����
		�������Լ�д�˹��캯������ô�������Ͳ�����Ϊ���Ǵ���Ĭ�Ϲ��캯��

	�塢=default��=delete
		C++11�������
		������Ϊ����=default�ĺ����Զ����ɺ�����,�൱�ڴ�����һ��Ĭ�Ϲ��캯����������ĺ�������ʹ��=default
		=delete�����ã���ֹĳ������
*/


int main() {
	Time time(11, 11, 11);
	printObj(time);
	cout << time._value << endl;  // 10

	system("pause");
}