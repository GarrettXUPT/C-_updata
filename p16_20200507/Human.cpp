#include"Human.h"


/*
	���캯��
*/

Human::Human() { 
	//cout << "ʹ����Human�Ĺ��캯��" << endl; 
};

Human::Human(int age, string name) :m_Age(age), m_Name(name) { 
	//cout << "ʹ����Human�Ĺ��캯��" << endl; 
};

/*
	��ӡ����
*/
void Human::printHuman() {
	cout << "name: " << m_Name << " age: " << m_Age << endl;
}

/*
	��������
*/
void Human::setAge(int age) { m_Age = age; };

/*
	��������
*/
void Human::setName(string name) { m_Name = name; };