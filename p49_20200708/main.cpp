#include<iostream>
#include<ctime>

using namespace std;

/*
	�ڴ�ظ������ʵ�ֺ���ϸ����
	һ���ڴ�صĸ����ʵ��ԭ�����
		malloc:������ڴ��˷ѣ�Ƶ���ķ���С���ڴ��ʹ�˷Ѹ�������
			1���ڴ�ؾ��ǿ��Լ��������ڴ���˷ѣ�ͨ������malloc�ĵ��ô���
			2�����ٵĵ��ô���������һЩ�ٶȺ�����Ч���ϵ���������������������
		�ڴ�ص�ʵ��ԭ��
			1����malloc����һ����ڴ棬����Ҫ�����ڴ��ʱ�򣬾�һ��һ��Ľ��ڴ�����ȥ����һ����ڴ�������ʱ��
			   ��ʹ��malloc����һ���ڴ棬��һ��һ��ķ����ȥ
			2�����ڵĸ������Ǽ����ڴ��˷ѣ��������Ч��
	
	�����ڴ��ʵ����ʾ����
		���һ������ڴ�ص�ʵ�֣�ʹ���ڴ����ʵ��new/deleteһ������

	�����ڴ�ش������˵��
		���ڴ���ͷ��ڴ��ʱ�򣬲����������Ĺ黹��ϵͳ�����ǷŻص��ڴ����


*/

class A {
public:
	/*
		���ز�����new
	*/
	static void* operator new(size_t size);
	/*
		���ز�����delete
	*/
	static void operator delete(void* phead);

	/*
		ͳ�Ʒ����ڴ�Ĵ���
	*/
	static int m_count;
	/*
		mallocʹ�ô���ͳ��
	*/
	static int malloc_count;
private:
	A* next; // 
	static A* m_free_pos;  // ����ָ��һ����Է����ȥ���ڴ���׵�ַ
	static int m_sTrunkCount;  // һ�η�����ٱ��ĸ����ڴ�
};
int A::m_count = 0;

int A::malloc_count = 0;

A* A::m_free_pos = nullptr;

int A::m_sTrunkCount = 50; // һ�η����屶���ڴ���Ϊ�ڴ�صĴ�С

void* A::operator new(size_t size) {
	A* tmplink;
	if (m_free_pos == nullptr) {
		// Ϊ�� ������һ����ڴ�
		size_t realisize = m_sTrunkCount * size;  // ����m_sTrunckCount��ô�౶���ڴ�
		m_free_pos = reinterpret_cast<A*>(new char[realisize]);  //  �˴���newʹ�õ���ϵͳ�ײ��malloc����ϵͳ�Դ���new
		tmplink = m_free_pos;
		/*
			�����������һ���(��С��)�ڴ�˴�Ҫ��������������ʹ��
		*/
		for (; tmplink != &m_free_pos[m_sTrunkCount - 1]; tmplink++) {
			tmplink->next = tmplink + 1;
		}
		tmplink->next = nullptr;
		malloc_count++;
	}
	tmplink = m_free_pos;
	m_free_pos = m_free_pos->next;
	m_count++;
	return tmplink;
}

void A::operator delete(void* phead) {
	static_cast<A*>(phead)->next = m_free_pos;
	m_free_pos = static_cast<A*>(phead);
}

void test01() {
	clock_t start, end;
	start = clock();
	for (int i = 0; i < 500'0000; i++) {
		A* pa = new A();
	}
	end = clock();
	cout << "�����ڴ����Ĵ�����" << A::m_count << endl;
	cout << "ʵ��malloc�Ĵ���Ϊ��" << A::malloc_count << endl;
	cout << "�ù�����ʱ(ms)��" << end - start << endl;
}

int main() {
	test01();
	return 0;
}