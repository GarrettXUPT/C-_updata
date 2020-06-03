#include<iostream>

using namespace std;

/*
	һ��shared_ptr��ʹ�ó���
	
	����shared_ptr��������ȱ�ݣ�һ���ô�Ҳ��������
		1��������ָ��
			����Ҫ��ס����Ҫʹ����ָ������ʼ�����shared_ptr
		2������get���ص�ָ��
			��Զ��Ҫʹ��get�õ���ָ������ʼ������һ������ָ������Ǹ�����һ������ָ�븳ֵ
		3����Ҫ�������ָ��(this)��Ϊshared_ptr���أ�����enable_shared_from_this
			�����洴��CT���������ָ���Լ�ͨ��CT���󷵻ص�this����ָ�붼�ǰ�ȫ��
			enable_shared_from_this����һ����ָ��weak_ptr�������ָ����Լ���this
			�����ǵ���enable_shared_from_this����ʱ���ڲ�ʵ�����ǵ�����weak_ptr��lock����
			lock����shared_ptrָ��ļ�����һ��ͬʱ���Է���shared_ptr
		4������ѭ������
	��������˵��
		shared_ptr�ĳߴ�����ָ�������
		1����һ����ָ��ָ���������ָ����ָ��Ķ���
		2���ڶ�����ָ��ָ��һ���ܴ�����ݽṹ
			1.��ָ�����ǿ���ü�����shared_ptr
			2.��ָ����������ü�����weak_ptr
			3.�������ݣ����磺ɾ����ָ�롢�ڴ������
			�ÿ��ƿ����ɵ�һ��ָ��ĳ��ָ�������shared_ptr������
			���ƿ鴴����ʱ����
				1��make_shared�����䲢��ʼ��һ�����󣬷���ָ��˶����shared_ptr�����ԣ����make_shared�ܹ�����һ�����ƿ�
				shared_ptr p1 = make_shared_ptr<int>(100);
				2��ʹ����ָ�봴��һ��shared_ptr�������ʱ��
				int * p = new int(100);
				shared_ptr<int> p1(p);  ��ָ��ֻ�ܳ�ʼ��һ������ָ�룬ǧ��Ҫ��ʼ�����������ͻ���� 
		�ƶ����壺
			�ƶ�����Ҫ�ȸ��ƿ죬������Ҫ�������ü������ƶ�����Ҫ
			�ƶ����캯��������ƹ��캯�����ƶ���ֵ���������ƶ����������
	�ġ�����˵����ʹ�ý���
		����ʹ�ã���ֵ��÷���Ҫ���׳��ԣ�����ʹ��make_shared����������ָ�룬��Ϊmake_shared���кܶ��Ż����ڴ������Ч�ʱȽϸ�
			

*/


/*
	shared_ptr��ʹ�ó���
*/
shared_ptr<int>creat1(int value) {
	return make_shared<int>(value);
}

void myfunc1() {
	auto ptmp = creat1(100);
	return;  // �뿪�������Ժ�ptmp�ᱻ�Զ��ͷţ�����ָ����ڴ�Ҳ�ᱻ�Զ��ͷ�
}

shared_ptr<int> myfunc2(int value) {
	auto ptmp = creat1(value);
	return ptmp; // ���ظ���ʱ���� 
}

void test01() {
	// �ڴ˲�ʹ�ñ���������myfunc���صĽ������ô���ص�shared_ptr�ͻᱻ����,��ָ��Ķ���ͻᱻ����
	myfunc2(200);
}

/*
	������ָ��
*/
void proc(shared_ptr<int> ptr) {
	return;
}

