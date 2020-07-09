#include<iostream>

using namespace std;

/*	Ƕ��ʽָ�����������ڴ�ظĽ���
	һ��Ƕ��ʽָ�����
		����ָ��һ��Ӧ�����ڴ����صĴ����У��ɹ�ʹ��Ƕ��ʽָ���ǰ����������A�����sizeof���벻С���ĸ��ֽ�
		����ԭ������A������ռ�ڴ���ڴ�ռ��ǰ�ĸ��ֽڣ����ĸ��ֽ�������ס��Щ���е��ڴ��
				  ����ĳһ��һ���������ȥ����ô�ÿ��ǰ�ĸ��ֽھͲ���Ҫ�ˣ���ʱ���ĸ��ֽڿ��Ա�����ʹ��

	����Ƕ��ʽָ����ʾ
		����4���ֽڵ��࣬�Ϳ��԰�ȫ��ʹ��Ƕ��ʽָ�룬�������ڴ棬������п�

	�����ڴ�ش���ĸĽ�
		�������ڴ�ؼ�����

*/

/*
	�ڴ��ʵ����
*/
class MyAllocator {  // ʹ�ø���ʱ�����뱣֤Ӧ�ñ�������sizeof()������4���ֽڣ���������
public:
	/*
		�����ڴ�ӿ�
	*/
	void* allocate(size_t size);
	/*
		���ز�����delete
	*/
	void deallocate(void* phead);


private:
	struct obj{
		struct obj* next;  // Ƕ��ʽָ��
	};
	int m_sTrunkCount = 0;
	obj* m_free_pos = nullptr;
};


void* MyAllocator::allocate(size_t size) {
	obj* tmplink;
	if (m_free_pos == nullptr) {
		// Ϊ�� ������һ����ڴ�
		size_t realisize = m_sTrunkCount * size;  // ����m_sTrunckCount��ô�౶���ڴ�
		m_free_pos = (obj*)malloc(realisize);  //  �˴���newʹ�õ���ϵͳ�ײ��malloc����ϵͳ�Դ���new
		tmplink = m_free_pos;
		/*
			�����������һ���(��С��)�ڴ�˴�Ҫ��������������ʹ��
		*/
		for (int i = 0; i < m_sTrunkCount - 1; i++) {
			tmplink->next = (obj*)((char*)tmplink + size);
			tmplink = tmplink->next;
		}
		tmplink->next = nullptr;
	}
	tmplink = m_free_pos;
	m_free_pos = m_free_pos->next;
	return tmplink;
}

void MyAllocator::deallocate(void* phead) {
	((obj*)phead)->next = m_free_pos;
	m_free_pos = (obj*)(phead);
}


/*
	Ƕ��ʽָ����ʾ
*/
class B {
public:
	int m_i;
	int m_j;
public:
	// Ҳ���Խ��ýṹ��������⣬���������Ļ������ĳ�ԱҲ�Ϳ��Է����������Է������ڿ������Ƹýṹ���������Χ
	struct obj
	{
		// ��Ա�Ǹ�ָ�룬����ָ��ýṹ��next���Ǹ�Ƕ��ʽָ�룬�Լ���һ��obj���󣬽��Լ������nextָ��ָ����һ��obj�ṹ�������ս��Լ�����
		// �Ķ���ṹ�崮��һ��
		struct obj* next;
	};
};

/*
	Ƕ��ʽָ��ʹ��
*/
void test02() {
	B mB;
	cout << sizeof(mB) << endl;

	B::obj* ptmp; // ����һ��ָ��
	ptmp = (B::obj*)&mB;  // ��ָ��ָ��mB���׵�ַ
	cout << sizeof(ptmp) << endl;  
	cout << sizeof(ptmp->next) << endl;  // ��ʱptmp��ptmp->nextָ��Ķ���mB���׵�ַ
	ptmp->next = nullptr;  // ������mB8���ֽڵ�ǰ4���ֽ�
}


/*
	�ڸ�����ʹ���ڴ����,��ʱ���Ǹ���ʹ���ڴ�ط����ڴ�
*/
class C {
public:
	int m_i;
	int m_j;
public:
	static MyAllocator myalloc;  
	static void* operator new(size_t size) {
		return myalloc.allocate(size);
	}

	static void  operator delete(void* phead) {
		return	myalloc.deallocate(phead);
	}
};
MyAllocator C::myalloc; // ���徲̬��Ա����

void test03() {
	C* mypa[100];
	for  (int i = 0; i < 15; ++i) {  // ++i�����ٲ���һ���м����
		mypa[i] = new C();
		cout << mypa[i] << endl;
	}

	for (int i = 0; i < 15; i++) {
		delete mypa[i];
	}

}

int main() {
	test03();
	return 0;
}