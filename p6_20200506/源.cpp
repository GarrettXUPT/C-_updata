#include<iostream>
#include<string>

using namespace std;

/*
	一、string类型简介：
		string:可变长字符串,在C++中是一个类
	二、定义和初始化

	三、string对象上的操作

*/

/*
	string定义及其初始化
*/
void test01() {

	string str1; // 默认初始化，表示空串""
	string str2 = "I Love China";  // 将字符串拷贝到str2中，这其中不包括末尾的\0
	string str3("I Love China");  // 效果与str2的效果是一样的
	string str4 = str2;  // 将str2中的内容拷贝到str4中
	string str5(6, 'a');   // 表示6个字符a组成字符串，这种方式不好，因为会在系统内部常见临时对象
}

/*
	string的操作
*/
void test02() {
	/*
		判断是否为空
	*/
	string str1 = "Garrett";
	cout << "str是否为空: " << str1.empty() << endl;  // 0

	/*
		返回字节/字符数量,代表字符串长度(unsigned int)
	*/
	cout << "str's size is " << str1.size() << " str's length is " << str1.length() << endl;  // 7

	/*
		str[n] 返回str中的第n个字符
	*/
	cout << "number 2 char is " << str1[1] << endl;  // a

	/*
		字符串连接,得到一个新的string对象
	*/
	cout << str1 + " Walker" << endl;  // Garrett Walker

	/*
		s1 = s2 字符串对象的赋值，str2中的内容取代str1中的内容
	*/
	string str2 = "Walker";
	str1 = str2;
	cout << str1 << endl;  // Walker

	/*
		str1 == str2 判断两个字符串是否相同，要注意的是 字符串大小写敏感
		str1 != str2 判断两个字符串是否不相等
	*/
	if (str1 == str2) {
		cout << "str1与str2相等" << endl;  // str1与str2相等
	}
	else
	{
		cout << "str1与str2不相等" << endl;
	}

	/*
		str.c_str()  返回字符串s中的内容指针，返回一个指向正规的c字符串的指针常量，以\0结尾
		为了与c语言兼容，将string对象转化为c语言中字符串样式
	*/


	/*
		读写string对象
	*/
	//string str3;
	//cin >> str3; // 1234
	//cout << "输入的字符串是：" << str3 << endl;  // 1234

	/*
		字面值与string相加
		但是语法上不允许将字符串直接相加，比如 str = "abs" + "www" 但是可以 str = "abs" + str + "www"
		两个明字符串不可以挨着直接相加
	*/
	string str4 = str1 + " and " + str2 + " end";
	cout << str4 << endl;  // Walker and Walker end

	/*
		范围for针对string的使用,可以将string看做字符序列
	*/
	for (auto x : str1) {
		cout << x;  // Walker
	}
	cout << endl;

	/*
		将字符串变为大写
	*/
	for (auto& c : str1) {
		c = toupper(c);
	}
	cout << str1 << endl;  // WALKER
}

int main() {

	/*
		string操作调用
	*/
	test02();

	system("pause");
	return 0;
}