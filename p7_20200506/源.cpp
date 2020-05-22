#include<iostream>
#include<vector>

using namespace std;

/*
	一、vector类型简介
		代表集合/动态数组，可以将对象放入
		vector可以将其他对象装进来，也被称为容器

	二、定义和初始化vector对象

	三、vector对象上的操作
*/

/*
	vector的使用
*/
void test01() {
	vector<int> vec; // 表示保存的是int型数据 vector是类模板 <int>表示的是类模版的实例化过程
	vector<vector<string>> strlist;  // 该集合的每一个元素又都是一个vector<string>对象，集合套集合，但是vector中不可以装引用
}

/*
	定义和初始化vector对象
*/
void test02() {
	/*
		创建一个空的string类型的vector对象
	*/
	vector<string> vec1;
	vec1.push_back("Garrett");
	vec1.push_back("Walker");
	for (string str : vec1) {
		cout << str << " ";
	}
	cout << endl;

	/*
		元素拷贝的初始化方式
	*/
	vector<string> vec2(vec1);  // 将vec1的元素拷贝到vec2中 也可以 vec2 = vec1完成拷贝

	/*
		C++11中，以列表初始化方法来给值，进行初始化
	*/
	vector<string> vec3 = { "aaa", "bbb" };

	/*
		创建指定数量的元素,与元素数量相关的，一般都会用圆括号
	*/
	vector<string> vec4(10, "aaa");   // 表示创建了10个aaa字符串
	vector<int> intVec(20);  // 创建了20个为0的int集合
	vector<string> strVec(10);  // 创建一个含有10个元素的空串

	/*
		多种初始化方式，()表示元素数量的概念，{}表示元素内容的概念，但是不绝对
	*/
	vector<int> intVec1{ 10 };  // 代表向量中只含有10一个元素

	vector<string> strVec1{ 10 }; // 代表10个元素，每个元素都是空串

}

/*
	vector对象上的操作,动态增加减少元素
*/
void test03() {
	/*
		判断容器是否为空
	*/
	vector<int> vec1;
	cout << "vector是否为空：" << vec1.empty() << endl;  // 1

	/*
		push_back，用于向容器末尾添加元素
	*/
	vec1.push_back(1);
	for (int ele : vec1) {
		cout << ele << " ";
	}
	cout << endl;	// 1

	/*
		size返回元素个数
	*/
	cout << "the vec's size is " << vec1.size() << endl;

	/*
		clear移除所有元素，将容器清空
	*/
	//vec1.clear();
	//cout << "vector是否为空：" << vec1.empty() << endl;  // 0

	/*
		vec[n]返回vec中第n个元素
	*/
	cout << "第1个元素" << vec1[0] << endl;  // 1

	/*
		=赋值,将vec2清空，然后将vec1拷贝到vec2中
	*/
	vector<int> vec2;
	vec2.push_back(12);
	vec2 = vec1;

	/*
		== != 判断两个容器中元素是否相等，元素数量是否一致，对应位置的元素值是否一致
	*/

	/*
		范围for的引用
	*/
	vector<int> vec;
	for (int i = 0; i < 10; i++) {
		vec.push_back(i);
	}

	for (auto& ele : vec) { // 最好使用引用
		cout << ele << " ";  // 0 1 2 3 4 5 6 7 8 9
	}
	cout << endl;

	/*
		范围for的详解
		在执行for循环中，切不可往容器中加入新的元素值，也不可以删除原有元素
	*/


}

int main() {

	test03();

	system("pause");
	return 0;
}