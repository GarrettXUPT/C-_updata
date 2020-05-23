#include<iostream>
#include<string>
#include<vector>

using namespace std;

/*
	һ��ֱ���ڴ����
		new�����Ķ����ڶ��ϣ�new���ַ��䷽ʽ�Ƕ�̬����(�����ڶ���)��ֱ���ڴ����new delete
		new��delete˵����
			new��deleteҪ�ɶ�ʹ�ã�delete����һ��ʹ��new������ڴ�(�ͷ��ڴ�),���ڴ����¹黹��ϵͳ
			������new�������ڴ棬������ʹ��delete�ͷţ�����ͻᱨ�쳣
			new�������ڴ棬ֻ�ܱ�deleteһ�Σ����ɶ��delete���ظ��ͷ�Ҳ�������쳣��delete������ڴ�Ͳ����Ա�ʹ����
			��ָ����Ա��ͷŶ�Σ����ǲ�û��ɶ����
		ע�����
			1��new�������ڴ�ǧ��Ҫ����delete�������ڳ��������£�����ͻ����
			2��delete���ڴ治����ʹ�ã�����ᱨ���쳣
			3��delete���ټ���pci = nullptr����ʾҲȷ����ָ�벻ָ���κε�ַ��
			4��һ���ڴ治�ܱ��ظ��ͷţ�ʹ��new��deleteһ��ҪС��
		C++11��ʼ��������ָ�룬new��������delete������ָ������Զ�delete

	���������¹��̣��۲��ڴ�й©
		MFCӦ�ó��򣬿�����һ���̶���(�ڳ����˳���ʱ��)�������Ƿ����ڴ�й©
		MFC��΢��˾����һ�����������ܣ��ص㣺��������һ�������ڽ���ĳ����ܣ�MFC���˽��濪������ 

	����new/delete
		1��ʲô��new��delete��
			sizeof(�ؼ���/�����)�������Ǹ���������ռ�õ��ֽ���
			new/deleteҲ�ǹؼ���/����������Ǻ���
			malloc/free��Ҫ����C���Ա���У�new/delete����C++��̣������߶��������ڶ��Ͻ��ж�̬�ڴ����
			malloc/free��new/delete������
				1��new/delete��malloc/free����˸���Ĺ�����new���������ڴ棬������һЩ��ʼ��������delete�������ͷ��ڴ棬�������һЩ������
				2��newһ�������ϵͳ����ø���Ĺ��캯����deleteһ��������ʱ��ϵͳ����������������
				3��new/delete�߱��Զ�����������ڴ���г�ʼ��/�ͷŵ���������Щ��malloc/free�����߱���
		
		2��operator new()��operator delete()
			������ֵ�operator new()��operator delete()�ⶼ�Ǻ���
			new��ɵĹ�����
				1�������ڴ棺����ͨ��operator new()�������ڴ�
				2��������Ĺ��캯������ʼ���ڴ�
			delete��ɵĹ�����
				1��������������
				2���ͷ��ڴ棺����operator delete()�ͷ��ڴ�
		
		3������new��μ�¼������ڴ��С��deleteʹ��
			��ͬ�ı�����new�ڲ����в�ͬ��ʵ�ַ�ʽ
			int* p = new int;  // ����ϵͳ����4���ֽ�
			delete p;		// �ͷ��ڴ��ʱ��ȷ���ͷ�4���ֽڣ�������Ϊ��new���ڲ����м�¼����
		
		4��������ͷ�����
			�˴���ʾ��memory_debug�У��˴�����Ҫע����ǣ����ǳ�ʼ��һ�����࣬Ҳ��ռ��һ���ֽڵ��ڴ�
			/
				��������û�й��캯�������Բ���Ҫ������ڴ��¼
			/
			int* p = new int[2];  // �����ڴ������Ϊ2�����飬��8���ֽ�
			�淶�ͷŴ��� delete[] p;
			/
				�ô��������ι��캯��
				��newһ�������ʱ��ϵͳ�Ὺ���ڴ��¼����Ԫ�صĸ���
			/
			A* pa = new A[2]();  
			/
				�ô�����������������
			/
			delete[]pa;    // �淶�ͷ������ڴ�

		5��Ϊʲônew/delete��delete[]/new[]Ҫ���ʹ��
			�������Ͳ���Ҫ������������������new�����ʱ��ϵͳ��û�ж����4�ֽڳ���������delete��Ȼ������ȷ���ͷ��ڴ�
			���ۣ�
				����һ������ʹ��new[]�������ڴ棬ȴʹ�õ�����delete������delete[]���ͷ��ڴ棬����������������������ʹ��delete[]��
					1��������������������
					2�����Զ��������������ڷ����ڴ�ʱ��ϵͳ��û��ʹ��4���ֽ�����¼�����Ϣ
				new�����Ķ�����Ҳǧ��Ҫʹ��delete[]����ʽ���ͷţ�����ϵͳ����ֲ���Ԥ�����Ϊ
				new/delete��new[]/delete[]һ��Ҫ���ʹ��

	��������ָ������
		new��delete��д��Ҫʮ��С�ģ���ֹ�����ͷŻ����������ͷ�
		ֱ��ʹ��new���ص�ָ�������ָ��(δ�����κΰ�װ)������ָ��ǿ�������ǿ�����Ҫȫ��ά����һ��С�ľ����׷���
		����ָ����ǿ��Խ����ָ������ĸ�������
		����ָ���Ƕ���ָ������˰�װ������ָ����������˰�װ����װ��Ϊ���Ǵ������ŵ㣺
			��ͻ�����ŵ��������ָ����� �Զ��ͷ� ��ָ�������ڴ�
		��������ʹ������ָ�룺ʹ������ָ��ĳ�������ױ�д�͵���
		C++��׼��������������ָ�룺�������Ƕ�̬���������������ڹ�������Ч��ֹ�ڴ�й©
			1��auto_ptr Ŀǰ��ȫ��unique_ptr�����C++11�з���ʹ��auto_ptr(����)
			2��unique_ptr
			3��shared_ptr
			4��weak_ptr
		��������ָ�붼����ģ�壬���ǿ��Խ�new��õĵ�ַ��ֵ�����ǣ���Ҫ�ĺ����ǣ�
			1��shared_ptr(����ʽָ�룺���ָ��ָ��ͬһ���������һ��ָ�뱻����ʱ��ָ��ᱻ�ͷ�)��weak_ptr����shared_ptr
			2��unique_ptr��ռʽ��ָ�룬ͬһʱ����ֻ��һ��ָ�����ָ��ö��󣬵�Ȼ�ö��������Ȩ�ǿ����ƽ���ȥ��
		����������delete��ʱ������ָ���������delete������˵������ѹ���Ͳ�����Ҫdelete������ָ��ı��־��ǰ�������delete

	����shared_ptr��������������Ȩ
		���Ǳ�һ��shared_ptrӵ�У����Ǳ����shared_ptr֮���໥Э��
		��ʹ�õ�ʱ��Ҫ���ǣ�ָ��ָ��Ķ����Ƿ���Ҫ����������Ҫ��unique_ptrָ��Ҫ��
		����ԭ�����ü�����ÿ��shared_ptr�Ŀ�����ָ����ͬ���ڴ棬����ֻ�����һ����ָ����ڴ��shared_ptrָ�벻��Ҫָ��ö����ʱ��
				  ��ȥȥ�ͷ�ָ��Ķ������һ��ָ��ö����shared_ptr�ͷŵ�ʱ�������֣�
							1�����shared_ptr������ʱ��
							2��shared_ptrָ����������ʱ
				 �е��������������ջ��ƣ����ǲ�����Ҫ���Ķ���ú�ʱ��delete
		��Ϊ����ģ�壬�����õ�<>,<>�����ָ��ָ������ͣ������ټ�������ָ����
		��ʽ��shared_ptr<ָ�������> ����ָ����
			shared_ptr<int> pi; ָ��int������ָ�룬����Ϊpi������ֻ��Ϊ�գ��Ǿ��ǿ�ָ��
		
		make_shared������
			��һ����׼����ĺ���ģ�壬����Ϊ�Ǹ�Ч��ȫ�ķ����ʹ��shared_ptr���������ڶ��з��䲢��ʼ������Ȼ�󷵻ش˶����shared_ptr


			
			


*/

