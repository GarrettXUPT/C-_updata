#include"Human.h"


/*
	构造函数
*/

Human::Human() { 
	//cout << "使用了Human的构造函数" << endl; 
};

Human::Human(int age, string name) :m_Age(age), m_Name(name) { 
	//cout << "使用了Human的构造函数" << endl; 
};

/*
	打印对象
*/
void Human::printHuman() {
	cout << "name: " << m_Name << " age: " << m_Age << endl;
}

/*
	设置年龄
*/
void Human::setAge(int age) { m_Age = age; };

/*
	设置姓名
*/
void Human::setName(string name) { m_Name = name; };