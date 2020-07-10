#include<iostream>
#include<map>
#include<functional>

using namespace std;

/*
	һ��C++С֪ʶ
		1��funct()��Ԫ�����ž��Ǻ������õı�ǣ�Ҳ���Ǻ���������������������������˺����������������ô�Ϳ�����ʹ�ú���һ��ʹ�øö���
		   ���÷�ʽ���ǣ�����();�����˺��������Ժ󣬾Ϳ�������ú���һ�����øö���
		   ֻҪ�ö�����������˺������������()����ô�ö���ͱ���˿��Ե��õĶ���汾��()��ֻҪ�����ͺ��������в��
		   ��������()�Ժ󣬸������Ϳ�����Ϊ��������

		2����ͬ���ö������ͬ���ø�ʽ
			����echovalue����biggerthanTwo���ص�()�����ò����ͷ���ֵ��ͬ���ͽ���������ʽ��ͬ
			һ�ֵ�����ʽ����Ӧһ����������,���ǵĺ������Ͷ���int(int)
			����echovalue�����ص�()�����ڿɵ��ö���
			����Щ�ɵ��ö����ָ�뱣��������Ŀ�������ǿ�����ʱ������Щ�ɵ��ö���

	������������
		1�����������������

		2��universal_reference	 
			&&��ʾ��ֵ���� ��Ҫ�ǰ�����ֵ��

		3����������
			1�����᣺const���δʻ����һ�����ó�Ϊ�������õ��ʸ񣬻Ὣ���Ϊ��ֵ����
			2�����ϣ�
			
*/

/*
	��������Ķ���
*/
class biggerThanTwo {
public:

	biggerThanTwo(int i) {
		//cout << "���캯����ִ��" << endl;
	}

	biggerThanTwo() {};

	int operator()(int value) const {
		return value; 
	}
};
/*
	���ú�������
*/
void test01() {
	biggerThanTwo bgt;
	cout << bgt(3) << endl; // 1  �ȼ��ڵ���bgt.operator()(i)
	cout << bgt(1) << endl;  // 0

	/*
		���������Ƕ����岢�ҳ�ʼ��,���õĹ��캯�������ǵ���operator()(i)
	*/
	biggerThanTwo bt(1);
}

/*
	��ͨ����,��ӡvalueֵ������ԭ������
*/
int echovalue(int value) {  // ���ò����ͷ���ֵ��ͬ
	cout << value << endl;
	return value;
}

/*
	����echovalue����biggerthanTwo���ص�()�����ò����ͷ���ֵ��ͬ���ͽ���������ʽ��ͬ
	һ�ֵ�����ʽ����Ӧһ����������,���ǵĺ������Ͷ���int(int)
*/
void test02() {
	/*
		����һ���ɵ��ö����ָ��
	*/
	map<string, int(*)(int)> myoper;
	myoper.insert({ "echovalue", echovalue });  // ������ָ���ֵ�Է���map������

	/*
		���к�������������Ķ���
	*/
	biggerThanTwo obj;

	/*
		functional��ģ�壬Ҫ�ṩģ���������ʾfunction�����ܹ���ʾ�Ķ��������ʽ
		����һ��function������ʾһ���ɵ��ö���,����ͨ����echovalue���������أ���ô�Ͳ����Էŵ���function<>���͵Ķ����У�����������ͨ������ָ�������

	*/
	function<int(int)> f1 = echovalue;
	function<int(int)> f2 = obj;  // ���Է��������Ϊ���д��ں������������������
	function<int(int)> f3 = biggerThanTwo();  // Ҳ����ʹ������������ʱ����
	
	cout << f3(2) << endl;  // 2
	map<string, function<int(int)>> myoper1 = { {"ev", echovalue}, {"bt", obj} ,{"bt2", biggerThanTwo()} };

	/*
		map�пɵ��ö����ʹ��
	*/
	cout << myoper1["bt2"](12) << endl;  // 12

	/*
		���庯��ָ�벻�����������,��Ϊ����ָ�����ж���Ĳ������ͺͷ���ֵ���ͣ����Ժ�ԭ����echovalue���бȶ�
	*/
	int(*fp)(int) = echovalue;
	function<int(int)> f4 = fp; // ֱ������ȥ����ָ������Ǻ�����  
}

/*
	
*/
void func(const int& abc){}  // abc�����;��ǣ�const int&  

/*
	����T�����ͺ�abc������������ͬ
*/
template <typename T>
void func1(const T& abc){}

void test03() {
	// T������ʱint��,abc�����;���const int&
	// 1�����ú���ģ��ʱ�Ĳ���10���T�����Ͳ���Ӱ��
	// 2��abc�����ͻ��T�����Ͳ���Ӱ�� 
	func1(10);
}

void myfunc2(int&& tmprv) {
	cout << tmprv << endl;
	return;
}

/*
	���亯������Ϊ����ģ��
*/
template<typename T>
void myfunc2(T&& tmprv) {  // �����&&�������β����͵�һ���֣���T�������޹ص�
	cout << tmprv << endl;
	return;
}


void test04() {
	/*
		���������ǿ��Ե�
	*/
	myfunc2(10);
	/*
		��ֵ���ò��ܰ���ֵ
	*/
	int i = 100;
	//myfunc2(i);  ����Ƕ���ֵ���ð���ֵ

	/* 
		�������˺���ģ�����ͣ���ô������ֵ�ǿ��Ե�
		1��tmprv���ܽ�����ֵ�����ܽ�����ֵ
		2��T&&����tmprv������
		����������Ҫ���ﾳ��1�������Ǻ���ģ�� 2�����뷢����ģ�������ƶ� ����ó�����T&&
		���������ﾳ�ſɷ�����autoҲ�������������������������õ���ʽ����T&&
		�������ú���ֵ���õ�����
			1����ֵ ���õô�����ֵ���������������
			2�����������������βε�ʱ�����ǿ��Դ��ݸ�����ֵ��Ҳ���Դ��ݸ�����ֵ���Ӵ����������
		tmprv������T&&�����������ã���������T�����������ã������ݽ�������һ�����͵���ֵ��tmprv��Ӧ�ñ��ƶϳ�int&&����

		1��void func(int&& param)  // ��ֵ���ã���Ϊ����ģ�����Բ�����������
		2��template<typename T> void func(T&& tmpvalue);  // ��������
		3��template<typename T> void func(vector<T>&& param) ��ֻ����ֵ���� ������������

	*/
	myfunc2(i);
}

int main() {
	test02();
	return 0;
}