class A {
public:
	A() {
		cout << "��A���󱻴���" << endl;
	}
};

void func() {
	/*
		��ʱ������ջ��
	*/
	int i = 5;
	/*
		�ֲ���̬�����ھ�̬�ڴ���
	*/
	static int j = 2;

	//A a;  // �����������Ǵ������Զ�����
	// �����������Ҫ�����Լ��������٣������������������Щ����

	/*
		��ʼ����̬����Ķ���
	*/
	int* point = new int;  // �˴���ֵδ����
	cout << *point << endl;  // -842150451

	string* mystr = new string;  // ���������string��Ĭ�Ϲ��캯������Щ���캯���ｫ���ʼ��Ϊ���ַ���
	cout << *mystr << endl;  // �մ�

	int* point1 = new int(100);  // �˴������˳�ʼ��
	cout << *point1 << endl; // 100

	string* mystr2 = new string("Hello,World");
	string* mystr3 = new string(5, 'a');  // ����5��a���ַ���

	cout << *mystr2 << endl;    // Hello,World
	cout << *mystr3 << endl;    // aaaaa

	vector<int>* pointVec = new vector<int>{ 1, 2, 3, 4, 5 };

	/*
		ֵ��ʼ��
		��new�����ʱ�򣬿��Խ���ֵ��ʼ�����ͽ���ֵ��ʼ��Ϊ�ã���ֹ����ֵû�б���ʼ��
	*/
	string* mystr4 = new string();  // ʹ�ÿ���������ʼ��������ֵ��ʼ������ʼ��Ϊһ���մ�
	int* point2 = new int();  // ʹ��ֵ��ʼ������point��ֵ��ʼ��Ϊ��0

	A* pa = new A;  // ��A������
	A* pa1 = new A();  // ���Լ������������Ƿ�ʹ��ֵ��ʼ����Ч������һ����

	/*
		��C++11�п��Խ�new��auto���ʹ��
	*/
	string* mystr5 = new string(5, 'b');
	auto mystr6 = new auto(mystr5);  // mystr6�ƶϳ����Ľ����string**
	/*
		����mystr5��ʼ��mystr6����ʱmystr5��mystr6ָ�����ͬһ���ڴ棬�ͷŵ�ʱ���ͷ�һ�ξ���
	*/
	cout << *mystr6 << endl;

	delete mystr6;  // ��ʱ����mystr6�������ͷŵ�mystr5���ڴ棬�����ͷŵ���mystr6������ڴ�
	delete mystr5;

	/*
		const����Ҳ�ǿ��Զ�̬�����,���ڵ�pointci�Ͳ��ɱ��޸�
	*/
	const int* pointci = new const int(200);

	/*
		�˴�ʡ��������delete����new��һ��Ҫ��delete
	*/
}

