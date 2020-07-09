
#include<iostream>

using namespace std;

/*
	�ڴ�߼�����
	1��new
		1.new������ʱ�򣬼Ӳ���������ɶ���
			a����Ϊ���࣬����д��û��������ʵ�в�����ֻдһ������
			b�������д��ڳ�Ա����:�����ŵĳ�ʼ����ʽ�ὫһЩ���Ա�����йص��ڴ����㣬���ǲ�������������ڴ�ȫ������
			c���������й��캯��:����д���õ��Ľ����һ���ģ�Ҳ��ûɶ���
			d�����������麯�������������г�Ա�����Ľ����ͬ��һ�������㣬��һ���������ֵ�������д����麯������ô���������Զ�����Ĭ�Ϲ��캯��
			e������ȥ�ĸо���û��ɶ����
		2��new������(�˴�����ʾ��new/malloc delete/free������)
			new��һ���ؼ���/����������Ҫ���ã�����operator new������������A�Ĺ��캯��
			A* pa1 = new A();
				operator new();����
					_malloc();�����ڴ�
				A::A();��������A�Ĺ��캯��,���������й��캯��������ã���û�У��򲻵��ã�����������������Ҳ��Ҫ����

			delete pa1;  // delete������new�����෴
				A::~A();
				operator delete();
					free();
		3��malloc������
			�����ڴ�

	new��ϸ�ڡ��������ڵ�operator new��delete
		1��new�ڴ����ϸ��
			һ���ڴ�Ļ��գ�Ӱ��ķ�Χ�ܹ㣬ԶԶ��ֹ����Ŀռ���ô��
			new/delete�ڲ�ʹ�õ���malloc/free�����ǽ�����mallco/freeҲ�Ǻܸ��ӵ�
			�����ڴ��ʱ��Ϊ�˼�¼�͹�������ȥ���ڴ棬���Զ�����˺ܶ��ڴ棬����˷ѣ������Ƕ������С���ڴ棬��ɵ��˷Ѹ������ԣ���������
		2���������е�operator new/delete
			���ֲ����������ǿ��������м�ͳ��������Ҫ������
		3���������е�operator new[]/delete[]
			
			
			
*/

class A {
public:
	A() { cout << "�����˹��캯��" << endl; };
	~A() { cout << "��������������" << endl; };
	/*
		����operator new
	*/
	static void* operator new(size_t size);
	/*
		����operator delete
	*/
	static void operator delete(void* phead);

	/*
		����operator new[]
	*/
	static void* operator new[](size_t size);
	/*
		����operator delete[]
	*/
	static void operator delete[](void* phead);


private:
	int m_i;
};

void* A::operator new(size_t size) {
	A* ppoint = (A*)malloc(size);
	cout << "����new" << endl;
	return ppoint;
}

void A::operator delete(void* phead) {
	cout << "����delete" << endl;
	free(phead);
}

void* A::operator new[] (size_t size) {
	A* ppoint = (A*)malloc(size);
	cout << "����new[]" << endl;
	return ppoint;
}

void A::operator delete[](void* phead) {
	cout << "����delete[]" << endl;
	free(phead);
}


/*
	1.new������ʱ�򣬼Ӳ���������ɶ���
*/
void test01() {
	A* pa1 = new A();
	A* pa2 = new A;
	// ....
	// һ���ڴ�Ļ��գ�Ӱ��ķ�Χ�ܹ㣬ԶԶ��ֹ����Ŀռ���ô��
	delete pa1;

	/*
		������
	*/
	int* p1 = new int();  // ��ֵΪ��
	int* p2 = new int;  // ��ֵ���
	int* p3 = new int(100);  // ��ֵΪ100
}

void test02() {
	char* cpoint = new char[10];
	memset(cpoint, 0, 10);  // ��10���ֽڽ�������
	delete[] cpoint;

	// �ڴ˴������ڴ��ʱ�򣬲����Ǽ򵥵ķ����4���ֽڣ���������4���ֽ���Χ�����������˺ܶദ��(��¼�����ȥ���ֽ�����)
	int* ipoint = new int(10);  // �˴��ڲ���¼�˷����ڴ�Ĵ�С
	delete ipoint;  
}


void test03() {
	/*
		����operator new
	*/
	void* temp = operator new(sizeof(A));
	A* pa = static_cast<A*>(temp);
	pa->A::A();

	/*
		����operator delete
	*/
	pa->A::~A();
	operator delete(pa);
}

/*
	�������غ��new/delete
*/
void test04() {
	A* pa = new A();
	delete pa;

	/*
		����ϵͳ��new/delete
	*/
	A* pa2 = ::new A();
	::delete pa2;  // ::ȫ�ֲ�����������ϵͳ��new/delete
}

void test05() {
	/*
		 ����ʹ�õ��������operator new[]/delete[],�����ǵ�������ķ��亯��
		 ���캯�����������������������Σ�����operator new[]/delete[]������������һ��
	*/
	A* pa = new A[3]();
	delete[] pa;
}

int main() {
	test05();
	return 0;
}