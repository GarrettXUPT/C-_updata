#include<iostream>
#include"ca.h"

/*
	��ʽʵ�����ֶ��е�ʵ�������壬����ʵ��������ֻ��Ҫ��һ��.cpp�ļ��оͿ���
	����������������룬��ֱ��ʵ��������һ��A<float>�࣬���ٴ��뿪��
	����ʵ���������ʵ����������ģ������г�Ա����
*/
template A1<float>;
/*
	��������Ϊ�����ɴ���
*/
template int MyAdd(int v1, int v2);

void test03() {
	A1<float> a(1, 2);
}

