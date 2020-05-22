#include<iostream>

using namespace std;

/*
	一、结构回顾
		结构：自定义的数据类型
		C++中的结构与C的结构有什么区别：
			C++中的结构除了具备C中的所有功能外，还增加了很多扩展功能，最突出的就是：
			C++中的结构不仅有成员变量，而且还可以在C中定义成员函数

	二、权限修饰符
		public:
			修饰的东西，那么这些东西就可以被外界访问，像外界暴露
		private:
			修饰的东西：只有在内部的成员函数才能使用，不向外界暴露
		protected在类中讲解

	三、类简介
		用户自定义的数据类型
		结构和类到底有什么区别：
			1、类在C++中有，C中没有这个概念
			2、结构struct 类class
			3、在C++中，定义一个属于该类的变量(对象)，结构定义的叫做结构变量
			4、不管是对象还是结构变量，他们都是一块能够存储数据并且具有某种类型的内存空间
			5、C++中结构和类及其相似
				1. 区别就是C++结构体中的成员变量及成员函数，默认访问级别都是public
				2. 类内部成员变量及成员函数默认访问级别是private
				3. C++结构体继承默认的是public，而C++类的继承默认都是private
		说明：
			1、标准的C++库中包含了大量丰富的类和函数
			2、C++中编程最好都是使用类
	
	四、类的组织
		将类的申明和类的定义(实现)进行分离，一般一个类放在一个文件中
*/

/*
	结构
*/
typedef struct student
{
	// 成员变量
	int number;  // 学号
	char name[100]; // 学生名

	/*
		成员函数
	*/
	void printStu() {
		cout << "stu.number = " << number << " stu.name = " << name << endl;
	}

}STU;

/*
	打印结构,形参使用结构变量的引用
*/
void printStu(STU const stu) {
	cout << "stu.number = " << stu.number << " stu.name = " << stu.name << endl;
}

void changeStu(STU& stu) {
	stu.number = 02;
	strcpy_s(stu.name, sizeof(stu.name), "Walker");
}

int main() {
	/*
		结构体使用
	*/
	STU stu1; 
	stu1.number = 01;

	strcpy_s(stu1.name, sizeof(stu1.name), "Garrett");
	//printStu(stu1);
	/*
		调用成员函数
	*/
	stu1.printStu();
	
	changeStu(stu1);
	printStu(stu1);

	system("pause");
	return 0;
}