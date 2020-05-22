#include<iostream>
#include"Time.h"

using namespace std;

/*
	一、构造函数
		一种特殊的成员函数，它的名字与类名相同，每次创建对象的时候就会被系统自动调用
		构造函数的目的就是初始化类对象的数据成员
		1.构造函数没有返回值
		2.不可以手动调用构造函数
		3.正常情况下，构造函数为public，创建对象时，才能被调用
		4.构造函数中若有多个参数，那么我们创建对象的时候也要带上这些参数
	二、多个构造函数
		一个类中可以有多个构造函数，就可以为对象的创建提供多种初始化方法，即支持重载
		从开始给默认值的参数之后，都要给默认值
	三、隐式转换和explicit
		构造函数是可以做隐式类型转换，但是若在声明中带有explicit，则构造函数只能用于初始化和显式转换
		对于多参数的构造函数，一般都声明为explicit
	四、构造函数初始化列表
		Time::Time(int hour, int minute, int second) :_hour(hour), _minute(minute), _second(second) {};
		有些情况必须得使用初始化列表赋值
		使用成员函数初始化列表可提高效率，虽然提升不是很明显
		不要使用成员变量给成员变量赋值
*/


/*
	Time类的使用
*/
void test01() {
	Time time1(11, 23, 34);
	time1.printTime();
	/*
		对象拷贝
	*/
	Time time2(time1);  // 此时调用的是拷贝对象函数，并不是构造函数
	time2.printTime();

	/*
		使用默认参数的构造函数
	*/
	Time time3(12, 23);
	time3.printTime();
}

/*
	普通函数也可以使用默认参数
*/
int test02(int base = 2, int index = 8) {
	return pow(base, index);
}

int main() {
	test01();

	int res1 = test02();
	cout << "res1 = " << res1 << endl;  // 256

	int res2 = test02(2, 10);
	cout << "res2 = " << res2 << endl;  // 1024

	system("pause");
	return 0;
}