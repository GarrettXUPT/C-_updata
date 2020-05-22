#include<iostream>
#include<map>
#include<string>

using namespace std;

/*
	一、using定义模板别名
		typedef:一般用来定义类型的别名，typedef只能用于固定类型起名字
		using中使用的模板既不是类模板也不是函数模板，我们可以将其看做是新的模板类型：类型模板(模板别名)

	二、显式指定模板参数
		
*/


/*
	现在希望key是固定的string型，value的值不固定,以变通的方式实现
*/
template<typename wt>
struct map_s  // 定义了一个类，只是结构成员的缺省都是public
{
	typedef map<string, wt>type;  // 定义了一个类型,键
};

/*
	现在希望key是固定的string型，value的值不固定，以C++11特性实现
	str_map_t起的是类型别名
	using用来给类型模板起名字时使用
	using在定义类型和定义类型模板时，是包含了typedef的所有功能
*/

template<typename T>
using str_map_t = map<string, T>;

void test01() {
	typedef unsigned int uint_t;  // 给unsigned int起了一个名字

	typedef std:: map<std::string, int> map_s_i;
	map_s_i mymap1;
	mymap1.insert({ "first", 1 });
	mymap1.insert({ "second", 2 });

	typedef map<string, string> map_s_s;
	map_s_s mymap2;
	mymap2.insert({ "first", "one" });
	mymap2.insert({ "second", "two" });

	/*
		现在希望key是固定的string型，value的值不固定，以变通的方式实现
	*/
	map_s<int>::type mymap3;
	mymap3.insert({ "third", 3 });

	map_s<string>::type mymap4;
	mymap4.insert({ "third", "three" });
	
	/*
		现在希望key是固定的string型，value的值不固定，以C++11特性实现
	*/
	str_map_t<int> mymap5;
	mymap5.insert({ "fourth", 4 });

	str_map_t<string> mymap6;
	mymap6.insert({ "fourth", "four" });
}


// 使用using给unsigned int定义别名
using uint_t1 = unsigned int;

// 使用typedef定义函数指针，感觉像定义变量
typedef int(*FunType1)(int, int);
// 使用using定义函数指针,感觉像赋值
using FunType2 = int(*)(int, int);

// 定义泛型函数指针
template <typename T>
using myFunc = T(*)(T, T);


int ResFunc(int i, int j) {
	return i + j;
}

void test02() {
	myFunc<int> pointFunc;  // 函数指针类型,是一个类型名,pointFunc是一个函数指针
	pointFunc = ResFunc;
	cout << pointFunc(2, 3) << endl;  // 5
}

/*
	显式指定模板参数
*/
template<typename T1, typename T2, typename T3>
T1 sum(T2 i, T3 j) {
	return i + j;
}

/*
	若不显式指定T1类型，则无法推断出返回值类型
*/
void test04() {
	auto res = sum<int>(10, 20);
	cout << res << endl;
}

int main() {
	test04();
	return 0;
}