#include<iostream>
#include<thread>
#include<string>

using namespace std;

/*
�����ڡ��̴߳�����⣬detach��ӣ���Ա�������̺߳���

1��������ʱ������Ϊ�̲߳���
	1.1 Ҫ��������壺
		�����߳������̷߳��룬�����߳���ǰ��������ô���õĵ�ַ�ͻᱻ���̻߳���
		��Ȼ����������ã�������Ȼ�Ƕ�mvar�ĸ��ƣ������ǰ�ȫ��
		��detachʹ��ʱ�����̴߳���ʱ���Ƽ�ʹ�����ã�Ҳ���Բ�����ʹ��ָ��

	1.2 Ҫ���������
		ֻҪʹ����ʱ�����A�������Ϊ�������ݸ��̣߳���ô��һ���ܹ������߳�ִ�����ǰ���Ϳ��Խ��ڶ�����������
		��ɣ�����detach�ˣ����߳�Ҳ�ǰ�ȫ��

	1.3 �ܽ�
		1��detachʱ��������int���ּ򵥵Ĳ��������鶼��ֵ���ݣ���Ҫʹ������
		2����ʹ�������ʱ��Ҫ������ʽ����ת����ȫ�����ڴ����߳�ʱ�͹�������ʱ�����ں������������������ӣ�
		   ����ϵͳ�ֻṹ���һ����������˷�
		�ռ����ۣ�
			��ò�Ҫʹ��detach��ֻʹ��join�������Ͳ����ھֲ�����ʧЧ�������̶߳��ڴ�ķǷ�Ӧ������

2����ʱ������Ϊ�̲߳���
	2.1 �߳�id
		ÿ���̶߳���Ӧ��һ��Ψһ�����֣���ͬ���̶߳��ڲ�ͬ��id�ǲ�ͬ�ģ�����ͨ���������к���ȥ��ȡ
		this_thread::get_id() ����ȡ

	2.2 ��ʱ������ʱ��ץ��

3���������������ָ����Ϊ�̲߳���
	std::ref����

4��ʹ�ó�Ա������ָ����Ϊ�̺߳���  operator()
		
*/



/*
	��Ϊ�̺߳���
*/
void myprint1(const int &i, char* pmybuf) {
	cout << i << endl;
	cout << pmybuf << endl;
	cout << "���߳�id = " << this_thread::get_id() << endl;
}

void myprint2(const int& i, const string& pmybuf) {
	cout << i << endl;
	cout << pmybuf.c_str() << endl;
	cout << "���߳�id = " << this_thread::get_id() << endl;
}

class A {
public:
	int m_i;
	// ����ת��������������Խ�intת��Ϊ��A����
	A(int a) :m_i(a) { cout << "���캯��ִ��" << endl; }
	
	A(const A& a) : m_i(a.m_i) { cout << "�������캯��" << endl; }

	~A() { cout << "��������" << endl; }

	void thread_work(int num) {
		cout << "���̵߳�thread_work��ʼִ����" << endl;
	}

	/*
		�̵߳���ں���
	*/
	void operator()(int num) {
		this->m_i = num;
		cout << "���̱߳�����" << endl;
	}
};


/*
	Ҫ���������
*/
void test01() {
	int mvar = 1;
	int& mvary = mvar;
	char mybuf[] = "this is a test";
	// ��Ȼ�����ﺯ���ӵ������ã������ڲ�ȷʵ��mvar�Ŀ���(ֵ����),�������߳��е�mvar�ᱻ���գ��������߳���Ȼ�ǰ�ȫ��
	// ��������ʹ��detach�ǰ�ȫ�ģ� ��Ȼ�������ǻ�������ʹ��detach
	// һ��Ҫ��ס����detachʹ��ʱ��ָ���Ǿ����������
	thread myobj(myprint1, mvar, mybuf);
	myobj.detach();
	cout << "Garrett" << endl;
}

/*
	����ӽ����е��ַ�����ֵ����
*/
void test02() {
	int mvar = 1;
	char mybuf[] = "this is a test";
	string str = "this is a str";
	/*
		mybuf��ʲôʱ��ת��Ϊstring��
		������������ִ����ϣ�����ʹ�����ֲ߳̾�����ʹ�������Ԥ�ϣ�����������ʽ����ת���Ļ����������ִ���Ŀ�����

		ֱ�ӽ�mybufת��Ϊstring���������Ϳ��Ա�֤���߳���һ������Ч����,�����߳�ִ�����֮ǰ�������Ѿ�������
		�ڴ����̵߳�ͬʱ������ʱ����ķ������ݲ����ǿ��е�
	*/
	thread myobj1(myprint2, mvar, string(mybuf));
	thread myobj2(myprint2, mvar, str);
	myobj1.join();
	myobj2.join();
	cout << "Garrett" << endl; 
}



/*
	�������д����Ƿ��������ʹ��Σ���ʵ���϶��ǿ����ʹ���
*/
void myprint3(A& pmybuf) {
	pmybuf.m_i = 199;  // �����޸ĸ�ֵ����Ӱ�쵽main�����е���ֵ
	cout << pmybuf.m_i << endl;
}

void test03() {
	/*
		����һ�������
	*/
	A myobj1(10);
	
	// thread mytobj1(myprint2, myobj1);  ���ִ��η�ʽ������ı����߳��е�A.m_i���

	/*
		��ʽ��ʾ������Ҫ�����߳��иı�A.m_i��ֵ���������߳������̵߳�������ͬ���ģ�����Ҫע�⣬��ʱ�Ͳ�����ʹ��detach
		�������Ϊ�����
		&myobj �ȼ��� ref(obj)��Ч��
		���ַ�ʽ˵�����ڴ����̵߳�ͬʱ���ٹ�����ʱ����ķ����ǿ��е�
	*/
	thread mytobj1(myprint3, ref(myobj1));
	mytobj1.join();
	cout << myobj1.m_i << endl;
}

/*
	�������Ϊ����ָ��
*/

/*
	����ָ��Ĵ��η�ʽ
*/
void myprint4(unique_ptr<int> pzn) {
	cout << *pzn << endl;
}

void test04() {
	unique_ptr<int> mvp(new int(100));  // ��ռʽ����ָ��
	// move����ռʽ����ָ��mvpת�Ƶ���ռʽ����ָ��pzn�У�ת�Ժ�mvp���ǿ���
	thread myobj2(myprint4, move(mvp));
	myobj2.join();
}

  
/*
	�������Ϊ��Ա��������Ҫ������������
*/
void test05() {
	// ����һ����A�Ķ���
	A myobj1(10);
	thread myobj3(&A::thread_work, myobj1, 15);
	myobj3.join();
}

///*
//	ʹ����д����������߳����,������������,ʹ�����������������Ϊ���̵����
//*/
void test06() {
	A myobj3(100);
	//thread mytobj2(myobj3, 15);
	thread mytobj2(ref(myobj3), 15); // ���ٵ��ÿ������캯������ʱ����ʹ��detach
	mytobj2.join();
	cout << myobj3.m_i << endl;
}

int main() {
	test06();
	//getchar();
	return 0;
}