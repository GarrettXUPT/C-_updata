#include<iostream>
#include"Man.h"
#include"func.h"
#include"A.h"
#include"C.h"

using namespace std;

/*
	һ����Ԫ����
		ֻҪʹ����func��ΪMan����Ԫ��������ôfunc�Ϳ��Է���Man�����г�Ա,�����ǹ��л���˽��
		��Ԫ���������ǲ���Ȩ�޿��Ʒ�������

	������Ԫ��
		����Խ��������ඨ�����Ԫ��
		��Ԫ����Է��ʸ����е����г�Ա
		ÿ���඼Ҫ��������Լ�����Ԫ�����Ԫ����������
		1.��Ԫ��ϵ���ɼ̳�
		2.��Ԫ��ϵ�ǵ����
		3.��Ԫ��ϵҲû�д�����

	������Ԫ��Ա����
		ʹ����Ԫ��Ա����������Ҫע��������֯�ṹ����Ϊ�ô��������Ͷ����������ϵ
		ֻ��public��ĺ������ܳ�Ϊ���������Ԫ��Ա����

	��Ԫ���ŵ㼰ȱ�㣺
		�ŵ㣺�����ض�����£�ĳЩ�ǳ�Ա�����������protected��private��Ա���Ӷ������Ԫ����
			  ʹ������нϸߵ������
		ȱ�㣺
			��Ҳ���ƻ�����ķ�װ�ԣ���������Ŀɿ��ԺͿ�ά����
*/

/*
	��Ԫ����ʹ��
*/

void test01() {
	Man man;
	func(man);
}

/*
	��Ԫ��
*/

//class B; // ��B����
//
//class A {
//private:
//	int data;
//	/*
//		��Ԫ�����������Ȼ��ʱ��Cû�ж��壬����˵����������ʱû���жϸ���C�Ƿ���ڣ����������������б���������ǰ������ԭ��
//	*/
//	friend class B;
//
//};
//
//class B {
//public:
//	/*
//		��A�е�˽�б�����ֵ
//	*/
//	void callCAF(int x, A& a) {
//		a.data = x; 
//		cout << "�޸�˽�б����ɹ�" << endl;
//	}
//
//};

/*
	��Ԫ��Ա����
*/
void test02() {
	A a;
	C c;
	c.callCAF(3, a);

}

int main() {

	/*
		��Ԫ����
	*/
	test01();

	/*
		��Ԫ��Ա����
	*/
	test02();
	system("pause");
	return 0;
}