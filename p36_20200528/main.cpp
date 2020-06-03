#include<iostream>
#include<string>

using namespace std;

/*
	һ��unique_ptr����
		��һ�ֶ�ռʽ������ָ�룬�Զ�����ר������Ȩ��ͬһʱ�̣�ֻ����һ��unique_ptrָ��ö���
		��unique_ptr������ʱ������ָ��Ķ���Ҳ�ᱻ����
		��ʽ��
			unique_ptr<ָ��Ķ�������> ָ���������
		1�������ʼ��(unique_ptr��new�໥���)
		2��make_unique����
	����unique_ptr�������
		1��unique_ptr��֧�ֵĲ���
			��������ָ��ָ��һ�����󣬲�����ֵ�������Ĳ���
		2���ƶ�����

		3�����и��ַ�������
			
*/

/*
	�����ʼ��
*/
void test01() {
	unique_ptr<int> p1;  // ��ʾһ��ָ��int����Ŀ�����ָ��
	if (p1 == nullptr) {
		cout << "������ָ��Ϊ��ָ��" << endl;
	}
	unique_ptr<int> p2(new int(105));  // unique_ptrָ����һ��ֵΪ105��int����
}

/*
	ʹ��make_unique������ʼ������C++11��û�У�������C++14���У�Ҳ���Ż�������ָ������������֧��ָ����ɾ�����﷨��
	�������Լ�����ɾ��������ô����ѡ��make_unique��������ָ��
*/
void test02() {
	auto p1 = make_unique<int>(100);
	cout << *p1 << endl;
}

/*
	unique_ptr�������
*/
void test03() {
	/*
		�ƶ�����
	*/
	unique_ptr<string> ps1(new string("Garrett"));
	
	// ��ps1�Ķ����ƶ���ps2��
	auto ps2 = std::move(ps1);

	/*
		release�������Զ���Ŀ���Ȩ���ж�������ָ�������ָ�����֮�����ϵ�����ص���ָ��������ָ�룬
		ͬʱ������ָ���ÿգ����ص���ָ������ֶ�delete���ͷ�(����ʹ�þ͵��ͷţ�����ᵼ���ڴ�й©)��
		Ҳ����������ʼ������һ����ָ�룬���߸�����һ������ָ�븳ֵ
	*/
	auto ps3 = make_unique<int>(200);
	unique_ptr<int> ps4(ps3.release());
	if (ps1 == nullptr) {
		cout << "ps1���ÿ�" << endl;
	}
	cout << *ps4 << endl;  // 200
	// �ֶ�delete�ͷ�
	int* p = ps4.release();
	delete p;
	/*
		reset��
			����������ʱ���ͷ�����ָ����ָ��Ķ��󣬲�������ָ���ÿ�
			��������ʱ���ͷ�����ָ����ָ��Ķ��󣬲�������ָ��ָ���¶���
	*/
	auto ps5 = make_unique<int>(400);
	ps5.reset();
	if (ps5 == nullptr) {
		cout << "ps5�Ѿ�Ϊ��" << endl;
	}

	// �������������ȷ���������ڴ�й©
	auto ps6 = make_unique<string>("garrett");
	auto ps7 = make_unique<string>("walker");
	ps6.reset(ps7.release());  // reset�ͷ�ps6��ָ��Ķ����ڴ棬��ps7ָ��ps6ָ��Ķ���ͬʱps7���ÿ�
	cout << *ps6 << endl;  // walker
	
	/*
		= nullptr�ͷ�����ָ����ָ��Ķ��󣬲�������ָ���ÿ�	
	*/
	auto ps8 = make_unique<int>(500);
	ps8 = nullptr;  // �ͷ�ps8ָ��Ķ��󣬲���ps8�ÿ�
	
	/*
		ָ��һ������
	*/
	unique_ptr<int[]> psarr1(new int[10]);  // ָ��һ�����������ָ��
	for (int i = 0; i < 10; i++) {
		psarr1[i] = i;
	}
	for (int i = 0; i < 10; i++) {
		cout << psarr1[i] << " ";
	}
	cout << endl;

	/*
		get����������ָ�������������ָ��
	*/
	auto ps9 = make_unique<string>("Garrett");
	string* pstr = ps9.get();
	*pstr = "Walker";
	cout << *pstr << endl;
	// ǧ��Ҫdelete pstr;
	
	/*
		*�����ã�������ָ��ָ�������ʱ�򣬾Ͳ�����ʹ��*���н�����	
	*/

	/*
		swap��������������ָ����ָ��Ķ���
	*/
	auto pstr1 = make_unique<string>("Garrett");
	auto pstr2 = make_unique<string>("Walker");
	cout << "pstr1 = " << *pstr1 << " pstr2 = " << *pstr2 << endl;
	pstr1.swap(pstr2);
	cout << "pstr1 = " << *pstr1 << " pstr2 = " << *pstr2 << endl;

	/*
		����ָ��������Ϊ�ж�����
	*/
	auto pstr3 = make_unique<string>("China");
	if (pstr3) {
		cout << "��ָ�벻Ϊ�գ��ɽ�����ز���" << endl;
	}
}


/*
	ת��Ϊshared_ptr����unique_ptrΪ��ֵ��ʱ�򣬾Ϳ��Խ�������shared_ptr
	��Ϊshared_ptr����һ����ʽ�Ĺ��캯�������Խ�unique_ptrת��Ϊshared_ptr��
	shared_ptr��ӹ�ԭ��unique_ptr������Ķ���
*/

auto myfunc() {
	return unique_ptr<string>(new string("Garrett")); // ��ʱ��������ֵ
}

void test04() {
	shared_ptr<string> pstr1 = myfunc();  // ��unique_ptrת��Ϊshared_ptr

	unique_ptr<string> ps(new string("Garrett"));
	shared_ptr<string> pstr2 = std::move(ps);   // ����������ֵ��psת�Ƶ���ֵ
}

int main() {
	test03();
	return 0; 
}