/*
	operator new()��operator delete()
	������ֵ�operator new()��operator delete()�ⶼ�Ǻ���
	new��ɵĹ�����
		1�������ڴ棺����ͨ��operator new()�������ڴ�
		2��������Ĺ��캯������ʼ���ڴ�
	delete��ɵĹ�����
		1��������������
		2���ͷ��ڴ棺����operator delete()�ͷ��ڴ�
*/
void test01() {
	int* pi = new int;
	delete pi;
}




/*
	shared_ptr����
*/
void test02() {
	shared_ptr<int> ptr(new int(100));  // ptrָ��ֵΪ100��int������
	//shared_ptr<int> ptr = new int(100);  // ����ָ����explicit �����Խ�����ʽ����ת��������ʹ��ֱ�ӳ�ʼ����ʽ
}

/*
	����ֵ��shared_ptr��
*/
shared_ptr<int> makes(int value) {
	return shared_ptr<int>(new int (value));  // ��ʽ��ʹ��int*����shared_ptr<int>
}

void test03() {
	/*
		shared_ptr�ĵ���
		����ָ�벻Ҫ����ʹ��
	*/
	shared_ptr<int> pi = makes(100);
}

/*
	make_shared����,����shared_ptrָ�룬�е�������int* pi = new int(100);
*/
void test04() {
	shared_ptr<int> pi = make_shared<int>(100);

	shared_ptr<string> pstr = make_shared<string>("Garrett");
	cout << *pstr << endl;  // Garrett

	shared_ptr<int> p2 = make_shared<int>();  // ����һ��ָ��0��shared_ptrָ��
	p2 = make_shared<int>(400);  // p2ָ�����ڴ�400��ԭ�ڴ汻�ͷ�

	/*
		ʹ��auto�ȽϷ���
	*/
	auto p3 = make_shared<string>("Walker");
	cout << *p3 << endl;  // Walker
}

int main() {
	test04();
	return 0;
}