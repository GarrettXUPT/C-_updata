#include<iostream>
#include"Human.h"
#include"Man.h"
#include"wowan.h"

using namespace std;

/*
	һ��RTTI(run time type identifiaction)������ʱ����ʶ��
		ͨ��RTTI�������ʹ�û����ָ����������������Щָ�����������ָ�����ʵ����������
		RTTI������ƺ�����Ϊһ��ϵͳ�ṩ�����ǵ�һ��������������һ�ֹ��ܣ����ֹ��ܻ���������ͨ����������������ֵ�
		1.dynamic_cast��������ܹ��������ָ��������ð�ȫ��ת��Ϊ�������ָ���������
		  ��ʹ��ת���������࣬�����ĵ�������ĳ�Ա
		2.typeid�����������ָ�����������ָ�����ʵ������
		ע�⣺
			���������������Ҫ�ܹ�������������ô�ڻ����б������ٴ���һ���麯������������������Ͳ�����������
			��Ϊֻ���麯���Ĵ��ڣ�������������Ż�ʹ��ָ������������󶨵Ķ���Ķ�̬����(new������)
			ֻ�д����麯��������ϵͳ�в����麯����Ȼ��ʹ����ָ������ָ������
		
		Ϊ�˽�����������Ա����Ҫ���Ա�Ǽ̳и�����麯�������������˸÷���  
	
	����dynamic_cast
		�����������ܹ�ת���ɹ�����ô˵����ָ��ʵ����ָ��ľ����Ǹ�Ҫת�������Ǹ����ͣ���������ȫ���
		�������ã���ʹ��dynamicת��ʧ�ܣ�ϵͳ���ܳ�һ��std::bad_cast�쳣��һ��ʹ��try...catch()....

	����typeid�����
		typeid(����)����������Ϳ�����ָ�룬Ҳ���������ã�Ҳ������typeid(���ʽ)
		�õ�����������Ϣ��typeid�ͻ᷵��һ��������������ã�����������һ����׼������type_info
		
		typeid��Ҫ��Ϊ�˱Ƚ�����ָ���Ƿ�ָ��ͬһ�����Ͷ���
		����ָ�붨���������ͬ��ʹ���Ƕ�ָ��Human

	�ġ�type_info��/������
		1. .name��ȡ��ָ��Ķ�����������һ��C�����ַ���
		2. ==��!= �����ֱȽϷ���ҲҪ����������麯��
	
	�塢RTTI���麯����
		��C++�У���һ���ຬ���麯�����������ͻ�Ը������һ���麯����(�������Ե�)
		�麯�����к��кܶ��ÿһ���һ��ָ�룬ÿ��ָ��ָ������������ĸ����麯������ڵ�ַ
		�麯���������һ�������Ǻ�����ģ���ָ��Ĳ����麯������ڵ�ַ����ָ������������������type_info����
*/