void test02() {
	int* p = new int(100);  // ��ָ��
	//proc(p);  ��֧��int*p��shared_ptr����ʽ����ת��

	proc(shared_ptr<int>(p));   // ʹ����ָ��ת��Ϊshared_ptr��ʽ����ת����������һ����ʱ��shared_ptr����һ����ָ����ʽ�Ĺ�����ʱ����
	//*p = 45; // ��ʱ�����Ǳ�ڵģ�����Ԥ�ϵ����⣬��Ϊpָ����ڴ��Ѿ����ͷ���

	// ��Ҫʹ����ָ���ʼ����������ָ����в�������Ҳ��Ҫʹ�����·�ʽ
	shared_ptr<int> p1(p);
	proc(p1);  
	//*p = 45;	// ��ʱ��ʹ�÷�ʽҲ���ǰ�ȫ�ģ���һ����ͨ��ָ�룬��shared_ptr�ϣ���ô�ڴ��������ξͽ�����shared_ptr���Ͳ�Ӧ��ʹ����ָ���������ڴ�
	//cout << *p << endl;   // 45

	shared_ptr<int> p3(new int(200));  // ����ʹ�÷�ʽ�ǰ�ȫ��
	proc(p3);
	*p3 = 250;  
	cout << *p3 << endl;
	// ����Ҫ��ס����Ҫʹ����ָ������ʼ�����shared_ptr

	/*
		����ʾ��
		��Ӧ��p4 p5��ָ��ͬһ���ڴ�飬�������ڵĽ�������Ƿֱ�ָ��ͬ���ڴ棬���³���
	*/
	/*int* pi = new int(100);
	shared_ptr<int>p4(p);
	shared_ptr<int>p5(p);*/

	shared_ptr<int> p4(new int);
	shared_ptr<int> p5(p4);  // ����д����OK�ģ�p1��p2ָ��ͬһ���ڴ��ַ���������ǻ�ͨ��(�õ���ͬһ�����ƿ�)
}

/*
	����get���ص�ָ��
	get:���ص�������ָ������Ӧ����ָ�룬���ص�ָ���ǲ�����delete�ģ�����ͻ��쳣
	���ۣ�
		��Զ��Ҫʹ��get�õ���ָ������ʼ������һ������ָ������Ǹ�����һ������ָ�븳ֵ
		�����ķ�ʽ����ʹ������ָ���ʼ������ָ��;���û������
*/
void test03() {
	shared_ptr<int> myp(new int(100));
	int* p = myp.get();	  // ��ָ�벻�������ͷţ�����myp���޷����������ָ��
	// ���ܽ���������ָ��󶨵�get���ص�ָ����
}

/*
	��Ҫ�������ָ��(this)��Ϊshared_ptr���أ�����enable_shared_from_this
	�����洴��CT���������ָ���Լ�ͨ��CT���󷵻ص�this����ָ�붼�ǰ�ȫ��
	enable_shared_from_this����һ����ָ��weak_ptr�������ָ����Լ���this
	�����ǵ���enable_shared_from_this����ʱ���ڲ�ʵ�����ǵ�����weak_ptr��lock����
	lock����shared_ptrָ��ļ�����һ��ͬʱ���Է���shared_ptr
*/
class CT : public enable_shared_from_this <CT>{
public:
	shared_ptr<CT> getself() {
		//return shared_ptr<CT>(this);  ���ַ�ʽ������ָ���γ�ʼ��������ָ��
		// ʹ��C++��׼���е���ģ��,Ҫ�ǵ�զ����̳�enable_shared_from_this�������������ʹ��ݽ�ȥ
		return shared_from_this();
	}
};

void test04() {
	shared_ptr<CT> pct1(new CT);
	shared_ptr<CT> pct2(pct1);  // ��������ǿָ��

	/*
		��ʼ������ָ��
	*/
	shared_ptr<CT> pct3 = pct1->getself();  // ��Ա�������ص���this���ͻ�������⣬Ӧ��������ʹ��enable_shared_from_this�Ϳ���
	
}

/*
	�ƶ�����
	�ƶ�����Ҫ�ȸ��ƿ죬������Ҫ�������ü������ƶ�����Ҫ
	�ƶ����캯��������ƹ��캯�����ƶ���ֵ���������ƶ����������
*/
void test05() {
	shared_ptr<int> p1(new int(100));
	shared_ptr<int> p2(std::move(p1));  // �����ƶ�����ᵼ��p1����ָ��ö������ü������ɻ���һ

	shared_ptr<int> p3;
	p3 = std::move(p2);  // �ƶ���ֵ������p2ָ��գ�p3ָ��ԭ�����ڴ棬���ü�������һ
}

/*
	����ʹ��make_shared
*/
void test05() {

	shared_ptr<string> ps1(new string("Garrett"));  // ���ַ�ʽ����������ڴ�

	auto ps2 = make_shared<string>("Garrett");  // ֻ�����һ���ڴ�
}

int main() {
	test04();
	return 0;
}