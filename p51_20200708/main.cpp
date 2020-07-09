#include<iostream>

using namespace std;

/*
	һ������ȫ��operator new/delete������
		һ�㲻����ô������������Ҳ������operator new/delete����ô�������صĺ����ͻḲ�ǵ�ȫ�ֵ����غ���

	������λnew(placement new)
		��placement new������û��palcement delete
		���ܣ����Ѿ������ԭʼ�ڴ��г�ʼ��һ������
			  1���Ѿ����䣬��λnew���������ڴ棬��Ҫ��ǰ����λnew����Ҫ���ڴ�������
			  2����ʼ��һ������Ҳ���ǵ��øö���Ĺ��캯��
			  ��λnew������һ��Ԥ�ȷ���õ��ڴ��ַ�й���һ������
		��ʽ��
			new (�Ѿ������ڴ���׵�ַ) ������()
		
*/

/*
	����ȫ�ֵ�operator new/delete
*/
void* operator new(size_t size) {
	return malloc(size);
}

void* operator new[](size_t size) {
	return malloc(size);
}

void operator delete(void* phead) {
	free(phead);
}

void operator delete[](void* phead) {
	free(phead);
}

class A {
public:
	A() { cout << "������A�Ĺ��캯��" << endl; }
	~A() { cout << "������A����������" << endl; }

public:
	void* operator new(size_t size) {
		A* ppint = (A*)malloc(size);
		return ppint;
	}

	void operator delete(void* phead) {
		free(phead);
		phead = nullptr;
	}
	
	/*
		���ض�λnew
	*/
	void* operator new(size_t size, void* phead) {
		return phead;   // ��Ϊ�յ������ڴ�Ŀ�ʼ��ַ����ô����ֱ��ԭ�����ؾ���
	}
};

void test01() {
	int* pint = new int(12);
	delete pint;

	char* pchar = new char[10];
	delete[] pchar;

	A* pa1 = new A();
	delete pa1;

	A* pa2 = new A[2]();
	delete[] pa2;
}


/*
	��λnew��ʹ��
*/
class B {
public:
	int m_a;
	B(int i_a) :m_a(i_a) {};
	B() { m_a = 0; };
	~B() {};
};

void test02() {
	/*
		���ڴ����ȷ������
	*/
	void* mymempoint = (void*)new char[sizeof(A)];
	/*
		������ڴ��г�ʼ��һ���������ﲢ�����������ڴ�
	*/
	B* pmyobj1 = new(mymempoint) B(12);

	/*
		�ͷ��Ѿ���ʼ���Ķ���,�ֶ��������������ǿ��Եģ����ǻ�û�м����ֶ����ù��캯��
	*/
	pmyobj1->~B();

	/*
		�ͷ��ڴ�
	*/
	delete[] pmyobj1;
}

/*
	���ְ汾��operator new/delete
*/


int main() {
	test02();
	return 0;
}