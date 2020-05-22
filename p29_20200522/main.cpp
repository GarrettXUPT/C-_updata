#include<iostream>
#include<map>
#include<string>

using namespace std;

/*
	һ��using����ģ�����
		typedef:һ�������������͵ı�����typedefֻ�����ڹ̶�����������
		using��ʹ�õ�ģ��Ȳ�����ģ��Ҳ���Ǻ���ģ�壬���ǿ��Խ��俴�����µ�ģ�����ͣ�����ģ��(ģ�����)

	������ʽָ��ģ�����
		
*/


/*
	����ϣ��key�ǹ̶���string�ͣ�value��ֵ���̶�,�Ա�ͨ�ķ�ʽʵ��
*/
template<typename wt>
struct map_s  // ������һ���ֻ࣬�ǽṹ��Ա��ȱʡ����public
{
	typedef map<string, wt>type;  // ������һ������,��
};

/*
	����ϣ��key�ǹ̶���string�ͣ�value��ֵ���̶�����C++11����ʵ��
	str_map_t��������ͱ���
	using����������ģ��������ʱʹ��
	using�ڶ������ͺͶ�������ģ��ʱ���ǰ�����typedef�����й���
*/

template<typename T>
using str_map_t = map<string, T>;

void test01() {
	typedef unsigned int uint_t;  // ��unsigned int����һ������

	typedef std:: map<std::string, int> map_s_i;
	map_s_i mymap1;
	mymap1.insert({ "first", 1 });
	mymap1.insert({ "second", 2 });

	typedef map<string, string> map_s_s;
	map_s_s mymap2;
	mymap2.insert({ "first", "one" });
	mymap2.insert({ "second", "two" });

	/*
		����ϣ��key�ǹ̶���string�ͣ�value��ֵ���̶����Ա�ͨ�ķ�ʽʵ��
	*/
	map_s<int>::type mymap3;
	mymap3.insert({ "third", 3 });

	map_s<string>::type mymap4;
	mymap4.insert({ "third", "three" });
	
	/*
		����ϣ��key�ǹ̶���string�ͣ�value��ֵ���̶�����C++11����ʵ��
	*/
	str_map_t<int> mymap5;
	mymap5.insert({ "fourth", 4 });

	str_map_t<string> mymap6;
	mymap6.insert({ "fourth", "four" });
}


// ʹ��using��unsigned int�������
using uint_t1 = unsigned int;

// ʹ��typedef���庯��ָ�룬�о��������
typedef int(*FunType1)(int, int);
// ʹ��using���庯��ָ��,�о���ֵ
using FunType2 = int(*)(int, int);

// ���巺�ͺ���ָ��
template <typename T>
using myFunc = T(*)(T, T);


int ResFunc(int i, int j) {
	return i + j;
}

void test02() {
	myFunc<int> pointFunc;  // ����ָ������,��һ��������,pointFunc��һ������ָ��
	pointFunc = ResFunc;
	cout << pointFunc(2, 3) << endl;  // 5
}

/*
	��ʽָ��ģ�����
*/
template<typename T1, typename T2, typename T3>
T1 sum(T2 i, T3 j) {
	return i + j;
}

/*
	������ʽָ��T1���ͣ����޷��ƶϳ�����ֵ����
*/
void test04() {
	auto res = sum<int>(10, 20);
	cout << res << endl;
}

int main() {
	test04();
	return 0;
}