void test01() {
	/*
		����ָ��ָ���������
	*/
	Human* phuman = new Man;
	Human& q = *phuman;  // q�Ǹö���ı�����*phuman��ʾָ��phuman��ָ��Ķ���
	/*
		ʹ�ü̳��麯����ʹ�������Ա����
	*/
	phuman->eat();  // ����ϲ������ʳ 
	
	
	/*
		ʹ��dynamic�������ʹ����ָ��ֱ�ӷ����������ͨ��Ա
	*/
	Human* phuman1 = new Man;
	
	// ʹ��C���Է���ǿ������ת��,���ܻ��а�ȫ����
	Man* pman1 = (Man*)phuman1;
	pman1->test01(); 
	
	Man* pman2 = dynamic_cast<Man*>(phuman1);
	if (pman2 != NULL) {  // ת��ΪMan�ɹ�
		pman2->test01();
		// ����Ϳ��Բ���Man�����еĳ�Ա���Ұ�ȫ
	}
	else  // ת�����ɹ�����ζ��phuman1����ָ��Man����
	{
		cout << "ת�����ɹ�" << endl;
	}

	Human* phuman2 = new Man;
	Human& q2 = *phuman2;  // ���������
	try
	{
		// ���ܻ�����쳣�Ĵ���
		// ת�����ɹ�����catch�Ჶ���쳣��������ɹ��������̻��������
		Man& manbm = dynamic_cast<Man&>(q2);
		cout << "����ת���ɹ�" << endl;
		manbm.test01();
	}
	catch (const std::bad_cast&)  // ת��ʧ�ܵĻ� ϵͳ�ͻ��׳��쳣
	{
		cout << "phumanʵ�ʲ���һ��man����" << endl;
	}
	
	cout << typeid(*phuman2).name() << endl;  // class man
	cout << typeid(q2).name() << endl;	// class man

	/*
		�Ƚ�����ָ����Ϊͬһ������
	*/
	Human* phuman3 = new Man;
	Human* phuman4 = new Woman;
	if (typeid(phuman3) == typeid(phuman4)) {  // �������Ƕ���ָ�����Ͷ���Human����������new����ɶ�����ǵ�typeid�����
		cout << "����ָ����ͬһ�����͵�" << endl;
	}
	else
	{
		cout << "����ָ��û��ͬһ�����͵�" << endl;
	}

	/*
		�Ƚ϶���ʱ���Ƚ�ָ��ָ���������ͣ��Ͷ����ָ��ʱ�����������ûɶ��ϵ
	*/
	Human* phuman5 = new Man;
	Human* phuman6 = new Woman;
	Human* phuman7 = new Man;
	if (typeid(*phuman5) == typeid(*phuman6)) {
		cout << "����ָ��ָ��Ķ���������ͬ" << endl;
	}
	else
	{
		cout << "����ָ��ָ��Ķ������Ͳ�ͬ" << endl;  // ����ָ��ָ��Ķ������Ͳ�ͬ
	}

	if (typeid(*phuman5) == typeid(*phuman7)) {
		cout << "����ָ��ָ��Ķ���������ͬ" << endl;	 // ����ָ��ָ��Ķ���������ͬ
	}
	else
	{
		cout << "����ָ��ָ��Ķ������Ͳ�ͬ" << endl; 
	}

	/*
		ָ��ָ��������������ȣ��������Ҫ���麯������������֪��ָ��ʵ��ָ�����Man
		��û���麯��typeid���ص��Ǳ��ʽ�ľ�̬����(����ʱ������)
	*/
	Human* phuman8 = new Man;
	if (typeid(*phuman8) == typeid(Man)) {
		cout << "phuman8ָ��man����" << endl;  // phuman8ָ��man����
	}
	else{
		cout << "phuman8��ָ��man����" << endl;
	}

	/*
		==��!= �����ֱȽϷ���ҲҪ����������麯��
	*/
	Human* phuman9 = new Man;
	const type_info& tp2 = typeid(*phuman9);

	Human* phuman10 = new Man;
	const type_info& tp3 = typeid(*phuman10);

	Human* phuman11 = new Woman;
	const type_info& tp4 = typeid(*phuman11);


	if (tp2 == tp3) {
		cout << "������ͬ" << endl;  // ������ͬ
	}
	else
	{
		cout << "���Ͳ�ͬ" << endl;
	}

	if (tp2 == tp4) {
		cout << "������ͬ" << endl;  
	}
	else
	{
		cout << "���Ͳ�ͬ" << endl;  // ���Ͳ�ͬ
	}

	/*
		phuman����������һ�����ǿ�������ָ�룬���ָ��ָ��˭��ָ������������������man
		������麯����
	*/
	Human* phuman12 = new Man;
	const type_info& ty = typeid(*phuman12);

	delete phuman;
	delete phuman1;
	delete phuman2;
	delete phuman3;
	delete phuman4;
	delete phuman5;
	delete phuman6;
	delete phuman7;
	delete phuman8;
	delete phuman9;
	delete phuman10;
	delete phuman11;

	delete pman1;
	delete pman2;

}

int main() {

	test01();

	return 0;
}